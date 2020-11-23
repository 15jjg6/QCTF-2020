#include <piece.hh>
#include <board.hh>
#include <math.h>
#include <moremath.hh>

bool rookInRange(Piece piece, int x, int y) {
    int dx = abs(x-piece.x);
    int dy = abs(y-piece.y);
    return
        (dx!=0 || dy!=0) &&
        (dx==0 || dy==0);
}

bool canRookMove(Piece piece, int x, int y, Board &board) {
    auto other = board.at(x,y);
    return 
        rookInRange(piece,x,y) &&
        clearBetween(piece.x,piece.y,x,y,board) &&
        (!other || piece.is_ai()!=other->is_ai());
}

PieceBehaviour createRookBehaviour() {
    PieceBehaviour behaviour;
    behaviour.can_move = canRookMove;
    return behaviour;
}