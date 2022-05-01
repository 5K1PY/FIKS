while True:
    h, w, y, x, t = map(int, input().split())
    for y1 in range(h):
        for x1 in range(w):
            d = abs(y1-y) + abs(x1-x)
            if d <= t and d % 2 == t % 2:
                print("#", end="")
            else:
                print(" ", end="")
        print()
