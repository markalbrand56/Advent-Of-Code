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
    f = open("input.txt", "r")
    lines = []

    for line in f:
        if line != "\n":
            lines.append(line.strip())

    f.close()

    directions = [c for c in lines[0]]
    lines = lines[1::]

    print(f"'{directions}'\n")
    instructions = {}
    startings = []
    for line in lines:
        line = line.replace(",", "")
        spl = line.split(" = ")

        label = spl[0]
        l = spl[1].split(" ")[0]
        l = l.replace("(", "")
        r = spl[1].split(" ")[1]
        r = r.replace(")", "")

        if label.endswith("A"):
            startings.append(label)

        instructions[label] = {"R": r, "L": l}

    print(instructions)

    counter = 0
    reached = False
    states = [s for s in startings]
    while not reached:
        dir = directions[(counter) % len(directions)]
        counter += 1
        ends = 0
        for s in states:
            new = instructions[s][dir]
            states[states.index(s)] = new
            if new.endswith("Z"):
                ends += 1
        if ends == len(startings):
            reached = True

    print(f"2. Ended in {counter}")


if __name__ == "__main__":
    part_1()
    part_2()
