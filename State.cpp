#include "State.h"
#include "Block.h"

extern int blockcount;


string state_make_random() {
    string res;

    
    int tmp = rand() % 3 + 1;
    for (int i = 0; i < tmp; i++) {
        int t = rand() % 3;

        blockcount = 0;
        res += block_make_random();
    }
    return res;
}

