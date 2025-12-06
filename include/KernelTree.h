#ifndef KERNELTREE_H
#define KERNELTREE_H

#include <string>
#include <iostream>
#include "../lib_terminal/Terminal.h"

struct SkillNode {
    std::string skillName;
    int cost;     // The Key for the BST
    int ramBonus; // Passive Buff: Max RAM increase
    bool unlocked;

    SkillNode* left;
    SkillNode* right;

    SkillNode(std::string name, int c, int r) 
        : skillName(name), cost(c), ramBonus(r), unlocked(false), left(nullptr), right(nullptr) {}
};

class KernelTree {
private:
    SkillNode* root;

    void printRecursive(SkillNode* node, Terminal& term, std::string prefix);
    void destroyRecursive(SkillNode* node);
    
    // Recursive Search (Requirement: Recursion & BST Search)
    SkillNode* searchRecursive(SkillNode* node, int costKey); // <--- THIS WAS MISSING

public:
    KernelTree();
    ~KernelTree();

    void insert(std::string name, int cost, int ramBonus);
    void printTree(Terminal& term);
    
    // Returns the node if found, so Daemon can apply stats
    SkillNode* findNode(int cost); // <--- THIS WAS MISSING
};

#endif