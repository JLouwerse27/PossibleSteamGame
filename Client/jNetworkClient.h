#pragma once

#include <SFML/Network.hpp>
#include <string>
#include "jPlayer.h"

class JNetworkClient {
private:
    sf::TcpSocket socket;
    bool connected = false;
    JPlayer* jpl;
public:
    bool connectToServer(const std::string& ip, unsigned short port);
    void sendPlaceBlock(int x, int y, unsigned char blockType);
    void sendMovePlayer(uint32_t x, uint32_t y);
    void receiveUpdates();
    bool isConnected() const;
    void setPlayer(JPlayer* jpl);
};