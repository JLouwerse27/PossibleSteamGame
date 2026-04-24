#include <iostream>
#include <string>
#include <thread>
#include <cstring>

#include "GameObject.h"
#include "jGraphics.h"
#include "jFileManager.h"
#include "jInputHandler.h"
#include "jVariables.h"
#include "jGameLogic.h"
#include "jGenerateWorld.h"
#include "jPlayer.h"

int main() {
    GameObject go;
    std::cout << go.getHealth() << std::endl;

    jLogicWorld = jWorldA;
    jRenderWorld.store(jWorldB);

    jgw::jGenerateWorld();

    std::memcpy(jWorldB, jWorldA, WORLD_SIZE);

    JPlayer * jpl = new JPlayer;

    JGraphics jg(WINDOW_WIDTH, WINDOW_HEIGHT, jpl);
    jg.init("simple terraria");

    JInputHandler ji;
    JGameLogic jgl;

    std::thread glt(&JGameLogic::startGameLogic, &jgl, jpl);

    while (jg.isOpen()) {
        ji.runInput();
        jg.doGraphics();
    }

    jRunning = false;
    glt.join();

    return 0;
}