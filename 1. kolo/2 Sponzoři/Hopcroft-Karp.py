from collections import deque
from math import inf


class Vertex():
    def __init__(self, id_, name, edges):
        self.id = int(id_)
        self.name = name
        self.connected = False
        self.edges = edges

    def __str__(self):
        return f"{self.id} {self.name}: {self.connected}, {self.edges}"

    __repr__ = __str__


class Animal(Vertex):
    def is_animal(self):
        return True

    def is_sponsor(self):
        return False


class Sponsor(Vertex):
    def is_animal(self):
        return False

    def is_sponsor(self):
        return True


def get_unconnected_animals(graph):
    return list(filter(lambda v: (v.connected is False and v.is_animal()), graph))


def bfs(graph):
    queue = deque(map(lambda v: (0, v), get_unconnected_animals(graph)))
    depth = [inf]*len(graph)

    finished_time = inf
    while len(queue):
        time, vertex = queue.popleft()
        if time > finished_time:
            break

        if depth[vertex.id] != inf:
            continue
        depth[vertex.id] = time

        if vertex.is_sponsor() and vertex.connected is False:
            finished_time = time
        else:
            for next_vertex in vertex.edges:
                if vertex.is_animal() or vertex.connected == next_vertex:
                    queue.append((time+1, graph[next_vertex]))

    return (finished_time != inf, depth)


def dfs(graph, depth):
    searched = [False]*len(graph)
    for v in get_unconnected_animals(graph):
        stack = [[v, 0]]
        while len(stack):
            vertex, neighbour = stack[-1]
            searched[vertex.id] = True

            if vertex.is_sponsor() and vertex.connected is False:
                break
            elif len(vertex.edges) == neighbour:
                stack.pop()
            elif depth[vertex.id] + 1 == depth[vertex.edges[neighbour]] and not searched[vertex.edges[neighbour]] \
                    and (vertex.is_animal() or vertex.connected == vertex.edges[neighbour]):
                stack.append([graph[vertex.edges[neighbour]], 0])
                stack[-2][1] += 1
            else:
                stack[-1][1] += 1

        for i in range(0, len(stack), 2):
            stack[i][0].connected = stack[i+1][0].id
            stack[i+1][0].connected = stack[i][0].id


n, m = map(int, input().split())

animals = [None]*n
for i in range(n):
    id_, name = input().split()
    animals[int(id_)] = Animal(id_, name, [])

sponsors = []
for id_ in range(m):
    sponsor = input().split()
    name, count, sponored = sponsor[0], int(sponsor[1]), list(map(int, sponsor[2:]))
    sponsors.append(Sponsor(n+id_, name, sponored))
    for animal in sponored:
        animals[animal].edges.append(n+id_)


graph = animals + sponsors
while True:
    found, depth = bfs(graph)
    if not found:
        break
    dfs(graph, depth)

possible = all(map(lambda x: x.connected is not False, animals))
print("Ano" if possible else "Ne")

pairs = []
for animal in animals:
    if animal.connected is not False:
        pairs.append(animal.name + " " + graph[animal.connected].name)
pairs.sort()
print("\n".join(pairs))
