#include <stdlib.h>

#include "Marker.h"

void ResetMarker(Marker *marker) {
    marker->minDistance = 2.0f;
    marker->agent = NULL;
    marker->isTaken = false;
}
