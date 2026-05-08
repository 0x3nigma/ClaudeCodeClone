#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "toolSpec.h"

extern std::unordered_map<std::string, std::unique_ptr<Tool>> toolRegistry;

void initRegistry();
