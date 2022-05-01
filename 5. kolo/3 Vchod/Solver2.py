from math import sqrt


SIZE = 2
DEPTH = 10


def distance(point1, point2):
    return sqrt(distance2(point1, point2))


def distance2(point1, point2):
    return (point1[0] - point2[0]) ** 2 + (point1[1] - point2[1]) ** 2


class Quadrant():
    def __init__(self, x, y, size, depth):
        self.x, self.y = x, y
        self.npoints = 0
        self.size = size
        self.depth = depth
        if depth == 0:
            self.subs = None
            self.points = []
        else:
            self.smaller = self.size / SIZE
            self.subs = [[
                Quadrant(self.x + x * self.smaller, self.y + y * self.smaller, self.smaller, depth-1)
                for y in range(SIZE)]
                for x in range(SIZE)
            ]

    def add(self, point):
        self.npoints += 1
        if self.depth == 0:
            self.points.append(point)
        else:
            self.quadrant(point).add(point)

    def remove(self, point):
        self.npoints -= 1
        if self.depth == 0:
            self.points.remove(point)
        else:
            self.quadrant(point).remove(point)

    def quadrant(self, point):
        x = int((point[0] - self.x) * SIZE // self.size)
        y = int((point[1] - self.y) * SIZE // self.size)
        if x == SIZE:
            x -= 1
        if y == SIZE:
            y -= 1
        return self.subs[x][y]

    def has(self):
        return self.npoints > 0

    def min(self, f):
        if not self.has():
            return -1
        return min(
            f((self.x, self.y)),
            f((self.x + self.size, self.y))
        )

    def max(self, f):
        if not self.has():
            return -1
        return max(
            f((self.x, self.y + self.size)),
            f((self.x + self.size, self.y + self.size))
        )

    def best(self, f):
        return max(
            [f(p) for p in self.points]
        )

    def get_subs(self):
        return [sub for sub in sum(self.subs, start=[]) if sub.has()]

    def get_all_points(self):
        if self.depth == 0:
            return self.points
        else:
            return sum([sub.get_all_points() for sub in sum(self.subs, start=[])], start=[])


file = open("input.txt")
g = open("output.txt", "w")
a, b = map(int, file.readline().split())
quadr = Quadrant(0, a, a, DEPTH)

alpha = 0
for i in range(b):
    q, x, y = file.readline().split()
    x, y = int(x), int(y)
    if q == "+":
        quadr.add((x, y))
        assert y > a
        assert 0 < x < a
    elif q == "-":
        quadr.remove((x, y))
    else:
        f = lambda p: min(
            distance((0, a), p) + (a - y) + x,
            distance((a, a), p) + (a - y) + (a - x)
        )
        quadrants = quadr.get_subs()
        for i in range(DEPTH-1):
            best = max([q.min(f) for q in quadrants])
            quadrants = [q for q in quadrants if q.max(f) > best]
            quadrants = sum([q.get_subs() for q in quadrants], start=[])
        res = max([q.best(f) for q in quadrants])
        g.write(str(round(res)) + "\n")
        alpha += 1

file.close()
g.close()
