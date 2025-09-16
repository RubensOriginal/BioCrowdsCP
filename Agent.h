#ifndef AGENT_H
#define AGENT_H

#include <list>
#include <omp.h>

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

    bool isDenW;
    float denW;

    Vector3 rotation{}; // movement vector
    Vector3 goalPosition{};
    Vector3 dirAgentGoal{};
public:
    omp_lock_t marker_vector_lock;

    Agent(Vector3 position, Vector3 goalPosition, Cell* cell, World* world);

    void clear();

    void movimentStep(float _timeStep);

    void calculateDirection();
    void calculateVelocity();

    float GetW(Marker* marker);
    float GetF(Marker* marker);
    void FindNearAuxins();

    void FindCell();
    void CheckAuxins(float *pDistToCellSqr, Cell* cell);
    bool isAtGoal();

    void removeMarker(Marker* marker);

    float getDistanceToGoal();
};

#endif
