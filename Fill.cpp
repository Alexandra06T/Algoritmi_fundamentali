#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
 * Floor legate intre ele formeaza o camera. Deci fllor = nod, adiacenta e data de vecinatatea( la stanga, dreapta, sus,
 * jos) in map a doua noduri, camerele = componentele conexe
 * Ideea este sa construim graful si sa il parcurgem. Fiecare parcurgere pe nodurile nevizitate anterior da o noua componenta conexa.
 * Initial, traducem matricea cu caractere in una cu numere, unde 0 - wall, nr != 0 - nod cu eticheta nr.
 * Din aceasta matrice numerica, construim listele de adiacenta ale grafului, apoi il parcurgem cu dfs.
*/

const int NMAX = 1000000;
int vis[NMAX + 1]; // marcarea nodurilor vizitate
vector <int> G[NMAX + 1]; // graful ca liste de adiacenta

void dfs(int nod) {
    vis[nod] = 1;
    for (auto next: G[nod]) {
        if(!vis[next]) {
            vis[next] = 1;
            dfs(next);
        }
    }
}

int main() {

    //citim map si traducem matricea - 0 == wall, != 0 == floor, numerotand nodurile
    int n, m;
    cin >> n >> m;

    int a[n+1][m+1], contor = 0;
    for(int i = 1; i <= n; i++ ) {
        string linie;
        cin >> linie;
        for (int j = 0; j < m; j++) {
            if (linie[j] == '#')
                a[i][j+1] = 0;
            else if (linie[j] == '.')
                a[i][j+1] = ++contor;
        }
    }
//    for(int i = 1; i <= n; i++)
//    {
//        for(int j = 1; j <= m ; j++)
//            cout << a[i][j] << " ";
//        cout << endl;
//    }

    //scriem graful ca liste de adiacenta
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++){
            if(a[i][j] != 0) {
                if(i != 1 && a[i-1][j] != 0) {
                    G[a[i][j]].push_back(a[i-1][j]);
                    G[a[i-1][j]].push_back(a[i][j]);
                }
                if(j != m && a[i][j+1] != 0) {
                    G[a[i][j]].push_back(a[i][j+1]);
                    G[a[i][j+1]].push_back(a[i][j]);
                }
            }
        }

//    for (int i = 1; i<= contor; i++) {
//        cout << i << ": ";
//        for (auto next: G[i]){
//            cout << next << " ";
//        }
//        cout << endl;
//    }

    //parcurgem graful si numaram componentele conexe
    int cc = 0;
    for(int i = 1; i <= contor; i++)
        if(vis[i] == 0) {
            cc++;
            dfs(i);
        }

    //afisam numarul de camere (componente conexe)
    cout << cc;

    return 0;
}
