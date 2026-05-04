#pragma once
#include "LLMClient.h"
#include <string>

class OpenRouterClient : public LLMCli{
public:
    std::string chat(const std::string& prompt);
};
