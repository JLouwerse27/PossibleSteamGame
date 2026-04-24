#pragma once
#include "jVariables.h"
#include "jPlayer.h"
class JGameLogic {
private:
	void applyGravity();
public:
	void startGameLogic(JPlayer* jpl);
};