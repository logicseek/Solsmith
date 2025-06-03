#include <vector>
#include "Function.h"
#include "Block.h"
#include "State.h"
#include "Test.h"
#include "Variable.h"

extern vector<sfunction> FuncList;
extern vector<sfunction> FuncReturnList;
extern string infunc;
extern string testtestevent;
extern string testtestemit;
extern vector<Variable> VariableList;
extern vector<Variable> LocalVarList;
extern vector<Variable> ArrayList;
extern vector<Variable> ArrayList_b;
extern int blockcount;


string genfunc(string funcName,int keyword,int otherContract) {
    string res;
    string sfuncname = funcName;
    int selector = otherContract;
    if(otherContract == 1) selector = rand() % 5000;
    infunc = funcName;
    int svisibility;
    string sreturnPara;



    enum visibility
    {
        ePublic,
        ePrivate,
        eExternal,
        eInternal
    };
    res = "function " + funcName + "() ";
    int tmp = keyword;//rand() % 4;
    switch (tmp)
    {
    case 0:
        res += "public ";
        svisibility = 0;
        break;
    case 1:
        res += "external ";
        svisibility = 1;
        break;
    case 2:
        res += "private ";
        svisibility = 2;
        break;
    case 3:
        res += "internal ";
        svisibility = 3;
        break;


    }

    int hasreturn = rand() % 2;
    if (selector == 1 && funcName == "func_c") {
        res += "returns (D) ";
    }else if (hasreturn == 1) {
        res += "returns(";
        int t = rand() % 2;
        switch (t) {
        case 0:
            res += "uint256";
            sreturnPara = "uint256";
            LocalVarList.emplace_back(Variable("uint256", "b_a", 0));
            FuncReturnList.emplace_back(sfunction(funcName, svisibility, "b_a"));
            break;
        case 1:
            res += "int256";
            sreturnPara = "int256";
            LocalVarList.emplace_back(Variable("int256", "b_a", 1));
            FuncReturnList.emplace_back(sfunction(funcName, svisibility, "b_a"));
            break;
        case 2:
            res += "bool";
            sreturnPara = "bool";
            LocalVarList.emplace_back(Variable("bool", "b_a", 2));
            FuncReturnList.emplace_back(sfunction(funcName, svisibility, "b_a"));
            break;
        case 3:
            res += "address";
            sreturnPara = "address";
            LocalVarList.emplace_back(Variable("address", "b_a", 3));
            FuncReturnList.emplace_back(sfunction(funcName, svisibility, "b_a"));
            break;
        case 4:
            res += "bytes32";
            sreturnPara = "bytes32";
            LocalVarList.emplace_back(Variable("bytes32", "b_a", 4));
            FuncReturnList.emplace_back(sfunction(funcName, svisibility, "b_a"));
            break;
        }
        res += " b_a)";
    }

    res += "\n{\n";


    res += "unchecked{\n";


    
    res += "uint256 l_z = 1;\n";

    if (selector == 1 && funcName == "func_b") {
        res += "func_c().func_a.selector;\n";
    }
    
    


    tmp = rand() % 2+1;

    LocalVarList.clear();
    for (int i = 0; i < tmp; i++) {
        res += genVariable(LocalVarList, i, true);
    }


    res += state_make_random();
    res += testtestemit;
    if (hasreturn == 1) res += "\nreturn b_a;";
    if (selector == 1 && funcName == "func_c") {
        res += "return new D();\n";
    }
    res += "\n}\n";
    res += "\n}\n";

    blockcount = 0;


    FuncList.emplace_back(sfunction(sfuncname, svisibility, sreturnPara));
    return res;
}