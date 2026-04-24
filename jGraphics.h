#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "jVariables.h"
#include "jPlayer.h"
class JGraphics {
private:
	sf::RenderWindow rw;
	sf::RectangleShape jRect;
	JPlayer* jpl;
public:
	const uint32_t WIDTH, HEIGHT;
	JGraphics(uint32_t w, uint32_t h, JPlayer * jpl);
	void init(std::string title);
	void doGraphics();
	bool isOpen() const;
};