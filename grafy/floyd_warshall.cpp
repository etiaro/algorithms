#include <iostream>
#include <vector>
using namespace std;

#define MAXD 2147483647
//Złożoność O(n^3)
//Niby djkstra z kazdego wierzcholka ma optymistycznie O(n^2*log(n)),
//ale pesymiestycznie to będzie O(n^3*log(n)) z większą stałą, więc wybierz mądrze

class FloydWarshall {
   public:
    vector<vector<int>> d;
    FloydWarshall(vector<vector<pair<int, int>>> &g) {
        d = vector<vector<int>>(g.size(), vector<int>(g.size(), MAXD));
        for (int u = 0; u < g.size(); u++)
            for (auto v : g[u])
                d[u][v.first] = min(d[u][v.first], v.second);
        for (int i = 0; i < g.size(); i++)
            d[i][i] = 0;

        for (int u = 0; u < g.size(); u++)
            for (int v = 0; v < g.size(); v++)
                for (int x = 0; x < g.size(); x++)
                    d[v][x] = min(d[v][x], d[v][u] + d[u][x]);
    }
};

int random(int from, int to) {
    return rand() % (to - from + 1) + from;
}
vector<vector<pair<int, int>>> randomGraphWeights(int n, int m, int C) {
    vector<vector<pair<int, int>>> res(n);
    for (int i = 0; i < m; i++) {
        int a = random(0, n - 1);
        int b = a;
        while (b == a) b = random(0, n - 1);
        int c = random(0, C);
        res[a].push_back({b, c});
        res[b].push_back({a, c});
    }
    return res;
}

void TESTER() {  //tested only for crashes, probably nothing to not work
    while (true) {
        int n = random(1, 500), m = random(1, 2 * n);
        vector<vector<pair<int, int>>> g = randomGraphWeights(n, m, 10);
        FloydWarshall d(g);
        cout << "ok";
    }
}

int main() {
    TESTER();
}