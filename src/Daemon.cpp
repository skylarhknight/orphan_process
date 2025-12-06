#include "../include/Daemon.h"
#include "../include/ArtAssets.h" 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

// ---------------------------------------------------------
// CONSTRUCTORS
// ---------------------------------------------------------

// Default Constructor
Daemon::Daemon() : Daemon("Unknown_Process") {}

// Parameterized Constructor
Daemon::Daemon(std::string pName) 
    : name(pName), ram(60), maxRam(100), corruption(0), age(0), bits(0), showFrame1(true) {
    
    // Initialize Evolution Tree (Costs act as IDs)
    evolutionTree.insert("Bit-Larva v1", 5, 0);       
    evolutionTree.insert("Firewall", 30, 20);         
    evolutionTree.insert("Overclock", 60, 50);        
    evolutionTree.insert("Encryption", 20, 10);       
    evolutionTree.insert("Singularity", 100, 100);    
}

// ---------------------------------------------------------
// GAME LOOP LOGIC
// ---------------------------------------------------------

void Daemon::update() {
    age++;           
    ram -= 5;        // Hunger
    corruption += 2; // Entropy
    
    // Bounds Checking
    if (ram < 0) ram = 0;
    if (ram > maxRam) ram = maxRam;
    
    if (corruption > 100) corruption = 100;
    if (corruption < 0) corruption = 0;
}

// ---------------------------------------------------------
// RENDER SYSTEM (DASHBOARD UI)
// ---------------------------------------------------------

// Helper to draw multi-line strings at specific coordinates
void drawArtAt(Terminal& term, int x, int y, std::string art) {
    std::stringstream ss(art);
    std::string line;
    int currentY = y;
    while (std::getline(ss, line)) {
        term.drawText(x, currentY++, line);
    }
}

void Daemon::render(Terminal& term) {
    // Clear Screen
    term.clear();
    term.setGreen();

    // DRAW DASHBOARD BOXES
    // Header
    term.drawBox(1, 1, 80, 3, "ORPHAN_PROCESS // KERNEL ACCESS");
    
    // SANDBOX
    term.drawBox(1, 4, 80, 30, "SANDBOX CONTAINMENT FIELD");
    
    // LOWER PANELS 
    term.drawBox(1, 35, 39, 6, "SYSTEM VITALS");
    term.drawBox(40, 35, 41, 6, "RESOURCE MONITOR");

    // SELECT ART
    std::string currentArt;
    if (age < 20) {
        currentArt = showFrame1 ? Art::LARVA_FRAME_1 : Art::LARVA_FRAME_2;
    } 
    else if (age < 50) {
        currentArt = showFrame1 ? Art::CONSTRUCT_FRAME_1 : Art::CONSTRUCT_FRAME_2;
    } 
    else {
        currentArt = showFrame1 ? Art::SINGULARITY_FRAME_1 : Art::SINGULARITY_FRAME_2;
    }

    // DRAW THE PET
    int artY = 6; 
    int artX = 20; 

    drawArtAt(term, artX, artY, currentArt);

    // Label (Pushed down to bottom of sandbox)
    term.drawCentered(32, "< PROCESS: " + name + " >");

    // DRAW STATS
    // RAM Bar
    std::string ramBar = "[";
    int bars = (ram * 10) / maxRam; 
    for(int i=0; i<10; i++) ramBar += (i < bars ? "#" : ".");
    ramBar += "]";
    
    term.drawText(3, 37, "RAM INTEGRITY: " + ramBar + " " + std::to_string(ram) + "/" + std::to_string(maxRam));

    // Corruption Bar
    std::string corrBar = "[";
    int cBars = corruption / 10;
    for(int i=0; i<10; i++) corrBar += (i < cBars ? "!" : ".");
    corrBar += "]";
    
    term.drawText(3, 39, "CORRUPTION   : " + corrBar + " " + std::to_string(corruption) + "%");

    // 6. DRAW RESOURCES
    term.drawText(42, 37, "BITS AVAILABLE: " + std::to_string(bits));
    term.drawText(42, 38, "UPTIME CYCLES : " + std::to_string(age));
    term.drawText(42, 39, "INVENTORY SIZE: " + std::to_string(backpack.size()));

    // Toggle Animation
    showFrame1 = !showFrame1;
    term.moveCursor(42, 1);
}

// ---------------------------------------------------------
// INTERACTION & UTILITIES
// ---------------------------------------------------------

void Daemon::feed(int amount) {
    assert(amount > 0 && "Cannot feed negative amount!");
    ram += amount;
    if (ram > maxRam) ram = maxRam;
}

void Daemon::clean(int amount) {
    corruption -= amount;
    if (corruption < 0) corruption = 0;
}

void Daemon::addBits(int amount) {
    bits += amount;
}

bool Daemon::isAlive() const {
    return (ram > 0) && (corruption < 100);
}

// ---------------------------------------------------------
// EVOLUTION LOGIC
// ---------------------------------------------------------

void Daemon::showTree(Terminal& term) {
    term.clear(); 
    evolutionTree.printTree(term);
}

void Daemon::refreshTree() {
    // 
}

std::string Daemon::tryEvolve(int cost) {
    SkillNode* node = evolutionTree.findNode(cost);
    
    if (node == nullptr) return "ERROR: Protocol not found.";
    if (node->unlocked) return "ERROR: Protocol already installed.";
    if (bits < cost) return "ERROR: Insufficient Bits.";
    
    // Transaction
    bits -= cost;
    node->unlocked = true;
    
    // Apply Stats
    maxRam += node->ramBonus;
    ram = maxRam; 
    
    return "SUCCESS: " + node->skillName + " installed. Max RAM upgraded.";
}

// ---------------------------------------------------------
// OPERATORS & FILE I/O
// ---------------------------------------------------------

void Daemon::operator+=(int foodAmount) {
    static_assert(sizeof(int) >= 4, "Integer size too small");
    feed(foodAmount);
}

bool Daemon::saveGame(std::string filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) return false;

    outFile << name << "\n" << ram << "\n" << maxRam << "\n" 
            << corruption << "\n" << age << "\n" << bits << "\n";
    
    outFile.close();
    return true;
}

bool Daemon::loadGame(std::string filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) return false;

    std::string tName;
    int tRam, tMax, tCorr, tAge, tBits;
    
    if (std::getline(inFile, tName) &&
        (inFile >> tRam >> tMax >> tCorr >> tAge >> tBits)) {
            
        this->name = tName;
        this->ram = tRam;
        this->maxRam = tMax;
        this->corruption = tCorr;
        this->age = tAge;
        this->bits = tBits;
        
        inFile.close();
        return true;
    }
    return false;
}