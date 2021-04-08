#include <iostream>
#include <vector>
using namespace std;

//Złożoność O(n)

//Pozwala odnajdować promienie najdłuższych palindromów w miejscu i
//results looks like this r[i] is palindrome r in index i
/* I - index of letter, i - index of palindrome center
I   0   1   2   3   4    5     6     7     8
i 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18

and values
A   B   A   A   B
1 0 3 0 1 4 1 0 1 bef div
0 0 1 0 0 2 0 0 0 DIVIDED by 2(done by default in constructor)

to access index on letter i = I*2+1
to access between index after letter i = I*2+2
to access between index before letter i = I*2
*/

template <typename T>
class Manacher {
   private:
    vector<T> v;

   public:
    vector<int> r;
    Manacher(vector<T>& c) {
        v = vector<T>(c.size() * 2);
        for (int i = 0; i < c.size(); i++)
            v[i * 2] = v[i * 2 + 1] = c[i];
        r = vector<int>(v.size() + 1);
        r[0] = 0;
        r[r.size() - 1] = 0;
        int i = 1, j = 0;
        while (i < r.size() - 1) {
            while (i - j - 1 >= 0 && i + j < v.size() && v[i - j - 1] == v[i + j])
                j++;
            r[i] = j;
            int k = 1;
            while (k < j && r[i - k] < j - k) {
                r[i + k] = r[i - k];
                k++;
            }
            j = max(0, j - k);
            i += k;
        }
        for (int i = 0; i < r.size(); i++)
            r[i] /= 2;
    }
};

template <typename T>
class Test {
   public:
    vector<T> v;
    Test(vector<T>& v) : v(v) {}
    int getLongest(int pos) {
        int i = 1;
        while (pos + i < v.size() && pos - i >= 0 && v[pos - i] == v[pos + i])
            i++;
        return i - 1;
    }
    int getLongestBetweenAfter(int pos) {
        int i = 0;
        while (pos - i >= 0 && pos + i + 1 < v.size() && v[pos - i] == v[pos + i + 1])
            i++;
        return i;
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
        int n = random(1, 100000000);
        vector<int> v = random(1, 10, n);
        Manacher<int> a(v);
        Test<int> t(v);
        for (int i = 1; i < a.r.size(); i++) {
            if (i % 2 == 0) {
                int r = t.getLongestBetweenAfter((i - 1) / 2);
                if (r != a.r[i]) {
                    cout << "error " << r << "bruted vs " << a.r[i];
                    return;
                }
            } else {
                int r = t.getLongest(i / 2);
                if (r != a.r[i]) {
                    cout << "error " << r << "bruted vs " << a.r[i];
                    return;
                }
            }
        }
        cout << "ok";
    }
}

int main() {
    TESTER();
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    Manacher<int> m(v);
}