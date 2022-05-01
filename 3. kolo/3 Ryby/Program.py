from time import time


def calc_coef(vertex):
    if sx == 0:
        return (vertex[0], vertex)
    return (sx*vertex[1] - sy*vertex[0], vertex)


def mpoint(vertex, char):
    return (vertex[0], char, vertex[1])


n, sx, sy = map(int, input().split())
points = []
for i in range(n):
    vertices = list(map(int, input().split()))
    vertices = list(map(calc_coef, [(vertices[i], vertices[i+1]) for i in range(1, len(vertices), 2)]))
    points.append(mpoint(min(vertices), "1"))
    points.append(mpoint(max(vertices), "2"))

points.sort()

intersect = 0
best_intersect = 0
for p in points:
    intersect += 2*(p[1] == "1")-1
    best_intersect = max(best_intersect, intersect)
print(best_intersect)
