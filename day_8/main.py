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


if __name__ == "__main__":
    main()
