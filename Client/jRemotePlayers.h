#pragma once

#include <vector>
#include "jRemotePlayer.h"

extern std::vector<RemotePlayer> remotePlayers;

void updateRemotePlayer(int id, uint32_t x, uint32_t y, uint32_t health);
void removeRemotePlayer(int id);