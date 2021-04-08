#include <iostream>
#include <set>
#include <vector>

using namespace std;

//O(n*log(n)) pamięciowo i obliczeniowo
//O(log(n)) znajdowanie przodka
//O(1) określanie czy u jest przodkiem v

//Lowest Common Anchestor służy do znajdowania najbliższego przodka
//dwóch wierzchołków w drzewie ukorzenionym(tutaj ukorzeniam w 0)

class LCA {
   private:
    vector<vector<int>> *g;
    vector<int> lasts, pre, post;
    int Pre, Post;

   public:
    vector<vector<int>> lca;
    LCA(vector<vector<int>> &g) : g(&g) {
        lca = vector<vector<int>>(g.size());
        lasts = vector<int>();
        pre = vector<int>(g.size());
        post = vector<int>(g.size());
        Pre = Post = 0;
        dfsBuild(0);
    }
    void dfsBuild(int act) {
        pre[act] = Pre++;
        for (int i = 1; i < lasts.size(); i *= 2) {  //ex. size = 10, we add here [9,8,6,2]
            lca[act].push_back(lasts[lasts.size() - i]);
        }
        if (lasts.size() > 0)
            lca[act].push_back(lasts[0]);
        lasts.push_back(act);
        for (auto v : (*g)[act])
            if (v != getP(act))
                dfsBuild(v);
        lasts.pop_back();
        post[act] = Post++;
    }
    int getP(int x) {
        if (lca[x].size() > 0)
            return lca[x][0];
        return -1;
    }
    bool isChild(int v, int p) {
        return pre[v] >= pre[p] && post[v] <= post[p];
    }

    int getLCA(int a, int b) {
        if (isChild(a, b)) return b;
        if (isChild(b, a)) return a;
        int i = a, j = lca[a].size() - 1;
        while (j >= 0) {
            if (j >= lca[i].size() || isChild(b, lca[i][j]))
                j--;
            else
                i = lca[i][j];
        }
        return lca[i][0];
    }
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

class Test {  //I assumed here that LCA.isChild and LCA.getP are working
   public:
    vector<vector<int>> g;
    Test(vector<vector<int>> g) : g(g) {}
    bool isOK(LCA &l) {
        for (int u = 0; u < g.size(); u++) {
            for (int v = u + 1; v < g.size(); v++) {
                int anch = l.getLCA(u, v);
                if (!l.isChild(u, anch) || !l.isChild(v, anch))
                    return false;  //anch is not CommonAnchestor
                for (auto x : g[anch]) {
                    if (x != l.getP(anch) && l.isChild(u, x) && l.isChild(v, x))
                        return false;  //we found child x of anch which is anchestor of v and u
                                       //it means anch is not LowestCA
                }
            }
        }
        return true;
    }
};

void TESTER() {
    while (true) {
        int n = random(1, 1000);
        vector<vector<int>> g = randomTree(n);
        LCA l(g);
        Test t(g);
        if (!t.isOK(l)) {
            cout << "error";
            return;
        }
        cout << "ok";
    }
}

int main() {
    TESTER();
}