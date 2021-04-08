#include <iostream>
#include <set>
#include <vector>
using namespace std;

//O(n) dla findCent, O((n+T(n))*log(n)) dla decomposition, gdzie T(n) to zlozonosc naszych operacji
//na jednej czesci grafu
//n w obu ma małą stałą, zazwyczaj w przybliżeniu wychodzi O(1), pesymistycznie O(n/2)

//Algorytm służy do znajdowania centroidów oraz wykonywania algorytmów divide and conquer na

class Centroid {
   private:
    vector<vector<int>>* g;
    vector<int> p, ile;
    vector<bool> kicked;

   public:
    Centroid(vector<vector<int>>& g) : g(&g) {
        p = vector<int>(g.size(), -1);
        ile = vector<int>(g.size(), 1);
        kicked = vector<bool>(g.size());
        for (int i = 0; i < g.size(); i++)
            if (p[i] == -1)
                dfs(i);
    }
    void dfs(int act) {
        for (auto v : (*g)[act])
            if (v != p[act]) {
                p[v] = act;
                dfs(v);
                ile[act] += ile[v];
            }
    }
    int findCent(int act, int size) {
        for (auto v : (*g)[act]) {
            if (!kicked[v] && ile[v] > size / 2) {
                int tmp = ile[act];
                ile[act] -= ile[v];
                ile[v] += tmp - ile[v];
                return findCent(v, size);
            }
        }
        return act;
    }

    void decomposition(int v) {  //this should be run from every tree in graph(and recursively will be run on every node)
        int c = findCent(v, ile[v]);
        //cout << "pre Ops size " << ile[c] << " in " << c << endl;
        //call here some pre function
        kicked[c] = true;
        for (auto u : (*g)[c]) {
            if (!kicked[u]) {
                decomposition(u);
                //you can even count something for u and then sum it up here in v
            }
        }
        kicked[c] = false;
        //call here some post function
        //cout << "    post Ops size " << ile[c] << " in " << c << endl;
    }
};

class Test {
   public:
    int get() { return 0; }
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
vector<vector<int>> randomTree(int n) {
    vector<vector<int>> res(n);
    if (n == 1) return res;
    vector<int> pruferSeq = random(0, n - 1, n - 2);
    vector<int> deg(n, 1);
    for (auto x : pruferSeq)
        deg[x]++;
    set<int> cand;
    for (int i = 0; i < n; i++)
        if (deg[i] == 1) cand.insert(i);

    for (auto x : pruferSeq) {
        res[x].push_back(*cand.begin());
        res[*cand.begin()].push_back(x);
        deg[x]--;
        deg[*cand.begin()]--;
        cand.erase(cand.begin());
        if (deg[x] == 1)
            cand.insert(x);
    }
    //here we should be left with 2 vertices in cand, which have deg = 1
    res[*cand.begin()].push_back(*cand.rbegin());
    res[*cand.rbegin()].push_back(*cand.begin());
    return res;
};

void TESTER() {  //tested if sum of all n in called count(n) is lower than n*log(n)
                 //and if all nodes were called in decomposition
    while (true) {
        int n = 100000;  //random(2, 100000);
        vector<vector<int>> g = randomTree(n);
        Centroid c(g);
        c.decomposition(0);
        cout << "ok" << n << endl;
    }
}

int main() {
    TESTER();
}