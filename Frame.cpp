#include <vector>
#include "Frame.h"
#include "Test.h"
#include "Function.h"
#include "Variable.h"
#include "Assign.h"

extern string testtestevent;
extern string testtestemit;
extern vector<Variable> VariableList;
extern vector<Variable> ArrayList;
extern vector<Variable> ArrayList_b;
extern vector<Variable> ConstVariableList;



string genOtherContract() {
    string res = "contract D{\n";
    int tmp = rand() % 2 + 1;
    for (int i = 0; i < tmp; ++i) res += genArray(ArrayList,i);
    res += genfunc("func_a", 1,0);
    res += "}\n";
    ArrayList.clear();
    return res;
}

string getFrame() {

    
    string res;
    res += "//SPDX-License-Identifier: GPL-3.0\n"
        "pragma solidity ^0.8.0;\n";
    int otherContract = 0; 
    if (rand() % 50 == 1) {
        res += genOtherContract();
        otherContract = 1;
    }
    res += "contract ContractName{\n\t";

    int count = rand() % 3 + 1;

    for (int i = 0; i < count; i++) {
        res += genVariable(VariableList, i, false);
    }
    count = rand() % 2 + 1;
    for (int i = 0; i < count; ++i) {
        res += genConstVariable(ConstVariableList, i);
    }

    
    int tmp = rand() % 2 + 1;
    for(int i = 0;i < tmp;++ i){
        res += genArray(ArrayList,i);
    }
    ArrayList_b = ArrayList;

    testtestevent.clear();
    testtestemit.clear();
    testtestevent += "event testtest(";
    testtestemit += "emit testtest(";

    for (vector<Variable>::iterator iter = VariableList.begin(); iter != VariableList.end(); iter++) {
        testtestevent += iter->Typename + " " + iter->Variablename;
        testtestemit += iter->Variablename;
        if (iter->Variablename != (VariableList.end() - 1)->Variablename) {
            testtestevent += ",";
            testtestemit += ",";
        }
    }

    testtestevent += ");\n";
    testtestemit += ");\n";
    res += testtestevent;
    
    testtestevent.clear();
    
    count = 3;  //rand() % 10 + 1;
    for (int i = 0; i < count; i++) {
        ArrayList = ArrayList_b;
        res += genfunc("func_" + getName(i),0,otherContract);
    }

    res += "}";
    VariableList.clear();
    ArrayList.clear();
    ArrayList_b.clear();
    ConstVariableList.clear();
    return res;
}



