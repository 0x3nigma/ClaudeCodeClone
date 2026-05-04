#include "api/OpenRouterClient.h"
#include <iostream>
#include <string>

int main() {
    try {
        OpenRouterClient client;

        std::cout << "Enter your prompt: ";
        std::string prompt;
        std::getline(std::cin, prompt);

        if (prompt.empty()) {
            std::cerr << "Prompt cannot be empty\n";
            return 1;
        }

        std::string response = client.chat(prompt);

        std::cout << "\nResponse:\n";
        std::cout << response << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
