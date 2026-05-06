#include "WriteTool.h"
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

using json = nlohmann::json;


json WriteTool::getToolSpec() const{
    json toolSpec = {
        {"type", "function"},
        {"function", {
            {"name", "Write"},
            {"description", "Write content to a file"},
            {"parameters", {
                {"type", "object"},
                {"required", json::array({"file_path", "content"})},
                {"properties", {
                    {"file_path", {
                        {"type", "string"},
                        {"description", "The path of the file to write to"}
                    }},
                    {"content", {
                        {"type", "string"},
                        {"description", "The content to write to the file"}
                    }}
                }}
            }}
        }}
    };
    return toolSpec;
}

std::string WriteTool::getName(){
    return "Write";
}
std::string WriteTool::doTask(const json& args){
    std::string file_path = args.at("file_path").get<std::string>();
    std::string contents = args.at("content").get<std::string>();
    std::ofstream file(file_path);
    if(!file){
        throw std::runtime_error("Couldnot open file" + file_path);
    }
    file << contents;
    return "Successfully written to the file " + file_path;
}

