#include <bits/stdc++.h>
using namespace std;

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

    bool operator== (point a) {
        return (a.x == x) && (a.y == y);
    }
    void operator-= (point a) {
        x -= a.x;
        y -= a.y;
    }
};

int sgn(int x) {
    return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

int det(point a, point b, point c) {
    return sgn(((b.x - a.x) * (c.y - a.y)) - ((b.y - a.y) * (c.x - a.x)));
}

point middle(0, 0);
bool operator< (point a, point b) {
    if (a.y >= 0 && b.y < 0)
        return true;
        
    if (a.y < 0 && b.y >= 0)
        return false;
        
    if (a.y == 0 && b.y == 0)
        return a.x > b.x;
        
    int d = det(middle, a, b);
    return d > 0 || (d == 0 && (a.x*a.x + a.y*a.y) < (b.x*b.x + b.y*b.y));
}

int main(){
    int n;
    cin >> n;

    vector<point> vertices;
    point origin;
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        vertices.push_back(point(x, y));
        if (origin.y > y) {
            origin = point(x, y);
        }
        if (origin.y == y && origin.x > x) {
            origin = point(x, y);
        }
    }

    for (auto &e : vertices) {
        e -= origin;
    }

    sort(vertices.begin(), vertices.end());

    stack<point> solution;
    solution.push(vertices[0]);
    solution.push(vertices[1]);
    point prev = point(0, 0);

    for (int i = 1; i < n; ++i) {
        while (det(prev, solution.top(), vertices[i]) == -1) {
            solution.pop();
        } 
        prev = solution.top();
        solution.push(vertices[i]);
    }
    if (det(prev, solution.top(), point(0, 0)) == -1) 
        solution.pop();

    stack<point> tmp;
    while (!solution.empty()) {
        tmp.push(solution.top());
        solution.pop();
    }
    
    while (!tmp.empty()) {
        cout << tmp.top().x << " " << tmp.top().y << '\n';
        tmp.pop();
    }
}
