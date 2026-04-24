#include "jNetworkClient.h"
#include "jVariables.h"

#include <iostream>

bool JNetworkClient::connectToServer(const std::string& ip, unsigned short port) {
    auto address = sf::IpAddress::resolve(ip);

    if (!address) {
        return false;
    }

    if (socket.connect(*address, port) == sf::Socket::Status::Done) {
        socket.setBlocking(false);
        connected = true;
        return true;
    }

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

void JNetworkClient::receiveUpdates() {
    if (!connected) {
        return;
    }

    while (true) {
        sf::Packet packet;
        sf::Socket::Status status = socket.receive(packet);

        if (status == sf::Socket::Status::Done) {
            std::string command;
            packet >> command;

            if (command == "FULL_WORLD") {
                for (int i = 0; i < WORLD_SIZE; i++) {
                    int value;
                    packet >> value;
                    jWorldA[i] = static_cast<unsigned char>(value);
                    jWorldB[i] = jWorldA[i];
                }
            }
        }
        else if (status == sf::Socket::Status::NotReady) {
            break;
        }
        else if (status == sf::Socket::Status::Disconnected) {
            std::cout << "Disconnected from server\n";
            connected = false;
            break;
        }
        else {
            break;
        }
    }
}

bool JNetworkClient::isConnected() const {
    return connected;
}