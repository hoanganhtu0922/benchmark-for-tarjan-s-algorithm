#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 300005; 

vector<int> adj[MAXN];
int low[MAXN], num[MAXN], cnt = 0;
bool is_articulation[MAXN];
int bridge_count = 0;
int n, m;

void find_critical(int u, int p = 0) {
    num[u] = low[u] = ++cnt;
    int children = 0;

    for (int v : adj[u]) {
        if (v == p) continue; 
        
        if (!num[v]) { 
            children++;
            find_critical(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] == num[v]) {
                bridge_count++;
            }

            if (p != 0 && low[v] >= num[u]) {
                is_articulation[u] = true;
            }
        } else {
            low[u] = min(low[u], num[v]);
        }
    }

    if (p == 0 && children > 1) {
        is_articulation[u] = true;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!num[i]) find_critical(i);
    }

    int articulation_count = 0;
    for (int i = 1; i <= n; i++) {
        if (is_articulation[i]) articulation_count++;
    }

    cout << "Articulation Points: " << articulation_count << endl;
    cout << "Bridges: " << bridge_count << endl;

    return 0;
}
