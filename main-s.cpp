#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <chrono>

#include "World.h"
#include "Agent.h"

#define SIMULATION_STEPS 100
#define DELTA_TIME 0.1f

int main() {

    float sim_time = 0.0f;

    auto start = std::chrono::high_resolution_clock::now();


    for (int i = 1; i <= 31; i++) {
        srand(i);
        World* world = new World(30, 30);

        double starttime, stoptime;

        // printf("Cells: %d\n", world->getCellsCount());
        // printf("Markers: %d\n", world->getMarkersCount());

        // world->exportCells("C:/Users/vhlab/CLionProjects/BioCrowdsCP/output/cells.csv");
        // world->exportMarkers("C:/Users/vhlab/CLionProjects/BioCrowdsCP/output/markers.csv");

        world->createAgents(30, Vector3{29.0f, 0.0f, 29.0f});

        int count = 0;


        while (!world->allAgentsNextToGoal()) {
            // printf("Count: %d | Distance: %.2f\n", count, world->getSumOfDistances());
            world->update();

            count++;
        }

        sim_time += (count/50.0f);

        delete world;
    }

    auto end = std::chrono::high_resolution_clock::now();
        
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Simulation Time: " << (sim_time/31.0f) << "segundos\n";
    std::cout << "Execution time: " << elapsed.count() << " seconds\n";

    return 0;
}
