#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

/*
 * Algoritmul Kosaraju
 * Componenta conexa a unui varf este data de toate varfurile accesibile din el si varfurile din care el este accesibil.
*/

const int NMAX = 100000;
int vis[NMAX + 1]; // marcarea nodurilor vizitate
vector <int> G[NMAX + 1], GT[NMAX+1]; // graful ca liste de adiacenta, graful transpus
stack <int> s;
int cc[NMAX + 1]; //eticheta comonentei conexe pt fiecare varf
int curent = 1;

void dfsOrdonare(int nod) {
    // marcam nodul ca vizitat
    vis[nod] = 1;

    //parcurgem vecinii nodului
    for(auto next : G[nod]) {
        //daca vecinul nu a fost vizitat
        if (!vis[next]) {
            //il parcurgem
            dfsOrdonare(next);
        }
    }

    //adaugam nodul finalizat pe stiva
    s.push(nod);
}

void GTranspus(int n, vector <int> G[NMAX + 1]) {
    //pentru fiecare varf
    for(int i = 1; i <= n; i++) {
        //parcurg lista de adiacenta
        for (auto next : G[i]) {
            //adaug muchia in lista noului graf
            GT[next].push_back(i);
        }
    }
}

void dfs(int nod, vector <int> g[NMAX + 1]) {
    // marcam nodul ca vizitat
    vis[nod] = 1;

    //il etichetam
    cc[nod] = curent;

    //parcurgem vecinii nodului
    for(auto next : g[nod]) {
        //daca vecinul nu a fost vizitat
        if (!vis[next]) {
            //il parcurgem
            dfs(next, g);
        }
    }

}

int main() {

    //citim graful
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
    }

    //stabilim ordinea prin dfsOrdonare
    for(int i = 1; i <= n; i++) {
        if(!vis[i])
            dfsOrdonare(i);
    }

    //cream graful transpus
    GTranspus(n, G);

    //reinintializam vectorul care tine evidenta vizitarii nodurilor
    for(int i = 1; i <= n; i++)
        vis[i] = 0;

    //in ordinea scoaterii nodurilor din stiva, parcurgem graful transpus, etichetand componentele conexe
    curent = 1;
    while(!s.empty()) {
        int nod = s.top();
        s.pop();
        if(!vis[nod]) {
            dfs(nod, GT);
            curent++;
        }
    }

    //afisam numarul de componente conexe
    cout << curent - 1 << "\n";

    //afisam pt fiecare nod componenta conexa
    for(int i = 1; i <=n; i++) {
        cout << cc[i] << " ";
    }

    return 0;
}
