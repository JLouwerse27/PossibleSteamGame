#pragma once
#include "jVariables.h"
#include "jPlayer.h"
class JGameLogic {
private:
	uint32_t tick = 0;
	void applyGravity();
	bool inAir = false;
	uint32_t tickJumpStarted;
	uint32_t timeInAir = 10;
public:
	void runGameLogic(JPlayer* jpl);
};