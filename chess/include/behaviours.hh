#include <piece.hh>
#include <unordered_map>

using std::unordered_map;

unordered_map<char,PieceBehaviour> createBehaviours();

PieceBehaviour createKingBehaviour();
PieceBehaviour createPawnBehaviour();
PieceBehaviour createQueenBehaviour();
PieceBehaviour createRookBehaviour();
PieceBehaviour createBishopBehaviour();
PieceBehaviour createHorseBehaviour();