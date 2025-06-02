#pragma once
#ifndef VARABLE_H
#define VARABLE_H

#include <cstring>
#include <string>
#include <vector>

using namespace std;
class Variable
{
public:
    Variable() = default;
    string Typename;//�洢������
    string Variablename;//������
    int num;//�洢������Ӧ��ֵ
    int a, b, c;//����������ά�����ȫΪ�㣬˵����������
    Variable(string tname, string vname) {
        Typename = tname;
        Variablename = vname;
    }
    Variable(string tname, string vname, int t) {
        Typename = tname;
        Variablename = vname;
        num = t;
        a = b = c = 0;
    }
    // ���飬l1 l2�Ƕ�ά����ĳ���,�����һά���飬��l2Ϊ��
    Variable(string tname,string vname,int l1,int l2){
        Typename = tname;
        Variablename = vname;
        a = l1;
        b = l2;
    }
};



string getName(int n);
string getUInt256();
string getInt256();
string getAdress();
string genVariable(vector<Variable>& VarList, int i, bool isLocal);
string genArray(vector<Variable>& VarList,int i);
string genConstVariable(vector<Variable>& VarList, int i);

#endif // !VARABLE_H
