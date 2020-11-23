#pragma once

#include <piece.hh>
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

const int BOARD_SIZE = 8;

struct Coord {
    int x,y;
    string toString() const;
};

struct Move {
    Coord from;
    Coord to;
    Move();
    Move(int x1, int y1, int x2, int y2);
    string toString() const;
};

struct c {
    bool moved;
    bool won;
};

class Board {
    vector<Piece> pieces;
    unordered_map<char,PieceBehaviour> behaviours;

    vector<Piece> aiPieces();
    vector<Move> possibleAiMoves();
    char asciiTile(int x, int y);
    char tryTakePiece(const Coord pos);
    void tryUpgradePiece(Piece *piece);
    bool canMove(Piece piece, int x, int y);

    public:
    Board(vector<Piece> pieces, unordered_map<char,PieceBehaviour> behaviours);
    MoveResult try_make_move(Coord from, Coord to, bool as_ai);
    void makeAiMove();
    Piece* at(int x, int y);
    void print();
};