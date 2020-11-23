#include <piece.hh>
#include <board.hh>
#include <math.h>
#include <moremath.hh>

bool kingInRange(Piece piece, int x, int y) {
    int dx = x-piece.x;
    int dy = y-piece.y;
    return max(abs(dx),abs(dy))==1;
}

bool canKingMove(Piece piece, int x, int y, Board &board) {
    auto other = board.at(x,y);
    return 
        kingInRange(piece,x,y) &&
        (!other || piece.is_ai()!=other->is_ai());
}

PieceBehaviour createKingBehaviour() {
    PieceBehaviour behaviour;
    behaviour.can_move = canKingMove;
    return behaviour;
}