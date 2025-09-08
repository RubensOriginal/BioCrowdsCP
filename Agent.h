#ifndef AGENT_H
#define AGENT_H

#include "Vector3.h"
#include "Marker.h"
#include "Cell.h"

typedef struct World World;

typedef struct Agent {
    Vector3 position;
    Vector3 velocity;
    float agentRadius;
    float maxSpeed;

    Cell* currentCell;
    // Auxin** auxins;
    int auxinsCount;
    int auxinsCapacity;

    World* world;

    Vector3 rotation; // movement vector
    Vector3 goalPosition;
    Vector3 dirAgentGoal;
} Agent;

#endif
