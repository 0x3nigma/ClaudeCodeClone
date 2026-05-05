#pragma once
#include "toolSpec.h"
#include <nlohmann/json.hpp>
#include <string>

class ReadTool: public Tool{
    std::string file_path;
public:
    nlohmann::json getToolSpec() const override;
    std::string doTask() override;
    void setFilePath(const std::string& path);
};
