#pragma once

#include <SFML/Network.hpp>
#include <string>

class JNetworkClient {
private:
    sf::TcpSocket socket;
    bool connected = false;

public:
    bool connectToServer(const std::string& ip, unsigned short port);
    void sendPlaceBlock(int x, int y, unsigned char blockType);
    void receiveUpdates();
    bool isConnected() const;
};