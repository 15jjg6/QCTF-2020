#include <piece.hh>
#include <board.hh>
#include <math.h>
#include <moremath.hh>

bool queenInRange(Piece piece, int x, int y) {
    int dx = abs(x-piece.x);
    int dy = abs(y-piece.y);
    return
        (dx!=0 || dy!=0) &&
        (dx==dy || dx==0 || dy==0);
}

bool canQueenMove(Piece piece, int x, int y, Board &board) {
    auto other = board.at(x,y);
    return 
        queenInRange(piece,x,y) &&
        clearBetween(piece.x,piece.y,x,y,board) &&
        (!other || piece.is_ai()!=other->is_ai());
}

PieceBehaviour createQueenBehaviour() {
    PieceBehaviour behaviour;
    behaviour.can_move = canQueenMove;
    return behaviour;
}