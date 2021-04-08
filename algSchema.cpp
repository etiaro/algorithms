#include <iostream>
using namespace std;

//schemat dla algorytmów,
//raczej stworzony do szybkiego kopiowania i testowania

class Alg {
   public:
    int get() { return 0; }
};

class Test {
   public:
    int get() { return 0; }
};

void TESTER() {
    while (true) {
        int n = rand();
        Alg a;
        Test t;
        int r1 = a.get();
        int r2 = t.get();
        if (r1 != r2) {
            cout << n << " error\n";  //i'm not writing down tests, cause I set up here debug point and lookup values by hand :)
            cout << r1 << " vs bruted " << r2;
            return;
        }
        cout << "ok";
    }
}

int main() {
    TESTER();
}