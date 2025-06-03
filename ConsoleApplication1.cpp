#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <string>
#include <cstring>
//#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
// #include "frame.h"
#include <shlwapi.h>


//#include "Ifelse.h"
//#include "Variable.h"
#include "Function.h"
//#include "Array.h"
//#include "Assembly.h"
//#include "Assign.h"
//#include "Block.h"
//#include "Loop.h"
//#include "State.h"

#include "Test.h"
#include "Variable.h"
#include "Frame.h"
using namespace std;


vector<Variable> AssemblyVarList;
int blockcount = 0;

vector<sfunction> FuncList;
vector<sfunction> FuncReturnList;
string infunc;
int inLoop = 0;
string testtestevent;
string testtestemit;
vector<Variable> VariableList;
vector<Variable> LocalVarList;
vector<Variable> GlobalVarList;
vector<Variable> ArrayList;
vector<Variable> ArrayList_b;
vector<Variable> ConstVariableList;

int main() {
    srand(time(0));
    ofstream fout;



    for (int i = 0; i < 10000; i++) {
        string res = getFrame();
        cout << "********" << i << "********" << endl;
        string testpath = "C:\\Users\\A\\Desktop\\paper\\testsuite\\";
        string contractpath = testpath + "test" + to_string(i);
        CreateDirectory(contractpath.c_str(), NULL);
        fout.open(contractpath + "/ContractName.sol");
        if (!fout.is_open()) cout << "could not open" << endl;
        fout << res;
        fout.close();
    }
    return 0;
}
