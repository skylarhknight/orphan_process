#ifndef DAEMON_H
#define DAEMON_H

#include <string>
#include "Entity.h"
#include "KernelTree.h"
#include "Inventory.h" 

class Daemon : public Entity {
private:
    std::string name;
    int ram;
    int maxRam;
    int corruption;
    int age;
    int bits;
    bool showFrame1; 
    
    KernelTree evolutionTree;

public:
    // Inventory System
    Inventory<std::string> backpack; 

    // Constructors (Requirement: Overloading)
    Daemon();
    Daemon(std::string pName);
    
    // Core Entity Functions
    void update() override;
    void render(Terminal& term) override;

    // Interaction Functions
    void feed(int amount);
    void clean(int amount);
    bool isAlive() const;
    std::string getName() const { return name; }
    
    // Evolution & Currency Functions
    void addBits(int amount);
    std::string tryEvolve(int cost);
    void showTree(Terminal& term);
    
    // Operator Overloading
    void operator+=(int foodAmount);
    
    // File I/O
    bool saveGame(std::string filename);
    bool loadGame(std::string filename);
    
    // THIS WAS MISSING:
    void refreshTree(); 
};

#endif