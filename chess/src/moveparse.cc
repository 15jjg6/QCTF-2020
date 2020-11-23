#include <moveparse.hh>

bool goodX(char x) {
    return x>='A'&&x<='H';
}

bool goodY(char y) {
    return y>='1'&&y<='8';
}

bool validInput(string input) {
    return 
        input.length()==5 &&
        goodX(toupper(input[0])) &&
        goodY(input[1]) &&
        input[2]==' ' &&
        goodX(toupper(input[3])) &&
        goodY(input[4]);
}

ParsedMove parseMove(string input) {
    if (!validInput(input)) {
        ParsedMove badMove;
        badMove.ok = false;
        return badMove;
    }
    ParsedMove parsed;
    parsed.ok = true;
    parsed.move.from.y = toupper(input.at(0))-'A';
    parsed.move.from.x = input.at(1)-'1';
    // reserve char at position 2 for :
    parsed.move.to.y = toupper(input.at(3))-'A';
    parsed.move.to.x = input.at(4)-'1';
    return parsed;
}

Move parseMoveFromInput(istream &in) {
    while (true) {
        string line;
        std::cout<<"Enter move: ";
        getline(in,line);
        const auto parsed = parseMove(line);
        if (parsed.ok) return parsed.move;
        else std::cout<<"Couldn't parse move."<<std::endl;
    }
}