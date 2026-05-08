#pragma once
#include "LLMClient.h"
#include <string>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <memory>
#include "../tools/toolSpec.h"

class OpenRouterClient : public LLMCli{
public:
    std::string chat(const std::string& prompt,
                     const std::unordered_map<std::string, std::unique_ptr<Tool>>& registry);
    OpenRouterClient();
private:
    nlohmann::json messages;
};
