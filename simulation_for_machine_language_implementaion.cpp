#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>

using namespace std;
vector<pair<string, string>> cell(256);
vector<string> cell2(256);
int currentIndex;

class machine {
public:

};

class memory : public machine {
protected:
    static int cells, index;

    int returnhexa(string hex);

    string returndec(string n);

public:

    void loadMemory(string instruct);

    void merge();

    string readMemory();

    void displayMemory();
};

int memory::cells = 0;
int memory::index = 0;

void memory::loadMemory(string instruct) {
    // take string instruction and divide it into two string each one in different memory cell
    string l = instruct.substr(0, 2);
    cell2[cells] = l;
    cells++;
    string k = instruct.substr(2, 4);
    cell2[cells] = k;
    cells++;
    // cout<<l<<" "<<k<<endl;
}


int memory::returnhexa(string hex) {
    // take hexadecimal return decimal
    int size = hex.size(), base = 1, dec_val = 0;
    for (int i = size - 1; i >= 0; i--) {
        // If character lies in '0'-'9', so we will convert it to integral 0-9 by subtracting 48 from ASCII value
        if (hex[i] >= '0' && hex[i] <= '9') {
            dec_val += (int(hex[i]) - 48) * base;

            // incrementing base by power
            base *= 16;
        }

            // If character lies in 'A'-'F' , so we will convert it to integral 10 - 15 by subtracting 55 from ASCII value
        else if (hex[i] >= 'A' && hex[i] <= 'F') {
            dec_val += (int(hex[i]) - 55) * base;

            // Incrementing base by power
            base *= 16;
        }
    }
    return dec_val;
}

string memory::readMemory() {
    // to return instruction found in memory cell
    string inst = cell2[index];
    index++;
    inst += cell2[index];
    return inst;
}

void memory::displayMemory() {
    // print all memory cells
    int num = 0;
    while (num <= cells) {
        cout << num << " " << cell2[num] << endl;
        num++;
    }
}

string memory::returndec(string n) {

    string xnum;// the hexadecimal number
    int u = stoi(n);
    int i = 0;
    while (u != 0) {
        int temp;
        temp = u % 16;
        if (temp < 10) {
            xnum.push_back(temp + 48);
            i++;
        } else {
            xnum.push_back(temp + 55);
            i++;
        }
        u /= 16;
    }
    reverse(xnum.begin(), xnum.end());
    return xnum;
}


vector<string> registers(16);


class Register : public machine {
protected:
public:
    void loadInstructions(int r, string val);

    void displayRegister();
};

void Register::loadInstructions(int r, string val) {
    // load instruction
    registers[r - 1] = val;
}

void Register::displayRegister() {
    // print registers cells
    for (int i = 0; i < registers.size(); ++i)
        cout << "Register " << i + 1 << " contains " << registers[i] << endl;
}

class instruction : public memory {
protected:
    static int ind;
    int i = 0;
public:
    string instr;

    void loadInstruction() {
        // fetch instructions to execute
        i = ind;
        instr = cell2[i] + cell2[i + 1];
        ind++;
//        cout<<instr<<endl;
    }

    void decode() {
        if (instr[0] == '1') {
            // load containt saved in memory cell in register cell
            unsigned char c = instr[1] - '0';
            registers[int(c)] = cell2[returnhexa(instr.substr(2, 2))];
        } else if (instr[0] == '2') {
            //2456 causes register 4 to be loaded with 56
            unsigned char c = instr[1] - '0';
            registers[int(c)] = instr.substr(2, 2);
            // cout<<registers[int(c)]<<endl;
        } else if (instr[0] == '3') {
            //35B1 cause the contents of register 5 to be placed in the memory cell whose address is B1.
            unsigned char c = instr[1] - '0';
            cell2[returnhexa(instr.substr(2, 2))] = registers[int(c)];
        } else if (instr[0] == '4') {
            //4034 causes register 4 to be loaded with contents of register 3
            unsigned char a = instr[2] - '0', b = instr[3] - '0';
            cout << "a , b : " << registers[int(a)] << ' ' << registers[int(b)] << endl;
            registers[int(b)] = registers[int(a)];
            // cout<<"a , b : "<<registers[int(a)]<<' '<<registers[int(b)]<<endl;

        } else if (instr[0] == '5') {
            // 5726 the binary values in registers 2 and 6 to be added and the sum placed in register 7.
            string k = "", x = "", b = "";
            k += instr[1];
            x += instr[2];
            b += instr[3];
            unsigned char c = returnhexa(k), c1 = returnhexa(x), c2 = returnhexa(b);
            registers[c] = returndec(registers[c1] + registers[c2]);
            //cout<<registers[c];


        } else if (instr[0] == 'B') {
            if (registers[int(instr[0] - '0')] == registers[0]) {
                string add = "" + instr[2] + instr[3];
                currentIndex = returnhexa(add);
            }
        } else if (instr[0] == 'C') {
            return;
        }
    }
};

int instruction::ind = 0;

int main() {
    memory m;
    instruction ity;

    ifstream in("test.txt");
    if (in.is_open()) {
        string instruction;
        while (getline(in, instruction) && !in.eof()) {
            m.loadMemory(instruction);
        }
    }
    for (currentIndex = 0; currentIndex <= cell2.capacity(); currentIndex += 2) {
        ity.loadInstruction();
        ity.decode();
    }
    for (auto ds: registers) {
        cout << ds << endl;
    }
    return 0;
}
