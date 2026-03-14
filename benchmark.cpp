#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

const int MAXN = 1000005; // Larger limit for benchmarking
vector<int> adj[MAXN];
int low[MAXN], num[MAXN], cnt = 0;
bool is_articulation[MAXN];
int bridge_count = 0;
int n, m;

void dfs(int u, int p = 0) {
    num[u] = low[u] = ++cnt;
    int children = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (!num[v]) {
            children++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] == num[v]) bridge_count++;
            if (p != 0 && low[v] >= num[u]) is_articulation[u] = true;
        } else {
            low[u] = min(low[u], num[v]);
        }
    }
    if (p == 0 && children > 1) is_articulation[u] = true;
}

void reset_state() {
    cnt = 0;
    bridge_count = 0;
    for (int i = 0; i <= n; i++) {
        num[i] = low[i] = 0;
        is_articulation[i] = false;
        adj[i].clear();
    }
}

int main(int argc, char* argv[]) {
    string suffix = (argc > 1) ? argv[1] : "1000";
    string filename = "datasets/dataset_" + suffix + ".txt";

    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: File " << filename << " not found!" << endl;
        return 1;
    }

    // --- Loading Phase ---
    auto t1 = high_resolution_clock::now();
    infile >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        infile >> u >> v;
        if (u < MAXN && v < MAXN) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    auto t2 = high_resolution_clock::now();

    // --- Algorithm Phase ---
    auto t3 = high_resolution_clock::now();
    for (int i = 1; i <= n; i++) {
        if (!num[i]) dfs(i);
    }
    int art_pts = 0;
    for (int i = 1; i <= n; i++) if (is_articulation[i]) art_pts++;
    auto t4 = high_resolution_clock::now();

    // --- Statistics ---
    auto load_time = duration_cast<milliseconds>(t2 - t1);
    auto algo_time = duration_cast<microseconds>(t4 - t3);

    cout << ">> Result for " << filename << endl;
    cout << "   Nodes: " << n << " | Edges: " << m << endl;
    cout << "   Load Time: " << load_time.count() << " ms" << endl;
    cout << "   Algo Time: " << algo_time.count() << " us (" << (double)algo_time.count()/1000.0 << " ms)" << endl;
    cout << "   Found: " << art_pts << " Articulation Points and " << bridge_count << " Bridges." << endl;
    cout << "-----------------------------------------------" << endl;

    return 0;
}
