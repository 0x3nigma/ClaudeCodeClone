#pragma once
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Tool{
public:
    virtual nlohmann::json getToolSpec() const = 0;
    virtual ~Tool() = default;
};




