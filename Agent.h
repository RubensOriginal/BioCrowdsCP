#ifndef AGENT_H
#define AGENT_H

#include <list>

#include "Vector3.h"
// #include "Marker.h"
// #include "Cell.h"

// typedef struct World World;

class World;
class Cell;
class Marker;

class Agent {
private:
    Vector3 position{};
    Vector3 velocity{};
    float agentRadius{};
    float maxSpeed{};

    Cell* currentCell{};
    std::list<Marker*> markers;

    World* world{};

    Vector3 rotation{}; // movement vector
    Vector3 goalPosition{};
    Vector3 dirAgentGoal{};
public:
    Agent(Vector3 position, Vector3 goalPosition, Cell* cell, World* world);

    void FindCell();
    void CheckAuxins(float *pDistToCellSqr, Cell* cell);
    bool isAtGoal();

    void removeMarker(Marker* marker);
};

#endif
