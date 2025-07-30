// Copyright 2025 Danny Nguyen

#include "Sokoban.hpp"
#include <fstream>

namespace SB {
Sokoban::Sokoban() {
    // Initialize default values or leave them as is
    S_width = 0;
    S_height = 0;
    S_playerLocation = sf::Vector2u(0, 0);  // Assuming default player location
}
Sokoban::Sokoban(const std::string& filename) {
    loadLevel(filename);
    loadTextures();
}
void Sokoban::loadTextures() {
    // Load textures into the map
    S_textures['@'] = std::make_pair(sf::Texture(), sf::Texture());
    S_textures['@'].first.loadFromFile("sokoban/ground_01.png");
    S_textures['@'].second.loadFromFile("sokoban/player_05.png");

    S_textures['.'] = std::make_pair(sf::Texture(), sf::Texture());
    S_textures['.'].first.loadFromFile("sokoban/ground_01.png");  // Ground

    S_textures['#'] = std::make_pair(sf::Texture(), sf::Texture());
    S_textures['#'].first.loadFromFile("sokoban/block_06.png");  // Wall

    S_textures['A'] = std::make_pair(sf::Texture(), sf::Texture());
    S_textures['A'].first.loadFromFile("sokoban/ground_01.png");
    S_textures['A'].second.loadFromFile("sokoban/crate_03.png");  // Crate

    S_textures['a'] = std::make_pair(sf::Texture(), sf::Texture());
    S_textures['a'].first.loadFromFile("sokoban/ground_04.png");  // Destination

    S_textures['1'] = std::make_pair(sf::Texture(), sf::Texture());
    S_textures['1'].first.loadFromFile("sokoban/ground_04.png");
    S_textures['1'].second.loadFromFile("sokoban/crate_03.png");  // Box in storage

    S_textures['2'] = std::make_pair(sf::Texture(), sf::Texture());
    S_textures['2'].first.loadFromFile("sokoban/ground_04.png");
    S_textures['2'].second.loadFromFile("sokoban/player_05.png");  // Player on storage
}
unsigned int Sokoban::pixelHeight() const {
    return S_height * TILE_SIZE;
}

unsigned int Sokoban::pixelWidth() const {
    return S_width * TILE_SIZE;
}

unsigned int Sokoban::height() const {
    return S_height;
}

unsigned int Sokoban::width() const {
    return S_width;
}

sf::Vector2u Sokoban::playerLoc() const {
    return S_playerLocation;
}

bool Sokoban::isWon() const {
    for (unsigned i = 0; i < S_height; ++i) {
        for (unsigned j = 0; j < S_width; ++j) {
            char tile = S_grid[i][j];
            if (tile == 'a' || tile == 'A') {
                return false;  // Still an unmatched storage or crate
            }
        }
    }
    return true;
}



void Sokoban::movePlayer(Direction dir) {
    auto dst = S_playerLocation;

    // Apply movement direction
    auto applyMovement = [&](sf::Vector2u& pos) {
      switch (dir) {
          case Direction::Up: {
              if (pos.y == 0) return;
              --pos.y;
              break;
          }
          case Direction::Down: {
              ++pos.y;
              break;
          }
          case Direction::Left: {
              if (pos.x == 0) return;
              --pos.x;
              break;
          }
          case Direction::Right: {
              ++pos.x;
              break;
          }
      }
    };


    applyMovement(dst);

    // Bounds check
    if (dst.x >= S_width || dst.y >= S_height) return;

    char targetTile = S_grid[dst.y][dst.x];

    // Lambda to check movable ground or storage
    auto isEmptyOrStorage = [](char c) { return c == '.' || c == 'a'; };

    // Case 1: move into empty space or storage
    if (isEmptyOrStorage(targetTile)) {
        // Restore current tile
        char& currTile = S_grid[S_playerLocation.y][S_playerLocation.x];
        currTile = (currTile == '2') ? 'a' : '.';

        // Update player position
        S_playerLocation = dst;
        S_grid[dst.y][dst.x] = (targetTile == 'a') ? '2' : '@';
        return;
    }

    // Case 2: try to push a crate ('A' or '1')
    if (targetTile == 'A' || targetTile == '1') {
        auto boxDst = dst;
        applyMovement(boxDst);

        if (boxDst.x >= S_width || boxDst.y >= S_height) return;

        char beyondTile = S_grid[boxDst.y][boxDst.x];

        if (!isEmptyOrStorage(beyondTile)) return;  // can't push into wall, crate, player

        // Push the crate
        S_grid[boxDst.y][boxDst.x] = (beyondTile == 'a') ? '1' : 'A';
        S_grid[dst.y][dst.x] = (targetTile == '1') ? 'a' : '.';

        // Move player
        char& currTile = S_grid[S_playerLocation.y][S_playerLocation.x];
        currTile = (currTile == '2') ? 'a' : '.';
        S_playerLocation = dst;
        S_grid[dst.y][dst.x] = (targetTile == '1' || targetTile == 'a') ? '2' : '@';
    }
}



void Sokoban::reset() {
    loadLevel(lastLoadedFilename);  // Reset to the last loaded filename
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (unsigned int i = 0; i < S_height; ++i) {
        for (unsigned int j = 0; j < S_width; ++j) {
            char tile = S_grid[i][j];
            float xPos = static_cast<float>(j * TILE_SIZE);
            float yPos = static_cast<float>(i * TILE_SIZE);

            // Skip unknown tiles
            if (S_textures.find(tile) == S_textures.end())
                continue;

            const auto& [groundTex, overlayTex] = S_textures.at(tile);

            // Draw ground
            sf::Sprite ground(groundTex);
            ground.setPosition(xPos, yPos);
            target.draw(ground, states);

            // Draw overlay if needed
            if (tile == '@' || tile == '2' || tile == 'A' || tile == '1') {
                sf::Sprite overlay(overlayTex);
                overlay.setPosition(xPos, yPos);
                target.draw(overlay, states);
            }
        }
    }
}


std::ostream& operator<<(std::ostream& out, const Sokoban& g) {
    out << g.S_height << ' ' << g.S_width << '\n';
    for (const auto& row : g.S_grid) {
        for (char tile : row) {
            out << tile;
        }
        out << '\n';
    }
    return out;
}

std::istream& operator>>(std::istream& in, Sokoban& g) {
    in >> g.S_height >> g.S_width;
    g.S_grid.resize(g.S_height, std::vector<char>(g.S_width, ' '));

    const std::string valid = "#.@aA12";

    for (unsigned int y = 0; y < g.S_height; ++y) {
        for (unsigned int x = 0; x < g.S_width; ++x) {
            in >> g.S_grid[y][x];
            char c = g.S_grid[y][x];

            if (valid.find(c) == std::string::npos) {
                std::cerr << "Invalid tile '" << c << "' at (" << x << ", " << y << ")\n";
                g.S_grid[y][x] = '.';  // Replace with safe default
            }

            if (c == '@' || c == '2') {
                g.S_playerLocation = sf::Vector2u(x, y);
            }
        }
    }
    return in;
}

void Sokoban::printGrid() const {
    for (unsigned int i = 0; i < S_height; ++i) {
        for (unsigned int j = 0; j < S_width; ++j) {
            std::cout << S_grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
void Sokoban::loadLevel(const std::string& filename) {
    std::ifstream file(filename);
    if (file) {
        file >> *this;
    } else {
        std::cerr << "Failed to open level file: " << filename << std::endl;
    }
    lastLoadedFilename = filename;
}

}  // namespace SB

