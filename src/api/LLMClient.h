#pragma once
#include <string>
#include <memory>
#include "../tools/toolSpec.h"

class LLMCli{
public:
    virtual std::string chat(const std::string& prompt,
                             const std::unordered_map<std::string, std::unique_ptr<Tool>>& registry) = 0;
    virtual ~LLMCli() = default;
};

