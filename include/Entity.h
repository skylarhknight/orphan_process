#ifndef ENTITY_H
#define ENTITY_H

#include "../lib_terminal/Terminal.h"

// Abstract Class (Requirement)
class Entity {
public:
    virtual ~Entity() {} // Virtual destructor
    
    // Pure Virtual Functions (must be implemented by Daemon/Virus)
    virtual void update() = 0;
    virtual void render(Terminal& term) = 0;
};

#endif