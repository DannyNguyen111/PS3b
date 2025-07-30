// Copyright 2025 Danny Nguyen
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sokoban.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = "sokoban/" + std::string(argv[1]);

    SB::Sokoban game(filename);
    int moveCount = 0;
    sf::RenderWindow window(sf::VideoMode(game.pixelWidth(), game.pixelHeight()), "Sokoban");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (!game.isWon()) {
                    switch (event.key.code) {
                        case sf::Keyboard::W:
                        case sf::Keyboard::Up:
                            game.movePlayer(SB::Direction::Up);
                            moveCount++;
                            break;
                        case sf::Keyboard::S:
                        case sf::Keyboard::Down:
                            game.movePlayer(SB::Direction::Down);
                            moveCount++;
                            break;
                        case sf::Keyboard::A:
                        case sf::Keyboard::Left:
                            game.movePlayer(SB::Direction::Left);
                            moveCount++;
                            break;
                        case sf::Keyboard::D:
                        case sf::Keyboard::Right:
                            game.movePlayer(SB::Direction::Right);
                            moveCount++;
                            break;
                        case sf::Keyboard::R:
                            game.reset();
                            moveCount = 0;
                            break;
                        default:
                            break;
                    }
                } else {
                    if (event.key.code == sf::Keyboard::R) {
                        game.reset();
                    }
                }
                game.printGrid();
            }
        }

        window.clear();
        window.draw(game);
        if (game.isWon()) {
          sf::Font font;
          if (!font.loadFromFile("sokoban/Movistar Text Regular.ttf")) {
            std::cerr << "Failed to load font." << std::endl;
          } else {
            sf::Text winText;
            winText.setFont(font);
            winText.setString("Congratulations! You won in " + std::to_string(moveCount) +
            " moves!\nPress 'R' to restart.");
            winText.setCharacterSize(24);
            winText.setFillColor(sf::Color::White);
            winText.setPosition(100.f, 100.f);
            window.draw(winText);
          }
        }

        window.display();
    }

    return 0;
}
