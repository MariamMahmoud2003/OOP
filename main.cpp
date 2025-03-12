#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
# include <map>
using namespace std;

map <string,string> mp;
vector <pair<string,string>> cell(256);

class memory {
    static int cells;
public :
    string inst;
    //vector <string> cell [256];
    memory ();
    memory (string m);
    void loadMemory(string k);
    string readMemory();
    void displayMemory();
    void fillCells ();
    friend class Register;
};
int memory :: cells =0;

memory :: memory (){
    cout<<"no instructions till now\n";
}

memory :: memory (string k){
    inst=k;
}

void memory::loadMemory(string m) {
    inst =m;
    string l = inst.substr(0,2);
    cell[cells].second = l;
    cells++;
    string k = inst.substr(2,4);
    cell[cells].second = k;
    cells++;
}

string memory ::readMemory() {
    return inst;
}

void memory ::displayMemory() {
    for(int i=0; i<cell.size();i+=2){
        cout << "Memory cell : " << i << "&" << i+1 << " instruction : "<<cell[i].second << cell[i+1].second << endl;
    }
}

void memory ::fillCells() {
    for(char c='0';c<='F';c++){
        if(c>'9' && c<'A')
            continue;
        for(char k='0';k<='F';k++) {
            if (k > '9' && k < 'A')
                continue;
            string ebaa ="" + c + k;
            mp[ebaa]="";
            ebaa.clear();
        }
    }
    int i=0;
    for (auto it = mp.begin(); it!=mp.end();++it){
        it->second = cell[i].second;
        i++;
    }
    for(auto val : mp)
        cout<<val.first<<" "<<val.second<<endl;
}


vector <int> saved(16);
class Register {
    static int registers;
    static int saves;
    int index;
public :

    string insts;
    int element ;
    Register ();
    Register (string k);
    void loadRegister();
    string readRegister ();
    void saveRegister (int k);
    void displayRegister();
    void loadCells();
    friend class Instruction;
};
int Register :: registers=0;
int Register :: saves=0;
Register ::Register() {
    cout<<"empty! \n";
}

Register ::Register(string k) {
    insts=k;
}

void Register ::loadRegister() {
    insts = cell[registers].second;
    registers++;
    insts+= cell[registers].second;
    registers++;
}

string Register ::readRegister() {
    return insts;
}

void Register ::loadCells() {
    for(int i=0; i<16;++i)
        saved [i]=i+1;

}

void Register ::saveRegister(int k) {
    element =k;
    saved[saves]=element;
    saves++;
}

void Register ::displayRegister() {
    cout<< "Register number : "<<index<<" contain : "<<element<<endl;
}

class Instruction {
public :
    void saveInRegister ();
    void add();
    void load ();
    void subtract ();
    void multiply ();
    void printInstruction ();
    friend class Register;

};

class CPU {
public:
    Register r[16];
    Instruction in;

};


class machine {
public :
    void readInstruction ();
    void loadInstruction ();
    memory m;
    CPU cpu;
};

int main() {
    machine k;
    k.cpu.r[0].loadRegister();
    return 0;
}