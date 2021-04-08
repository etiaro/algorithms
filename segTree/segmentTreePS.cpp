#include <iostream>
#include <vector>
using namespace std;

//złożoność zapytania i zmiany O(log(n))
//zlozonosc pamieciowa O(n*log2(n))

//pozwala zmieniac wartosc w punkcie i
//zbierać sumy/maxy/(inne wartosci lączne) dla danego przedziału

struct segTreeNode {
    int sum = 0;
    void fillFromChilds(segTreeNode &ch1, segTreeNode &ch2) {
        sum = ch1.sum + ch2.sum;
    }
    void collect(segTreeNode &ch) {
        sum += ch.sum;
    }
    void change(segTreeNode &v) {
        sum = v.sum;
    }
};

class SegTreePS {  //point change -segment query
   public:
    vector<segTreeNode> tree;
    SegTreePS(vector<segTreeNode> &v) {
        initTree(v.size());
        for (int i = 0; i < v.size(); i++)
            tree[tree.size() / 2 + i] = v[i];

        for (int i = tree.size() / 2 - 1; i > 0; i--)
            fill(i);
    }
    SegTreePS(int size) {
        initTree(size);
    }
    void initTree(int n) {
        int size = 1;
        while (size < n * 2)
            size *= 2;
        tree = vector<segTreeNode>(size);
    }
    void fill(int a) {
        tree[a].fillFromChilds(tree[a * 2], tree[a * 2 + 1]);
    }
    void change(int a, segTreeNode &val) {
        a = tree.size() / 2 + a;
        tree[a].change(val);
        while (a != 1) {
            a /= 2;
            fill(a);
        }
    }
    segTreeNode query(int a, int b) {
        a = tree.size() / 2 + a;
        b = tree.size() / 2 + b;
        segTreeNode res = tree[a];
        if (a != b)
            res.collect(tree[b]);
        while (a / 2 != b / 2) {
            if (a % 2 == 0)
                res.collect(tree[a + 1]);
            if (b % 2 == 1)
                res.collect(tree[b - 1]);
            a /= 2;
            b /= 2;
        }
        return res;
    }
};

class Test {
   public:
    vector<segTreeNode> v;
    Test(vector<segTreeNode> v) : v(v) {}
    void change(int a, segTreeNode val) { v[a] = val; }
    segTreeNode query(int a, int b) {
        segTreeNode res = v[a];
        for (int i = a + 1; i <= b; i++)
            res.collect(v[i]);
        return res;
    }
};

int random(int from, int to) {
    return rand() % (to - from + 1) + from;
}
vector<segTreeNode> random(int from, int to, int n) {
    vector<segTreeNode> v(n);
    for (int i = 0; i < n; i++)
        v[i].sum = random(from, to);
    return v;
}

void TESTER() {
    while (true) {
        int n = random(1, 10000);
        vector<segTreeNode> v = random(1, 100000, n);
        SegTreePS a(v);
        Test t(v);
        int m = random(1, 10);
        for (int i = 0; i < m; i++) {
            int x = random(0, n - 1);
            segTreeNode v;
            v.sum = random(-10000, 10000);
            a.change(x, v);
            t.change(x, v);
            int x1 = random(0, n - 1);
            int x2 = random(x1, n - 1);
            segTreeNode r1 = a.query(x1, x2);
            segTreeNode r2 = t.query(x1, x2);
            if (r1.sum != r2.sum) {
                cout << n << " error\n";
                cout << r1.sum << " vs bruted " << r2.sum;
                return;
            }
        }
        cout << "ok";
    }
}

int main() {
    TESTER();
}