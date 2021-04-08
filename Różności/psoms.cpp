#include <iostream>
#include <vector>
using namespace std;

//schemat dla algorytmów,
//raczej stworzony do szybkiego kopiowania i testowania

class Psoms {
   public:
    int res;
    Psoms(vector<int>& v) {
        res = 0;
        int act = 0;
        for (int i = 0; i < v.size(); i++) {
            act = max(0, act + v[i]);
            res = max(res, act);
        }
    }
};

int random(int from, int to) {
    return rand() % (to - from + 1) + from;
}

vector<int> random(int from, int to, int n) {
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        v[i] = random(from, to);
    return v;
}

void TESTER() {
    while (true) {
        int n = random(1, 1000000);
        vector<int> v = random(-10, 10, n);
        Psoms a(v);
        cout << "ok";
    }
}

int main() {
    TESTER();
}