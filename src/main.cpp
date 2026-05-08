#include "api/OpenRouterClient.h"
#include "tools/ToolRegistry.h"
#include <iostream>
#include <string>

int main() {
    // Creating the tool Registry
    initRegistry();
    try {
        OpenRouterClient client{};

        while(true){
            std::cout << "Enter your prompt: ";
            std::string prompt;
            std::getline(std::cin, prompt);
            if (prompt == "exit" || prompt == "quit") break;  // clean exit
            if (prompt.empty()) continue;                      // skip, don't crash

            std::string response = client.chat(prompt, toolRegistry);

            std::cout << "\nResponse:\n";
            std::cout << response << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
