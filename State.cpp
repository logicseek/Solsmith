#include "State.h"
#include "Block.h"

extern int blockcount;

//һ�����������ɶ��ٸ���
string state_make_random() {
    string res;

    //������������Ŀ�
    int tmp = rand() % 3 + 1;
    for (int i = 0; i < tmp; i++) {
        int t = rand() % 3;
        //������ÿ����ǰ���������գ���֤ÿ���鶼��������Ϊ5
        blockcount = 0;
        res += block_make_random();
    }
    return res;
}

