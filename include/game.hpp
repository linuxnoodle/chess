#pragma once
#include <cmath>
#include <vector>

#define BOARD_HEIGHT 8
#define BOARD_WIDTH 8

enum PIECE{
    PAWN=0,
    KNIGHT=1,
    BISHOP=2,
    ROOK=3,
    QUEEN=4,
    KING=5,
    EMPTY=6,
};

struct vector2{
    int x, y;
};

struct piece{
    PIECE type;
    char team = 0; // 0 = no team, 1 = white, 2 = black
    unsigned int moves = 0; 
};

namespace game{
    extern char currentTurn;
    extern piece grid[BOARD_HEIGHT][BOARD_WIDTH];

    void movePieces(piece (&board)[BOARD_HEIGHT][BOARD_WIDTH], vector2 firstPiece, vector2 secondPiece);
    std::vector<vector2> getPossibleMoves(piece type, vector2 currentPosition);
}
