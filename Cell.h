#ifndef CELL_H
#define CELL_H

// #include "Marker.h"
#include "Vector3.h"

#include <vector>

class Marker;

// typedef struct Cell {
//     int X;
//     int Z;
//
//     Vector3 position;
//
//     int markersCount;
//     Marker** markers;      // array of pointers
// } Cell;

class Cell {
private:
    int X;
    int Z;
    Vector3 position{};

    std::vector<Marker*> markers;
public:
    Cell(int X, int Z, Vector3 position);

    int getX();
    int getZ();

    Vector3 getPosition();

    void addMarker(Marker* marker);
    int getMarkersSize();
    Marker* getMarker(int index);
};

#endif
