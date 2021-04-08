#include <iostream>
#include <queue>
#include <vector>
using namespace std;

//Złożoność O(m)

//pozwala posortować topologicznie wierzchołki acyklicznego grafu skierowanego(WAŻNE!)
//jak nie wiesz czy graf jest ok to puść na nim najpierw silnie spojne skladowe

class TopoSort {
   private:
    vector<vector<int>> *g;  //odwrocony graf
    vector<int> *we;         //stopnie wejscia wierzcholkow(zostaną zepsute!)
    static void helper(int) {}

   public:
    vector<int> topoNum;
    void (*next)(int) = helper;
    TopoSort(vector<vector<int>> &g, vector<int> &we, void next(int)) : g(&g), we(&we), next(next) {
        run();
    }
    TopoSort(vector<vector<int>> &g, vector<int> &we) : g(&g), we(&we) {
        run();
    }
    void run() {
        topoNum = vector<int>((*g).size());
        queue<int> q;
        int I = 0;
        for (int i = 0; i < (*g).size(); i++)
            if ((*we)[i] == 0) {
                q.push(i);
                next(i);
                topoNum[i] = I++;
            }
        while (!q.empty()) {
            int act = q.front();
            q.pop();
            for (auto v : (*g)[act]) {
                (*we)[v]--;
                if ((*we)[v] == 0) {
                    q.push(v);
                    next(v);
                    topoNum[v] = I++;
                }
            }
        }
    }
};

//not created tests, tested only by hand

void tmp(int n) {
    cout << n << " ";
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> we(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        we[b]++;
    }

    TopoSort t(g, we, tmp);
}