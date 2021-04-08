#include <set>
#include <vector>

using namespace std;

int random(int from, int to) {
    return rand() % (to - from + 1) + from;
}

vector<int> random(int from, int to, int n) {
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        v[i] = random(from, to);
    return v;
}

vector<vector<int>> randomGraph(int n, int m) {  //robi losowy(niekoniecznie spojny) graf, ale bez krawedzi a->a
    vector<vector<int>> res(n);
    if (n == 1) return res;
    for (int i = 0; i < m; i++) {
        int a = random(0, n - 1);
        int b = a;
        while (b == a) b = random(0, n - 1);
        res[a].push_back(b);
        res[b].push_back(a);
    }
    return res;
}
vector<vector<int>> randomDiGraph(int n, int m) {  //robi losowy(niekoniecznie spojny) skierowany graf, ale bez krawedzi a->a
    vector<vector<int>> res(n);
    for (int i = 0; i < m; i++) {
        int a = random(0, n - 1);
        int b = a;
        while (b == a) b = random(0, n - 1);
        res[a].push_back(b);
    }
    return res;
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