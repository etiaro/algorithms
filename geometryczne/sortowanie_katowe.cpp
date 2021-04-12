#include <bits/stdc++.h>
using namespace std;

typedef   signed long long  ll;
typedef unsigned long long ull;

// struktura i operator porównywania umożliwiające sortowanie kątowe przy pomocy std::sort
// złożoność O(n*log(n)) ze względu na fukcję sortującą

// struktura do zapisywania punktów (może używać doubli albo ułamków zwykłych jak są konieczne)
struct point {
    int x;
    int y;
    point() { }
    point(int a, int b) {
        x = a;
        y = b;
    }
};

// punkt wedle którego sortujemy
point middle = point(0, 0);

// funkcja signum
int sgn(int x) {
    return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

// obliczanie wyznacznika (trzeba troche pozmieniać dla ułamków zwykłych)
int det(point a, point b, point c) {
    return sgn(((b.x - a.x) * (c.y - a.y)) - ((b.y - a.y) * (c.x - a.x)));
}

// operator potrzebny dla std::sort do porównywania elementów w wektorze (trzeba poprawić warunki przy ułamkach zwykłych)
bool operator< (point a, point b) {
    if (a.y >= 0 && b.y < 0)
        return true;
        
    if (a.y < 0 && b.y >= 0)
        return false;
        
    if (a.y == 0 && b.y == 0)
        return a.x > b.x;
        
    return det(middle, a, b) >= 0;
}

int main(){
    // przykładowe zastosowanie
    int n;
    cin >> n;
    vector<point> pointless_points;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        pointless_points.push_back(point(x, y));
    }

    sort(pointless_points.begin(), pointless_points.end());
}
