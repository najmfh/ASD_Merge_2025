#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector<vector<int>> adj;
vector<int> disc, low;
vector<bool> visited;
vector<pair<int, int>> bridges;
set<pair<int, int>> edge_set;
int timer;

void dfs(int u, int parent);
void findBridges(int n);

int main(){
    int n, e; //jumlah simpul dan edge

    cout << "=== Bridge Finder === \n\n";
    cout << "Masukkan jumlah node : ";
    cin >> n;
    cout << "Masukkan jumlah edge : ";
    cin >> e;

    adj.assign(n+1, vector<int>());

    cout << "\nMasukkan " << e << " edge (format : node-1 node-2), gunakan angka 1 sampai " << n << " : \n";
    for (int i = 0; i < e; ++i){
        int node1, node2;
        cout << "Edge-" << i+1 << " : ";
        cin >> node1 >> node2;
        
        //Menyeleksi Self-Loop
        if (node1 == node2){
            cout << "Self-Loop tidak diperbolehkan. Edge diabaikan.\n";
            --i;
            continue;
        }

        // Menyeleksi Node Ganda
        pair<int, int> g = {min(node1, node2), max(node1, node2)};
        if (edge_set.count(g)){
            cout << "Edge yang berkaitan sudah diinput. Edge diabaikan.\n";
            --i;
            continue;
        }

        edge_set.insert(g);
        adj[node1].push_back(node2);
        adj[node2].push_back(node1);
    }

    findBridges(n);

    cout << "\n=== HASIL BRIDGE ===\n";
    if (bridges.empty()) {
        cout << "Tidak ada bridge dalam graf ini.\n";
    } else {
        cout << "Bridge Ditemukan!\n";
        for (auto [u, v] : bridges) {
            cout << u << " - " << v << "\n";
        }
    }

    cout << "\nProgram selesai. Terima kasih!\n";
    return 0;
}

void dfs(int u, int parent){
    visited[u] = true;
    disc[u] = low[u] = timer++;

    for (int v : adj[u]){
        if (v == parent) continue;

        if (!visited[v]){
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] > disc[u]){
                bridges.emplace_back(min(u,v), max(u,v));
            }
        } else {
            low[u] = min(low[u], disc[v]);
        }
    }
}

void findBridges(int n){
    timer = 0;
    disc.assign(n, -1);
    low.assign(n, -1);
    visited.assign(n, false);
    bridges.clear();

    for (int i = 0; i < n; ++i){
        if (!visited[i]) {
            dfs(i, -1);
        }
    }
}