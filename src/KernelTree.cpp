#include "../include/KernelTree.h"

KernelTree::KernelTree() : root(nullptr) {}

KernelTree::~KernelTree() {
    destroyRecursive(root);
}

void KernelTree::destroyRecursive(SkillNode* node) {
    if (node != nullptr) {
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
    }
}

void KernelTree::insert(std::string name, int cost, int ramBonus) {
    SkillNode* newNode = new SkillNode(name, cost, ramBonus);
    if (root == nullptr) {
        root = newNode;
        return;
    }
    SkillNode* current = root;
    while (true) {
        if (cost < current->cost) {
            if (current->left == nullptr) {
                current->left = newNode;
                break;
            }
            current = current->left;
        } else {
            if (current->right == nullptr) {
                current->right = newNode;
                break;
            }
            current = current->right;
        }
    }
}

// THE SEARCH LOGIC
SkillNode* KernelTree::findNode(int cost) {
    return searchRecursive(root, cost);
}

SkillNode* KernelTree::searchRecursive(SkillNode* node, int costKey) {
    if (node == nullptr || node->cost == costKey) {
        return node; // Found it (or hit dead end)
    }

    // BST Logic: If cost is lower, go left. Higher, go right.
    if (costKey < node->cost) {
        return searchRecursive(node->left, costKey);
    } 
    return searchRecursive(node->right, costKey);
}

void KernelTree::printTree(Terminal& term) {
    term.print("=== KERNEL EVOLUTION TREE ===");
    printRecursive(root, term, "");
}

void KernelTree::printRecursive(SkillNode* node, Terminal& term, std::string prefix) {
    if (node == nullptr) return;

    // Visual feedback: [X] = Unlocked, [ ] = Locked
    std::string status = node->unlocked ? "[INSTALLED]" : "[LOCKED]";
    std::string color = node->unlocked ? "\033[1;36m" : "\033[1;30m"; // Cyan vs Grey

    term.print(prefix + "> " + status + " " + node->skillName + " (Cost: " + std::to_string(node->cost) + ")");

    printRecursive(node->left, term, prefix + "  L-");
    printRecursive(node->right, term, prefix + "  R-");
}