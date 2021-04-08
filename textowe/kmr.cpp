#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

//Złożoność budowania O(n*log2^2(n))
//Złożoność zapytania O(1)

//Pozwala porównywać leksykograficznie fragmenty ciągu

template <typename T>
class KMR {  //DOSC DUZA STAŁA, ale niby n*log2^2(n)
   private:
    vector<T>* v;

   public:
    deque<vector<int>> kmr;
    int maxLvlSize = 1;
    bool full;

    KMR(vector<T>& v, bool countAll, bool full) : full(full), v(&v) {  //you must guarantee v will exist on every query of size <= 2
        //counting lvl 0 is other syntax :)
        maxLvlSize *= 2;
        if (full)
            kmr.push_back(vector<int>(v.size()));
        else
            kmr.push_back(vector<int>(v.size() - maxLvlSize + 1));
        set<pair<int, int>> s;
        for (int i = 0; i < kmr.back().size(); i++)
            s.insert({v[i], (i + 1 < v.size() ? v[i + 1] : -1)});

        map<pair<int, int>, int> m;
        int i = 0;
        for (auto it = s.begin(); it != s.end(); it++, i++)
            m[*it] = i;

        for (int i = 0; i < kmr.back().size(); i++)
            kmr.back()[i] = m[{v[i], (i + 1 < v.size() ? v[i + 1] : -1)}];

        if (countAll)
            while (maxLvlSize * 2 < v.size()) countNextLvl();
    }
    void countNextLvl() {
        maxLvlSize *= 2;
        if (full)
            kmr.push_back(vector<int>(v->size()));
        else
            kmr.push_back(vector<int>(v->size() - maxLvlSize + 1));
        set<pair<int, int>> s;
        for (int i = 0; i < kmr.back().size(); i++)
            s.insert({kmr[kmr.size() - 2][i],
                      (i + maxLvlSize / 2 < kmr[kmr.size() - 2].size() ? kmr[kmr.size() - 2][i + maxLvlSize / 2] : -1)});

        map<pair<int, int>, int> m;
        int i = 0;
        for (auto it = s.begin(); it != s.end(); it++, i++)
            m[*it] = i;

        for (int i = 0; i < kmr.back().size(); i++)
            kmr.back()[i] = m[{kmr[kmr.size() - 2][i],
                               (i + maxLvlSize / 2 < kmr[kmr.size() - 2].size() ? kmr[kmr.size() - 2][i + maxLvlSize / 2] : -1)}];
    }
    void removeLvl(int lvl) {  //WEIRD SYNTAX, if you delete lvls from begin, all gets moved!
        kmr[lvl].clear();
        kmr[lvl].shrink_to_fit();
        while (kmr.back().empty()) kmr.pop_back();
        while (kmr.front().empty()) kmr.pop_front();
        kmr.shrink_to_fit();
    }

    bool isEqual(int a, int b, int c, int d) {
        if (b - a != d - c) return false;
        int lvl = -1;
        int pow = 1;
        while (pow * 2 < b - a + 1) {
            lvl++;
            pow *= 2;
        }
        if (lvl == -1) return make_pair((*v)[a], (*v)[b]) == make_pair((*v)[c], (*v)[d]);  //a=b||a+1=b
        return make_pair(kmr[lvl][a], kmr[lvl][b - pow + 1]) == make_pair(kmr[lvl][c], kmr[lvl][d - pow + 1]);
    }

    bool isLower(int a, int b, int c, int d) {  //I assume "a" < "aa"
        int len = min(b - a + 1, d - c + 1);

        int lvl = -1;
        int pow = 1;
        while (pow * 2 < len) {
            lvl++;
            pow *= 2;
        }
        pair<int, int> v1, v2;
        if (lvl == -1) {
            v1 = {(*v)[a], (*v)[a + len - 1]};
            v2 = {(*v)[c], (*v)[c + len - 1]};
        } else {
            int diff = min((b - pow + 1) - a, (d - pow + 1) - c);
            v1 = {kmr[lvl][a], kmr[lvl][diff + a]};
            v2 = {kmr[lvl][c], kmr[lvl][diff + c]};
        }
        if (v1 == v2)
            return b - a < d - c;
        return v1 < v2;
    }

    bool isLowerOrEq(int a, int b, int c, int d) {
        if (isEqual(a, b, c, d)) return true;
        return isLower(a, b, c, d);
    }
};

template <typename T>
class Test {
   public:
    vector<T> v;
    Test(vector<T>& v) { this->v = v; }
    bool isEqual(int a, int b, int c, int d) {
        if (b - a != d - c) return false;
        for (int i = 0; i < b - a + 1; i++)
            if (v[a + i] != v[c + i]) return false;
        return true;
    }

    bool isLower(int a, int b, int c, int d) {
        int len = min(b - a + 1, d - c + 1);
        for (int i = 0; i < len; i++) {
            if (v[a + i] < v[c + i]) return true;
            if (v[a + i] > v[c + i]) return false;
        }
        return b - a < d - c;
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
        int n = 100000;  //random(1, 100000);
        vector<int> v = random(1, 10, n);
        KMR<int> k(v, true, true);
        /*Test<int> t(v);
        for (int a = 0; a < n; a++)
            for (int b = a; b < n; b++)
                for (int c = 0; c < n; c++)
                    for (int d = c; d < n; d++) {
                        int r1 = k.isLower(a, b, c, d);
                        int r2 = t.isLower(a, b, c, d);
                        int r3 = k.isEqual(a, b, c, d);
                        int r4 = t.isEqual(a, b, c, d);
                        if (r1 != r2 || r3 != r4) {
                            cout << n << " error\n";
                            cout << r1 << " vs bruted " << r2 << endl;
                            cout << r3 << " vs bruted " << r4 << endl;
                            return;
                        }
                    }*/
        cout << "ok";
    }
}

int main() {
    TESTER();

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    KMR<int> k(v, true, true);
}