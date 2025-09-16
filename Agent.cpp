#include "Agent.h"

#include <cstdlib>
#include <cmath>
#include <cstdio>

#include "World.h"


Agent::Agent(Vector3 position, Vector3 goalPosition, Cell *cell, World *world) {
    this->position = position;
    this->goalPosition = goalPosition;

    this->world = world;
    this->currentCell = cell;

    this->isDenW = false;
    this->denW = 0.0f;
    this->maxSpeed = 1.5f;
}

void Agent::clear() {
    this->denW = 0.0f;
    this->markers.clear();
    this->isDenW = false;
    this->rotation = Vector3(0.0f, 0.0f, 0.0f);

    this->dirAgentGoal = this->goalPosition - this->position;

}

void Agent::movimentStep(float _timeStep) {
    // printf("Distancia: %f | Velocity: %f\n", vector3_distance(this->velocity * _timeStep, Vector3{0,0,0}), vector3_sqr_magnitude(this->velocity));
    // printf("Distancia: %f | Velocity: %f\n", vector3_distance(this->position, this->goalPosition), vector3_sqr_magnitude(this->velocity));
    if (vector3_sqr_magnitude(this->velocity) > 0.0f) {
        this->position = this->position + this->velocity * _timeStep;
    }
}

void Agent::calculateDirection() {
    for (Marker* marker : this->markers){
    // for (int k = 0; k < this->markers.size(); k++) {


        float w = GetW(marker);
        if (this->denW < 0.0001f)
            w = 0.0f;

        // printf("%.4f | %.4f | %.4f | %.4f\n", vector3_distance(this->rotation, Vector3{0, 0, 0}), vector3_distance((marker->position - this->position), Vector3{0, 0, 0}), w, this->maxSpeed);

        this->rotation = this->rotation + ((marker->position - this->position) * w * this->maxSpeed);
    }
}

void Agent::calculateVelocity() {

    float moduleM = vector3_distance(this->rotation, Vector3{0.0f, 0.0f, 0.0f});

    float s = moduleM * M_PI;

    if (s > this->maxSpeed) {
        s = this->maxSpeed;
    }

    if (moduleM > 0.0001f) {
        this->velocity = (this->rotation / moduleM) * s;
    } else {
        this->velocity = Vector3(0.0f, 0.0f, 0.0f);
    }
}


float Agent::GetW(Marker* marker) {
    float fValue = GetF(marker);

    if (!this->isDenW) {
        this->denW = 0;

        for (Marker* m : this->markers){
            this->denW += GetF(m);
        }

        this->isDenW = true;
    }

    return fValue/this->denW;
}

float Agent::GetF(Marker* marker)
{
    Vector3 vecZero = (Vector3){0.0f, 0.0f, 0.0f};

    float Ymodule = vector3_distance(marker->position - this->position, vecZero);

    float Xmodule = vector3_magnitude(vector3_normalize(this->dirAgentGoal));

    float dot = vector3_dot(marker->position - this->position, vector3_normalize(this->dirAgentGoal));

    if (Ymodule < 0.00001f)
        return 0.0f;

    return static_cast<float>((1.0 / (1.0 + Ymodule)) * (1.0 + ((dot) / (Xmodule * Ymodule))));
}

void Agent::FindNearAuxins()
{
    this->markers.erase(this->markers.begin(), this->markers.end());

    for (int i = 0; i < this->world->getMarkersCount(); i++) {
        Marker* marker = this->world->getMarker(i);

        omp_set_lock(&this->world->locks[i]);
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
        omp_unset_lock(&this->world->locks[i]);
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
    return this->getDistanceToGoal() <= GOAL_DISTANCE_THRESHOLD;
}



void Agent::removeMarker(Marker *marker) {
    this->markers.remove(marker);
}

float Agent::getDistanceToGoal() {
    return vector3_distance(this->position, this->goalPosition);
}


