#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include "mpi.h"

#include "World.h"
#include "Agent.h"

#define SIMULATION_STEPS 100
#define DELTA_TIME 0.1f
#define NUM_SIM 62

int main(int argc, char** argv) {

    int my_rank;  /* Identificador do processo */
    int proc_n;   /* Número de processos */
    int source;   /* Identificador do proc.origem */
    int dest;     /* Identificador do proc. destino */
    int tag = 50; /* Tag para as mensagens */
    int sim_seed = 1;
    int sim_recv = 0;

    int invalid = -1;

    MPI_Status status; /* Status de retorno */
 
    MPI_Init (&argc , &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_n);

    if (my_rank == 0) {
        // Coordenador
        float sim_time = 0.0f;

        // std::cout << "Coordenador Iniciando" << std::endl;

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 1; i < proc_n; i++) {
            MPI_Send(&sim_seed, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
            // std::cout << my_rank << ">> Enviei a seed " << sim_seed << " para o " << i << "/" << proc_n << std::endl;


            sim_seed++;
        }

        while (sim_recv < NUM_SIM) {
            float payload = 0.0f;

            MPI_Recv(&payload, 1, MPI_FLOAT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);

            sim_time += payload;

            sim_recv++;

            if (sim_seed > NUM_SIM) {
                MPI_Send(&invalid, 1, MPI_INT, status.MPI_SOURCE, tag, MPI_COMM_WORLD);
                // std::cout << my_rank << ">> Enviei a seed " << -1 << " para o " << status.MPI_SOURCE << std::endl;
            } else {
                MPI_Send(&sim_seed, 1, MPI_INT, status.MPI_SOURCE, tag, MPI_COMM_WORLD);
                // std::cout << my_rank << ">> Enviei a seed " << sim_seed << " para o " << status.MPI_SOURCE << std::endl;

                sim_seed++;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Simulation Time: " << (sim_time/NUM_SIM) << " seconds\n";
        std::cout << "Execution time: " << elapsed.count() << " seconds\n";

    } else {
        // Trabalhador

        // std::cout << "Trabalhador " << my_rank << " Iniciando" << std::endl;

        while (sim_seed != -1) {
            // std::cout << my_rank << ">> Aguardando uma seed" << std::endl;

            MPI_Recv(&sim_seed, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
            // std::cout << my_rank << ">> Recebi a seed " << sim_seed << std::endl;

            if (sim_seed == -1)
                continue;

            srand(sim_seed);
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

            float sim_time = count / 50.0f;

            delete world;


            MPI_Send(&sim_time, 1, MPI_FLOAT, 0, tag, MPI_COMM_WORLD);
        }

    }


    MPI_Finalize();
    
    return 0;
}
