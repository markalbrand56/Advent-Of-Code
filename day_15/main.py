def part1():
    file = open("input.txt", "r")

    lines = file.readlines()
    file.close()

    steps = []

    for line in lines:
        n = line.strip().split(",")
        for i in range(len(n)):
            steps.append(n[i])

    # Determine the ASCII code for the current character of the string.
    # Increase the current value by the ASCII code you just determined.
    # Set the current value to itself multiplied by 17.
    # Set the current value to the remainder of dividing itself by 256.

    sum = 0
    for i in range(len(steps)):
        value = 0
        for c in steps[i]:
            value += ord(c)
            value *= 17
            value %= 256

        # print(value)
        sum += value

    print(f"Part 1: Sum {sum}")


def part2():
    file = open("input.txt", "r")

    lines = file.readlines()
    file.close()

    steps = []

    for line in lines:
        n = line.strip().split(",")
        for i in range(len(n)):
            steps.append(n[i])

    hmap: dict[int, list[list]] = {}
    for i in range(len(steps)):
        value = 0

        label = ""
        lens = -1

        for c in steps[i]:
            if c == '=' or c == '-':
                break
            value += ord(c)
            value *= 17
            value %= 256

        if steps[i].find("=") != -1:  #
            label = steps[i].split("=")[0]
            lens = int(steps[i].split("=")[1])

            if hmap.get(value) is not None:
                prev = hmap[value]
                labels = [x[0] for x in prev]

                if label in labels:
                    prev[labels.index(label)][1] = lens
                else:
                    hmap[value].append([label, lens])

            else:
                hmap[value] = [[label, lens]]

        elif steps[i].find("-") != -1:  # go to the box and remove the lens with the given label
            label = steps[i].split("-")[0]

            if hmap.get(value) is not None:
                prev = hmap[value]
                labels = [x[0] for x in prev]

                if label in labels:
                    # delete the list with the given label
                    del prev[labels.index(label)]

        # print(f"'{label}': {value} -> {lens}")

    power = 0
    for i in range(256):
        if hmap.get(i) is not None:
            if len(hmap[i]) > 0:
                for j in range(len(hmap[i])):
                    # print(f"{(i+1) * (j+1) * hmap[i][j][1]}")
                    power += (i+1) * (j+1) * hmap[i][j][1]

    print(f"Part 2: Power {power}")


if __name__ == '__main__':
    part1()
    part2()
