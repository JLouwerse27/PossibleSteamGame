#include <SFML/Network.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "jServerVariables.h"
#include "jServerWorldGeneration.h"

const unsigned short PORT = 5000;

//const int WORLD_WIDTH = 400;
//const int WORLD_HEIGHT = 300;
//const int WORLD_SIZE = WORLD_WIDTH * WORLD_HEIGHT;

using Block = unsigned char;
//
//Block world[WORLD_SIZE] = {};

struct Client {
    sf::TcpSocket* socket;
};

std::vector<Client> clients;

void sendFullWorld(sf::TcpSocket& socket) {
    sf::Packet packet;

    packet << std::string("FULL_WORLD");

    for (int i = 0; i < WORLD_SIZE; i++) {
        packet << static_cast<int>(world[i]);
    }

    socket.send(packet);
}

void sendBlockUpdate(sf::TcpSocket& socket, int x, int y, Block blockType) {
    sf::Packet packet;

    packet << std::string("BLOCK_UPDATE");
    packet << x;
    packet << y;
    packet << static_cast<int>(blockType);

    socket.send(packet);
}

void broadcastBlockUpdate(int x, int y, Block blockType) {
    for (Client& client : clients) {
        sendBlockUpdate(*client.socket, x, y, blockType);
    }
}

int main() {
    jgw::jGenerateWorld();

    sf::TcpListener listener;

    if (listener.listen(PORT) != sf::Socket::Status::Done) {
        std::cout << "Failed to listen on port " << PORT << "\n";
        return 1;
    }

    listener.setBlocking(false);

    std::cout << "Server running on port " << PORT << "\n";

    while (true) {
        sf::TcpSocket* newClient = new sf::TcpSocket;
        newClient->setBlocking(false);

        if (listener.accept(*newClient) == sf::Socket::Status::Done) {
            std::cout << "Client connected\n";

            clients.push_back({ newClient });

            sendFullWorld(*newClient);
        }
        else {
            delete newClient;
        }

        for (int i = 0; i < static_cast<int>(clients.size()); i++) {
            sf::Packet packet;
            sf::Socket::Status status = clients[i].socket->receive(packet);

            if (status == sf::Socket::Status::Done) {
                std::string command;
                packet >> command;

                if (command == "PLACE_BLOCK") {
                    int x;
                    int y;
                    int blockInt;

                    packet >> x >> y >> blockInt;

                    if (x >= 0 && x < WORLD_WIDTH &&
                        y >= 0 && y < WORLD_HEIGHT) {

                        Block blockType = static_cast<Block>(blockInt);

                        world[y * WORLD_WIDTH + x] = blockType;

                        broadcastBlockUpdate(x, y, blockType);
                    }
                }
            }
            else if (status == sf::Socket::Status::Disconnected) {
                std::cout << "Client disconnected\n";

                delete clients[i].socket;
                clients.erase(clients.begin() + i);
                i--;
            }
        }

        sf::sleep(sf::milliseconds(1));
    }

    return 0;
}