#include <algorithm>
#include <iostream>

using namespace std;

#include "kmr.cpp"  //JUST copy KMR class code here

//Złożoność O(n*log2^2(n)) - przez KMR, samo SA,LCP mają O(n*log(n)) i O(n)

//pozwala stworzyć posortowaną leksykograficznie tablicę suffixów(SA),
//ich pozycji w SA(RANK)
//oraz najdluższych wspolnych prefiksów tych suffixów(LCP)
//LCP[i] = najdluzszy wspolny prefix SA[i] oraz SA[i-1]

template <typename T>
class SuffixArray {  //WARNING! DOŚĆ DUŻA STAŁA KMR!
   public:
    vector<int> RANK, SA;
    vector<int> LCP;
    SuffixArray(vector<T>& v) {
        KMR<T> k(v, false, true);
        k.countNextLvl();
        while (k.maxLvlSize < v.size()) {
            k.removeLvl(0);
            k.countNextLvl();
        }
        k.removeLvl(0);
        RANK = k.kmr.back();

        vector<pair<int, int>> tmp(v.size());
        for (int i = 0; i < v.size(); i++)
            tmp[i] = {RANK[i], i};
        sort(tmp.begin(), tmp.end());

        SA = vector<int>(v.size());
        for (int i = 0; i < v.size(); i++)
            SA[i] = tmp[i].second;

        int u = 0;
        LCP = vector<int>(v.size());
        for (int i = 0; i < v.size(); i++) {
            if (RANK[i] == 0) continue;
            LCP[RANK[i]] = u;
            while (i + LCP[RANK[i]] < v.size() && SA[RANK[i] - 1] + LCP[RANK[i]] < v.size() && v[i + LCP[RANK[i]]] == v[SA[RANK[i] - 1] + LCP[RANK[i]]])
                LCP[RANK[i]]++;
            u = max(0, LCP[RANK[i]] - 1);
        }
    }
};

template <typename T>
class brute {
   public:
    vector<T> v;
    brute(vector<T>& v) : v(v) {}
    bool checkLCP(vector<int>& SA, vector<int>& LCP) {
        if (LCP[0] != 0)
            return false;
        for (int i = 1; i < LCP.size(); i++) {
            int r = sameNum(SA[i], SA[i - 1]);
            if (r != LCP[i])
                return false;
        }
        return true;
    }
    bool checkRANK(vector<int>& rank, vector<int>& SA) {  //it assumes SA is correct
        for (int i = 0; i < SA.size(); i++)
            if (SA[rank[i]] != i)
                return false;
        return true;
    }
    bool checkSA(vector<int>& SA) {
        for (int i = 1; i < SA.size(); i++)
            if (!isLower(SA[i - 1], SA[i]))
                return false;
        return true;
    }
    bool isLower(int a, int b) {
        for (int i = 0; i < min(v.size() - a, v.size() - b); i++) {
            if (v[a + i] < v[b + i]) return true;
            if (v[a + i] > v[b + i])
                return false;
        }
        return b < a;  //means a->end is shorter than b->end
    }
    int sameNum(int a, int b) {
        int i = 0;
        while (a + i < v.size() && b + i < v.size() && v[a + i] == v[b + i])
            i++;
        return i;
    }
};

void TESTEr() {
    while (true) {
        int n = 1000;  //random(1, 10000);
        vector<int> v = random(1, 10, n);
        SuffixArray<int> a(v);
        brute<int> t(v);

        if (!t.checkSA(a.SA) || !t.checkRANK(a.RANK, a.SA) || !t.checkLCP(a.SA, a.LCP)) {
            cout << n << " error\n";
            return;
        }
        cout << "ok";
    }
}

int main() {
    TESTEr();
}