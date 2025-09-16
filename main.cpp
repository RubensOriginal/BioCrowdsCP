#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <omp.h>

#include "World.h"
#include "Agent.h"

#define SIMULATION_STEPS 100
#define DELTA_TIME 0.1f

int main() {
    srand(1);
    omp_set_num_threads(16);

    World* world = new World(100, 100);

    double starttime, stoptime;

    printf("Cells: %d\n", world->getCellsCount());
    printf("Markers: %d\n", world->getMarkersCount());

    // world->exportCells("C:/Users/vhlab/CLionProjects/BioCrowdsCP/output/cells.csv");
    // world->exportMarkers("C:/Users/vhlab/CLionProjects/BioCrowdsCP/output/markers.csv");

    world->createAgents(20, Vector3{99.0f, 0.0f, 99.0f});

    int count = 0;

    starttime = omp_get_wtime(); 

    while (!world->allAgentsNextToGoal()) {
        //printf("Count: %d | Distance: %.2f\n", count, world->getSumOfDistances());
        world->update();

        count++;
    }

    printf("Tempo de Simulacao: %.2f segundos\n", count/50.0f);

    stoptime = omp_get_wtime();
	
    printf("\nTempo de execucao: %3.2f segundos\n\n", stoptime-starttime);

    delete world;

    return 0;
}
