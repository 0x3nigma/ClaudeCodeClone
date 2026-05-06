#pragma once
#include "toolSpec.h"
#include <nlohmann/json.hpp>
#include <string>

class WriteTool: public Tool{
public:
    nlohmann::json getToolSpec() const override;
    std::string doTask(const nlohmann::json& args) override;
    std::string getName() override;
};
