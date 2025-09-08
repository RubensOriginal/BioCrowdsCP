#ifndef AUXIN_H
#define AUXIN_H

#include <stdbool.h>

#include "Vector3.h"

struct Agent;
struct Cell;

typedef struct Marker {
    Vector3 position;
    float minDistance;
    bool isTaken;

    struct Agent* agent;
    struct Cell* cell;
} Marker;

void ResetMarker(Marker *marker);

#endif
