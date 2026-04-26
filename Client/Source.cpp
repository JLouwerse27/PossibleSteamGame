#include <iostream>
#include <string>
#include <thread>
#include <cstring>

#include "jGraphics.h"
#include "jInputHandler.h"
#include "jVariables.h"
#include "jClientLogic.h"
#include "jClientWorldGeneration.h"
#include "jPlayer.h"
#include "jNetworkClient.h"


int main() {

    jLogicWorld = jWorldA;
    jRenderWorld.store(jWorldB);

    JNetworkClient net;
    std::string ip;
    std::cout << "Enter server IP: ";
    std::cin >> ip;
    net.connectToServer(ip, 5000);

    //net.connectToServer("10.37.15.150", 5000);

    //if (!net.isConnected()) {
    //    jgw::jGenerateWorld();
    //    std::memcpy(jWorldB, jWorldA, WORLD_SIZE);
    //}

    JPlayer * jpl = new JPlayer;
    jpl->x = WORLD_WIDTH / 2;
    jpl->y = jDirtLevel;
    jpl->health = 30;
    jpl->id = -1;


    net.setPlayer(jpl);

    JGraphics jg(WINDOW_WIDTH, WINDOW_HEIGHT, jpl);
    jg.init("simple terraria: multiplayer client");

    JInputHandler ji;
    JGameLogic jgl;

    //std::thread glt(&JGameLogic::startGameLogic, &jgl, jpl);

    while (jg.isOpen()) {
        ji.runInput();
        jgl.startGameLogic(jpl);
        net.sendMovePlayer(jpl->x, jpl->y);
        net.receiveUpdates();
        jg.doGraphics();
        std::this_thread::sleep_for(std::chrono::milliseconds(4));
    }

    jRunning = false;
    //glt.join();

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