#include "jInputHandler.h"
#include <SFML/Window.hpp>
#include <iostream>
#include "jVariables.h"


JInputHandler::JInputHandler() {

}

void JInputHandler::runInput(JGraphics& jc) {

	/*while (const std::optional event = jc.getWindow().pollEvent()) {

		if (const auto* resized = event->getIf<sf::Event::Resized>()) {
			WINDOW_WIDTH = resized->size.x;
			WINDOW_HEIGHT = resized->size.y;
			jXBlocksInCameraView = WINDOW_WIDTH / jBlockSize;
			jYBlocksInCameraView = WINDOW_HEIGHT / jBlockSize;
		}
	}*/

	jNextTurn = false;
	for (int i = 0; i < sizeof(jIsKeyPressed) / sizeof(bool); i++) {
		jIsKeyPressed[i] = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
		jIsKeyPressed[0] = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
		jIsKeyPressed[1] = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
		jIsKeyPressed[2] = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
		jIsKeyPressed[3] = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Tab)) {
		jIsKeyPressed[6] = true;
		if (jEditing) {
			jEditing = false;
		}
		else {
			jEditing = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Period)) {
		jIsKeyPressed[7] = true;
		jNextTurn = true;
	}
}