#pragma once
#ifndef	GLOBALVARIABLE_H
#define GOLBALVARIABLE_H

#include <vector>

#include "Variable.h"
#include "Function.h"

vector<Variable> AssemblyVarList; // ������������еı���
int blockcount = 0;//��ֹ����block

vector<sfunction> FuncList;//��ź���
vector<sfunction> FuncReturnList;//��ź������ͷ���ֵ����
string infunc;//��¼��ǰ�������ĸ������е����ݣ�������õ�ǰ����
int inLoop = 0;//������¼�ڵڼ�ѭ���У��������
string testtestevent;   //ֻ��¼״̬����
string testtestemit;
vector<Variable> VariableList;//���״̬����
vector<Variable> LocalVarList;//��žֲ�����
vector<Variable> GlobalVarList = { };//���ȫ�ֱ���

#endif