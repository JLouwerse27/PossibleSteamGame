#pragma once
#include "jVariables.h"
#include "jPlayer.h"
class JGameLogic {
private:
	int tick = 0;
	void applyGravity();
	bool inAir = false;
	int tickJumpStarted = -3000;
	int timeInAir = 25;
	bool atEdge[4] = { false, false, false, false };
	bool goingThisDirection[4] = { false, false, false, false };
	uint32_t speedMod = 8;
	uint32_t yIncrement = 1;
	bool isGoingUpNextTick = false;
	bool isGoingDownNextTick = false;
	bool isGoingLeftNextTick = false;
	bool isGoingRightNextTick = false;
public:
	void runGameLogic(JPlayer* jpl);
};