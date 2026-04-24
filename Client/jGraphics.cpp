#include "jGraphics.h"

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
    jRect.setPosition(sf::Vector2f( ((jpl->getX())-jX)*jBlockSize, ((jpl->getY())-jY)*jBlockSize));
    rw.draw(jRect);

    rw.display();
}

bool JGraphics::isOpen() const {
    return rw.isOpen();
}