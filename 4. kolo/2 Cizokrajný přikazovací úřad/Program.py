import enum


IFILE = open("input.txt")
OFILE = open("output.txt", "w")

def cont(x):
    return x % 2**32


class Memory:
    def __init__(self):
        self.data = [0]*256

    def read(self, adress):
        if adress == 666:
            return -1
        return self.data[adress % 256]

    def write(self, adress, content):
        if adress == 666:
            return -1
        self.data[adress % 256] = cont(content)
        self.data[0] = 0
        return 0

    def __repr__(self):
        return str(self.data)
    __str__ = __repr__


class Stack:
    def __init__(self):
        self.stack = []

    def size(self):
        return len(self.stack)

    def get(self, i):
        if i < 0 or i >= len(self.stack):
            return -1
        return self.stack[i]

    def push(self, item):
        if len(self.stack) == 16:
            return -1
        self.stack.append(cont(item))
        return 0

    def pop(self):
        if len(self.stack) == 0:
            return -1
        return self.stack.pop()

    def __repr__(self):
        return str(self.stack)
    __str__ = __repr__


class Program:
    def __init__(self, mem):
        self.mem = mem
        data = list(map(int, IFILE.readline().split()))
        self.pc = data[0]
        for i in range(data[1]):
            self.mem.write(self.pc+i, data[2+i])
        self.stack = Stack()
        self.dead = False
        self.tp = False

    def exec(self):
        if self.dead or self.tp:
            return 0

        instruct = self.mem.read(self.pc)
        if instruct == -1:
            return -1
        instruct_c = instruct % 2**8
        if instruct_c >= len(INSTRUCTIONS):
            return -1
        instruct_a = (instruct >> 8) % 2**16
        # print(INSTRUCTIONS[instruct_c], instruct_a)
        return INSTRUCTIONS[instruct_c](self, instruct_a)

    def finish(self):
        if self.dead or self.tp:
            return 0

        self.pc += 1
        self.pc %= 256

    # --- instructions ---
    def _nop(self, arg):
        return 0

    def _pc(self, arg):
        return self.stack.push(self.pc)

    def _push(self, arg):
        return self.stack.push(arg)

    def _pop(self, arg):
        return min(0, self.stack.pop())

    def _swap(self, arg):
        a, b = self.stack.pop(), self.stack.pop()
        if a == -1 or b == -1:
            return -1
        self.stack.push(a)
        self.stack.push(b)
        return 0

    def _dup(self, arg):
        a = self.stack.get(self.stack.size()-1)
        if a == -1:
            return -1
        return self.stack.push(a)

    def _pushsize(self, arg):
        return self.stack.push(self.stack.size())

    def _load(self, arg):
        a = self.stack.pop()
        if a == -1:
            return -1
        b = self.mem.read(a)
        if b == -1:
            return -1
        return self.stack.push(b)

    def _store(self, arg):
        a, b = self.stack.pop(), self.stack.pop()
        if a == -1 or b == -1:
            return -1
        return self.mem.write(a, b)

    def _add(self, arg):
        a, b = self.stack.pop(), self.stack.pop()
        if a == -1 or b == -1:
            return -1
        return self.stack.push(a+b)

    def _sub(self, arg):
        a, b = self.stack.pop(), self.stack.pop()
        if a == -1 or b == -1:
            return -1
        return self.stack.push(a-b)

    def _div(self, arg):
        a, b = self.stack.pop(), self.stack.pop()
        if a == -1 or b == -1 or b == 0:
            return -1
        return self.stack.push(a//b)

    def _pow(self, arg):
        a, b = self.stack.pop(), self.stack.pop()
        if a == -1 or b == -1:
            return -1
        return self.stack.push(pow(a, b, 2**32))

    def _br(self, x, arg):
        a = self.stack.pop()
        if a == -1:
            return -1
        if a == x:
            self.pc += arg
        return 0

    def _brz(self, arg):
        return self._br(0, arg)

    def _br3(self, arg):
        return self._br(3, arg)

    def _br7(self, arg):
        return self._br(7, arg)

    def _brge(self, arg):
        a, b = self.stack.pop(), self.stack.pop()
        if a == -1 or b == -1:
            return -1
        if a >= b:
            self.pc += arg
        return 0

    def _jmp(self, arg):
        self.pc = arg
        return 0

    def _abomb(self, arg):
        return -1

    def _bomb(self, arg):
        return self.mem.write(self.pc, 18)

    def _tp(self, arg):
        self.tp = True
        return 0

    def _jntr(self, arg):
        for i in range(1, 4):
            self.mem.write(self.pc - 2**i, 19)
            self.mem.write(self.pc + 2**i, 19)


INSTRUCTIONS = [
    Program._nop,
    Program._pc,
    Program._push,
    Program._pop,
    Program._swap,
    Program._dup,
    Program._pushsize,
    Program._load,
    Program._store,
    Program._add,
    Program._sub,
    Program._div,
    Program._pow,
    Program._brz,
    Program._br3,
    Program._br7,
    Program._brge,
    Program._jmp,
    Program._abomb,
    Program._bomb,
    Program._tp,
    Program._jntr
]


class Simulation:
    def __init__(self):
        self.memory = Memory()
        self.program_count = int(IFILE.readline())
        self.programs = [Program(self.memory) for i in range(self.program_count)]

        for i in range(5000):
            to_swap = []
            for program in self.programs:
                result = program.exec()
                if result == -1:
                    program.dead = True
                elif program.tp:
                    to_swap.append(program)

            if len(to_swap) >= 2:
                counters = [program.pc for program in to_swap]
                counters.append(counters.pop(0))
                for i, pc in enumerate(counters):
                    to_swap[i].pc = pc
                    to_swap[i].tp = False

            if all(map(lambda x: x.dead, self.programs)):
                break

            for program in self.programs:
                program.finish()

        res1 = self.memory.read(42)
        res2 = sum(map(lambda x: x.pc, self.programs))
        OFILE.write(f"{res1} {res2}\n")


n = int(IFILE.readline())
for i in range(n):
    print(i)
    Simulation()

IFILE.close()
OFILE.close()
