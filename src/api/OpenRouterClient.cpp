#include "OpenRouterClient.h"
#include "../tools/WriteTool.h"
#include "../tools/ReadTool.h" 
#include "../tools/BashTool.h"
#include <cpr/cpr.h>
#include <cstring>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include "../tools/toolSpec.h"

#define MAX_ITER 10


using json = nlohmann::json;

OpenRouterClient::OpenRouterClient(): messages(json::array()){};

std::string OpenRouterClient::chat(const std::string& prompt,
                                   const std::unordered_map<std::string, std::unique_ptr<Tool>>& registry){
    // Getting the api keys :
    const char* openrouterApi_env{std::getenv("OPENROUTER_API_KEY")};
    if(!openrouterApi_env || strlen(openrouterApi_env) == 0){
        throw std::runtime_error("No api key found");
    }
    std::string openrouterApi{openrouterApi_env};
    std::string baseUrl{"https://openrouter.ai/api/v1"};

    messages.push_back({{"role", "user"}, {"content", prompt}});

    auto tools = json::array();
    for(const auto& [name, tool_ptr] : registry){
        tools.push_back(tool_ptr->getToolSpec());
    }

    int count{};

    while(1){
        count++;
        if(count > MAX_ITER) break;

        json request_body = {
            {"model", "openrouter/free"},
            {"messages", messages},
            {"tools", tools}
        };
            cpr::Response response = cpr::Post(
            cpr::Url{baseUrl + "/chat/completions"},
            cpr::Header{
                {"Authorization", "Bearer " + openrouterApi},
                {"Content-Type", "application/json"}
            },
            cpr::Body{request_body.dump()}
        );

        if (response.status_code != 200) {
            std::cerr << "HTTP error: " << response.status_code << std::endl;
            throw std::runtime_error("Status Code not 200");
        }

        json result = json::parse(response.text);

        if (!result.contains("choices") || result["choices"].empty()) {
            std::cerr << "No choices in response" << std::endl;
            throw std::runtime_error("No choices in response");
        }

        auto& message = result["choices"][0]["message"];
        messages.push_back(message);

        if(!message.contains("tool_calls") || message["tool_calls"].empty()){
            return message["content"].get<std::string>();
        }

        else{
            auto tools_called = message["tool_calls"];
            for(const auto& tool_info : tools_called){
                auto func_name = tool_info["function"]["name"].get<std::string>();
                if(registry.find(func_name) != registry.end()){
                    auto& tool_ptr = registry.at(func_name);
                    json args = json::parse(tool_info["function"]["arguments"].get<std::string>());
                    std::string result = tool_ptr->doTask(args);
                    messages.push_back({
                        {"role", "tool"},
                        {"tool_call_id", tool_info.at("id")},
                        {"content", result}
                    });
                }
            }
        }
    }
    throw std::runtime_error("Max Iterations exceeded.");
}

