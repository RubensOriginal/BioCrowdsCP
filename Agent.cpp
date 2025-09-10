#include "Agent.h"

#include <cstdlib>

#include "World.h"


Agent::Agent(Vector3 position, Vector3 goalPosition, Cell *cell, World *world) {
    this->position = position;
    this->goalPosition = goalPosition;

    this->world = world;
    this->currentCell = cell;

    this->isDenW = false;
    this->denW = 0.0f;
}

float Agent::GetW(int relationIndex) {
    float fValue = GetF(relationIndex);

    if (!this->isDenW) {
        this->denW = 0;

        for(int k = 0; k < this->world->getCellsCount(); k++) {
            this->denW += GetF(k);
        }

        this->isDenW = true;
    }

    return fValue/denW;
}

float Agent::GetF(int pRelationIndex)
{
    Vector3 vecZero = (Vector3){0.0f, 0.0f, 0.0f};

    float Ymodule = vector3_distance(this->world->getMarker(pRelationIndex)->position, vecZero);

    float Xmodule = vector3_magnitude(vector3_normalize(this->goalPosition));

    float dot = vector3_dot(this->world->getMarker(pRelationIndex)->position, vector3_normalize(this->goalPosition));

    if (Ymodule > 0.00001f)
        return 0.0f;

    return static_cast<float>((1.0 / (1.0 + Ymodule)) * (1.0 + ((dot) / (Xmodule * Ymodule))));
}

void Agent::FindNearAuxins()
{
    this->markers.erase(this->markers.begin(), this->markers.end());

    for (int i = 0; i < this->world->getMarkersCount(); i++) {
        Marker* marker = this->world->getMarker(i);

        float dis = vector3_sqr_magnitude(this->position - marker->position);

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

    float distanceToCellSqr = vector3_sqr_magnitude(this->position - this->currentCell->getPosition());

}


void Agent::CheckAuxins(float *pDistToCellSqr, Cell* cell) {
    // Marker** markers = cell->markers;

    for (int i = 0; i < cell->getMarkersSize(); i++) {
        Marker* marker = cell->getMarker(i);

        float dis = vector3_sqr_magnitude(this->position - marker->position);

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

    float distanceToNeighbourCell = vector3_sqr_magnitude(this->position - cell->getPosition());

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


