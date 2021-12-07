// Compile: g++ -g -O2 -std=gnu++17 -static problemA.cxx
// Run: ./a.out
#include <iostream>
#include <math.h>

int r, c;

struct Coord {
    int r;
    int c;
};


Coord indexToCoord(int x) {
    return {ceil(float(x) / c), (x - 1) % c + 1};
}

Coord newPosition(int row, int p) {
    return indexToCoord(r * (p - 1) + row);
}

int distance(Coord pos) {
    return abs(pos.r - (r + 1) / 2.0) + abs(pos.c - (c + 1) / 2.0);
}

void findStablePosOfRow(int row, int p, Coord& posReturn, int& countReturn) {
    Coord pos = newPosition(row, p);
    int count = 1;

    while (true) {
        Coord newPos = newPosition(pos.r, p);

        if ((newPos.r == pos.r) && (newPos.c == pos.c)) {
            posReturn.r = pos.r;
            posReturn.c = pos.c;
            countReturn = count;
            break;
        }

        pos.r = newPos.r;
        pos.c = newPos.c;
        count += 1;
    }
}


void findStablePos(int p, Coord& posReturn, int& countReturn) {
    Coord stablePos;
    int maxCount;

    findStablePosOfRow(1, p, stablePos, maxCount);

    for (int row = 2; row <= r; row++) {
        Coord pos;
        int count;
        findStablePosOfRow(row, p, pos, count);

        if (pos.r != stablePos.r || pos.c != stablePos.c) {
            posReturn.r = 0;
            posReturn.c = 0;
            countReturn = 0;
            return;
        }

        if (count > maxCount) {
            maxCount = count;
        }
    }

    posReturn.r = stablePos.r;
    posReturn.c = stablePos.c;
    countReturn = maxCount;
}


int main() {
    std::cin >> r >> c;

    int p=0, i=0, j=0, s=0;
    
    for (int p_ = 1; p_ <= c; p_++) {
        Coord pos;
        int count;
        findStablePos(p_, pos, count);
        if (distance(pos) < distance({i, j})) {
            p = p_;
            i = pos.r;
            j = pos.c;
            s = count;
        }
    }

    std::cout << p << " " << i << " " << j << " " << s << std::endl;
}
