#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "World.h"
#include "Agent.h"

#define SIMULATION_STEPS 100
#define DELTA_TIME 0.1f

int main() {
    srand(1);
    World* world = new World(20, 20);

    printf("Cells: %d\n", world->getCellsCount());
    printf("Markers: %d\n", world->getMarkersCount());

    world->exportCells("C:/Users/vhlab/CLionProjects/BioCrowdsCP/output/cells.csv");

    world->exportMarkers("C:/Users/vhlab/CLionProjects/BioCrowdsCP/output/markers.csv");

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
