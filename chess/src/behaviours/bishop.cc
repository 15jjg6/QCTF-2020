#include <piece.hh>
#include <board.hh>
#include <math.h>
#include <moremath.hh>

bool bishopInRange(Piece piece, int x, int y) {
    int dx = abs(x-piece.x);
    int dy = abs(y-piece.y);
    return dx==dy && dx!=0;
}

bool canBishopMove(Piece piece, int x, int y, Board &board) {
    auto other = board.at(x,y);
    return 
        bishopInRange(piece,x,y) &&
        clearBetween(piece.x,piece.y,x,y,board) &&
        (!other || piece.is_ai()!=other->is_ai());
}

PieceBehaviour createBishopBehaviour() {
    PieceBehaviour behaviour;
    behaviour.can_move = canBishopMove;
    return behaviour;
}