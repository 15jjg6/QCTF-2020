#include <behaviours.hh>

unordered_map<char,PieceBehaviour> createBehaviours() {
    return unordered_map<char,PieceBehaviour> {
        {'k',createKingBehaviour()},
        {'p',createPawnBehaviour()},
        {'q',createQueenBehaviour()},
        {'r',createRookBehaviour()},
        {'b',createBishopBehaviour()},
        {'h',createHorseBehaviour()}
    };
}