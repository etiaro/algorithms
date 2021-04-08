#include <iostream>
#include <vector>

//Złożoność O(n)

//Szuka najdluzszych prefiksosufiksów dla każdego fragmentu 0...i
//można wykorzystać do szukania wzorca w tekście podając jako tekst
//"wzorzec<NieIstniejącyZnak>tekst"(drugi konstruktor) i szukając gdzie prefiksosufiks
//ma wartosc równą długości wzorca

using namespace std;

template <typename T>
class KMP {
   private:
    vector<T> v;

   public:
    vector<int> p;
    int wzLen;
    void (*found)(int, int);
    KMP(vector<T> &v) {  //only pre-suf
        this->v = v;
        this->p = vector<int>(v.size());
        wzLen = -10;  //never found
        countP();
    }
    KMP(vector<T> &wz, vector<T> &v, T NonExist, void found(int, int)) {  //pre-suf with wzorzec
        this->v = wz;
        this->v.push_back(NonExist);

        this->v.insert(this->v.end(), v.begin(), v.end());
        this->p = vector<int>(wz.size() + 1 + v.size());
        wzLen = wz.size();
        this->found = found;
        countP();
    }
    void countP() {
        p[0] = 0;
        for (int i = 1; i < v.size(); i++) {
            int pref = p[i - 1];
            while (pref > 0 && v[i] != v[pref])
                pref = p[pref - 1];
            if (v[i] == v[pref])
                pref++;
            p[i] = pref;
            if (pref == wzLen) (*found)(i - 2 * wzLen, i - wzLen - 1);
        }
    }
};

template <typename T>
class Test {
   public:
    vector<T> v;
    Test(vector<T> &V) : v(V) {}
    int maxPreSuf(int pos) {
        int res = 0;
        for (int i = 1; i <= pos; i++) {
            bool can = true;
            for (int j = 0; j < i; j++) {
                if (v[pos - i + 1 + j] != v[j]) {
                    can = false;
                    break;
                }
            }
            if (can) res = i;
        }
        return res;
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
        int n = random(1000, 5000);
        vector<int> v = random(1, 2, n);
        KMP<int> a(v);
        Test<int> t(v);
        for (int i = 0; i < n; i++) {
            int r1 = a.p[i];
            int r2 = t.maxPreSuf(i);
            if (r1 > 10)
                break;
            if (r1 != r2) {
                cout << n << " error\n";
                cout << r1 << " vs bruted " << r2;
                return;
            }
        }
        cout << "ok";
    }
};

void FOUNDWZ(int beg, int end) {  //sample func
    cout << beg << " " << end << endl;
}

int main() {
    TESTER();

    int n, m;
    cin >> n >> m;
    vector<char> c(n), wz(m);
    for (int i = 0; i < n; i++) cin >> c[i];
    for (int i = 0; i < m; i++) cin >> wz[i];

    KMP<char> k(wz, c, (char)0, FOUNDWZ);  //sample use
}

/*

*/