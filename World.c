#include "World.h"

#include <stdio.h>
#include <stdlib.h>


void initWorld(World *w, int x, int z) {
    w->dimension = (Vector3){x, 0.0f, z};
    w->cellsCount = 0;
    w->markersCount = 0;

    createCells(w);
    createMarkers(w);
}

void createCells(World *world) {

    world->cellsCount = ((int)world->dimension.x / 2)  * ((int)world->dimension.z / 2);


    world->cells = (Cell**)malloc(world->cellsCount * sizeof(Cell*));

    for (int x = 0; x < ((int)world->dimension.x / 2); x++) {
        for (int z = 0; z < ((int)world->dimension.z / 2); z++) {
            Cell *cell = (Cell*)malloc(sizeof(Cell));
            cell->X = x;
            cell->Z = z;
            cell->markersCount = 0;


            cell->position = (Vector3){2.0f * x, 0.0f, 2.0f * z};

            world->cells[x*((int)world->dimension.x/2) + z] = cell;
        }
    }

}

void createMarkers(World *world) {
    int maxMarkersPerCell = (int)(MARKER_DENSITY/(MARKER_RADIUS * MARKER_RADIUS));

    for (int c = 0; c < world->cellsCount; c++) {
        Cell* cell = world->cells[c];

        cell->markers = (Marker**)malloc(maxMarkersPerCell * sizeof(Marker*));

        populateCell(world, c, maxMarkersPerCell);
    }

}

void populateCell(World* world, int c, int maxMarkers) {
    // float cellHalfSize = 1.0f * (1.0f - (MARKER_RADIUS/2.f));
    Cell *cell = world->cells[c];


    for (int i = 0; i < maxMarkers; i++) {
        Marker* marker = malloc(sizeof(Marker));

        float x = random_range(0, 2);
        float z = random_range(0, 2);

        marker->position = (Vector3){x + (cell->X * 2), 0,z + (cell->Z * 2)};
        marker->cell = cell;

        cell->markersCount++;
        // world->markers[world->markersCount] = marker;
        world->markersCount++;

        cell->markers[i] = marker;

    }
}

// -----------------------------------------------


float random_range(float min, float max) {
    return min + (max - min) * ((float)rand() / RAND_MAX);
}

void exportCells(World *world, const char* filename) {
    FILE* file = fopen(filename, "w");

    if (!file) {
        perror("Erro ao abrir arquivo");
        return;
    }

    fprintf(file, "cell_x,cell_z\n");

    for (int i = 0; i < world->cellsCount; i++) {
        Cell *cell = world->cells[i];
        fprintf(file, "%d,%d\n",
                    cell->X, cell->Z);
    }

    fclose(file);
}

void exportMarkers(World *world, const char* filename) {
    FILE* file = fopen(filename, "w");


    if (!file) {
        perror("Erro ao abrir arquivo");
        return;
    }

    fprintf(file, "marker_x,marker_z\n");

    for (int i = 0; i < world->cellsCount; i++) {
        Cell *cell = world->cells[i];
        for (int j = 0; cell->markersCount > j; j++) {
            // printf("i = %d | j = %d\n", i, j);
            Marker* marker = cell->markers[j];
            fprintf(file, "%.3f,%.3f\n",
                    marker->position.x, marker->position.z);
        }
    }

    fclose(file);
}




