#include <iostream>
#include <vector>
using namespace std;

//złożoność zapytania i zmiany O(log(n))
//zlozonosc pamieciowa O(n*log2(n))

//pozwala zmieniac wartosc w przedziale i
//zbierać sumy/maxy/(inne wartosci lączne) dla danego przedziału

#define MAXINT 1999999999

struct segTreeNodeSamp {  //sample for {add on seg, sum on seg}
    int val = 0;
    void fillFromChilds(segTreeNodeSamp &ch1, segTreeNodeSamp &ch2) {  //called on init and after every tree insert
        val = ch1.val + ch2.val;
    }
    void collect(segTreeNodeSamp &ch) {  //collects nodes together to res on query
        val += ch.val;
    }
    void change(segTreeNodeSamp &v, int leaves) {  //changes on propagate and on tree insert(also called for changing propTree)
        val += v.val * leaves;
    }
};
struct segTreeNodeSamp2 {  //sample for {add on seg, max on seg}
    int val = 0;
    int Max = 0;
    void fillFromChilds(segTreeNodeSamp2 &ch1, segTreeNodeSamp2 &ch2) {  //called on init and after every tree insert
        Max = max(ch1.Max, ch2.Max);
    }
    void collect(segTreeNodeSamp2 &ch) {  //collects nodes together to res on query
        Max = max(Max, ch.Max);
    }
    void change(segTreeNodeSamp2 &v, int leaves) {  //changes on propagate and on tree insert(also called for changing propTree)
        val += v.val;
        Max += v.val;
    }
};

struct segTreeNode {  //sample for {set on seg, sum on seg}
    int val = 0;      //THIS ONE - the most buggy one of all trees!
    int sum = 0;
    int lazy = -1;
    void fillFromChilds(segTreeNode &ch1, segTreeNode &ch2) {  //called on init and after every tree insert
        sum = ch1.sum + ch2.sum;
    }
    void collect(segTreeNode &ch) {  //collects nodes together to res on query
        sum += ch.sum;
    }
    void change(segTreeNode &v, int leaves) {  //changes on propagate and on tree insert(also called for changing propTree)
        if (lazy < v.lazy) {
            val = v.val;
            lazy = v.lazy;
            sum = val * leaves;
        }
    }
};

class SegTreeSS {  //segment change -point query
   public:
    vector<segTreeNode> tree, propTree;
    SegTreeSS(vector<segTreeNode> &v) {
        initTree(v.size());
        for (int i = 0; i < v.size(); i++)
            tree[tree.size() / 2 + i] = v[i];

        for (int i = tree.size() / 2 - 1; i > 0; i--)
            fill(i);
    }
    SegTreeSS(int size) {
        initTree(size);
    }
    void initTree(int n) {
        int size = 1;
        while (size < n * 2)
            size *= 2;
        tree = vector<segTreeNode>(size);
        propTree = vector<segTreeNode>(size);
    }
    void fill(int a) {
        tree[a].fillFromChilds(tree[a * 2], tree[a * 2 + 1]);
    }
    void propagate(int a, int lvl) {
        if (a > 1) propagate(a / 2, lvl * 2);
        if (a * 2 + 1 < tree.size()) {
            propTree[a * 2].change(propTree[a], 1);
            propTree[a * 2 + 1].change(propTree[a], 1);
            tree[a * 2].change(propTree[a], lvl / 2);
            tree[a * 2 + 1].change(propTree[a], lvl / 2);
            propTree[a] = segTreeNode();
        }
    }
    void change(int a, int b, segTreeNode val) {  //TODO fix this crap
        a = tree.size() / 2 + a;
        b = tree.size() / 2 + b;
        propagate(a, 1);
        propagate(b, 1);
        int _a = a / 2;
        int _b = b / 2;
        int lvl = 1;
        tree[a].change(val, lvl);
        if (a != b) tree[b].change(val, lvl);
        while (a / 2 != b / 2) {
            if (a % 2 == 0) {
                tree[a + 1].change(val, lvl);
                propTree[a + 1].change(val, 1);
            }
            if (b % 2 == 1) {
                tree[b - 1].change(val, lvl);
                propTree[b - 1].change(val, 1);
            }
            a /= 2;
            b /= 2;
            lvl *= 2;
        }

        while (_a != _b) {
            fill(_a);
            fill(_b);
            _a /= 2;
            _b /= 2;
        }
        while (_a != 0) {
            fill(_a);
            _a /= 2;
        }
    }
    segTreeNode query(int a, int b) {
        a = tree.size() / 2 + a;
        b = tree.size() / 2 + b;
        propagate(a, 1);
        propagate(b, 1);
        segTreeNode res = tree[a];
        if (a != b) res.collect(tree[b]);
        while (a / 2 != b / 2) {
            if (a % 2 == 0) res.collect(tree[a + 1]);
            if (b % 2 == 1) res.collect(tree[b - 1]);
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
    void change(int a, int b, segTreeNode val) {
        for (int i = a; i <= b; i++)
            v[i].change(val, 1);
    }
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
        v[i].val = v[i].sum = random(from, to);
    return v;
}

void TESTER() {
    srand(51443281);
    while (true) {
        int n = random(1, 100);
        vector<segTreeNode> v = random(1, 1000, n);
        SegTreeSS a(v);
        Test t(v);
        int m = 100;  //random(1,10);
        for (int i = 0; i < m; i++) {
            int x1 = random(0, n - 1);
            int x2 = random(x1, n - 1);
            segTreeNode v;
            v.val = v.sum = random(-1000, 1000);
            a.change(x1, x2, v);
            t.change(x1, x2, v);
            for (int X1 = 0; X1 < n; X1++)
                for (int X2 = X1; X2 < n; X2++) {
                    segTreeNode r1 = a.query(X1, X2);
                    segTreeNode r2 = t.query(X1, X2);
                    if (r1.sum != r2.sum) {
                        cout << n << " error\n";
                        cout << r1.sum << " vs bruted " << r2.sum;
                        return;
                    }
                }
            /*x1 = random(0, n - 1);
            x2 = random(x1, n - 1);
            segTreeNode r1 = a.query(x1, x2);
            segTreeNode r2 = t.query(x1, x2);
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