#pragma once
#include <string>

class LLMCli{
public:
    virtual std::string chat(const std::string& prompt) = 0;
    virtual ~LLMCli() = default;
};

