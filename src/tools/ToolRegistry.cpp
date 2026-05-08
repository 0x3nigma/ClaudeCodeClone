#include "ToolRegistry.h"
#include "ReadTool.h"
#include "WriteTool.h"
#include "BashTool.h"

std::unordered_map<std::string, std::unique_ptr<Tool>> toolRegistry;

void initRegistry() {
    toolRegistry["Read"]  = std::make_unique<ReadTool>();
    toolRegistry["Write"] = std::make_unique<WriteTool>();
    toolRegistry["Bash"]  = std::make_unique<BashTool>();
}
