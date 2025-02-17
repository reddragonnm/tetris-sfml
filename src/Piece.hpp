#pragma once

#include <array>

#include "Random.hpp"

using PieceCoords = std::array<std::pair<int, int>, 4>;

namespace Piece {
    struct Piece {
        int numSquares;
        PieceCoords pieceCoords;
        std::array<PieceCoords, 4> rotationData;

        constexpr Piece(int numSquares, PieceCoords pieceCoords) : numSquares(numSquares), pieceCoords(pieceCoords) {
            for (int i = 0; i < 4; i++) {
                PieceCoords coords{};

                for (int j = 0; j < 4; j++) {

                    std::pair<int, int> newCoord{ pieceCoords[j] };
                    for (int k = 0; k < i; k++) {
                        std::swap(newCoord.first, newCoord.second);
                        newCoord.first = numSquares - newCoord.first - 1;
                    }

                    coords[j] = newCoord;
                }

                rotationData[i] = coords;
            }
        }
    };

    constexpr Piece pieceO{ 2, {{ {0, 0}, {1, 0}, {0, 1}, {1, 1} }} };
    constexpr Piece pieceI{ 4, {{ {0, 1}, {1, 1}, {2, 1}, {3, 1} }} };
    constexpr Piece pieceT{ 3, {{ {1, 0}, {0, 1}, {1, 1}, {2, 1} }} };
    constexpr Piece pieceL{ 3, {{ {2, 0}, {0, 1}, {1, 1}, {2, 1} }} };
    constexpr Piece pieceJ{ 3, {{ {0, 0}, {0, 1}, {1, 1}, {2, 1} }} };
    constexpr Piece pieceS{ 3, {{ {1, 0}, {2, 0}, {0, 1}, {1, 1} }} };
    constexpr Piece pieceZ{ 3, {{ {0, 0}, {1, 0}, {1, 1}, {2, 1} }} };

    constexpr std::array<const Piece*, 7> allPieces{ &pieceO, &pieceI, &pieceT, &pieceL, &pieceJ, &pieceS, &pieceZ };

    const Piece* getRandomPiece() {
        return allPieces[Random::get(0, 6)];
    }
}
