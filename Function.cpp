#include <vector>
#include "Function.h"
#include "Block.h"
#include "State.h"
#include "Test.h"
#include "Variable.h"

extern vector<sfunction> FuncList;//��ź���
extern vector<sfunction> FuncReturnList;//��ź������ͷ���ֵ����
extern string infunc;//��¼��ǰ�������ĸ������е����ݣ�������õ�ǰ����
extern string testtestevent;   //ֻ��¼״̬����
extern string testtestemit;
extern vector<Variable> VariableList;//���״̬����
extern vector<Variable> LocalVarList;//��žֲ�����
extern vector<Variable> ArrayList; // ����������
extern vector<Variable> ArrayList_b; // �������������
extern int blockcount;//��ֹ����block



// funcName ��ʾ��Ҫ���ɵĺ���������
// keyword ���뺯���Ŀɼ��ԣ����Ϊ0�����ѡ�����Ϊ1��̶�Ϊexternal
string genfunc(string funcName,int keyword,int otherContract) {
    string res;
    string sfuncname = funcName;
    int selector = otherContract;
    if(otherContract == 1) selector = rand() % 5000;                                     //////֮���ٵ�
    infunc = funcName;
    int svisibility;
    string sreturnPara;
    //�޸�״̬��1�޸�״̬����2�����¼�3����������Լ4����selfdestruct
    //5ͨ�����÷�����̫��6���÷�view��pure����7�����ͼ�����8ʹ�ð���ĳЩ��������������

    //��ȡ״̬��1��״̬�����ж�ȡ2����address(this).balance��address.balance
    //3����block tx msg���κγ�Ա(����msg.sig msg.data)
    //4���÷�pure����5ʹ�ð���ĳЩ��������������
    //enum funcstate
    //{
    //    eView,//���޸�״̬ 
    //    ePure//����ȡ���޸�״̬
    //};
    enum visibility
    {
        ePublic,
        ePrivate,
        eExternal,//ֻ�ܴӺ�Լ�ⲿ���ã����Ҫ�����ܺ�Լ�ڲ�������������ʹ��this��
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

    //���modifiy�����3����
    /*tmp = rand() % 3;
    for (int i = 0; i <= tmp; i++) {
        res += "mod" + to_string(i);
    }*/


    //���صı����ŵ��ֲ�����list�У�ͬʱ���������ͷ��ر����ı���������ϳ�һ���µı����ŵ�״̬����list��
    //returns(uint256 b_a)  ����b_a�����ں����в������κι��̡�
    int hasreturn = rand() % 2;
    if (selector == 1 && funcName == "func_c") {
        res += "returns (D) ";
    }else if (hasreturn == 1) {//�з���ֵ
        res += "returns(";
        int t = rand() % 2;//��������������ʱ�޶���uint��int����
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

    // ����unchecked����0.8�汾֮ǰ�������������������κδ���0.8�汾���������������Ứ�Ѳ���gas���Ѿ����е�����ָ�
    // ʹ��unchecked��ʹ��������Ϊ��0.8�汾ǰһ��
    res += "unchecked{\n";

    // ����һ��l_z����������ѭ���в���ѭ���������������޸�
    
    res += "uint256 l_z = 1;\n";

    if (selector == 1 && funcName == "func_b") {
        res += "func_c().func_a.selector;\n";
    }
    
    

    //���ɾֲ����� ����4��
    tmp = rand() % 2+1;
    //�����һ���ϸ��������ɵľֲ�����
    LocalVarList.clear();
    for (int i = 0; i < tmp; i++) {
        res += genVariable(LocalVarList, i, true);
    }

    //ȷ���ں���������������
    //��state�����ɺ�����
    res += state_make_random();
    res += testtestemit;
    if (hasreturn == 1) res += "\nreturn b_a;";
    if (selector == 1 && funcName == "func_c") {
        res += "return new D();\n";
    }
    res += "\n}\n"; // unchecked��������
    res += "\n}\n"; // ������������

    blockcount = 0;

    //���뺯���б�
    FuncList.emplace_back(sfunction(sfuncname, svisibility, sreturnPara));
    return res;
}