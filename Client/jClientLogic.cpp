#include "jClientLogic.h"
#include <thread>
#include <chrono>

void JGameLogic::runGameLogic(JPlayer * jpl) {
    uint32_t height = 1;//measured in blocks, not pixels
    bool atEdge[4] = { false,false,false,false };
    //while (jRunning) {
        
    if (jIsKeyPressed[0] && jY > 0){
        if (jWorldA[(jpl->y + 1) * WORLD_WIDTH + jpl->x] == 1) {
            jY--;
            inAir = true;
            tickJumpStarted = tick;
        }
        
    }
    if (jIsKeyPressed[2] && jY < WORLD_HEIGHT - jYBlocksInCameraView) {
        //jY++;
    }
    if (jIsKeyPressed[1] && jX > 0) {
        jX--;
    }
    if (jIsKeyPressed[3] && jX < WORLD_WIDTH - jXBlocksInCameraView) {
        jX++;
    }

    //jumping
    

    if (inAir) {
        if (tickJumpStarted + timeInAir <= tick && jWorldA[(jpl->y + 1) * WORLD_WIDTH + jpl->x] != 1) {
            jY++;//fall
        }else if (tickJumpStarted + timeInAir > tick){// && inAir) {
            jY--;// incline
        }
        if (jWorldA[(jpl->y + 1) * WORLD_WIDTH + jpl->x] == 1 && tickJumpStarted + timeInAir <= tick) {
            inAir = false;
        }
    }


        /*if (jIsKeyPressed[0] && jpl->y > 0) {
            if (jY > 0 + jYBlocksInCameraView) {
                jY--;
                atEdge[0] = false;
            }
            else {
                atEdge[0] = true;
                jpl->y--;
            }
        }

        if (jIsKeyPressed[2] && jpl->y < WORLD_HEIGHT) {
            if (jY < WORLD_HEIGHT - jYBlocksInCameraView) {
                jY++;
                atEdge[2] = false;
            }
            else {
                atEdge[2] = true;
                jpl->y++;
            }
        }

        if (jIsKeyPressed[1] && jpl->x > 0) {
            if (jX > 0 && !atEdge[3]) {
                jX--;
                atEdge[1] = false;
            }
            else{
                if (jX < 0) jX = 0;
                if (jX == 0) {
                    atEdge[1] = true;
                    if (jpl->x > 0) {
                        jpl->x--;
                    }
                }
                else {
                    if (jpl->x <= WORLD_WIDTH - jXBlocksInCameraView/2) {
                        jX--;
                    }
                    if (jpl->x > 0) {
                        jpl->x--;
                    }
                }
            }
        }

        if (jIsKeyPressed[3] && jpl->x < WORLD_WIDTH) {
            if (jX < WORLD_WIDTH - jXBlocksInCameraView && !atEdge[1]) {
                jX++;
                atEdge[3] = false;
            }
            else {
                if (jX > WORLD_WIDTH - jXBlocksInCameraView) jX = WORLD_WIDTH - jXBlocksInCameraView;
                if (jX == WORLD_WIDTH - jXBlocksInCameraView) {
                    atEdge[3] = true;
                    if (jpl->x < WORLD_WIDTH) {
                        jpl->x++;
                    }
                }
                else {
                    if (jpl->x >= jXBlocksInCameraView / 2) {
                        atEdge[1] = false;
                        jX++;
                    }
                    if (jpl->x < WORLD_WIDTH) {
                        jpl->x++;
                    }
                }
            }
        }*/

        applyGravity();
        //if (!atEdge[0] && !atEdge[1] && !atEdge[2] && !atEdge[3]) {
            jpl->x = ((jX + jXBlocksInCameraView / 2));
            jpl->y = ((jY + jYBlocksInCameraView / 2 - 1));
        //}

        tick++;

        //std::this_thread::sleep_for(std::chrono::milliseconds(4));
    //}
}
void JGameLogic::applyGravity() {
    //if(jwo)
}
