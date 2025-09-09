//
// Created by vhlab on 09/09/2025.
//

#ifndef BIOCROWDSCP_MARKER_H
#define BIOCROWDSCP_MARKER_H
#include <stdbool.h>

// #include "Cell.h"
#include "Agent.h"
#include "Vector3.h"

class Cell;


class Marker
{
private:

public:
    Marker(Vector3 position, Cell *cell);

    Vector3 position{};
    float minDistance;
    bool isTaken;

    Cell* cell;
    Agent* agent;

    void ResetMarker();

    // Vector3 getPosition();
    // float getMinDistance();
};


#endif //BIOCROWDSCP_MARKER_H