#include "jServerVariables.h"
#include "jServerWorldGeneration.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

namespace jgw {
    int islandHeight = 60;
    int minTreeHeight = jDirtLevel - 4;
	int maxTreeHeight = jDirtLevel - 10;
    int dirtHeight = jDirtLevel;//100
    int stoneHeight = 130;
    int ironHeight = 180;
    int diamondHeight = 240;

    int chunkSize = 20;
    int numIslands = 0;
    const int targetIslands = 5;

    int numTrees = 0;
	const int targetTrees = 60;

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
                                world[k * WORLD_WIDTH + l] = 4;
                            }
                        }
                        numIslands++;
                        std::cout << "made island\n";

                    }
                }
            }

            if (i >= dirtHeight - chunkSize && i < dirtHeight) {
                int genTree;
                for (int j = 0; j < WORLD_WIDTH; j += chunkSize) {
                    for (int l = j; l < j + chunkSize && l < WORLD_WIDTH; l+=4) {
                        genTree = rand() % (WORLD_WIDTH / targetTrees);
                        bool killTree = false;
                        if (numTrees < targetTrees && genTree < 1) {
                            for (int k = i + chunkSize - 1; k >= i; k--) {
                                if (k >= dirtHeight - 3 && k < dirtHeight) {
                                    world[k * WORLD_WIDTH + l] = 3;//tree trunk
                                }
                                else if (k < dirtHeight - 3 && k >= dirtHeight - 5) {
                                    if (rand() % 2 == 0 && k % 2 == 0) {
                                        world[k * WORLD_WIDTH + l - 1] = 3;//left branch
                                    }
                                    if (rand() % 2 == 0 && k % 2 == 0) {
                                        if (rand() % 2 == 0 && k % 2 == 0) {
                                            world[k * WORLD_WIDTH + l - 1] = 3;//right branch
                                        }
                                    }
                                    world[k * WORLD_WIDTH + l] = 3;
                                }
                                else if (k < dirtHeight - 5) {
                                    if(rand() % 5 == 0) killTree = true;
                                    if (!killTree) {
                                        if (rand() % 2 == 0 && k % 2 == 0) {
                                            world[k * WORLD_WIDTH + l - 1] = 3;//branches
                                            world[k * WORLD_WIDTH + l + 1] = 3;
                                        }
                                        world[k * WORLD_WIDTH + l] = 3;
                                    }
                                }
                            }
                            killTree = false;
                            numTrees++;
                            std::cout << "made tree\n";
                        }
                        
                    }
                    
                }
            }

            if (i >= dirtHeight) {
                for (int j = 0; j < WORLD_WIDTH; j += chunkSize) {
                    for (int k = i; k < i + chunkSize && k < WORLD_HEIGHT; k++) {
                        for (int l = j; l < j + chunkSize && l < WORLD_WIDTH; l++) {
                            world[k * WORLD_WIDTH + l] = 1;
                        }
                    }
                }
            }
        }
    }
}