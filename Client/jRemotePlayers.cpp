#include "jRemotePlayers.h"
#include <iostream>
#include <algorithm>

std::vector<RemotePlayer> remotePlayers;

void updateRemotePlayer(int id, uint32_t x, uint32_t y, uint32_t health) {
    for (RemotePlayer& p : remotePlayers) {
        if (p.id == id) {
            p.x = x;
            p.y = y;
            p.health = health;
            std::cout << "received other player: " << p.x << ", " << p.y << "\n";
            return;
        }
    }

    remotePlayers.push_back({ id, x, y, health });
}

void removeRemotePlayer(int id) {
    remotePlayers.erase(
        std::remove_if(
            remotePlayers.begin(),
            remotePlayers.end(),
            [id](const RemotePlayer& p) {
                return p.id == id;
            }
        ),
        remotePlayers.end()
    );
}