n = int(input())
animals = list(map(int, input().split()))
p = int(input())
i = 0

animals = list(sorted(enumerate(animals), key=lambda x: x[1]))

while i < len(animals):
    min_animal = animals[i]
    pavilion = [min_animal[0]]
    i += 1
    while i < len(animals) and animals[i][1] <= min_animal[1] + p:
        pavilion.append(animals[i][0])
        i += 1
    print(f"({' '.join(map(lambda x: str(x+1), sorted(pavilion)))})")
