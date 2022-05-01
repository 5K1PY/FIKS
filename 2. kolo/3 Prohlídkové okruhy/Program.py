def dfs(graph, startnode, visited, out, comp_id=0):
    stack = [[startnode, 0]]
    while len(stack):
        node, i = stack[-1]

        visited[node] = comp_id
        while i < len(graph[node]) and visited[graph[node][i]] != -1:
            # keep in mind - those two sit at two diffrent adresses
            i += 1
            stack[-1][1] += 1

        if i == len(graph[node]):
            out.append(stack.pop()[0])
        else:
            stack[-1][1] += 1
            stack.append([graph[node][i], 0])


def calc_strong_comp(n, graph):
    graphT = {i: [] for i in range(n)}
    for node, sons in graph.items():
        for son in sons:
            graphT[son].append(node)

    visited = [-1]*n
    out = []
    for i in range(n):
        if visited[i] == -1:
            dfs(graphT, i, visited, out)

    strong_comps = [-1]*n
    comp_id = 0
    while len(out):
        node = out.pop()
        if strong_comps[node] == -1:
            dfs(graph, node, strong_comps, [], comp_id)
            comp_id += 1

    return comp_id, strong_comps


n, m, q = map(int, input().split())

graph = {i: [] for i in range(n)}


for _ in range(m):
    a, b = map(int, input().split())
    a, b = a-1, b-1
    graph[a].append(b)

comp_id, strong_comps = calc_strong_comp(n, graph)
reachable = []
comp_edges = {i: [] for i in range(comp_id)}

for node, edges in graph.items():
    for node2 in edges:
        comp_edges[strong_comps[node]].append(strong_comps[node2])

for comp in range(comp_id):
    reachable.append([-1]*comp_id)
    dfs(comp_edges, comp, reachable[-1], [])
    for i in range(comp_id):
        reachable[-1][i] += 1

for _ in range(q):
    a, b = map(int, input().split())
    if reachable[strong_comps[a-1]][strong_comps[b-1]]:
        print("Cesta existuje")
    else:
        print("Cesta neexistuje")
