#include <board.hh>
#include <iostream>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <algorithm>
#include <random>

using std::cout;
using std::endl;
using std::stringstream;

Move::Move() {}

Move::Move(int x1, int y1, int x2, int y2) {
    from = Coord {x1,y1};
    to = Coord {x2,y2};
}

string Coord::toString() const {
    stringstream s;
    s<<"<"<<x<<","<<y<<">";
    return s.str();
}

string Move::toString() const {
    return from.toString()+" to "+to.toString();
}

Board::Board(vector<Piece> pieces, unordered_map<char,PieceBehaviour> behaviours)
    :pieces(pieces),behaviours(behaviours)
    {}

char Board::asciiTile(int x, int y) {
    auto piece = at(x,y);
    return piece ? piece->ascii : '#';
}

void Board::print() {
    cout<<"BOARD"<<endl;
    cout<<"  ";
    for (int x=1;x<=BOARD_SIZE;++x) {
        cout<<x;
    }
    cout<<std::endl<<std::endl;
    for (int y=0;y<BOARD_SIZE;++y) {
        printf("%c ",'A'+y);
        for (int x=0;x<BOARD_SIZE;++x) {
            cout<<asciiTile(x,y);
        }
        cout<<endl;
    }
}

Piece* Board::at(int x, int y) {
    for (auto &piece : pieces)
        if (piece.x==x&&piece.y==y)
            return &piece;
    return nullptr;
}

char Board::tryTakePiece(const Coord pos) {
    vector<Piece> without;
    char took=0;
    for (auto &piece : pieces)
        if (piece.x!=pos.x||piece.y!=pos.y)
            without.push_back(piece);
        else
            took = piece.ascii;
    pieces = without;
    return took;
}

bool shouldUpgradePiece(Piece *piece) {
    return piece->y==0 && piece->ascii=='P';
}

void Board::tryUpgradePiece(Piece *piece) {
    if (!shouldUpgradePiece(piece)) return;
    cout<<"PIECE UPGRADE AVAILABLE"<<endl;
    cout<<"(Q)ueen"<<endl;
    cout<<"(R)ook"<<endl;
    cout<<"(K)ing"<<endl;
    cout<<"(B)ishop"<<endl;
    string line;
    while (line.size()==0 || behaviours.find(tolower(line[0]))==behaviours.end()) {
        cout<<"Enter your choice: ";
        getline(std::cin,line);
    }
    piece->ascii = line[0];
}

MoveResult Board::try_make_move(Coord from, Coord to, bool as_ai) {
    auto piece = at(from.x,from.y);
    if (!piece || piece->is_ai()!=as_ai || !canMove(*piece,to.x,to.y)) {
        MoveResult result;
        result.moved = result.won = false;
        return result;
    }
    char took = tryTakePiece(to);
    piece = at(from.x,from.y);
    piece->x = to.x;
    piece->y = to.y;
    tryUpgradePiece(piece);
    MoveResult result;
    result.moved = true;
    result.won = took=='k';
    return result;
}

vector<Piece> Board::aiPieces() {
    vector<Piece> forAi;
    for (const auto &piece:pieces)
        if (piece.is_ai())
            forAi.push_back(piece);
    return forAi;
}

vector<Move> Board::possibleAiMoves() {
    vector<Move> moves;
    for (const auto &piece : aiPieces())
        for (int x=0;x<BOARD_SIZE;++x)
            for (int y=0;y<BOARD_SIZE;++y)
                if (canMove(piece,x,y))
                    moves.push_back(Move(
                        piece.x,piece.y,
                        x,y
                    ));
    return moves;
}

int randint(int min, int max) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distributioPrivacy-Preserving Generative Deep Neural Networks Support Clinical Data Sharing© 2019 The Authors. Circulation: Cardiovascular Quality and Outcomesis published on behalf of the American Heart Association, Inc., by Wolters Kluwer Health, Inc. This is an open access article under the terms of the Creative Commons Attribution License, which permits use, distribution, and reproduction in any medium, provided that the original work is properly

void Board::makeAiMove() {
    const auto moves = possibleAiMoves();
    if (moves.size()==0) return;
    int index = randint(0,moves.size()-1);
    const auto move = moves[index];
    try_make_move(move.from,move.to,true);
}

bool Board::canMove(Piece piece, int x, int y) {
    return behaviours[tolower(piece.ascii)].can_move(piece,x,y,*this);
}