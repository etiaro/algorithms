#include <iostream>
#include <vector>
using namespace std;

//O(n*log(n))

//algorytm sortuje ciąg rosnąco używając operatora <
//(w szczególności możesz go przeładować dla danego typu aby posortować ciąg malejąco :))

struct num {
    int n;
    num() : n(0) {}
    num(int x) : n(x) {}
};
bool operator<(num &i, num &i2) {
    return i.n > i2.n;
}

template <typename T>
class MergeSort {
   private:
    vector<T> *v;

   public:
    MergeSort(vector<T> &v) : v(&v) {
        merge(0, v.size() - 1);
    }
    void merge(int l, int r) {
        if (r < l)
            return;  //something gone wrong?
        if (l == r) return;
        int size = (r - l) / 2;
        merge(l, l + size);
        merge(l + size + 1, r);
        vector<T> tmp(r - l + 1);
        int i = l, j = l + size + 1;
        int x = 0;
        while (i <= l + size || j <= r) {
            if ((i <= l + size && (*v)[i] < (*v)[j]) || j > r)
                tmp[x++] = (*v)[i++];
            else
                tmp[x++] = (*v)[j++];
        }
        for (i = 0; i < r - l + 1; i++)
            (*v)[l + i] = tmp[i];
    }
};

template <typename T>
bool isOK(vector<T> &v) {
    for (int i = 1; i < v.size(); i++)
        if (v[i] < v[i - 1]) return false;
    return true;
}

int random(int from, int to) {
    return rand() % (to - from + 1) + from;
}

vector<num> random(int from, int to, int n) {
    vector<num> v(n);
    for (int i = 0; i < n; i++)
        v[i] = random(from, to);
    return v;
}
void TESTER() {
    while (true) {
        int n = 10000;  //random(1, 100000);
        vector<num> v = random(1, 10000000, n);
        MergeSort<num> m(v);
        if (!isOK(v)) {
            cout << "error";
            return;
        }
        cout << "ok";
    }
}

int main() {
    TESTER();
}