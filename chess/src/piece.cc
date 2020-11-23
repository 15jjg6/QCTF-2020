#include <piece.hh>
#include <unordered_map>
#include <ctype.h>
#include <moremath.hh>
#include <board.hh>

using std::unordered_map;

bool Piece::is_ai() const {
    return islower(ascii);
}

bool clearBetween(int x1, int y1, int x2, int y2, Board &board) {
    int sx = sign(x2-x1);
    int sy = sign(y2-y1);
    int x = x1+sx;
    int y = y1+sy;
    while (x!=x2 || y!=y2) {
        if (board.at(x,y)) return false;
        x+=sx;
        y+=sy;
    }
    return true;
}