#include <piece.hh>
#include <board.hh>
#include <math.h>
#include <moremath.hh>

bool horseInRange(Piece piece, int x, int y) {
    int dx = abs(x-piece.x);
    int dy = abs(y-piece.y);
    return min(dx,dy)==1 && max(dx,dy)==2;
}

bool canHorseMove(Piece piece, int x, int y, Board &board) {
    auto other = board.at(x,y);
    return 
        horseInRange(piece,x,y) &&
        (!other || piece.is_ai()!=other->is_ai());
}

PieceBehaviour createHorseBehaviour() {
    PieceBehaviour behaviour;
    behaviour.can_move = canHorseMove;
    return behaviour;
}