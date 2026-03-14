import sys

# Increase recursion depth for deep DFS trees in large graphs
sys.setrecursionlimit(10**6)

def solve():
    # Read N and M
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    n = int(input_data[0])
    m = int(input_data[1])
    
    adj = [[] for _ in range(n + 1)]
    idx = 2
    for _ in range(m):
        u = int(input_data[idx])
        v = int(input_data[idx+1])
        adj[u].append(v)
        adj[v].append(u)
        idx += 2

    num = [0] * (n + 1)
    low = [0] * (n + 1)
    is_articulation = [False] * (n + 1)
    timer = 0
    bridges = 0

    def dfs(u, p):
        nonlocal timer, bridges
        timer += 1
        num[u] = low[u] = timer
        children = 0
        
        for v in adj[u]:
            if v == p:
                continue
            if num[v] == 0:
                children += 1
                dfs(v, u)
                low[u] = min(low[u], low[v])
                
                # Bridge condition
                if low[v] == num[v]:
                    bridges += 1
                # Articulation point condition
                if p != -1 and low[v] >= num[u]:
                    is_articulation[u] = True
            else:
                low[u] = min(low[u], num[v])
        
        return children

    for i in range(1, n + 1):
        if num[i] == 0:
            if dfs(i, -1) > 1:
                is_articulation[i] = True

    articulation_count = sum(is_articulation)
    print(f"Articulation Points: {articulation_count}")
    print(f"Bridges: {bridges}")

if __name__ == "__main__":
    solve()
