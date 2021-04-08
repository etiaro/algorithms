#include <iostream>
#include <vector>
using namespace std;

//O(n)

//Algorytm za pomocą tablicy LOW znajduje wszystkie mosty w grafie

struct Edge {
    int fr, to, i;
};

class Mosty {
   private:
    vector<vector<Edge>>* g;
    vector<int> low, lvl;
    vector<bool> used;

   public:
    vector<int> pktart;
    Mosty(vector<vector<Edge>>& g, int m) : g(&g) {
        low = vector<int>(g.size());
        lvl = vector<int>(g.size(), -1);
        used = vector<bool>(m);
        for (int i = 0; i < g.size(); i++)
            if (lvl[i] == -1) {
                lvl[i] = 0;
                dfs(i);
            }
    }
    void dfs(int act) {
        low[act] = lvl[act];
        bool ispart = false;
        int num = 0;
        for (auto v : (*g)[act]) {
            if (used[v.i]) continue;
            if (lvl[v.to] == -1) {
                lvl[v.to] = lvl[act] + 1;
                used[v.i] = true;
                dfs(v.to);
                low[act] = min(low[act], low[v.to]);
                num++;
                if (low[v.to] >= lvl[act])
                    ispart = true;
            } else {
                low[act] = min(low[act], lvl[v.to]);
            }
        }
        if ((lvl[act] != 0 && ispart) || (lvl[act] == 0 && num >= 2))
            pktart.push_back(act);
    }
};

class Test {
   public:
    int get() { return 0; }
};

int random(int from, int to) {
    return rand() % (to - from + 1) + from;
}
vector<vector<Edge>> randomGraph(int n, int m) {  //robi losowy(niekoniecznie spojny) graf, ale bez krawedzi a->a
    vector<vector<Edge>> res(n);
    if (n == 1) return res;
    for (int i = 0; i < m; i++) {
        int a = random(0, n - 1);
        int b = a;
        while (b == a) b = random(0, n - 1);
        res[a].push_back({a, b, i});
        res[b].push_back({b, a, i});
    }
    return res;
}

void TESTER() {
    srand(124514);
    while (true) {
        int n = random(1, 100000), m = random(1, n * 2);
        vector<vector<Edge>> g = randomGraph(n, m);
        Mosty alg(g, m);
        Test t;
        cout << "ok";
    }
}

int main() {
    TESTER();
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back({a, b, i});
        g[b].push_back({b, a, i});
    }
    Mosty alg(g, m);
}