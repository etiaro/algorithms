#include <iostream>
#include <set>
#include <vector>
using namespace std;

#define MAXD 2147483647
//Złożoność O(m*log(n))

//Służy do odnajdowania wszystkich najkrotszych sciezek od wierzcholka do innych

class Djkstra {
   public:
    vector<int> d;
    Djkstra(vector<vector<pair<int, int>>>& g, int start) {
        //implementacja na secie umozliwia usuwanie niepotrzebnych wierzcholkow - optymalizacja pamieci do O(n)
        d = vector<int>(g.size(), MAXD);
        set<pair<int, int>> s;
        s.insert({0, start});
        d[start] = 0;
        while (!s.empty()) {
            auto act = *s.begin();
            s.erase(s.begin());
            for (auto v : g[act.second]) {
                if (v.second + act.first < d[v.first]) {
                    if (d[v.first] != MAXD)
                        s.erase({d[v.first], v.first});
                    s.insert({v.second + act.first, v.first});
                    d[v.first] = v.second + act.first;
                }
            }
        }
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
        int n = random(1, 100000), m = random(1, 2 * n);
        vector<vector<pair<int, int>>> g = randomGraphWeights(n, m, 10);
        Djkstra d(g, 0);
        cout << "ok";
    }
}

int main() {
    TESTER();
}