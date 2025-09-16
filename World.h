#ifndef WORLD_H
#define WORLD_H

#include <omp.h>

#include "Agent.h"
#include "Cell.h"
#include "Marker.h"

#define SIMULATION_TIME_STEP 0.02f
#define AGENT_RADIUS 1.0f
#define MARKER_RADIUS 0.1f
#define MARKER_DENSITY 0.5f
#define GOAL_DISTANCE_THRESHOLD 0.5f

#define MAX_AGENTS 20

// typedef struct World {
//     Vector3 dimension;
//
//     Agent** agents;
//     int agentsCount;
//     int agentsCapacity;
//
//     Cell** cells;
//     int cellsCount;
//
//     Marker** markers;
//     int markersCount;
//
// } World;

class World {
private:
    Vector3 dimension;

    int cellsCount;

    std::vector<Agent*> agents;
    std::vector<Cell*> cells;
    std::vector<Marker*> markers;


public:
    World(int X, int Z);
    ~World();

    void createCells();
    void createMarkers();
    void populateCell(int c, int maxMarkers);
    void createAgents(int numAgents, Vector3 goal);

    void removeAgents();

    void update();

    int getCellsCount();
    int getMarkersCount();
    bool allAgentsNextToGoal();

    Marker* getMarker(int i);

    static float random_range(float min, float max);

    void exportCells(const char* filename);
    void exportMarkers(const char* filename);

    float getSumOfDistances();
};


// void initWorld(World* world, int x, int z);
// void createCells(World* world);
// void createMarkers(World* world);
// void populateCell(World* world, int c, int maxMarkers);
//
// float random_range(float min, float max);
// void exportCells(World *world, const char* filename);
// void exportMarkers(World *world, const char* filename);

#endif
