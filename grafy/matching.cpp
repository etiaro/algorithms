#include <iostream>
#include <vector>
using namespace std;

//O(n^2) pesymistycznie, zwykle koło O(n*log(n))

//służy do matchowania wierzchołków w grafie dwudzielnym

class Turbomatching {
   private:
    vector<vector<int>> *g;
    vector<int> was;
    int wasI = 3;

   public:
    vector<int> partner;
    int matches;
    Turbomatching(vector<vector<int>> &g) : g(&g) {}

    void countMatch() {
        matches = 0;
        partner = vector<int>(g->size(), -1);
        for (int i = 0; i < g->size(); i++) {
            if (partner[i] == -1) {
                if (dfsMatch(i)) {
                    wasI++;
                    matches++;
                }
            }
        }
    }
    bool dfsMatch(int act) {
        was[act] = wasI;
        for (auto v : (*g)[act])
            if (partner[v] == -1) {
                partner[act] = v;
                partner[v] = act;
                return true;
            }
        for (auto v : (*g)[act])
            if (was[partner[v]] != wasI && dfsMatch(partner[v])) {
                partner[act] = v;
                partner[v] = act;
                return true;
            }
        return false;
    }

    bool isBipartite() {
        was = vector<int>((*g).size());
        for (int i = 0; i < g->size(); i++)
            if (was[i] == 0) {
                was[i] = 1;
                if (!bipartDfs(i)) return false;
            }
        return true;
    }
    bool bipartDfs(int act) {
        for (auto v : (*g)[act])
            if (was[v] == 0) {
                was[v] = was[act] == 1 ? 2 : 1;
                if (!bipartDfs(v)) return false;
            } else if (was[v] == was[act])
                return false;
        return true;
    }
};

int random(int from, int to) {
    return rand() % (to - from + 1) + from;
}
vector<vector<int>> randomGraph(int n, int m) {
    vector<vector<int>> res(n);
    for (int i = 0; i < m; i++) {
        int a = random(0, n - 1);
        int b = a;
        while (b == a) b = random(0, n - 1);
        res[a].push_back(b);
        res[b].push_back(a);
    }
    return res;
}

void TESTER() {  //tested only for crashes, but probably works :)
    while (true) {
        int n = random(2, 10000), m = random(1, 4 * n);
        vector<vector<int>> g = randomGraph(n, m);
        Turbomatching d(g);
        if (d.isBipartite()) {
            d.countMatch();
            cout << "ok";
            d.matches;
        }
    }
}
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    Turbomatching t(g);
    cout << t.isBipartite() << endl;
    t.countMatch();
    TESTER();
}