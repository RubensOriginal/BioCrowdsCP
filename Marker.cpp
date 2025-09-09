//
// Created by vhlab on 09/09/2025.
//

#include "Marker.h"

Marker::Marker(Vector3 position, Cell* cell)
{
    this->position = position;
    this->minDistance = 2.0f;
    this->isTaken = false;
    this->agent = nullptr;

    this->cell = cell;
}

void Marker::ResetMarker() {
    this->minDistance = 2.0f;
    this->isTaken = false;
    this->agent = nullptr;
}
