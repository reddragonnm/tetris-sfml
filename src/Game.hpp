#pragma once

#include <algorithm>

#include "Piece.hpp"
#include "Random.hpp"

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
    int m_rotationNum;

    bool m_isGameOver{ false };

    std::pair<int, int> getSpawnPos() {
        return { (numCols - m_piece->numSquares) / 2, 0 };
    }

    sf::Color getRandomColor() {
        return sf::Color{ Random::get(0, 255), Random::get(0, 255), Random::get(0, 255) };
    }

    void setNewPiece() {
        // TODO: check if piece coincides with blocks already on board

        m_piece = Piece::getRandomPiece();
        m_piecePos = getSpawnPos();
        m_pieceColor = getRandomColor();
        m_rotationNum = 0;

        bool valid{ true };
        for (const auto& coord : m_piece->rotationData[m_rotationNum]) {
            auto x = m_piecePos.first + coord.first;
            auto y = m_piecePos.second + coord.second;

            if (m_board[y][x] != sf::Color::Black) {
                m_isGameOver = true;
                break;
            }
        }
    }

    bool inBoundsLR() {
        for (const auto& coord : m_piece->rotationData[m_rotationNum]) {
            auto x = m_piecePos.first + coord.first;
            auto y = m_piecePos.second + coord.second;

            if (x < 0 || x >= numCols || m_board[y][x] != sf::Color::Black)
                return false;
        }
        return true;
    }

public:
    Game() {
        setNewPiece();
    }

    bool isGameOver() {
        return m_isGameOver;
    }

    bool handleCollision() {
        bool hasCollided{ false };
        for (const auto& coord : m_piece->rotationData[m_rotationNum]) {
            auto x = m_piecePos.first + coord.first;
            auto y = m_piecePos.second + coord.second;

            if (y >= numRows || m_board[y][x] != sf::Color::Black) {
                hasCollided = true;
                break;
            }
        }

        if (hasCollided) {
            m_piecePos.second--;
            for (const auto& coord : m_piece->rotationData[m_rotationNum]) {
                auto x = m_piecePos.first + coord.first;
                auto y = m_piecePos.second + coord.second;

                m_board[y][x] = m_pieceColor;
            }

            setNewPiece();
        }

        return hasCollided;
    }

    void handleLineClears() {
        int j{ numRows - 1 };
        for (int i = numRows - 1; i >= 0; i--) {
            bool isFilled{ true };
            for (const auto& c : m_board[j]) {
                if (c == sf::Color::Black) isFilled = false;
            }

            if (isFilled) j--;

            if (i == j) {
                j--;
                continue;
            }

            if (j >= 0)
                m_board[i] = m_board[j];
            else {
                std::array<sf::Color, numCols> s;
                m_board[i] = s;
            }

            j--;
        }
    }

    void movePieceDown() {
        m_piecePos.second++;
    }

    void dropDown() {
        while (!handleCollision()) {
            movePieceDown();
        }
    }

    void movePieceLeft() {
        m_piecePos.first--;
        if (!inBoundsLR()) m_piecePos.first++;
    }

    void movePieceRight() {
        m_piecePos.first++;
        if (!inBoundsLR()) m_piecePos.first--;

    }

    void rotatePiece() {
        m_rotationNum = (m_rotationNum + 1) % 4;
        if (!inBoundsLR()) m_piecePos.first = std::clamp(m_piecePos.first, 0, numCols - m_piece->numSquares);
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

        for (const auto& coord : m_piece->rotationData[m_rotationNum]) {
            auto x = m_piecePos.first + coord.first;
            auto y = m_piecePos.second + coord.second;

            sf::RectangleShape square{ {squareSize, squareSize} };
            square.setPosition({ (float)x * squareSize, (float)y * squareSize });
            square.setFillColor(m_pieceColor);

            window.draw(square);
        }
    }
};
