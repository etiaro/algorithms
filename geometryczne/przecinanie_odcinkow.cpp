#include <bits/stdc++.h>
using namespace std;

struct point {
    int x;
    int y;
    point() { }
    point(int a, int b) {
        x = a;
        y = b;
    }
};

int sgn(int x) {
    return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

int det(point a, point b, point c) {
    return sgn(((b.x - a.x) * (c.y - a.y)) - ((b.y - a.y) * (c.x - a.x)));
}

bool inside_edge(point p, point e1, point e2) {
    return ((p.x >= min(e1.x, e2.x)) && 
            (p.y >= min(e1.y, e2.y)) &&
            (p.x <= max(e1.x, e2.x)) &&
            (p.y <= max(e1.y, e2.y)) &&
            (det(e1, e2, p) == 0));
}

bool intersects(point a1, point a2, point b1, point b2) {
    int d1 = (det(a1, a2, b1));
    int d2 = (det(a1, a2, b2));
    int d3 = (det(b1, b2, a1));
    int d4 = (det(b1, b2, a2));

    if ((d1 * d2 != 1) &&
        (d3 * d4 != 1)) {

        if (d1 == 0 && d2 == 0 && d3 == 0 && d4 == 0) {
            if (inside_edge(b1, a1, a2) || inside_edge(b2, a1, a2)) 
                return true;

            return false;
        } 
        return true;
    } 
    return false;
}

int main(){
    int n;
    cin >> n;
    while (n--) {
        point a1, b1, a2, b2;
        cin >> a1.x >> a1.y >> a2.x >> a2.y;
        cin >> b1.x >> b1.y >> b2.x >> b2.y;

        if (intersects(a1, a2, b1, b2)) {
            cout << "Tak\n";
        } else {
            cout << "Nie\n";
        }
    }
}
