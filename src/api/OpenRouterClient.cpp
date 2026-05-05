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

    //Getting the required tool specs;
    ReadTool rt{};
    json readToolSpec = rt.getToolSpec();

    json request_body{
        {"model", "openrouter/free"},
        {"messages", json::array({
            {{"role", "user"}, {"content", prompt}}
        })},
        {"tools", json::array({
            readToolSpec
        })}
    };
    cpr::Response response{
        cpr::Post(
            cpr::Url{baseUrl + "/chat/completions"},
            cpr::Header{
                {"Authorization", "Bearer " + openrouterApi},
                {"Content-Type", "application/json"}
            },
            cpr::Body{request_body.dump()}
        )
    };
    if (response.status_code != 200) {
        throw std::runtime_error("Couldnot get a response");
    }

    json result = json::parse(response.text);

    if (!result.contains("choices") || result["choices"].empty()) {
        throw std::runtime_error("Response is empty");
    }

    auto& message = result["choices"][0]["message"];
    if(!message.contains("tool_calls") || message["tool_calls"].empty()){
        return message["content"].get<std::string>();
    }
    else{
        std::string args = message["tool_calls"][0]["function"]["arguments"];
        json args_json = json::parse(args);
        std::string file_path = args_json["file_path"].get<std::string>();
        rt.setFilePath(file_path);
        return rt.doTask();
    }
    return "";
}

