#include <vector>

#include <string>
#include <cstring>
#include <unordered_map>
#include "Function.h"
#include "Assign.h"
#include "Variable.h"

using namespace std;

extern vector<Variable> VariableList;
extern vector<Variable> LocalVarList;
extern vector<Variable> ArrayList;
extern vector<Variable> ArrayList_b;
extern vector<Variable> ConstVariableList;
extern vector<sfunction> FuncReturnList;
extern string infunc;
extern int inLoop;
unordered_map<string,int> hashvar;

string AddSub(string varname);

string getRvalue(Variable tmpV) {
    int rs = VariableList.size() + LocalVarList.size() + ArrayList.size() + ConstVariableList.size();
    int count = rand() % 2;
    bool flag = tmpV.Typename == "uint256";
    string tmpstring;
    Variable tmpR;
    string tmpRname, tmpRAftername; // 
    auto numtypecast = [tmpV](int n)->string {return tmpV.Typename + "(" + to_string(n) + ")"; };
    int t = rand() % 3 + 1;
    char preop = ' ';
    for (int i = 0; i < t; ++i) {
        int tmp = rand() % rs;
        string varname;
        if (flag) tmpstring += "uint256(";
        else tmpstring += "int256(";
        if (tmp < VariableList.size()) { 
            tmpR = VariableList[tmp];
            tmpRname = tmpR.Variablename;
            tmpRAftername = tmpRname;
            if (hashvar.count(tmpRname) == 0) { 
                if (rand() % 4 == 1) { 
                    hashvar[tmpRname] = 2;
                    tmpRAftername = AddSub(tmpRname); 
                }
                else {
                    hashvar[tmpRname] = 1;
                }
            }
            else if (hashvar[tmpRname] == 2) {
                tmpRAftername = to_string(rand() % 50);
            }
            if (preop == '/') tmpstring += tmpRname + "==0?1:" + tmpRAftername;
            else tmpstring += tmpRAftername;
        }
        else if (tmp < VariableList.size() + LocalVarList.size()) {
            tmpR = LocalVarList[tmp - VariableList.size()];
            tmpRname = tmpR.Variablename;
            tmpRAftername = tmpRname;
            if (hashvar.count(tmpRname) == 0) { 
                if (rand() % 4 == 1) { 
                    hashvar[tmpRname] = 2;
                    tmpRAftername = AddSub(tmpRname); 
                }
                else {
                    hashvar[tmpRname] = 1;
                }
            }
            else if (hashvar[tmpRname] == 2) {
                tmpRAftername = to_string(rand() % 50);
            }
            if (preop == '/')  tmpstring += tmpRname + "==0?1:" + tmpRAftername;
            else tmpstring += tmpRAftername;
        }
        else if(tmp < VariableList.size() + LocalVarList.size() + ArrayList.size()){ 
            tmpR = ArrayList[tmp - VariableList.size() - LocalVarList.size()];
            tmpRname = tmpR.Variablename + "[" + to_string(rand() % tmpR.a) + "]";
            tmpRAftername = tmpRname;
            if (hashvar.count(tmpRname) == 0) { 
                if (rand() % 4 >= 1) { 
                    hashvar[tmpRname] = 2;
                    tmpRAftername = AddSub(tmpRname);
                }
                else {
                    hashvar[tmpRname] = 1;
                }
            }
            else if (hashvar[tmpRname] == 2) {
                tmpRAftername = to_string(rand() % 50);
            }
            int tmpp = rand() % tmpR.a;
            if (preop == '/') tmpstring += tmpRname  + "==0?1:" + tmpRAftername;
            else tmpstring += tmpRAftername;
        }
        else {
            tmpR = ConstVariableList[tmp - VariableList.size() - LocalVarList.size() - ArrayList.size()];
            if (preop == '/') tmpstring += tmpR.Variablename + "==0?1:" + tmpR.Variablename;
            else tmpstring += tmpR.Variablename;
        }
        tmpstring += ")";
        
        switch (rand() % 2)
        {
        case 0:
            
            switch (rand() % 4)
            {
            case 0:
                tmpstring += " + " + numtypecast(rand() % 200);
                break;
            case 1:
                if (flag) tmpstring += " + " + numtypecast(rand() % 100 + 200);
                tmpstring += " - " + numtypecast(rand() % 200);
                break;
            case 2:
                tmpstring += " / " + numtypecast(rand() % 5 + 1);
                tmpstring += " * " + numtypecast(rand() % 5);
                break;
            case 3:
                tmpstring += " / " + numtypecast(rand() % 20 + 1);
                break;
            }
            break;
        case 1:
            
            break;
        }
        if (i != t - 1) {
            tmp = rand() % 4;
            if (flag) tmp = 0;
            switch (tmp)
            {
            case 0:
                tmpstring += " + ";
                preop = '+';
                break;
            case 1:
                tmpstring += " - ";
                preop = '-';
                break;
            case 2:
                tmpstring += " / ";
                preop = '/';
                break;
            case 3:
                tmpstring += "/" + to_string(rand() % 200 + 1);
                tmpstring += " * ";
                preop = '*';
                break;
            }
        }
    }
    hashvar.clear();
    return tmpstring;
}
string assign_make_random() {
    string res;
    long long numres = 0;
    long long numtmp = 0;
    int a = 0;
    res += "\n";
    int ls = VariableList.size() + LocalVarList.size() + ArrayList.size();
    int rs = ls;
    
    int pushpop = rand() % 10;
    int tmparray = rand() % ArrayList.size();
    if (pushpop == 1) {
        Variable tmpv = ArrayList[tmparray];
        if(rand() % 2 == 1)res += tmpv.Variablename + ".push(" + getRvalue(tmpv) + ");\n";
        else res += tmpv.Variablename + ".push();\n";
    }
    else if(pushpop == 0 && ArrayList[tmparray].a > 1 && inLoop == 0) {
        Variable tmpv = ArrayList[tmparray];
        if(rand() % 2 == 1) res += tmpv.Variablename + ".push(" + getRvalue(tmpv) + ");\n";
        else res += tmpv.Variablename + ".push();\n";
        res += ArrayList[tmparray].Variablename + ".pop();\n";
        
    }
    else {
        
        int tmp = rand() % ls;
        Variable tmpV;
        if (tmp < VariableList.size()) {
            tmpV = VariableList[tmp];
            res += VariableList[tmp].Variablename;
        }
        else if(tmp < VariableList.size() + LocalVarList.size()){
            tmpV = LocalVarList[tmp - VariableList.size()];
            res += LocalVarList[tmp - VariableList.size()].Variablename;
        }else { 
            tmpV = ArrayList[tmp - VariableList.size() - LocalVarList.size()];
            res += tmpV.Variablename + "[" + to_string(rand() % tmpV.a) + "]";

        }
        
        tmp = rand() % 4;
        switch (tmp)
        {
        case 0:
            res += " = ";
            break;
        case 1:
            res += " += ";
            break;
        case 2:
            res += " -= ";
            break;
        case 3:
            res += " = ";
            break;
        case 4:
            res += " *= ";
            break;
        }
        res += getRvalue(tmpV);
        res += ";\n";
    }
    return res;
}

string getRvalue_onlyvariable(Variable tmpV) {
    int rs = VariableList.size() + ArrayList.size() + ConstVariableList.size();
    
    char preop = ' ';

    int count = rand() % 2;
    bool flag = tmpV.Typename == "uint256";
    string tmpstring;
    Variable tmpR;
    string tmpRname, tmpRAftername;
    bool firstconst = true;
    int t = rand() % 3 + 1;
    auto numtypecast = [tmpV](int n)->string {return tmpV.Typename + "(" + to_string(n) + ")"; };
    for (int i = 0; i < t; ++i) {
        int tmp = rand() % rs;
        string varname;
        if (flag) tmpstring += "uint256(";
        else tmpstring += "int256(";
        if (tmp < VariableList.size()) {
            tmpR = VariableList[tmp];
            tmpRname = tmpR.Variablename;
            tmpRAftername = tmpR.Variablename;
            if (hashvar.count(tmpRname) == 0) { 
                if (rand() % 4 == 1) {
                    hashvar[tmpRname] = 2;
                    tmpRAftername = AddSub(tmpRname); 
                }
                else {
                    hashvar[tmpRname] = 1;
                }
            }
            else if (hashvar[tmpRname] == 2) {
                tmpRAftername = to_string(rand() % 50);
            }
            if (preop == '/') tmpstring += tmpRname + "==0?1:" + tmpRAftername;
            else tmpstring += tmpRAftername;
        }
        else if(tmp < VariableList.size() + ArrayList.size() ){
            tmpR = ArrayList[tmp - VariableList.size()];
            tmpRname = tmpR.Variablename + "[" + to_string(rand() % tmpR.a) + "]";
            tmpRAftername = tmpRname;
            if (hashvar.count(tmpRname) == 0) {
                if (rand() % 4 == 1) {
                    hashvar[tmpRname] = 2;
                    tmpRAftername = AddSub(tmpRname);
                }
                else {
                    hashvar[tmpRname] = 1;
                }
            }
            else if (hashvar[tmpRname] == 2) {
                tmpRAftername = to_string(rand() % 50);
            }
            if(preop == '/') tmpstring += tmpRname  + "==0?1:" + tmpRAftername;
            else tmpstring += tmpRAftername;
        }
        else {
            tmpR = ConstVariableList[tmp - VariableList.size() - ArrayList.size()];
            if (preop == '/') tmpstring += tmpR.Variablename + "==0?1:" + tmpR.Variablename;
            else tmpstring += tmpR.Variablename;
        }
        tmpstring += ")";
        switch (rand() % 2)
        {
        case 0:
            
            switch (rand() % 4)
            {
            case 0:
                tmpstring += " + " + numtypecast(rand() % 200);
                break;
            case 1:
                if (flag) tmpstring += " + " + numtypecast(rand() % 100 + 200);
                tmpstring += " - " + numtypecast(rand() % 200);
                break;
            case 2:
                tmpstring += " / " + numtypecast(rand() % 5 + 1);
                tmpstring += " * " + numtypecast(rand() % 5);
                break;
            case 3:
                tmpstring += " / " + numtypecast(rand() % 20 + 1);
                break;
            }
            break;
        case 1:
            
            break;
        }
        if (i != t - 1) {
            tmp = rand() % 4;
            if (flag) tmp = 0;
            switch (tmp)
            {
            case 0:
                tmpstring += " + ";
                preop = '+';
                break;
            case 1:
                tmpstring += " - ";
                preop = '-';
                break;
            case 2:
                tmpstring += " / ";
                preop = '/';
                break;
            case 3:
                tmpstring += "/" + to_string(rand() % 200 + 1);
                tmpstring += " * ";
                preop = '*';
                break;
            }
        }
        
    }
    hashvar.clear();
    return tmpstring;
}

string assign_make_random_onlyVariable() {
    string res = "";
    int ls = VariableList.size() + ArrayList.size();
    int rs = ls;
    int pushpop = rand() % 5;
    int tmparray = rand() % ArrayList.size();
    if (pushpop == 1) {
        Variable tmpv = ArrayList[tmparray];
        if (rand() % 2 == 1) {
            res += tmpv.Variablename + ".push(" + getRvalue_onlyvariable(tmpv) + ");\n";
        }
        else {
            res += tmpv.Variablename + ".push();\n";
        }
        
    }
    else if (pushpop == 0 && ArrayList[tmparray].a > 1 && inLoop == 0) {
        Variable tmpv = ArrayList[tmparray];
        if (rand() % 2 == 1) {
            res += tmpv.Variablename + ".push(" + getRvalue_onlyvariable(tmpv) + ");\n";
        }
        else {
            res += tmpv.Variablename + ".push();\n";
        }
        res += ArrayList[tmparray].Variablename + ".pop();\n";
    }
    else {
        
        int tmp = rand() % ls;
        Variable tmpV;
        if (tmp < VariableList.size()) {
            tmpV = VariableList[tmp];
            res += VariableList[tmp].Variablename;
        }
        else {
            tmpV = ArrayList[tmp - VariableList.size()];
            res += tmpV.Variablename + "[" + to_string(rand() % tmpV.a) + "]";

        }
        
        tmp = rand() % 4;
        switch (tmp)
        {
        case 0:
            res += " = ";
            break;
        case 1:
            res += " += ";
            break;
        case 2:
            res += " -= ";
            break;
        case 3:
            res += " = ";
            break;
        case 4:
            res += " *= ";
            break;
        }
        res += getRvalue_onlyvariable(tmpV);
        res += ";\n";
    }

    return res;
}

string AddSub(string varname) {
    string res = "";
    int tmp = rand() % 4;
    switch (tmp) {
    case 0:
        res += varname + "++";
        break;
    case 1:
        res += varname + "--";
        break;
    case 2:
        res += "++" + varname;
        break;
    case 3:
        res += "--" + varname;
        break;
    }
    return res;
}
