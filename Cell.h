#ifndef CELL_H
#define CELL_H

#include "Marker.h"

typedef struct Cell {
    int X;
    int Z;

    Vector3 position;

    int markersCount;
    Marker** markers;      // array of pointers
} Cell;

#endif
