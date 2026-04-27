#include "jGraphics.h"
#include "jRemotePlayers.h"
#include <iostream>
#include <string>
#include <optional>

JGraphics::JGraphics(uint32_t w, uint32_t h, JPlayer * jpl) : WIDTH(w), HEIGHT(h), jpl(jpl) {

}

void JGraphics::init(std::string title) {
    rw.create(sf::VideoMode(sf::Vector2u(WIDTH, HEIGHT)), title);
    rw.setVerticalSyncEnabled(true);

    jRect.setPosition(sf::Vector2f(0, 0));
    jRect.setSize(sf::Vector2f(jBlockSize, jBlockSize));
    jRect.setFillColor(sf::Color::Magenta);
}

void JGraphics::doGraphics() {
    while (const std::optional event = rw.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            rw.close();
        }
    }

    unsigned char* localWorld = jRenderWorld.load();

    if (localWorld == nullptr) {
        return;
    }

    rw.clear();

    uint32_t camX = jX.load();
    uint32_t camY = jY.load();

    for (int i = camY; i < camY + jYBlocksInCameraView && i < WORLD_HEIGHT; i++) {
        for (int j = camX; j < camX + jXBlocksInCameraView && j < WORLD_WIDTH; j++) {
            unsigned char block = localWorld[i * WORLD_WIDTH + j];

            sf::Color blockColour = sf::Color::Magenta;

            if (block == 0) {
                blockColour = sf::Color(10, 90, 240);
            }
            else if (block == 1) {
                blockColour = sf::Color(80, 30, 20);
            }
            else if (block == 2) {
                //blockColour = sf::Color::White;
            }
            else if (block == 3) {
                blockColour = sf::Color(60, 30, 20);
            }
            else if (block == 4) {
                blockColour = sf::Color::White;
            }

            int xPos = (j - camX) * jBlockSize;
            int yPos = (i - camY) * jBlockSize;

            jRect.setFillColor(blockColour);
            jRect.setPosition(sf::Vector2f(xPos, yPos));

            rw.draw(jRect);
        }
    }

    jRect.setFillColor(sf::Color(180, 90, 50));
    jRect.setPosition(sf::Vector2f(((jpl->x)-jX)*jBlockSize, ((jpl->y)-jY)*jBlockSize));
    float rx = jRect.getPosition().x;
    float ry = jRect.getPosition().y;
    if (rx < 0 || rx >(jXBlocksInCameraView)*jBlockSize ||
        ry < 0 || ry >(jYBlocksInCameraView) * jBlockSize) {
        std::cout << "player rectangle out of screen " << rx << " " << ry << "\n";
    }
    rw.draw(jRect);

    drawOtherPlayers(camX, camY);

    rw.display();
}

void JGraphics::drawOtherPlayers(uint32_t camX, uint32_t camY) {
    for (const RemotePlayer& p : remotePlayers) {
        // draw 
        if (p.x >= camX && p.x <= camX + jXBlocksInCameraView) {
            if (p.y >= camY && p.y <= camY + jYBlocksInCameraView) {
                jRect.setFillColor(sf::Color(30, 30, 200));
                jRect.setPosition(sf::Vector2f((p.x-jX) * jBlockSize, (p.y-jY) * jBlockSize));
                rw.draw(jRect);
            }
        }
    }
}


bool JGraphics::isOpen() const {
    return rw.isOpen();
}

sf::RenderWindow& JGraphics::getWindow() {
    return rw;
}