#include <iostream>
#include <limits> 
#include <thread> 
#include <chrono>
#include <vector>

#include "../lib_terminal/Terminal.h"
#include "../include/SystemLog.h"
#include "../include/Daemon.h"
#include "../include/ArtAssets.h" 

// ---------------------------------------------------------
// VISUAL HELPERS
// ---------------------------------------------------------
void sleep_ms(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void typeText(std::string text, int delay = 30) {
    for (char c : text) {
        std::cout << c << std::flush;
        sleep_ms(delay);
    }
    std::cout << std::endl;
}

void showLoadingBar(std::string label) {
    std::cout << label << " [";
    for (int i = 0; i < 20; i++) {
        std::cout << "#" << std::flush;
        sleep_ms(50 + (rand() % 100)); 
    }
    std::cout << "] 100%" << std::endl;
    sleep_ms(500);
}

// ---------------------------------------------------------
// INTRO SEQUENCE
// ---------------------------------------------------------
std::string playIntroSequence(Terminal& term) {
    term.clear();
    term.setGreen();

    // Setup Sequence
    typeText("INITIALIZING NETRUNNER UPLINK...", 20);
    sleep_ms(200);
    showLoadingBar("SCANNING SECTOR");
    
    // The "Discovery"
    term.clear();
    std::cout << "SCAN RESULTS:\n   > PORT 8080: [SECURE]\n   > MEMORY 0x5F3A: "; 
    sleep_ms(1000); 
    typeText("!!! ANOMALY DETECTED !!!", 60);
    
    std::cout << "\n[RAW_DATA]: 010101 %$# ERROR ... HUNGRY ... 0101" << std::endl;
    sleep_ms(800);
    
    std::cout << "\nPress [ENTER] to initiate SANDBOX CONTAINMENT...";
    std::cin.get(); 

    // The Capture
    term.clear();
    showLoadingBar("ISOLATING ENTITY");
    
    // Name Entry
    term.clear();
    std::cout << Art::SPLASH_SCREEN << std::endl;
    typeText("\n[SYSTEM]: Connection established. Entity requires identification.", 30);
    
    std::string petName;
    while (true) {
        std::cout << "\n> ENTER PROCESS ID: ";
        std::getline(std::cin, petName);
        if (!petName.empty()) break;
    }
    
    typeText("Process '" + petName + "' registered.", 30);
    sleep_ms(1000);
    
    return petName;
}

// ---------------------------------------------------------
// MAIN LOOP
// ---------------------------------------------------------
int main() {
    Terminal term;
    SystemLog log;

    // 1. Run Intro
    std::string petName = playIntroSequence(term);
    Daemon pet(petName);
    
    log.addEntry("Connection established.");
    log.addEntry("Rogue fragment '" + petName + "' isolated.");

    // 2. Game Loop
    bool running = true;
    while (running && pet.isAlive()) {
        // A. Render Dashboard (Handles Clear & Box Drawing)
        pet.render(term); 
        
        // B. Position Log below Dashboard (Row 23)
        term.moveCursor(42, 1);
        log.printLog(term);
        
        // C. Draw Menu below Log
        std::cout << "\n--------------------------------------------------------------------------------\n";
        std::cout << "CMD: [1] Inventory  [2] Scavenge  [3] Tree  [4] Save  [5] Load  [6] Quit\n";
        std::cout << "> ";
        
        // D. Handle Input
        char input;
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch(input) {
            case '1': // INVENTORY
            {
                // We clear screen temporarily to show inventory list clearly
                term.clear();
                term.setGreen();
                term.drawBox(1, 1, 40, 20, "BACKPACK CONTENTS");
                term.moveCursor(3, 2);
                pet.backpack.display(term);
                
                term.drawText(2, 22, "[U]se Item (Index) or [C]ancel?");
                term.moveCursor(23, 2);
                
                char choice;
                std::cin >> choice;
                if (isdigit(choice)) {
                    int idx = choice - '0';
                    try {
                        if (idx < pet.backpack.size()) {
                            std::string item = pet.backpack.use(idx);
                            if (item == "Data_Packet") {
                                pet += 20; 
                                log.addEntry("Used Data_Packet: RAM restored.");
                            } else if (item == "Sec_Patch") {
                                pet.clean(15);
                                log.addEntry("Used Sec_Patch: Corruption cleansed.");
                            }
                        }
                    } catch (...) { log.addEntry("Invalid Selection."); }
                }
            }
            break;
                
            case '2': // SCAVENGE
            {
                term.clear();
                showLoadingBar("SCANNING NETWORK");
                int rng = rand() % 100;
                int bits = (rand() % 10) + 5;
                pet.addBits(bits);
                
                std::string msg = " Found " + std::to_string(bits) + " Bits.";

                if (rng < 40) {
                    if (pet.backpack.add("Data_Packet"))
                        log.addEntry("SCAVENGE: Found Data_Packet." + msg);
                    else
                        log.addEntry("SCAVENGE: Backpack Full! (Kept Bits)");
                } else if (rng < 60) {
                    if (pet.backpack.add("Sec_Patch"))
                        log.addEntry("SCAVENGE: Found Sec_Patch." + msg);
                    else
                        log.addEntry("SCAVENGE: Backpack Full!");
                } else {
                    log.addEntry("SCAVENGE: No items." + msg);
                }
            }
            break;
                
            case '3': // TREE
                pet.showTree(term);
                std::cout << "\n[B]uy Upgrade (Enter Cost) or [E]xit?\n> ";
                int cost;
                if (std::cin >> cost) {
                    log.addEntry(pet.tryEvolve(cost));
                } else {
                    std::cin.clear(); std::cin.ignore(1000, '\n');
                }
                break;
                
            case '4': // SAVE
                if (pet.saveGame("savegame.txt")) log.addEntry("SUCCESS: System state saved.");
                else log.addEntry("ERROR: Save failed.");
                break;
                
            case '5': // LOAD
                if (pet.loadGame("savegame.txt")) log.addEntry("SUCCESS: System state loaded.");
                else log.addEntry("ERROR: Load failed.");
                break;
                
            case '6': // QUIT
                running = false;
                break;
                
            default:
                log.addEntry("SYNTAX ERROR.");
        }
        
        // E. Update Simulation
        if (running) pet.update();
    }

    // 3. TERMINATION SEQUENCE
    term.clear();
    
    // Switch to standard output for the crash screen to ensure it scrolls naturally
    if (!pet.isAlive()) {
        // 1. Print the "FATAL ERROR" Window (The Asset)
        std::cout << "\n\n"; 
        std::cout << Art::LOGO << std::endl; 
        
        sleep_ms(500); // Suspense pause

        // 2. Print the Notification Text
        std::cout << "\n   >>> FATAL SYSTEM ERROR <<<" << std::endl;
        sleep_ms(800);
        
        std::cout << "   PROCESS HAS BEEN TERMINATED UNEXPECTEDLY." << std::endl;
        sleep_ms(800);
        
        // 3. Print the "Deleted Process" line
        std::cout << "   > DELETED PROCESS: " << pet.getName() << std::endl;
        sleep_ms(800);

        std::cout << "\n   [DUMPING MEMORY] ... 100%" << std::endl;
    } 
    else {
        // Safe Quit (If user pressed 6)
        std::cout << "\n\n";
        std::cout << "   [SESSION TERMINATED BY USER]" << std::endl;
        std::cout << "   Safe shutdown complete. Good hunting, Netrunner." << std::endl;
    }
    
    // Prevent the window from closing immediately
    std::cout << "\n   Press [ENTER] to exit terminal...";
    std::cin.get(); 
    std::cin.get(); // Double get() handles any leftover newline characters
    
    return 0;
}