#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Złożoność O(n) dla stworzenia tablic
//O(1) dla zapytań
//Używaj podwójnego jeżeli pojedyńcze ma zbyt dużą szansę na konfilkt(reszty różnych fragmentów się "nachodzą")

//Pozwala na porównywanie identyczności zadanych fragmentów całego ciągu w czasie stałym
//brutalnie czas jest liniowy

#define LL long long int

#define mod 1000000009
#define P 29172384

#define mod2 1000000007
#define P2 84658192

class Hash {
   public:
    vector<LL> hash, pows;
    vector<LL> hash2, pows2;
    bool doubleH = false;
    Hash(vector<int> &v, bool doubleH) {
        this->doubleH = doubleH;
        pows = vector<LL>(v.size());
        hash = vector<LL>(v.size());
        pows[0] = 1;
        hash[0] = v[0];
        if (doubleH) {
            pows2 = vector<LL>(v.size());
            hash2 = vector<LL>(v.size());
            pows2[0] = 1;
            hash2[0] = v[0];
        }
        for (int i = 1; i < v.size(); i++) {
            pows[i] = (pows[i - 1] * P) % mod;
            hash[i] = (v[i] * pows[i]) % mod;
            hash[i] = (hash[i] + hash[i - 1]) % mod;
            if (doubleH) {
                pows2[i] = (pows2[i - 1] * P2) % mod2;
                hash2[i] = (v[i] * pows2[i]) % mod2;
                hash2[i] = (hash2[i] + hash2[i - 1]) % mod2;
            }
        }
    }
    Hash(string &v, bool doubleH) {
        this->doubleH = doubleH;
        pows = vector<LL>(v.size());
        hash = vector<LL>(v.size());
        pows[0] = 1;
        hash[0] = v[0];
        if (doubleH) {
            pows2 = vector<LL>(v.size());
            hash2 = vector<LL>(v.size());
            pows2[0] = 1;
            hash2[0] = v[0];
        }
        for (int i = 1; i < v.size(); i++) {
            pows[i] = (pows[i - 1] * P) % mod;
            hash[i] = (v[i] * pows[i]) % mod;
            hash[i] = (hash[i] + hash[i - 1]) % mod;
            if (doubleH) {
                pows2[i] = (pows2[i - 1] * P2) % mod2;
                hash2[i] = (v[i] * pows2[i]) % mod2;
                hash2[i] = (hash2[i] + hash2[i - 1]) % mod2;
            }
        }
    }
    LL val(int fr, int to, bool sec) {
        if (sec) {
            LL res = fr > 0 ? (hash2[to] - hash2[fr - 1] + mod2) % mod2 : hash2[to];
            res = (res * pows2[hash2.size() - to - 1]) % mod2;
            return res;
        } else {
            LL res = fr > 0 ? (hash[to] - hash[fr - 1] + mod) % mod : hash[to];
            res = (res * pows[hash.size() - to - 1]) % mod;
            return res;
        }
    }
    bool cmp(int a, int b, int c, int d) {
        if (b - a != d - c) return false;
        if (doubleH)
            return val(a, b, false) == val(c, d, false) && val(a, b, true) == val(c, d, true);
        return val(a, b, false) == val(c, d, false);
    }
};

class Test {
   public:
    vector<int> v;
    Test(vector<int> &x) {
        v = x;
    }
    bool cmp(int a, int b, int c, int d) {
        if (b - a != d - c) return false;
        for (int x = 0; x <= b - a; x++)
            if (v[a + x] != v[c + x]) return false;
        return true;
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

void TESTER() {
    while (true) {
        int n = random(1, 200);
        vector<int> v = random(1, 20, n);
        Hash a(v, true);
        Test t(v);
        for (int x1 = 0; x1 < n; x1++)
            for (int x2 = x1; x2 < n; x2++)
                for (int x3 = 0; x3 + (x2 - x1) < n; x3++) {
                    int x4 = x3 + (x2 - x1);
                    int r1 = a.cmp(x1, x2, x3, x4);
                    int r2 = t.cmp(x1, x2, x3, x4);
                    if (r1 != r2) {
                        cout << n << " error\n";
                        cout << r1 << " vs bruted " << r2;
                        return;
                    }
                }

        cout << "ok";
    }
}

int main() {
    TESTER();
}