#include "OpenRouterClient.h"
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
    json request_body{
        {"model", "openrouter/free"},
        {"messages", json::array({
            {{"role", "user"}, {"content", prompt}}
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
    return result["choices"][0]["message"]["content"].get<std::string>();
}

