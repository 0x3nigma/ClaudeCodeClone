#include "OpenRouterClient.h"
#include "../tools/ReadTool.h" 
#include <cpr/cpr.h>
#include <cstring>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <cstdlib>


using json = nlohmann::json;

std::string OpenRouterClient::chat(const std::string& prompt){
    // Getting the api keys :
    const char* openrouterApi_env{std::getenv("OPENROUTER_API_KEY")};
    if(!openrouterApi_env || strlen(openrouterApi_env) == 0){
        throw std::runtime_error("No api key found");
    }
    std::string openrouterApi{openrouterApi_env};
    std::string baseUrl{"https://openrouter.ai/api/v1"};

    json messages = json::array();
    messages.push_back({{"role", "user"}, {"content", prompt}});

    while(1){
        json request_body = {
            {"model", "openrouter/free"},
            {"messages", messages},
            {"tools", json::array({
                ReadTool{}.getToolSpec()
            })}
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
            for(const auto& tool : tools_called){
                auto func = tool["function"];
                if(func["name"].get<std::string>() == "Read"){
                    ReadTool rt{};
                    json args = json::parse(func["arguments"].get<std::string>());
                    std::string result = rt.doTask(args);
                    messages.push_back({
                        {"role", "tool"},
                        {"tool_call_id", tool.at("id")},
                        {"content", result}
                    });
                }
            }
        }
    }
}
