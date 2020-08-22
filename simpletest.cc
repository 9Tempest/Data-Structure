#include "vector.h"

int main(){
    Vector<int> v1 = Vector<int>();
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(3+1);
    v1.print();
    Vector<int> v2 = Vector<int>();
    v2.push_back(4);
    v1.swap(v2);
    v1.erase(v1.begin());
    v1.print();
    for (auto o = v2.begin(); o != v2.end(); ++o){
        std::cout << *o;
    }
    std::cout << std::endl;
}