#pragma once
#include "toolSpec.h"
#include <nlohmann/json.hpp>

class ReadTool: public Tool{
public:
    nlohmann::json getToolSpec() const override;
};
