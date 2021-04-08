#include <iostream>
#include <stack>
#include <vector>
using namespace std;

//Złożoność O(n)

//pozwala zgrupować wierzchołki w silnie spójne składowe
//oraz stworzyć skierowany graf acykliczny tych S. spójnych

class SSS {
   private:
    vector<vector<int>>*g, *gRev;
    stack<int> s;
    vector<bool> was;

   public:
    //if you dont need both sNum&sG, cut them of,
    //if you dont need sss, cut it of
    vector<vector<int>> sss;  //list of vertices in every group [group][i]=vertId
    vector<int> sNum;         //num of SSS for every vert
    vector<vector<int>> sG;   //graph of SSS
    vector<int> sGWe;         //st. wejscia grafu sG
    stack<int> stackTopo;
    bool make2SatStack;
    SSS(vector<vector<int>>& g, vector<vector<int>>& gRev, bool make2SatStack) : g(&g), gRev(&gRev) {
        s = stack<int>();
        was = vector<bool>(g.size());
        for (int i = 0; i < g.size(); i++)
            if (!was[i])
                dfsStack(i);

        sss = vector<vector<int>>();
        sNum = vector<int>(g.size(), -1);
        sG = vector<vector<int>>();
        sGWe = vector<int>();
        while (!s.empty()) {
            int act = s.top();
            s.pop();
            if (sNum[act] != -1) continue;
            if (make2SatStack)
                stackTopo.push(sss.size());
            sss.push_back(vector<int>());
            sG.push_back(vector<int>());
            sGWe.push_back(0);
            dfsCollect(act);
        }
    }
    void dfsStack(int act) {
        was[act] = true;
        for (auto v : (*g)[act])
            if (!was[v])
                dfsStack(v);
        s.push(act);
    }
    void dfsCollect(int act) {
        sss.back().push_back(act);
        sNum[act] = sss.size() - 1;
        for (auto v : (*gRev)[act]) {
            if (sNum[v] == -1) {
                dfsCollect(v);
            } else if (sNum[v] != sNum[act]) {
                sG[sNum[v]].push_back(sNum[act]);
                sGWe[sNum[act]]++;
            }
        }
    }
};

//Tested also by 2sat, so probably OK
//not created tester yet, tested only by hand
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n), gRev(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        gRev[b].push_back(a);
    }

    SSS s(g, gRev, false);
    cout << s.sss.size();
}