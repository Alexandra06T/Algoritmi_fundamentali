//
// Created by email on 24.10.2023.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

/*
*/

const int NMAX = 100000;
int vis[NMAX + 1]; // marcarea nodurilor vizitate
int a[NMAX + 1]; // marcarea nodurilor care sunt articulatii
int niv[NMAX + 1]; // retinem nivelul fiecarui nod
int low[NMAX + 1]; // retinem low-ul fiecarui nod
vector <int> G[NMAX + 1]; // graful ca liste de adiacenta
int r, nr_copii; //radacina, numarul de copii ai radacinii
queue <int> sol;// numarul de noduri de articulatie pentru fiecare graf

void dfs(int nod, int p) {
    // marcam nodul ca vizitat
    vis[nod] = 1;
    //nivelul nodului este mai mare cu unu decat al parintelui
    niv[nod] = niv[p]+1;
    //momentan low este nivelul, actualizam mai tarziu daca este necesar
    low[nod] = niv[nod];

    //parcurgem vecinii nodului
    for(auto next : G[nod]) {
        //daca vecinul nu a fost vizitat
        if (!vis[next]) {
            //il parcurgem
            dfs(next, nr_copii);
            //actualizam low ul in functie de low ul vecinului
            low[nr_copii] = min(low[nr_copii], low[next]);
            //daca nodul e radacina, numaram copilul
            if (nod == r) {
                nr_copii++;
            } else {
                //daca nodul nu e radacina, verificam daca e nod de articulatie
                if (low[next] >= niv[nr_copii]) {
                    a[nr_copii] = 1;
                }
            }
        } else {
            //daca vecinul a fost vizitat, dar nu este parintele nodului pe care il verificam actualizam low
            if (next != p) {
                low[nr_copii] = min(low[nr_copii], niv[next]);
            }
        }
    }
}

int main() {
    while(true) {
        int n, m;
        int nr_sol = 0;
        cin >> n >> m;
        if(n == 0 && m == 0) {
            cout << sol.front();
            sol.pop();
            while(!sol.empty()) {
                cout << "\n" << sol.front();
                sol.pop();
            }
            break;
        }
        while(m--) {
            int x, y;
            cin >> x >> y;
            G[x].push_back(y);
            G[y].push_back(x);
        }

        //radacina e nodul 1
        r = 1;

        dfs(r, 0);

        //daca radacina are cel putin 2 copii e punct de articulatie
        if(nr_copii >= 2) {
            a[1] = 1;
        }
        //numaram punctele de articulatie
        for(int i = 1; i <= n; i++) {
            if(a[i] == 1) {
                nr_sol++;
            }
        }
        //resetam valorile pentru urmatorul graf
        for(int i = 1; i <= n; i++) {
            G[i].clear();
            a[i] = vis[i] = niv[i] = low[i] = 0;
        }
        //retinem numarul de puncte de articulatie (numarul de insule cerute)
        sol.push(nr_sol);
    }
    return 0;
}
