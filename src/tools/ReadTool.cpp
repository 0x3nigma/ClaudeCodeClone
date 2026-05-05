#include "ReadTool.h"
#include <nlohmann/json.hpp>
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

