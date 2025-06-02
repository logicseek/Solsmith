#include "Assembly.h"
#include "Function.h"
#include <iostream>

extern vector<Variable> AssemblyVarList; // ������������еı���
extern vector<Variable> VariableList;//���״̬����
extern vector<Variable> LocalVarList;//��žֲ�����
extern vector<Variable> GlobalVarList;//���ȫ�ֱ���
extern vector<sfunction> FuncReturnList;//��ź������ͷ���ֵ����
extern string infunc;//��¼��ǰ�������ĸ������е����ݣ�������õ�ǰ����

vector<sfunction> AssemblyFunctionList;

string AssemblyAssign(int l);

// ��������еı����ͺ����еľֲ���������ֱ�ӻ��ำֵ��������������еı�����״̬��������ֱ�Ӹ�ֵ
// uint256 a = 12;a��״̬������Ҫ��ֵ�����������еı���a_a����Ҫ�ȶ���һ���ֲ�����aValue.
// aValue := sload(a.slot),֮������aValue���в���  ����ʱ��ʹ��״̬������Ϊ��ֵ
// ���Ҫ��a_a��ֵ��a����Ҫʹ��sstore(a.slot,a_a)
// û�ҵ���storage���͵����鸳ֵ�ķ�������ʱ���������������ʹ������
string inlineassembly() {
    /*
    let x := y
    let res := add(x,div(x,y))
    */

    AssemblyFunctionList.clear();
    AssemblyVarList.clear(); // ���֮ǰ�����ı���
    
    string res = "assembly{\n";
    //���������������
    int tmp = rand() % 1 + 1;
    
    for (int i = 0; i < tmp; ++i) {
        string varname = "aa" + getName(i);
        int varval = rand() % 10;
        res += "let " + varname + ":= " + to_string(varval) + "\n";
        AssemblyVarList.emplace_back(Variable("assemblyvar", varname, varval));
    }
    tmp = rand() % 3+1;
    for (int i = 0; i < tmp; ++i) res += assemblyfunc(i);

    res += AssemblyAssign(rand() % 2 + 1);
    tmp = rand() % 2 + 1;
    for (int i = 0; i < tmp; ++i) {
        switch (rand() % 3) {
        case 0:
            res += assemblyfor(0);
            break;
        case 1:
            res += assemblyif(0);
            break;
        }
    }
    res += "}\n";
    return res;
}
// ��ȡ��ֵ
string getLvalue(){
    string res = "";
    int ls = LocalVarList.size() + AssemblyVarList.size();//�Ⱥ���߿�����״̬�����;ֲ�����
    int tmp = rand() % ls;
    if(tmp < LocalVarList.size()){
        res += LocalVarList[tmp].Variablename;
    }else if(tmp < LocalVarList.size() + AssemblyVarList.size()){
        res += AssemblyVarList[tmp - LocalVarList.size()].Variablename;
    }
    return res;
}
// ��ȡ��ֵ
string getRvalue(){
    string res;
    int rs = LocalVarList.size() + AssemblyVarList.size();//�Ⱥ���߿�����״̬�����;ֲ�����
    int tmp = rand() % (rs + rs/2);
    if(tmp < LocalVarList.size()){
        res = LocalVarList[tmp].Variablename;
    }else if(tmp < LocalVarList.size() + AssemblyVarList.size()){
        res = AssemblyVarList[tmp - LocalVarList.size()].Variablename;
    }else{
        res = to_string(rand() % 100);
    }
    return res;
}
string AssemblyKeccak(){
    string res = "keccak256(";
    res += to_string(rand() % 10) + ",";
    res += to_string(rand() % 33) + ")";
    return res;
}
string mload(){
    string res = "mload("+ to_string(rand()%10) + ")";
    return res;
}
// ���� �Ӽ��˳�ȡ�����
string AssemblyOp(int deep){
    string res = "";
    if(deep >= 3) return to_string(rand() % 50 + 1);
    if(deep == 0) res += getLvalue() + " := ";
    switch (rand() % 5)
    {
    case 0:
        res += "add(";
        break;
    case 1: 
        res += "sub(";
        break;
    case 2:
        res += "mul(";
        break;
    case 3:
        res += "div("; // �������Ϊ�㣬div���Ϊ0������Ҫ���⴦��
        break;
    case 4:
        res += "mod(";
        break;
    }
    switch (rand()%5)
    {
    case 0:
        res += getRvalue();
        break;
    case 1:
        res += mload();
        break;
    case 2:
        // res += AssemblyKeccak();
        res += to_string(rand() % 50);
        break;
    case 3:
        res += to_string(rand() % 50);
        break;
    case 4:
        res += AssemblyOp(deep+1);
        break;
    }
    res += ",";
    switch (rand() % 5)
    {
    case 0:
        res += getRvalue();
        break;
    case 1:
        res += mload();
        break;
    case 2:
        //res += AssemblyKeccak();
        res += to_string(rand() % 50);
        break;
    case 3:
        res += to_string(rand() % 50);
        break;
    case 4:
        res += AssemblyOp(deep+1);
        break;
    }
    res += ")";
    return res;
}
string AssemblyMstore(){
    string res = "";
    res += "mstore(" + to_string(rand()%10) + "," ;
    switch (rand() % 4)
    {
    case 0:
        res += to_string(rand() % 50);
        break;
    case 1:
        res += getRvalue();
        break;
    case 2:
    case 3:
        res += AssemblyOp(1);
        break;
    }
    res += ")";
    return res;
}
// ��״̬������ֵ
string AssemblySstore() {
    string res = "sstore(";
    res += VariableList[rand() % VariableList.size()].Variablename + ",";
    res += AssemblyOp(1);
    res += ")";
    return res;
}
// ����l����ֵ���
string AssemblyAssign(int l){
    string res = "";
    for(int m = 0;m < l;++ m){
        switch(rand() % 6){
        case 0:
        case 1:
        case 2:
            res += AssemblyOp(0) + "\n";
            break;
        case 3:
            res += AssemblyMstore() + "\n";
            break;
        case 4:
            res += getLvalue() + ":=" + mload() + "\n";
            break;
        case 5:
            if(rand() % 3 == 1) // �ʵ����ͺ������õĴ���
                res += getLvalue() + ":=" + callassemblyfunc() + "\n";
            break;
        case 6:
            res += AssemblySstore() + "\n";
            break;
        }
    }
    return res;
}

string AssemblyAssignNoFunc(int l) {
    string res = "";
    for (int m = 0; m < l; ++m) {
        switch (rand() % 6) {
        case 0:
        case 1:
        case 2:
            res += AssemblyOp(0) + "\n";
            break;
        case 3:
            res += AssemblyMstore() + "\n";
            break;
        case 4:
            res += getLvalue() + ":=" + mload() + "\n";
            break;
        case 5:
            res += AssemblySstore() + "\n";
            break;
        }
    }
    return res;
}

// i�������
// tmp��ʾ�ж��ٸ��������ı��� ������ûʲô��
string assemblyfor(int i) { 
    if (i >= 2)return "";
    string var = "assemblyfor_";
    var.push_back('i' + i);
    string res = "for {let " + var + " := 0} lt(" + var + "," + to_string(rand() % 10) + ") {" + var + " := add(" + var +",1)}\n{\n";
    // �����������
    int l = rand() % 2;
    res += AssemblyAssign(l);
    switch (rand() % 3) {
    case 0:
        res += assemblyfor(i + 1);
        break;
    case 1:
        res += assemblyif(i + 1);
        break;
    case 2:
        break;
    }
    l = rand() % 2;
    res += AssemblyAssign(l);
    res += "}\n";
    return res;
}
// i�������
string assemblyif(int i) {
    string res;
    if (i >= 2) return res;
    switch (rand() % 3)
    {
    case 0:
        res += "if eq(";
        break;
    case 1:
        res += "if lt(";
        break;
    case 2:
        res += "if gt(";
        break;
    }
    res += AssemblyVarList[rand() % AssemblyVarList.size()].Variablename + "," + AssemblyVarList[rand() % AssemblyVarList.size()].Variablename + ")\n{\n";
    // �����������
    int l = rand() % 2;  
    res += AssemblyAssign(l);
    switch (rand() % 3) {
    case 0:
        res += assemblyif(i + 1);
        break;
    case 1:
        res += assemblyfor(i + 1);
        break;
    case 2:
        break;
    }
    l = rand() % 2;
    res += AssemblyAssign(l);
    res += "}\n";
    return res;
}

string assemblyfunc(int i) {
    string assemblyfuncname = "assemblyfunc_" + getName(i);
    string res = "function " + assemblyfuncname + "(";
    int paranum = rand() % 3;
    switch (paranum) { //�������������
    case 0:
        res += "";
        break;
    case 1:
        res += "x";
        break;
    case 2:
        res += "x,y";
    }
    res += ") -> r { \n";
    int tmp = rand() % 3;
    for (int i = 0; i < tmp; ++i) {
        res += AssemblyAssignNoFunc(0);
    }
    switch (rand() % 3) {
    case 0:
        res += "return(0,0)\n";
        break;
    case 1:
        //res += "revert(0,0)\n";
        break;
    case 2:
        break;
    }
    res += "}\n";
    AssemblyFunctionList.emplace_back(sfunction(assemblyfuncname, paranum));
    return res;
}
// ������������еĺ���
string callassemblyfunc() {
    sfunction tmpF = AssemblyFunctionList[rand() % AssemblyFunctionList.size()];
    string res = tmpF.funcname + "(";
    for (int i = 0; i < tmpF.paranum; ++i) {
        if (rand()%5 != 1) {
            res += getRvalue(); // ��������ֵ
        }
        else { 
            // ������������һ����������Ϊ�����ĺ����Ĳ����������Ǻ���
            sfunction tmptmpF = AssemblyFunctionList[rand() % AssemblyFunctionList.size()];
            res += tmptmpF.funcname + "(";
            for (int j = 0; j < tmptmpF.paranum; ++j) {
                res += getRvalue();
                if (j != tmptmpF.paranum - 1) res += ",";
            }
            res += ")";
        }
        if (i != tmpF.paranum - 1) res += ",";
    }
    res += ")\n";
    return res;
}