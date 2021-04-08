#include <iostream>
#include <vector>
using namespace std;

//złożoność zapytania i zmiany O(log(n))
//zlozonosc pamieciowa O(n*log2(n))

//pozwala zmieniac wartosc w przedziale i
//zapytac o wartosc w punkcie

#define MAXINT 1999999999

struct segTreeNodeSamp {  //sample for operations {add on seg, get val on point}
    int val = 0;
    void fillFromChilds(segTreeNodeSamp &ch1, segTreeNodeSamp &ch2) {
        //nothing to do here
    }
    void collect(segTreeNodeSamp &ch) {
        val += ch.val;
    }
    void change(segTreeNodeSamp &v) {
        val += v.val;
    }
};
struct segTreeNode {  //sample for {set on seg, get on point}
    int val = MAXINT;
    int lazy = -1;
    void fillFromChilds(segTreeNode &ch1, segTreeNode &ch2) {
        //nothing to do here
    }
    void collect(segTreeNode &ch) {
        if (ch.lazy > lazy) {
            val = ch.val;
            lazy = ch.lazy;
        }
    }
    void change(segTreeNode &v) {
        if (v.lazy > lazy) {
            val = v.val;
            lazy = v.lazy;
        }
    }
};

class SegTreeSP {  //segment change -point query
   public:
    vector<segTreeNode> tree;
    SegTreeSP(vector<segTreeNode> &v) {
        initTree(v.size());
        for (int i = 0; i < v.size(); i++)
            tree[tree.size() / 2 + i] = v[i];

        for (int i = tree.size() / 2 - 1; i > 0; i--)
            fill(i);
    }
    SegTreeSP(int size) {
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
    void change(int a, int b, segTreeNode val) {
        a = tree.size() / 2 + a;
        b = tree.size() / 2 + b;
        tree[a].change(val);
        if (a != b) tree[b].change(val);
        while (a / 2 != b / 2) {
            if (a % 2 == 0) tree[a + 1].change(val);
            if (b % 2 == 1) tree[b - 1].change(val);
            a /= 2;
            b /= 2;
        }
    }
    segTreeNode query(int a) {
        a = tree.size() / 2 + a;
        segTreeNode res = tree[a];
        while (a != 1) {
            a /= 2;
            res.collect(tree[a]);
        }
        return res;
    }
};

class Test {
   public:
    vector<segTreeNode> v;
    Test(vector<segTreeNode> v) : v(v) {}
    void change(int a, int b, segTreeNode val) {
        for (int i = a; i <= b; i++)
            v[i].change(val);
    }
    segTreeNode query(int a) {
        return v[a];
    }
};

int random(int from, int to) {
    return rand() % (to - from + 1) + from;
}
vector<segTreeNode> random(int from, int to, int n) {
    vector<segTreeNode> v(n);
    for (int i = 0; i < n; i++)
        v[i].val = random(from, to);
    return v;
}

void TESTER() {
    while (true) {
        int n = random(1, 1000);
        vector<segTreeNode> v = random(1, 1000, n);
        SegTreeSP a(v);
        Test t(v);
        int m = random(1, 1000);
        for (int i = 0; i < m; i++) {
            int x1 = random(0, n - 1);
            int x2 = random(x1, n - 1);
            segTreeNode v;
            v.val = random(-100000, 100000);
            v.lazy = i;
            a.change(x1, x2, v);
            t.change(x1, x2, v);
            for (int x = 0; x < n; x++) {
                segTreeNode r1 = a.query(x);
                segTreeNode r2 = t.query(x);
                if (r1.val != r2.val) {
                    cout << n << " error\n";
                    cout << r1.val << " vs bruted " << r2.val;
                    return;
                }
            }
            /*int x = random(0, n - 1);
            segTreeNode r1 = a.query(x);
            segTreeNode r2 = t.query(x);
            if (r1.val != r2.val) {
                cout << n << " error\n";
                cout << r1.val << " vs bruted " << r2.val;
                return;
            }*/
        }
        cout << "ok";
    }
}

int main() {
    TESTER();
}