#include <moremath.hh>

int max(int x, int y) {
    return y > x ? y : x;
}
int min(int x, int y) {
    return y < x ? y : x;
}

int sign(int x) {
    if (x==0) return x;
    if (x<0) return -1;
    return 1;
}