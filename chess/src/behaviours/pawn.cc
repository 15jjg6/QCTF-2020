#include <piece.hh>
#include <board.hh>
#include <math.h>
#include <moremath.hh>

bool pawnInRange(Piece piece, int x, int y) {
    int dx = x-piece.x;
    int dy = y-piece.y;
    int sy = piece.is_ai() ? 1:-1;
    return dx==0 && dy==sy;
}

bool canPawnMove(Piece piece, int x, int y, Board &board) {
    int sy = piece.is_ai() ? 1:-1;
    int dx = x-piece.x;
    int dy = y-piece.y;
    auto other = board.at(x,y);
    if (dx==0)
        return 
            dy==sy && !other;
    else
        return 
            dy==sy && abs(dx)==1 &&
            (!other || other->is_ai()!=piece.is_ai());
}

PieceBehaviour createPawnBehaviour() {
    PieceBehaviour behaviour;
    behaviour.can_move = canPawnMove;
    return behaviour;
}