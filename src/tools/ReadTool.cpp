#include "ReadTool.h"
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
using json = nlohmann::json;

json ReadTool::getToolSpec() const{
    return json{
        {"type", "function"},
        {"function", {
            {"name", "Read"},
            {"description", "Read and return the contents of a file"},
            {"parameters", {
                {"type", "object"},
                {"properties", {
                    {"file_path", {
                        {"type", "string"},
                        {"description", "The path to the file to read"}
                    }}
                }},
                {"required", {"file_path"}}
            }}
        }}
    };
}
void ReadTool::setFilePath(const std::string& path){
    file_path = path;
}
std::string ReadTool::doTask(){
    std::ifstream file(ReadTool::file_path);
    if(!file){
        throw std::runtime_error("Couldnot open file");
    }
    std::ostringstream content;
    content << file.rdbuf();
    return content.str();
}
