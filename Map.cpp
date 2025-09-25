#include "Map.h"
#include <fstream>
#include <iostream>

Map::Map(const std::string& filename, int tileSize) : tileSize(tileSize), player(nullptr) {
    if (!wallTexture.loadFromFile("D:\\PBL2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\wall.png")) {
        std::cerr << "Failed to load wall texture!" << std::endl;
    }
    if (!floorTexture.loadFromFile("D:\\PBL2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\floor.png")) {
        std::cerr << "Failed to load floor texture!" << std::endl;
    }
    if (!boxTexture.loadFromFile("D:\\PBL2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\box.png")) {
        std::cerr << "Failed to load box texture!" << std::endl;
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Khong the mo file map: " << filename << std::endl;
        return;
    }

    std::string line;
    int y = 0;
    while (std::getline(file, line)) {
        for (int x = 0; x < (int)line.size(); x++) {
            char c = line[x];
            if (c == '#') {
                walls.emplace_back(x, y, tileSize);
                walls.back().setTexture(wallTexture);
            }
            else if (c == '@') {
                player = new Player(x, y, tileSize);
                if (!player->loadAnimations()) {
                    std::cerr << "Failed to load player animations!" << std::endl;
                }
            }
            else if (c == '$') {
                boxes.emplace_back(x, y, tileSize);
                boxes.back().setTexture(boxTexture);
            }
            else if (c == '.' || c == ' ') {
                floors.emplace_back(x, y, tileSize);
                floors.back().setTexture(floorTexture);
            }
        }
        y++;
    }
    file.close();
}

Map::~Map() {
    delete player;
}

void Map::update() {
    if (player) {
        player->update();
    }
    else {
        std::cerr << "Error: Player is null" << std::endl;
    }
    for (auto& box : boxes) {
        box.update();
    }
}

void Map::draw(sf::RenderWindow& window) {
    if (player) {
        sf::View view = window.getView();
        sf::Vector2f playerPos(player->getX() * tileSize + tileSize / 2, player->getY() * tileSize + tileSize / 2);
        view.setCenter(playerPos);
        window.setView(view);
    }
    for (auto& floor : floors) {
        floor.draw(window);
    }
    for (auto& wall : walls) {
        wall.draw(window);
    }
    for (auto& box : boxes) {
        box.draw(window);
    }
    if (player) {
        player->draw(window);
    }
}

Player* Map::getPlayer() {
    return player;
}