#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include "mpi.h"

#include "World.h"
#include "Agent.h"

#define SIMULATION_STEPS 100
#define DELTA_TIME 0.1f
#define NUM_SIM 31

int main() {

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

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 1; i < proc_n; i++) {
            MPI_Send(&sim_seed, 1, MPI_INT, i, tag, MPI_COMM_WORLD);

            sim_seed++;
        }

        while (sim_recv < NUM_SIM) {
            MPI_Recv(&sim_seed, 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);

            sim_recv++;

            if (sim_seed > NUM_SIM) {
                MPI_Send(&invalid, 1, MPI_INT, status.MPI_SOURCE, tag, MPI_COMM_WORLD);
            } else {
                MPI_Send(&sim_seed, 1, MPI_INT, status.MPI_SOURCE, tag, MPI_COMM_WORLD);

                sim_seed++;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Execution time: " << elapsed.count() << " seconds\n";

    } else {
        // Trabalhador

        while (sim_seed != -1) {
            MPI_Recv(&sim_seed, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);

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

    // // Criar o mundo
    // World* world = world_create(20.0f, 20.0f); // largura, altura, maxAgents
    // if (!world) {
    //     printf("Erro ao criar o mundo!\n");
    //     return 1;
    // }
    //
    // // 2. Cria as células
    //
    //
    // // 3. Cria os marcadores de auxina (exemplo: 5 auxinas)
    //
    // export_cells_csv(world, "C:/Users/Rubens/CLionProjects/BioCrowdsCP/output/cells.csv");
    // save_markers_csv(world, "C:/Users/Rubens/CLionProjects/BioCrowdsCP/output/markers.csv");
    //
    // return 0;
    //
    // // Inicializar posições aleatórias dos agentes
    // for (int i = 0; i < world->maxAgents; i++) {
    //     Agent* agent = world->agents[i];  // agents é um array de ponteiros
    //     agent->position.x = (float)(rand() % (int)world->dimension.x);
    //     agent->position.z = (float)(rand() % (int)world->dimension.z);
    //     agent->position.y = 0.0f;
    // }
    //
    // // Loop principal de simulação
    // for (int step = 0; step < SIMULATION_STEPS; step++) {
    //     printf("Step %d\n", step);
    //     for (int i = 0; i < world->maxAgents; i++) {
    //         Agent* agent = world->agents[i];
    //
    //         // Atualizar comportamento do agente
    //         agent_find_near_auxins(agent);
    //         agent_calculate_direction(agent);
    //         agent_calculate_velocity(agent);
    //         agent_update_position(agent, DELTA_TIME);
    //
    //         printf("Agent %d position: (%.2f, %.2f, %.2f)\n",
    //                i,
    //                agent->position.x,
    //                agent->position.y,
    //                agent->position.z);
    //     }
    // }
    //
    // // Liberar memória
    // world_destroy(world);
    //
    // return 0;
}
