#pragma once

class Board;

#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

struct Piece {
    int x,y;
    char ascii;

    bool is_ai() const;
};

struct PieceBehaviour {
    bool (*can_move)(Piece piece, int x, int y, Board &board);
};

bool clearBetween(int x1, int y1, int x2, int y2, Board &board);