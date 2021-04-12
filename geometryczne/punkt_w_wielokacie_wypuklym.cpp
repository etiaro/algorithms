#include <bits/stdc++.h>
using namespace std;

// algorytm sprawdzający czy punkt leży wewnątrz wielokąta wypukłego w czasie O(log(n))
// punkt wielokąta o indeksie 0 musi mieć najmniejszą wspólrzędną y z całego wielokąta
// jeżeli istnieje wiele punktów o najmiejszym y, punkt 0 musi mieć najmniejszą współrzędną x spośród nich

struct point {
    int x;
    int y;
    point(int a, int b) {
        x = a;
        y = b;
    }

    point() {
        x = 0;
        y = 0;
    }
};

// funkcja signum
int sgn(int x) {
    return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

// wyznacznik
int det(point a, point b, point c) {
    return sgn(((b.x - a.x) * (c.y - a.y)) - ((b.y - a.y) * (c.x - a.x)));
}

// sprawdza czy punkt a leży wewnątrz wielokąta spełniającego warunki podane na początku programu
bool point_in_poly(vector<point> &vertices, point a) {
    int b = 1;
    int e = vertices.size() - 1;

    while (e - b > 1) {
        int mid = (b + e) / 2;
        if (det(vertices[0], vertices[mid], a) >= 0) {
            b = mid;
        } else {
            e = mid;
        }
    }

    int d1 = det(vertices[0], vertices[b], a);
    int d2 = det(vertices[b], vertices[e], a);
    int d3 = det(vertices[e], vertices[0], a);
    return (d1 >= 0) && (d2 >= 0) && (d3 >= 0);
}

int main(){
   int n, k;
   cin >> n >> k;

   vector<point> points;
   for (int i = 0; i < n; ++i) {
       point a;
       cin >> a.x >> a.y;
       points.push_back(a);
   }

   for (int i = 0; i < k; ++i) {
       point a;
       cin >> a.x >> a.y;
       cout << (point_in_poly(points, a) ? "t" : "n") << '\n';
   }
}
