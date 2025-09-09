#include "Cell.h"
#include <vector>

Cell::Cell(int X, int Z, Vector3 position) {
    this->X = X;
    this->Z = Z;
    this->position = position;
}

int Cell::getX() {
    return X;
}

int Cell::getZ() {
    return Z;
}

Vector3 Cell::getPosition() {
    return position;
}

void Cell::addMarker(Marker *marker) {
    this->markers.push_back(marker);
}

int Cell::getMarkersSize() {
    return markers.size();
}

Marker* Cell::getMarker(int index) {
    return markers[index];
}


