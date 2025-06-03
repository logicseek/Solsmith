#include "Block.h"
#include "Assign.h"
#include "Ifelse.h"
#include "Loop.h"
#include "Assembly.h"
#include "Function.h"

extern int blockcount;
extern int inLoop;

string block_make_random() {
    
    blockcount++;
    string res;
    
    if (blockcount >= 3) {
        int l = rand() % 5 + 1;
        for (int i = 0; i < l; i++)
            res += assign_make_random();
        return res;
    }
    int tmp = rand() % 5 + 1;
    for (int i = 0; i < tmp; i++) {
        int t = rand() % 10;
        if (t <= 2) {
            res += assign_make_random();
        }
        else if (t <= 5) {
            if (inLoop <= 3) {
                res += loop_make_random();
            }
        }
        else if (t <= 8) {
            res += ifelse_make_random();
        }
        else if (t == 9) {
            res += inlineassembly();
        }
    }
    blockcount--;
    
    return res;
}

