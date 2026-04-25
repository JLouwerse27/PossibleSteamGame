#include "jNetworkClient.h"
#include "jVariables.h"
#include "jRemotePlayers.h"
#include <iostream>

int myId = -1;

bool JNetworkClient::connectToServer(const std::string& ip, unsigned short port) {
    std::cout << "Trying to connect to " << ip << ":" << port << "\n";

    auto address = sf::IpAddress::resolve(ip);

    if (!address) {
        std::cout << "Could not resolve IP\n";
        connected = false;
        return false;
    }

    sf::Socket::Status status = socket.connect(*address, port);

    if (status == sf::Socket::Status::Done) {
        socket.setBlocking(false);
        connected = true;
        std::cout << "Connected to server\n";
        return true;
    }

    std::cout << "Connect failed. Status = " << static_cast<int>(status) << "\n";
    connected = false;
    return false;
}

void JNetworkClient::sendPlaceBlock(int x, int y, unsigned char blockType) {
    if (!connected) {
        return;
    }

    sf::Packet packet;
    packet << std::string("PLACE_BLOCK");
    packet << x;
    packet << y;
    packet << static_cast<int>(blockType);

    socket.send(packet);
}

void JNetworkClient::sendMovePlayer(uint32_t x, uint32_t y) {
    if (!connected) return;

    sf::Packet packet;

    packet << std::string("MOVE_PLAYER");
    packet << static_cast<int>(x);
    packet << static_cast<int>(y);

    socket.send(packet);
}


void JNetworkClient::receiveUpdates() {
    if (!connected) return;

    while (true) {
        sf::Packet packet;
        auto status = socket.receive(packet);

        if (status == sf::Socket::Status::Done) {
            std::string command;
            packet >> command;

            if (command == "FULL_WORLD") {
                for (int i = 0; i < WORLD_SIZE; i++) {
                    int value;
                    packet >> value;
                    jWorldA[i] = (unsigned char)value;
                    jWorldB[i] = jWorldA[i];
                }
                std::cout << "Received FULL_WORLD\n";
            }
            else if (command == "PLAYER_UPDATE") {
                int id, x, y, health;
                packet >> id >> x >> y >> health;

                updateRemotePlayer(id, x, y, health);
            }
            else if (command == "YOUR_ID") {
                packet >> myId;
            }
        }
        else if (status == sf::Socket::Status::NotReady) {
            break; // nothing left
        }
        else {
            break;
        }
    }
}


bool JNetworkClient::isConnected() const {
    return connected;
}

void JNetworkClient::setPlayer(JPlayer* jpl) {
    this->jpl = jpl;
}