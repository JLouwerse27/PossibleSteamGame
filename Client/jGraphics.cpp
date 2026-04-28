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
    jRect.setSize(sf::Vector2f(jBlockWidth, jBlockHeight));
    jRect.setFillColor(sf::Color::Magenta);
}

void JGraphics::doGraphics() {
    while (const std::optional event = rw.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            rw.close();
        }
        if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            WINDOW_WIDTH = resized->size.x;
            WINDOW_HEIGHT = resized->size.y;

            //jBlockWidth = WINDOW_WIDTH / jXBlocksInCameraView;
            //jBlockHeight = WINDOW_HEIGHT / jYBlocksInCameraView;

            //jXBlocksInCameraView = WINDOW_WIDTH / jBlockWidth;
            //jYBlocksInCameraView = WINDOW_HEIGHT / jBlockHeight;
            std::cout << "resized to " << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << "\n";
            std::cout << "blocksize " << jBlockWidth << "," << jBlockHeight << " camerablock width " << jXBlocksInCameraView << " camerablock height " << jYBlocksInCameraView << "\n";
        }
    }

    unsigned char* localWorld = jRenderWorld.load();

    if (localWorld == nullptr) {
        return;
    }

    rw.clear();

    uint32_t camX = jX.load();
    uint32_t camY = jY.load();
    jRect.setSize(sf::Vector2f(jBlockWidth, jBlockHeight));

    for (int i = camY; i < camY + jYBlocksInCameraView + 1 && i < WORLD_HEIGHT; i++) {
        for (int j = camX; j < camX + jXBlocksInCameraView + 1 && j < WORLD_WIDTH; j++) {
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

			//int xPos = (j - camX) * jBlockWidth;//"blocky" camera, not pixel camera
            //int yPos = (i - camY) * jBlockHeight;
            int xPos = (j + jXBlocksInCameraView / 2) * jBlockWidth - jpl->x;
            int yPos = (i + jYBlocksInCameraView / 2) * jBlockHeight - jpl->y;

            jRect.setFillColor(blockColour);
            jRect.setPosition(sf::Vector2f(xPos, yPos));

            rw.draw(jRect);
        }
    }

    jRect.setFillColor(sf::Color(180, 90, 50));
    jRect.setPosition(sf::Vector2f((jXBlocksInCameraView / 2 * jBlockWidth), (jYBlocksInCameraView / 2 * jBlockHeight)));
    //jRect.setPosition(sf::Vector2f(((jpl->x)), ((jpl->y))));
    //jRect.setPosition(sf::Vector2f(((jpl->x) - (jXBlocksInCameraView / 2 * jBlockWidth)), ((jpl->y) - (jYBlocksInCameraView / 2 * jBlockHeight))));
    //jRect.setPosition(sf::Vector2f(((jpl->x) - jX * jBlockWidth), ((jpl->y) - jY * jBlockHeight)));
    float rx = jRect.getPosition().x;
    float ry = jRect.getPosition().y;
    if (rx < 0 || rx >(jXBlocksInCameraView) * jBlockWidth ||
        ry < 0 || ry >(jYBlocksInCameraView) * jBlockHeight) {
        std::cout << "player rectangle out of screen " << rx << " " << ry << "\n";
    }
    rw.draw(jRect);

    drawOtherPlayers(camX, camY);

    rw.display();
}

void JGraphics::drawOtherPlayers(uint32_t camX, uint32_t camY) {
    for (const RemotePlayer& p : remotePlayers) {
        // draw 
        if (p.x/jBlockWidth >= camX && p.x / jBlockWidth <= camX + jXBlocksInCameraView) {
            if (p.y / jBlockHeight >= camY && p.y / jBlockHeight <= camY + jYBlocksInCameraView) {
                jRect.setFillColor(sf::Color(30, 30, 200));
                jRect.setPosition(sf::Vector2f((p.x - jX * jBlockWidth), (p.y - jY * jBlockHeight)));
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