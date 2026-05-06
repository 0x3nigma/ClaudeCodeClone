#include "BashTool.h"
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>
#include <stdexcept>
#include <array>
#include <cstdio>
using json = nlohmann::json;

json BashTool::getToolSpec() const{
    json spec = {
        {"type", "function"},
        {"function", {
            {"name", "Bash"},
            {"description", "Execute a shell command"},
            {"parameters", {
                {"type", "object"},
                {"required", json::array({"command"})},
                {"properties", {
                    {"command", {
                        {"type", "string"},
                        {"description", "The command to execute"}
                    }}
                }}
            }}
        }}
    };
    return spec;
}
std::string BashTool::getName(){
    return "Bash";
}
std::string BashTool::doTask(const json& args){
    std::string command = args.at("command").get<std::string>();
    std::array<char, 128> buffer;
    std::string result;

    std::string fullCommand = command + " 2>&1";

    FILE* pipe = popen(fullCommand.c_str(), "r");

    if (!pipe) {
        throw std::runtime_error("Failed to open pipe");
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }

    pclose(pipe);

    return result;
}
