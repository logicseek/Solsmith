#include "Variable.h"
using namespace std;

//ȷ�����ɵı�����name
string getName(int n) {
    string res;
    if (n / 26 == 1) {
        res += "a";
    }
    res += ('a' + n % 26);
    return res;
}
//��Ϊsolidity��uint256,int256��2��255�η���c++���޷������ֱ�ʾ��ֻ��ֱ�������ַ��������ɵ�����������������������Ӹ��š�
//2��255�η�������64λ16����������ʾ��

string getUInt256() {

    // string res = "0x";
    //������ɵ�����
    // for(int i = 0;i < 5;i ++){
    //     res += '0';
    // }
    // for (int i = 5; i < 64; i++) {
    //     res += '0' + rand() % 10;
    // }
    string res = to_string(rand() % 255);
    return res;
}
string getInt256() {

    // string res = "0x";
    // //������ɵ�����
    // for(int i = 0;i < 5;i ++){
    //     res += '0';
    // }
    // for (int i = 5; i < 64; i++) {
    //     res += '0' + rand() % 10;
    // }
    string res = to_string(rand() % 255);
    return res;
}

string getAdress() {

    string res = "0x";
    //������ɵ����֣���nλ����Ч�ģ�ǰ64-nȫ��0��
    int n = rand() % 40;
    for (int i = 0; i < 40 - n; i++) {
        res += '0';
    }
    for (int i = n; i < 40; i++) {
        res += '0' + rand() % 10;
    }
    return res;
}



string genVariable(vector<Variable>& VarList, int i, bool isLocal) {
    string res;//��¼���ɵĴ��롣
    string value;
    int typec = rand() % 2;
    string tmpname = getName(i);
    //����Ǿֲ�����������ǰ��һ��l_��ǰ׺
    if (isLocal) {
        tmpname = "l_" + tmpname;
    }
    switch (typec)
    {
    case 0:
        value = getUInt256();
        VarList.emplace_back(Variable("uint256", tmpname, stoi(value)));
        //�����ı�
        res += "\n\tuint256 ";
        if (!isLocal) res += " public ";
        res += tmpname + " = " + value;

        break;
    case 1:
        value = getInt256();
        //�����0�����ɸ���������Ϊ����
        res += "\n\tint256 ";
        if (!isLocal) res += " public ";
        res += tmpname + " = ";
        if (rand() % 2 == 0) value = "-" + value;
        res += getInt256();
        VarList.emplace_back(Variable("int256", tmpname, stoi(value)));
        break;
    case 2:
        VarList.emplace_back(Variable("bool", tmpname, 2));
        if (rand() % 2 == 0) res += "\n\tbool " + tmpname + " = " + "false";
        else res += "\n\tbool " + tmpname + " = " + "true";
        break;
    case 3://address ʹ��40��16��������ʾ
        VarList.emplace_back(Variable("address", tmpname, 3));
        res += "\n\taddress " + tmpname + " = " + getAdress();
        break;
    case 4:
        VarList.emplace_back(Variable("bytes32", getName(i), 4));
        res += "\n\tbytes32 " + tmpname + " = " + getInt256();
        break;
    }
    res += ";\n";
    return res;
}

string genArray(vector<Variable> &VarList,int i){
    string res = "";
    int tmpl = rand() % 3 + 3;
    res += "\tuint[] Array" + getName(i);
    
    // �����鸳��ֵ
    res += " = [";
    for(int i = 0;i < tmpl; ++ i){
        if(i != 0) {
            res += "," + to_string(rand() % 65);
        }else{
            res += to_string(rand() % 65);
        }
    }
    res += "];\n";
    VarList.emplace_back(Variable("uint256","Array"+getName(i),tmpl,0));
    return res;
}

string genConstVariable(vector<Variable> &VarList,int i) {
    string res = "uint256 constant const_" + getName(i) + " = ";
    if (rand() % 2 == 1) {
        res += to_string(rand() % 50) + ";\n";
    }
    else {
        res += "0xfffffffffffffffffffffffffffffffffffffffffffffffe;\n";
    }
    VarList.emplace_back(Variable("uint256", "const_" + getName(i)));
    return res;
}

