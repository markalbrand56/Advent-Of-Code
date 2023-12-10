from math import lcm


class Instruction:
    label: str
    left = None
    right = None

    def __init__(self, n, l, r):
        self.label = n
        self.left = l
        self.right = r

    def __repr__(self):
        return f"{self.label} -> R:'{self.right}' L:'{self.left}'"


END = "ZZZ"


def part_1():
    f = open("input.txt", "r")
    lines = []

    for line in f:
        if line != "\n":
            lines.append(line.strip())

    f.close()

    directions = lines[0]
    lines = lines[1::]

    print(f"'{directions}'\n")
    instructions = {}
    for line in lines:
        line = line.replace(",", "")
        spl = line.split(" = ")

        label = spl[0]
        l = spl[1].split(" ")[0]
        l = l.replace("(", "")
        r = spl[1].split(" ")[1]
        r = r.replace(")", "")

        instructions[label] = {"r": r, "l": l}

    reached = False
    counter = 0
    current = "AAA"
    while not reached:
        for c in directions:
            counter += 1
            if c == "L":
                current = instructions[current]["l"]
            if c == "R":
                current = instructions[current]["r"]

        if current == END:
            reached = True

    print(f"Reached in {counter}")


def part_2():
    print("Part 2")
    f = open("input.txt", "r")
    lines = [line.strip() for line in f if line != "\n"]
    f.close()

    directions = [c for c in lines[0]]
    lines = lines[1::]

    instructions = {}
    startings = []
    for line in lines:
        line = line.replace(",", "")
        spl = line.split(" = ")

        label = spl[0]
        l = spl[1].split(" ")[0].replace("(", "")
        r = spl[1].split(" ")[1].replace(")", "")

        if label.endswith("A"):
            startings.append(label)

        instructions[label] = {"R": r, "L": l}

    cycles = []
    for starting in startings:
        current = starting
        cycle_length = 0
        while True:
            dir = directions[cycle_length % len(directions)]
            current = instructions[current][dir]
            cycle_length += 1
            if current.endswith("Z"):
                break
        cycles.append(cycle_length)

    lcm_value = cycles[0]
    for cycle in cycles[1:]:
        lcm_value = lcm(lcm_value, cycle)

    print(f"2. Ended in {lcm_value}")


if __name__ == "__main__":
    part_1()
    part_2()
