#pragma once
#include "GameObject.h"
#include "jVariables.h"
#include <atomic>

class JPlayer : public GameObject {
private:
	std::atomic<uint32_t> jPX, jPY;
	const std::atomic<uint32_t> jPH = 1;
public:
	JPlayer();
	std::atomic<uint32_t> getX();
	std::atomic<uint32_t> getY();
	std::atomic<uint32_t> getH();
	void setX(std::atomic<uint32_t> x);
	void setY(std::atomic<uint32_t> y);
};