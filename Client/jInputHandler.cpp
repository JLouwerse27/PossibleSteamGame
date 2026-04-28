#include "jInputHandler.h"
#include <SFML/Window.hpp>
#include <iostream>
#include "jVariables.h"


JInputHandler::JInputHandler() {

}

void JInputHandler::runInput(JGraphics& jc) {

	for (int i = 0; i < sizeof(jIsMousePressed) / sizeof(bool); i++) {
		jIsMousePressed[i] = false;
	}

	if (sf::Mouse::getPosition(jc.getWindow()).x >= 0 && sf::Mouse::getPosition(jc.getWindow()).x < WINDOW_WIDTH) {
		mouseX = sf::Mouse::getPosition(jc.getWindow()).x;
	}
	if (sf::Mouse::getPosition(jc.getWindow()).y >= 0 && sf::Mouse::getPosition(jc.getWindow()).y < WINDOW_HEIGHT) {
		mouseY = sf::Mouse::getPosition(jc.getWindow()).y;
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		jIsMousePressed[0] = true;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		jIsMousePressed[1] = true;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)) {
		jIsMousePressed[2] = true;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Extra1)) {
		jIsMousePressed[3] = true;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Extra2)) {
		jIsMousePressed[4] = true;
	}

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