#include <iostream>

using namespace std;

void test(int a) {
    cout << a;
}

int main() {
    void (*func)(int x) {
        cout << x;
    };
    func(1);
}