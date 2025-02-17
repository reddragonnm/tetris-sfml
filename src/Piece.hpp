#pragma once

#include <array>

#include "Random.hpp"

using PieceCoords = std::array<std::pair<int, int>, 4>;

namespace Piece {
    struct Piece {
        int numSquares;
        PieceCoords pieceCoords;

        constexpr Piece(int numSquares, PieceCoords pieceCoords) : numSquares(numSquares), pieceCoords(pieceCoords) {}
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
