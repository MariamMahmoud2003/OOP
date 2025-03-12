#include <iostream>
#include <vector>
using namespace std;
template <class T>
class Array{
    vector<T> v;
    int size;
public:
    Array(){
        size=0;
    }
    Array(int s) : size(s) , v(s){}
    void push(T value){
        if(size==0)
            cout<<"overflow\n";
        else {
            v.push_back(value);
            size--;
        }
    }
    void pop(){
        if(v.empty())
            cout<<"underflow\n";
        else
            v.pop_back();
    }
    void print (){
        for(T val : v)
            cout<<val<<' ';
        cout<<endl;
    }
};
int main() {
    Array<int> k (5);
    k.push(5);
    k.push(5);
    k.push(5);
    k.push(5);
    k.push(5);
    k.push(5);
    k.pop();
    k.print();
    k.pop();
    return 0;
}
