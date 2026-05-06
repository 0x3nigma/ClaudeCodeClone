#pragma once
#include <nlohmann/json.hpp>
#include <string>
using json = nlohmann::json;

class Tool{
public:
    virtual nlohmann::json getToolSpec() const = 0;
    virtual std::string doTask(const json& args) = 0;
    virtual std::string getName() = 0;
    virtual ~Tool() = default;
};




