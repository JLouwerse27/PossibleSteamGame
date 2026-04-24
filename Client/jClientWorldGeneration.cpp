#include "jVariables.h"
#include "jClientWorldGeneration.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

namespace jgw {
    int islandHeight = 60;
    int dirtHeight = jDirtLevel;
    int stoneHeight = 130;
    int ironHeight = 180;
    int diamondHeight = 240;
    int chunkSize = 20;
    int numIslands = 0;
    int targetIslands = 5;

    void jGenerateWorld() {
        srand(static_cast<unsigned int>(time(nullptr)));

        for (int i = 0; i < WORLD_HEIGHT; i += chunkSize) {
            if (i <= islandHeight) {
                int genIsland;

                for (int j = 0; j < WORLD_WIDTH; j += chunkSize) {
                    genIsland = rand() % ((WORLD_WIDTH / chunkSize) * ((islandHeight)/chunkSize));

                    if (numIslands < targetIslands && genIsland < targetIslands) {
                        for (int k = i; k < i + chunkSize/2 && k < WORLD_HEIGHT; k++) {
                            for (int l = j; l < j + chunkSize && l < WORLD_WIDTH; l++) {
                                jWorldA[k * WORLD_WIDTH + l] = 4;
                            }
                        }
                        numIslands++;
                        std::cout << "made island\n";

                    }
                }
            }

            if (i >= dirtHeight) {
                for (int j = 0; j < WORLD_WIDTH; j += chunkSize) {
                    for (int k = i; k < i + chunkSize && k < WORLD_HEIGHT; k++) {
                        for (int l = j; l < j + chunkSize && l < WORLD_WIDTH; l++) {
                            jWorldA[k * WORLD_WIDTH + l] = 1;
                        }
                    }
                }
            }
        }
    }
}