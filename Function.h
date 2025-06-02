#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <cstring>

using namespace std;

class sfunction
{
public:
    string funcname;//������
    int visbility;//�����ɼ��� 0 public 1 private 2 external 3 internal 
    //string funcstate;//����״̬
    string returnPara;//��������ֵ������Щ,�ݶ����һ������ֵ
    int paranum = 0;

    sfunction(const string& funcname, int visbility, const string& returnPara)
        : funcname(funcname), visbility(visbility), returnPara(returnPara)
    {
    }
    sfunction(const string& funcname,int paranum) : funcname(funcname), paranum(paranum) {}

    sfunction() = default;

    bool operator==(const sfunction& other) const
    {
        return funcname == other.funcname && visbility == other.visbility && returnPara == other.returnPara;
    }
};

string genfunc(string funcName,int keyword,int otherContract);

#endif // !FUNCTION_H
