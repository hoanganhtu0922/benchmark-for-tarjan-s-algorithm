import sys
import time
import os

# CRITICAL: Python's default limit is 1000. 
# We increase it to handle deep DFS trees in large datasets.
sys.setrecursionlimit(10**6)

def benchmark():
    # Get dataset suffix from command line argument
    suffix = sys.argv[1] if len(sys.argv) > 1 else "1000"
    file_path = f"datasets/dataset_{suffix}.txt"

    if not os.path.exists(file_path):
        print(f"Error: {file_path} not found.")
        return

    # --- Loading Phase ---
    start_load = time.time()
    with open(file_path, 'r') as f:
        lines = f.readlines()
        if not lines: return
        
        n, m = map(int, lines[0].split())
        adj = [[] for _ in range(n + 1)]
        for i in range(1, m + 1):
            u, v = map(int, lines[i].split())
            adj[u].append(v)
            adj[v].append(u)
    end_load = time.time()

    # --- Algorithm Phase ---
    num = [0] * (n + 1)
    low = [0] * (n + 1)
    is_articulation = [False] * (n + 1)
    timer = 0
    bridge_count = 0

    def dfs(u, p):
        nonlocal timer, bridge_count
        timer += 1
        num[u] = low[u] = timer
        children = 0
        
        for v in adj[u]:
            if v == p: continue
            if num[v] == 0:
                children += 1
                dfs(v, u)
                low[u] = min(low[u], low[v])
                
                if low[v] == num[v]:
                    bridge_count += 1
                if p != -1 and low[v] >= num[u]:
                    is_articulation[u] = True
            else:
                low[u] = min(low[u], num[v])
        return children

    start_algo = time.time()
    for i in range(1, n + 1):
        if num[i] == 0:
            if dfs(i, -1) > 1:
                is_articulation[i] = True
    end_algo = time.time()

    # --- Results ---
    load_ms = (end_load - start_load) * 1000
    algo_ms = (end_algo - start_algo) * 1000
    art_count = sum(is_articulation)

    print(f"--- Python Benchmark Results [{suffix}] ---")
    print(f"Nodes: {n} | Edges: {m}")
    print(f"Load Time: {load_ms:.2f} ms")
    print(f"Algo Time: {algo_ms:.2f} ms")
    print(f"Found: {art_count} Articulation Points, {bridge_count} Bridges")
    print("-" * 40)

if __name__ == "__main__":
    benchmark()
