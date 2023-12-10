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

def main():
    print("Hello world")

    f = open("sample.txt", "r")
    lines = []

    for line in f:
        if (line != "\n"):
            lines.append(line.strip())

    f.close()

    directions = lines[0]
    lines = lines[1::]

    print(f"'{directions}'\n")
    instructions = []
    for line in lines:
        print(f"'{line}'")
        line = line.replace(",", "")
        spl = line.split(" = ")

        label = spl[0]
        l = spl[1].split(" ")[0]
        l = l.replace("(", "")
        r = spl[1].split(" ")[1]
        r = r.replace(")", "")

        ins = Instruction(label, l, r)
        print(f"{ins}")
        instructions.append(ins)

    for x in instructions:
        for y in instructions:
            if y.right == x.label:
                y.righ == x
            if y.left == x.label:
                y.left == x

    reached = False
    while(!reached):
        current = instructions[0]
        for c in directions:
            if c == "L":
                current = current.left
            else if c == "R":
                current = current.r


if __name__ == "__main__":
    main()
