#pragma once

#include <board.hh>
#include <string>
#include <iostream>

using std::istream;
using std::string;

struct ParsedMove {
    Move move;
    bool ok;
};

ParsedMove parseMove(string input);
Move parseMoveFromInput(istream &in);