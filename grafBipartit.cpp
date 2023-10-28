//
// Created by email on 24.10.2023.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

const int NMAX = 100000;
vector <int> G[NMAX + 1];
int col[NMAX + 1];
bool ok = true;

void bfs(int x) {
    col[x] = 1;
    queue <int> q;
    q.push(x);
    while (!q.empty()) {
        x = q.front();
        q.pop();
        for(auto next : G[x]) {
            if(!col[next]) {
                col[next] = 3-col[x];
                q.push(next);
            }
            else
            if(col[next] == col[x])
                ok = false;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    while(m--) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i = 1; i <= n; i++) {
        if(!col[i])
            bfs(i);
    }
    if(!ok)
        cout << "IMPOSSIBLE";
    else
        for(int i = 1; i <= n; i++)
            cout << col[i] << " ";
    return 0;
}