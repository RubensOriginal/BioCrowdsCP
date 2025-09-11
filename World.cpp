#include "World.h"

#include <stdio.h>
#include <stdlib.h>


World::World(int x, int z) {
    this->dimension = (Vector3){(float)x, 0.0f, (float)z};

    this->createCells();
    this->createMarkers();
}

World::~World() {
    for (Cell* cell : this->cells) {
        delete cell;
    }

    for (Marker* marker : this->markers) {
        delete marker;
    }

    for (Agent* agent : this->agents) {
        delete agent;
    }
}

void World::createCells() {

    this->cellsCount = (static_cast<int>(this->dimension.x) / 2)  * (static_cast<int>(this->dimension.z) / 2);

    // world->cells = (Cell**)malloc(world->cellsCount * sizeof(Cell*));

    for (int x = 0; x < (static_cast<int>(this->dimension.x) / 2); x++) {
        for (int z = 0; z < (static_cast<int>(this->dimension.z) / 2); z++) {
            // Cell *cell = (Cell*)malloc(sizeof(Cell));

            Cell *cell = new Cell(x, z, Vector3{0, 0, 0});

            cells.push_back(cell);
            // world->cells[x*((int)world->dimension.x/2) + z] = cell;
        }
    }

}

void World::createMarkers() {
    int maxMarkersPerCell = (int)(MARKER_DENSITY/(MARKER_RADIUS * MARKER_RADIUS));

    for (int c = 0; c < this->cellsCount; c++) {
        Cell* cell = this->cells[c];

        // cell->markers = (Marker**)malloc(maxMarkersPerCell * sizeof(Marker*));

        populateCell(c, maxMarkersPerCell);
    }


}

void World::populateCell(int c, int maxMarkers) {
    // float cellHalfSize = 1.0f * (1.0f - (MARKER_RADIUS/2.f));
    Cell *cell = this->cells[c];


    for (int i = 0; i < maxMarkers; i++) {

        float x = random_range(0, 2);
        float z = random_range(0, 2);

        // Vector3 ->position = ;
        Marker* marker = new Marker((Vector3){x + (2 * cell->getX()), 0,z + (2 * cell->getZ())}, cell);

        // cell->markersCount++;
        // world->markers[world->markersCount] = marker;
        // world->markersCount++;

        cell->addMarker(marker);
        this->markers.push_back(marker);

        // cell->markers[i] = marker;
    }
}

void World::createAgents(int numAgents, Vector3 goal) {
    for (int a = 0; a < numAgents; a++) {
        float x = random_range(0.0f, 1.0f);
        float z = random_range(0.0f, 1.0f);

        Agent* agent = new Agent(Vector3{x, 0.0f, z}, Vector3{20.0f, 0.0f, 20.0f}, nullptr, this);
        this->agents.push_back(agent);
    }
}

void World::update() {
    for (auto & marker : this->markers) {
        marker->ResetMarker();
    }

    for (int a = 0; a < this->agents.size(); a++) {
        this->agents[a]->FindNearAuxins();
    }

    for (int a = 0; a < this->agents.size(); a++) {
        Agent* agent = this->agents[a];

        agent->calculateDirection();
        agent->calculateVelocity();

        agent->movimentStep(SIMULATION_TIME_STEP);
    }

    for (int a = 0; a < this->agents.size(); a++) {
        this->agents[a]->clear();
    }
}

int World::getCellsCount() {
    return this->cells.size();
}

int World::getMarkersCount() {
    return this->markers.size();
}

bool World::allAgentsNextToGoal() {
    for (Agent* agent : this->agents) {
        if (!agent->isAtGoal()) {
            return false;
        }
    }

    return true;
}

Marker *World::getMarker(int i)
{
    return this->markers[i];
}

// -----------------------------------------------


float World::random_range(float min, float max) {
    return min + (max - min) * ((float)rand() / RAND_MAX);
}

void World::exportCells(const char* filename) {
    FILE* file = fopen(filename, "w");

    if (!file) {
        perror("Erro ao abrir arquivo");
        return;
    }

    fprintf(file, "cell_x,cell_z\n");

    for (int i = 0; i < this->cells.size(); i++) {
        Cell *cell = this->cells[i];
        fprintf(file, "%d,%d\n",
                    cell->getX(), cell->getZ());
    }

    fclose(file);
}

void World::exportMarkers(const char* filename) {
    FILE* file = fopen(filename, "w");


    if (!file) {
        perror("Erro ao abrir arquivo");
        return;
    }

    fprintf(file, "marker_x,marker_z\n");

    for (int i = 0; i < this->cells.size(); i++) {
        Cell *cell = this->cells[i];
        for (int j = 0; cell->getMarkersSize() > j; j++) {
            // printf("i = %d | j = %d\n", i, j);
            Marker* marker = cell->getMarker(j);
            fprintf(file, "%.3f,%.3f\n",
                    marker->position.x, marker->position.z);
        }
    }

    fclose(file);
}

float World::getSumOfDistances() {
    float sum = 0;

    for (Agent* agent : this->agents) {
        sum += agent->getDistanceToGoal();
    }

    return sum;
}




