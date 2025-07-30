// Copyright 2025 Danny Nguyen
#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

namespace SB {
enum class Direction {
    Up, Down, Left, Right
};

class Sokoban : public sf::Drawable {
 public:
    static const int TILE_SIZE = 64;

    Sokoban();
    explicit Sokoban(const std::string& filename);

    unsigned int pixelHeight() const;
    unsigned int pixelWidth() const;

    unsigned int height() const;
    unsigned int width() const;

    sf::Vector2u playerLoc() const;
    bool isWon() const;

    void movePlayer(Direction dir);
    void reset();
    void printGrid() const;
    const std::vector<std::vector<char>>& getGrid() const { return S_grid; }

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    unsigned int S_width = 0;
    unsigned int S_height = 0;
    std::vector<std::vector<char>> S_grid;  // To store the game grid
    sf::Vector2u S_playerLocation;
    std::unordered_map<char, std::pair<sf::Texture, sf::Texture>> S_textures;  // Map for textures
    void loadLevel(const std::string& filename);
    std::string lastLoadedFilename;
    void loadTextures();
    friend std::ostream& operator<<(std::ostream& out, const Sokoban& s);
    friend std::istream& operator>>(std::istream& in, Sokoban& s);
};

std::ostream& operator<<(std::ostream& out, const Sokoban& s);
std::istream& operator>>(std::istream& in, Sokoban& s);
}  // namespace SB
