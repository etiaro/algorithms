#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

//złożoność O(n*log(n))

//algorytm znajduje minimalne drzewo rozpinające grafu

struct Edge {
    int a, b, cost;
    bool operator<(Edge& e) {
        return cost < e.cost;
    }
};
class SpanningTree {
   private:
    vector<int> u;

   public:
    vector<Edge> edges;
    int cost;
    vector<vector<pair<int, int>>> tree;
    SpanningTree(int n, vector<Edge>& e) {
        sort(e.begin(), e.end());
        u = vector<int>(n);
        tree = vector<vector<pair<int, int>>>(n);
        edges = vector<Edge>();
        cost = 0;
        for (int i = 0; i < n; i++) u[i] = i;
        for (Edge act : e)
            if (find(act.a) != find(act.b)) {
                cost += act.cost;
                edges.push_back(act);
                u[find(act.a)] = u[find(act.b)];
                tree[act.a].push_back({act.b, act.cost});
                tree[act.b].push_back({act.a, act.cost});
            }
    }

    int find(int v) {
        if (u[v] == v) return u[v];
        u[v] = find(u[v]);
        return u[v];
    }
};

int random(int from, int to) {
    return rand() % (to - from + 1) + from;
}

void TESTER() {  //tested only for crashes, probably nothing to not work
    while (true) {
        int n = random(1, 10000), m = random(1, 2 * n);
        vector<Edge> e(m);
        for (int i = 0; i < m; i++)
            e[i] = {random(0, n - 1), random(0, n - 1), random(0, 10)};
        SpanningTree d(n, e);
        cout << "ok";
    }
}

int main() {
    TESTER();
}