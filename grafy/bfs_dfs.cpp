#include <iostream>
#include <queue>
#include <vector>
using namespace std;
//ZŁOŻONOŚĆ OBU O(n)

//odwiedza wierzcholki wszerz - po kolei wg odleglosci od startowego
void bfs(vector<vector<int>>& g, vector<bool> was, vector<int> p, int start) {
    queue<int> q;
    q.push(start);
    was[start] = true;
    while (!q.empty()) {
        int act = q.front();
        cout << "I visited" << act << " from " << p[act] << endl;
        q.pop();
        for (auto v : g[act])
            if (!was[v] && p[act] != v) {  //you can use here just one of if's(depends if you need p/was)
                q.push(v);
                p[v] = act;
                was[v] = true;
            }
    }
}

//odwiedza wierzcholki wgłąb, wchodząc jak najdalej się da, a potem się cofając
void dfs(vector<vector<int>>& g, vector<bool>& was, vector<int> p, int act) {
    cout << "I visited " << act << " from " << p[act] << endl;  //pre dfs operations
    was[act] = true;
    for (auto v : g[act])
        if (!was[v] && p[act] != v) {
            p[v] = act;
            dfs(g, was, p, v);
        }
    cout << "I leave " << act << endl;  //post dfs operations
}

int main() {
    vector<vector<int>> g(6);
    g[0] = {1, 2, 3};
    g[1] = {0, 2, 3, 4};
    g[2] = {0, 1, 3, 5};
    g[3] = {1, 2, 3};
    g[4] = {1};
    g[5] = {2};
    vector<bool> was(6, 0);
    vector<int> p(6, -1);
    cout << "BFS\n";
    bfs(g, was, p, 0);
    fill(p.begin(), p.end(), -1);
    fill(was.begin(), was.end(), 0);
    cout << "DFS\n";
    dfs(g, was, p, 0);
}