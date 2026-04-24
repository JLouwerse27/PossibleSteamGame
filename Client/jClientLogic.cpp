#include "jClientLogic.h"
#include <thread>
#include <chrono>

void JGameLogic::startGameLogic(JPlayer * jpl) {
    uint64_t tick = 0;
    uint32_t height = jpl->getH();
    bool atEdge[4] = { false,false,false,false };
    while (jRunning) {
        

        if (jIsKeyPressed[0] && jpl->getY() > 0) {
            if (jY > 0 + jYBlocksInCameraView) {
                jY--;
                atEdge[0] = false;
            }
            else {
                atEdge[0] = true;
                jpl->setY(jpl->getY() - 1);
            }
        }

        if (jIsKeyPressed[2] && jpl->getY() < WORLD_HEIGHT) {
            if (jY < WORLD_HEIGHT - jYBlocksInCameraView) {
                jY++;
                atEdge[2] = false;
            }
            else {
                atEdge[2] = true;
                jpl->setY(jpl->getY() + 1);
            }
        }

        if (jIsKeyPressed[1] && jpl->getX() > 0) {
            if (jX > 0 && !atEdge[3]) {
                jX--;
                atEdge[1] = false;
            }
            else{
                if (jX < 0) jX = 0;
                if (jX == 0) {
                    atEdge[1] = true;
                    if (jpl->getX() > 0) {
                        jpl->setX(jpl->getX() - 1);
                    }
                }
                else {
                    if (jpl->getX() <= WORLD_WIDTH - jXBlocksInCameraView/2) {
                        jX--;
                    }
                    if (jpl->getX() > 0) {
                        jpl->setX(jpl->getX() - 1);
                    }
                }
            }
        }

        if (jIsKeyPressed[3] && jpl->getX() < WORLD_WIDTH) {
            if (jX < WORLD_WIDTH - jXBlocksInCameraView && !atEdge[1]) {
                jX++;
                atEdge[3] = false;
            }
            else {
                if (jX > WORLD_WIDTH - jXBlocksInCameraView) jX = WORLD_WIDTH - jXBlocksInCameraView;
                if (jX == WORLD_WIDTH - jXBlocksInCameraView) {
                    atEdge[3] = true;
                    if (jpl->getX() < WORLD_WIDTH) {
                        jpl->setX(jpl->getX() + 1);
                    }
                }
                else {
                    if (jpl->getX() >= jXBlocksInCameraView / 2) {
                        atEdge[1] = false;
                        jX++;
                    }
                    if (jpl->getX() < WORLD_WIDTH) {
                        jpl->setX(jpl->getX() + 1);
                    }
                }
            }
        }

        applyGravity();
        if (!atEdge[0] && !atEdge[1] && !atEdge[2] && !atEdge[3]) {
            jpl->setX((jX + jXBlocksInCameraView / 2));
            jpl->setY((jY - height + jYBlocksInCameraView / 2));
        }

        tick++;

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
void JGameLogic::applyGravity() {
    //if(jwo)
}
