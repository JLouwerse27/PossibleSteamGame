#include "jGameLogic.h"
#include <thread>
#include <chrono>

void JGameLogic::startGameLogic(JPlayer * jpl) {
    uint64_t tick = 0;
    uint32_t height = jpl->getH();
    while (jRunning) {
        if (jIsKeyPressed[0] && jY > 0) {
            jY--;
        }

        if (jIsKeyPressed[2] && jY < WORLD_HEIGHT - jYBlocksInCameraView) {
            jY++;
        }

        if (jIsKeyPressed[1] && jX > 0) {
            jX--;
        }

        if (jIsKeyPressed[3] && jX < WORLD_WIDTH - jXBlocksInCameraView) {
            jX++;
        }

        applyGravity();

        jpl->setX((jX + jXBlocksInCameraView / 2));
        jpl->setY((jY - height + jYBlocksInCameraView / 2));


        tick++;

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
void JGameLogic::applyGravity() {
    //if(jwo)
}
