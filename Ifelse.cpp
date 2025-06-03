#include "Ifelse.h"
#include "Loop.h"
#include "Variable.h"
#include "Function.h"
#include "Block.h"

extern vector<Variable> VariableList;
extern vector<Variable> LocalVarList;
extern vector<Variable> GlobalVarList;
extern vector<Variable> ArrayList;
extern vector<sfunction> FuncReturnList;
extern int inLoop;

string returnInt(string int1, string int2) {


    string  res;
    res += "(" + int1;
    switch (rand() % 7) {
    case 0:
        res += "+";
        break;
    case 1:
        res += "-";
        break;
    case 2:
        res += "*";
        break;
    case 3:
        res += "/";
        break;
    case 4:
        res += "|";
        break;
    case 5:
        res += "&";
        break;
    case 6:
        res += "^";
        break;
    }
    res += int2 + ")";
    return res;
}
string returnBool(string int1, string int2) {

    string  res;
    res += "(" + int1;
    switch (rand() % 4) {
    case 0:
        res += "<";
        break;
    case 1:
        res += ">";
        break;
    case 2:
        res += "==";
        break;
    case 3:
        res += "!=";
        break;
    }
    res += int2 + ")";
    return res;
}
string boolreturnBool(string bool1, string bool2) {

    string  res;
    res += "(" + bool1;
    switch (rand() % 4) {
    case 0:
        res += "||";
        break;
    case 1:
        res += "&&";
        break;
    case 2:
        res += "==";
        break;
    case 3:
        res += "!=";
        break;
    }
    res += bool2 + ")";
    return res;
}


string ifelse_make_random() {
    string res;
    res += "\nif(";


    int vl = VariableList.size() + LocalVarList.size() + ArrayList.size();

    int tmp = rand() % 3 + 1;

    string val1[4], val2[4], boolval[4];
    for (int i = 0; i < tmp; i++) {
        int t = rand() % vl;
        val1[i] = "int256(";
        if (t < VariableList.size()) {
            val1[i] += VariableList[t].Variablename;
        }
        else if (t < VariableList.size() + LocalVarList.size()) {
            val1[i] += LocalVarList[t - VariableList.size()].Variablename;
        }
        else{
            Variable tmpv = ArrayList[t - VariableList.size() - LocalVarList.size()];
            val1[i] += tmpv.Variablename + "[" + to_string(rand() % tmpv.a) + "]";
        }
        val1[i] += ")";

        t = rand() % vl;
        val2[i] = "int256(";
        if (t < VariableList.size()) {
            val2[i] += VariableList[t].Variablename;
        }
        else if (t < VariableList.size() + LocalVarList.size()) {
            val2[i] += LocalVarList[t - VariableList.size()].Variablename;
        }
        else {
            Variable tmpv = ArrayList[t - VariableList.size() - LocalVarList.size()];
            val2[i] += tmpv.Variablename + "[" + to_string(rand() % tmpv.a) + "]";
        }
        val2[i] += ")";
        boolval[i] = returnBool(val1[i], val2[i]);
    }
    for (int i = 1; i < tmp; ++i) {
        boolval[0] = boolreturnBool(boolval[0], boolval[i]);
    }
    res += boolval[0] + ")\n{\n";


    res += block_make_random();

    if (inLoop != 0) {
        tmp = rand() % 3;
        switch (tmp) {
        case 0://break;
            res += "\nbreak;\n";
            break;
        case 1://continue;
            res += "\ncontinue;\n";
            break;
        case 2://
            break;
        }
    }

    res += "}\n";
    return res;
}