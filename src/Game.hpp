#pragma once

#include "Piece.hpp"

#include <SFML/Graphics.hpp>

constexpr int squareSize{ 40 };

constexpr int numCols{ 10 };
constexpr int numRows{ 20 };

using Board = std::array<std::array<sf::Color, numCols>, numRows>;

class Game {
    Board m_board;
    const Piece::Piece* m_piece{ nullptr };
    std::pair<int, int> m_piecePos;
    sf::Color m_pieceColor;

    std::pair<int, int> getSpawnPos() {
        return { (numCols - m_piece->numSquares) / 2, 0 };
    }

    sf::Color getRandomColor() {
        return sf::Color::Red;
    }

    void setNewPiece() {
        m_piece = Piece::getRandomPiece();
        m_piecePos = getSpawnPos();
        m_pieceColor = getRandomColor();
    }

public:
    Game() {
        setNewPiece();
    }

    void movePieceDown() {
        m_piecePos.second++;
    }

    void movePieceLeft() {
        m_piecePos.first--;
    }

    void movePieceRight() {
        m_piecePos.first++;
    }

    void rotatePieceLeft() {

    }

    void rotatePieceRight() {

    }

    void displayBoard(sf::RenderWindow& window) {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                sf::Color sqColor{ m_board[i][j] };

                if (sqColor != sf::Color::Black) {
                    sf::RectangleShape square{ {squareSize, squareSize} };
                    square.setPosition({ (float)j * squareSize, (float)i * squareSize });
                    square.setFillColor(sqColor);

                    window.draw(square);
                }
            }
        }

        for (const auto& coord : m_piece->pieceCoords) {
            auto x = m_piecePos.first + coord.first;
            auto y = m_piecePos.second + coord.second;

            sf::RectangleShape square{ {squareSize, squareSize} };
            square.setPosition({ (float)x * squareSize, (float)y * squareSize });
            square.setFillColor(m_pieceColor);

            window.draw(square);
        }
    }
};
