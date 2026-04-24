#include <iostream>
#include <string>
#include <thread>
#include <cstring>

#include "GameObject.h"
#include "jGraphics.h"
#include "jInputHandler.h"
#include "jVariables.h"
#include "jClientLogic.h"
#include "jClientWorldGeneration.h"
#include "jPlayer.h"
#include "jNetworkClient.h"


int main() {
    GameObject go;
    std::cout << go.getHealth() << std::endl;

    jLogicWorld = jWorldA;
    jRenderWorld.store(jWorldB);

    JNetworkClient net;
    net.connectToServer("127.0.0.1", 5000);

    //if (!net.isConnected()) {
    //    jgw::jGenerateWorld();
    //    std::memcpy(jWorldB, jWorldA, WORLD_SIZE);
    //}

    JPlayer * jpl = new JPlayer;

    JGraphics jg(WINDOW_WIDTH, WINDOW_HEIGHT, jpl);
    jg.init("simple terraria: multiplayer client");

    JInputHandler ji;
    JGameLogic jgl;

    std::thread glt(&JGameLogic::startGameLogic, &jgl, jpl);

    while (jg.isOpen()) {
        ji.runInput();
        net.receiveUpdates();
        jg.doGraphics();
    }

    jRunning = false;
    glt.join();

    return 0;
}


//    JInputHandler ji;
//
//    while (jg.isOpen()) {
//        ji.runInput();
//        jgl::updateGameLogic();
//        
//        jg.doGraphics();
//    }
//
//    jRunning = false;
//    return 0;
//}