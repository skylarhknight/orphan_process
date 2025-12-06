#include <iostream>
#include <string>
#include "Daemon.h"

void GameEngine::init() {
    // 1. Show Splash Screen (Extra Credit)
    std::cout << "=== ORPHAN_PROCESS BOOT SEQUENCE ===" << std::endl;
    std::cout << "Loading Kernel..." << std::endl;

    // 2. Prompt for Name (Interaction Requirement)
    std::string playerName;
    std::cout << "\n[SYSTEM]: Rogue process detected." << std::endl;
    std::cout << "[SYSTEM]: Assign identifier to process: ";
    
    // getline allows names with spaces (e.g., "Unit 734")
    std::getline(std::cin, playerName);

    // Validation (Prevent empty names)
    if (playerName.empty()) {
        playerName = "Unknown_Glitch";
    }

    // 3. Instantiate the Daemon with the name
    myDaemon = new Daemon(playerName);
    
    std::cout << "\n[SYSTEM]: Process " << myDaemon->getName() << " initialized.\n";
}