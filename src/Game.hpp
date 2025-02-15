#pragma once

#include <array>
#include <SFML/Graphics.hpp>

constexpr int numCols{ 10 };
constexpr int numRows{ 20 };

using Board = std::array<std::array<sf::Color, numCols>, numRows>;

class Game {
    Board m_board;

public:
    Game() {

    }

    void movePieceDown() {

    }

};
