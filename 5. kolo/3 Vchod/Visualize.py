from PIL import Image
import numpy as np

def c(x):
    return (x + npoints//2) // acc

size = 800
npoints = 4*10**8
acc = npoints // size

f = open("input.txt")
a, b = map(int, f.readline().split())
points = [[(255, 255, 255)]*size for i in range(size)]

for x in range(0, a, acc):
    for y in [0, a]:
        points[c(y)][c(x)] = (0, 0, 0)

for y in range(0, a, acc):
    for x in [0, a]:
        points[c(y)][c(x)] = (0, 0, 0)

for i in range(b):
    q, x, y = f.readline().split()
    x, y = int(x), int(y)
    if q == "?":
        points[c(y)][c(x)] = (0, 255, 0)
    else:
        points[c(y)][c(x)] = (255, 0, 0)


points = np.uint8(points)
im = Image.fromarray(points)
im.show()
