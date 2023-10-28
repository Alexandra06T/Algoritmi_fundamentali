//
// Created by email on 24.10.2023.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

/*
    O sortare topologica nu poate avea loc daca graful are circuite. Daca in parcurgerea DFS gasim in vecinii unui nod
    un nod vizitat, dar nu finalizat, inseamna ca muchia care le leaga este un arc de intoarcere care inchide un circuit.
    Daca nu avem circuit:
    o sortare topologica <=> oricare uv muchie din graf u se afla inaintea lui v in sortare
    in parcurgerea dfs, daca uv muchie din graf => fin[u] > fin[v]
    Deci, parcurgem dfs graful, dar afisam in ordine inversa finalizarii nodurile
*/

const int NMAX = 100000;
int vis[NMAX + 1]; //vis = 1, daca nodul a fost descoperit , vis = 2, daca nodul a fost finalizat
vector <int> G[NMAX + 1];
stack <int> s;
bool circuit = false;

void dfs(int u) {
    // marcam nodul ca vizitat
    vis[u] = 1;
    for(auto next : G[u]) {
        //daca vecinul nu a fost vizitat
        if(!vis[next]) {
            //continuam parcurgerea
            dfs(next);
        }
        else if(vis[next] == 1){
            //are circuit. iesim
            circuit = true;
            return;
        }
    }
    //punem pe stiva nodul finalizat
    s.push(u);
    //il marcam ca finalizat
    vis[u] = 2;
}

int main() {
    //citim graful ca lista de muchii si il asezam intr-o lista de adiacenta
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
    }

    //facem dfs pe toate componentele
    for(int i = 1; i <= n && !circuit; i++) {
        if(!vis[i])
            dfs(i);
    }

    if(!circuit) {
        //afisam sortarea topologica
        while(!s.empty()) {
            int u = s.top();
            s.pop();
            cout << u << " ";
        }
    }
    else
        //avem circuit
        cout << "IMPOSSIBLE";
    return 0;
}
