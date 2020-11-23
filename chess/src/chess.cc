#include <vector>
#include <iostream>
#include <memory>
#include <piece.hh>
#include <board.hh>
#include <moveparse.hh>
#include <behaviours.hh>

using std::unique_ptr;

vector<Piece> startingPieces() {
    return vector<Piece> {
        Piece {0,0,'r'},
        Piece {1,0,'h'},
        Piece {2,0,'b'},
        Piece {3,0,'q'},
        Piece {5,0,'b'},
        Piece {6,0,'h'},
        Piece {7,0,'r'},

        Piece {0,1,'p'},
        Piece {1,1,'p'},
        Piece {2,1,'p'},
        Piece {3,1,'p'},
        Piece {4,1,'p'},
        Piece {5,1,'p'},
        Piece {6,1,'p'},
        Piece {7,1,'p'},

        Piece {0,6,'P'},
        Piece {1,6,'P'},
        Piece {2,6,'P'},
        Piece {3,6,'P'},
        Piece {4,6,'P'},
        Piece {5,6,'P'},
        Piece {6,6,'P'},
        Piece {7,6,'P'},

        Piece {0,7,'R'},
        Piece {1,7,'H'},
        Piece {2,7,'B'},
        Piece {3,7,'Q'},
        Piece {4,7,'K'},
        Piece {5,7,'B'},
        Piece {6,7,'H'},
        Piece {7,7,'R'},
    };
}

int main(int argc, char **argv) {
    if (argc<2) {
        std::cout<<"Error: no flag provided"<<std::endl;
        return 1;
    }
    std::cout<<"Welcome to chess!"<<std::endl;
    auto pieces = startingPieces();
    auto behaviours = createBehaviours();
    auto board = Board(pieces,behaviours);
    bool won = false;
    while (!won) {
        // clear screen
        printf("\e[1;1H\e[2J");
        board.print();
        const auto move = parseMoveFromInput(std::cin);
        auto result = board.try_make_move(move.from,move.to,false);
        if (!result.moved)
            std::cout<<"Illegal move."<<std::endl;
        else
            board.makeAiMove();
        won = result.won;
    }
    std::cout<<"GAME OVER U WIN... "<<argv[1]<<std::endl;
}