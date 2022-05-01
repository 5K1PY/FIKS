letters = ["A", "C", "G", "T"]

def to_letter(x):
    return letters[x]

f = open("input (9).txt", "rb")
g = open("mod_input.txt", "w")
n = int(f.readline())
g.write(f"{n}\n")
for problem_i in range(n):
    animals, diffrence = map(int, f.readline().split())
    g.write(f"{animals} {diffrence}\n")
    for j in range(animals):
        lenght = ""
        char = f.read(1).decode("ascii")
        while char != " ":
            lenght += char
            char = f.read(1).decode("ascii")
        lenght = int(lenght)
        for i in range((lenght+3)//4):
            byte = ord(f.read(1))
            for letter_i in range(4 if (i+1)*4 <= int(lenght) else lenght%4):
                new_x = (byte // 2**(6-2*letter_i)) % 2**2
                g.write(to_letter(new_x))
        f.read(1)
        g.write("\n")

f.close()
g.close()
