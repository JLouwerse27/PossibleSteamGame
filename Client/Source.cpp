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
bool singleplayer = false;

void askForSingleplayer();
void continueStuff();

int main() {

    jLogicWorld = jWorldA;
    jRenderWorld.store(jWorldB);


    askForSingleplayer();

    continueStuff();

    /*while (jg.isOpen()) {
        ji.runInput(jg);
        jgl.runGameLogic(jpl);
        net.sendMovePlayer(jpl->x, jpl->y);
        net.receiveUpdates();
        jg.doGraphics();
        std::this_thread::sleep_for(std::chrono::milliseconds(4));
    }*/

    jRunning = false;
    //glt.join();

    return 0;
}

void askForSingleplayer() {
    std::string input;
    while (true) {
        std::cout << "Singleplayer? (y/n): ";
        std::cin >> input;
        if (input == "y" || input == "Y") {
            singleplayer = true;
            break;
        }
        else if (input == "n" || input == "N") {
            singleplayer = false;
            break;
        }
        else {
            std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
        }
    }
}

void continueStuff() {
    if (!singleplayer) {
        JNetworkClient net;
        std::string ip;
        std::cout << "Enter server IP: ";
        std::cin >> ip;
        net.connectToServer(ip, 5000);

        //net.connectToServer("10.37.15.150", 5000);

        if (!net.isConnected()) {
            askForSingleplayer();
            return;
        }

        JPlayer* jpl = new JPlayer;
        jpl->x = (WORLD_WIDTH / 2) * jBlockWidth;
        jpl->y = (jDirtLevel - 1) * jBlockWidth;
        jpl->health = 30;
        jpl->id = -1;


        net.setPlayer(jpl);

        JGraphics jg(WINDOW_WIDTH, WINDOW_HEIGHT, jpl);
        jg.init("simple terraria: multiplayer client");

        JInputHandler ji;
        JGameLogic jgl;

        //std::thread glt(&JGameLogic::startGameLogic, &jgl, jpl);

        sf::Clock clock;
        float accumulator = 0.0f;
        const float dt = 1.0f / 120.0f;

        while (jg.isOpen()) {
            float frameTime = clock.restart().asSeconds();
            accumulator += frameTime;



            while (accumulator >= dt) {
                ji.runInput(jg);
                jgl.runGameLogic(jpl);
                accumulator -= dt;
            }

            jg.doGraphics();
            net.sendMovePlayer(jpl->x, jpl->y);
            net.receiveUpdates();


        }
    }
    else {
        JPlayer* jpl = new JPlayer;
        jpl->x = (WORLD_WIDTH / 2) * jBlockWidth;
        jpl->y = (jDirtLevel - 1) * jBlockWidth;
        jpl->health = 30;
        jpl->id = -1;

        JGraphics jg(WINDOW_WIDTH, WINDOW_HEIGHT, jpl);
        jg.init("simple terraria: singleplayer client");

        JInputHandler ji;
        JGameLogic jgl;

		jgw::jGenerateWorld();

        //std::thread glt(&JGameLogic::startGameLogic, &jgl, jpl);

        sf::Clock clock;
        float accumulator = 0.0f;
        const float dt = 1.0f / 120.0f;

        while (jg.isOpen()) {
            float frameTime = clock.restart().asSeconds();
            accumulator += frameTime;
            while (accumulator >= dt) {
                ji.runInput(jg);
                jgl.runGameLogic(jpl);
                accumulator -= dt;
            }
            jg.doGraphics();
        }
    }
}