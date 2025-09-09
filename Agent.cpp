#include "Agent.h"

#include <stdlib.h>

#include "World.h"


Agent::Agent(Vector3 position, Vector3 goalPosition, Cell *cell, World *world) {
    this->position = position;
    this->goalPosition = goalPosition;

    this->world = world;
    this->currentCell = cell;
}

float Agent::GetF(int pRelationIndex)
{
    Vector3 vecZero = (Vector3){0.0f, 0.0f, 0.0f};

    float Ymodule = vector3_distance(this->world->getMarker(pRelationIndex)->position, vecZero);

    float Xmodule = 
}

void Agent::FindNearAuxins()
{
    this->markers.erase(this->markers.begin(), this->markers.end());

    for (int i = 0; i < this->world->getMarkersCount(); i++) {
        Marker* marker = this->world->getMarker(i);

        float dis = vector3_magnitude(vector3_sub(this->position, marker->position));

        if (dis < marker->minDistance && dis <= AGENT_RADIUS * AGENT_RADIUS) {

            if (marker->isTaken) {
                marker->agent->markers.remove(marker);
            }

            marker->isTaken = true;
            marker->agent = this;
            marker->minDistance = dis;
            this->markers.push_back(marker);
        }
    }
}

void Agent::FindCell() {

    float distanceToCellSqr = vector3_magnitude(vector3_sub(this->position, this->currentCell->getPosition()));

}


void Agent::CheckAuxins(float *pDistToCellSqr, Cell* cell) {
    // Marker** markers = cell->markers;

    for (int i = 0; i < cell->getMarkersSize(); i++) {
        Marker* marker = cell->getMarker(i);

        float dis = vector3_magnitude(vector3_sub(this->position, marker->position));

        if (dis < marker->minDistance && dis <= AGENT_RADIUS*AGENT_RADIUS) {

            if (marker->isTaken) {
                marker->agent->removeMarker(marker);
            }

            marker->isTaken = true;
            marker->agent = this;
            marker->minDistance = dis;

            this->markers.push_back(marker);
        }
    }

    float distanceToNeighbourCell = vector3_magnitude(vector3_sub(this->position, cell->getPosition()));

    if (distanceToNeighbourCell < *pDistToCellSqr) {
        *pDistToCellSqr = distanceToNeighbourCell;
        this->currentCell = cell;
    }
}

bool Agent::isAtGoal() {
    return vector3_distance(this->position, this->goalPosition) <= GOAL_DISTANCE_THRESHOLD;
}



void Agent::removeMarker(Marker *marker) {
    this->markers.remove(marker);
}


