#include <iostream>

class pooopoo{
    public:
        int x;

        pooopoo(int x) {
            x = x;
        }
};

int main() {
    pooopoo* p;

    if(!p) {
        std::cout << "hit\n";
    
    }
    return 0;

}
