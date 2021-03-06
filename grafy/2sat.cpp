#include <iostream>
using namespace std;
#include "silnie_spojne_skladowe.cpp"  //copy here SSS class

class TwoSat {  //ZEPSUTE NIE UŻYWAĆ
   public:
    vector<int> res;
    bool can = false;
    TwoSat(int n, vector<pair<int, int>> &w) {      //w = [{-1,2},[0,-1]...] max n-1
        vector<vector<int>> g(2 * n), gRev(2 * n);  //[0,^0,1,^1...]
        for (auto v : w) {
            int v1 = v.first < 0 ? 2 * (-v.first) + 1 : 2 * v.first;
            int v2 = v.second < 0 ? 2 * (-v.second) + 1 : 2 * v.second;
            int n1 = neg(v1);
            int n2 = neg(v2);
            g[n1].push_back(v2);
            g[n2].push_back(v1);
            gRev[v2].push_back(n1);
            gRev[v1].push_back(n2);
        }

        SSS s(g, gRev);
        for (int i = 0; i < g.size(); i++)
            if (s.sNum[i] == s.sNum[neg(i)]) {
                can = false;
                return;
            } else if (i % 2 == 0 && s.sNum[i] > s.sNum[neg(i)])
                res.push_back(i / 2);
        can = true;
    }
    int neg(int i) {
        return i % 2 == 0 ? i + 1 : i - 1;
    }
};

class Test {
   public:
    vector<pair<int, int>> w;
    int n;
    Test(int n, vector<pair<int, int>> &w) {
        this->w = w;
        this->n = n;
    }
    bool check(vector<int> sel) {
        vector<bool> is(n);
        for (int i = 0; i < sel.size(); i++) {
            is[sel[i]] = true;
        }
        for (auto v : w) {
            bool ok1, ok2;
            if (v.first >= 0)
                ok1 = is[v.first];
            else
                ok1 = !is[-v.first];
            if (v.second >= 0)
                ok2 = is[v.second];
            else
                ok2 = !is[-v.second];

            if (!(ok1 || ok2))
                return false;
        }
        return true;
    }
};

int random(int from, int to) {
    return rand() % (to - from + 1) + from;
}

void TESTER() {  //TESTED ONLY CORRECTNESS OF result, not checked when it throws cannot build
    while (true) {
        int n = random(1, 500000), m = random(0, 2 * n);
        vector<pair<int, int>> w(m);
        for (int i = 0; i < m; i++)
            w[i] = {random(-n + 1, n - 1), random(-n + 1, n - 1)};
        TwoSat a(n, w);
        Test t(n, w);
        if (a.can && !t.check(a.res)) {
            cout << n << " error\n";  //i'm not writing down tests, cause I set up here debug point and lookup values by hand :)
            cout << a.can;
            return;
        }
        cout << "ok";
    }
}

int main() {
    TESTER();
}