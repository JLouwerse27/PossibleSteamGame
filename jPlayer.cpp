#include "jPlayer.h"

JPlayer::JPlayer() {
	jPX = WORLD_WIDTH / 2;
	jPY = jDirtLevel;
}
std::atomic<uint32_t> JPlayer::getX() {
	return jPX.load();
}
std::atomic<uint32_t> JPlayer::getY() {
	return jPY.load();
}
std::atomic<uint32_t> JPlayer::getH() {
	return jPH.load();
}
void JPlayer::setX(std::atomic<uint32_t> x) {
	jPX.store(x);
}
void JPlayer::setY(std::atomic<uint32_t> y) {
	jPY.store(y);
}