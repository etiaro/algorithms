#include <iostream>
#include <vector>
using namespace std;

//złożoność jednorazowa max O(n)
//koszt zamortyzowany, można założyć że złożoność
//wszystkich wywołań razem wyniesie O(n)

//pozwala przyporządkowywać wierzchołki do innych, "większych",
//tworzy grupy wierzcholkow podpięte pod jeden "największy"

int find(int v, vector<int> &u) {
    if (u[v] == v) return u[v];
    u[v] = find(u[v], u);
    return u[v];
}

int main() {
    vector<int> u = {
        //przykladowy case, wszystkie mają ostatecznie union z 5
        1,
        2,
        3,
        4,
        5,
        5,
    };
    find(0, u);
    cout << u[0];
}