def part_1():
    print("Part 1")
    # |: Arriba o abajo
    # -: Izquierda o derecha
    # L: Arriba o derecha
    # J: Arriba o izquierda
    # 7: Abajo o izquierda
    # F: Abajo o derecha
    # .: Piso
    # S: Inicio


def next_pipe(c: str, dir: str) -> list[str]:
    # Dir: N, S, E, W

    if c == '|':
        if dir == 'N':
            # From | to : |, 7, F
            return ['|', '7', 'F']
        elif dir == 'S':
            # From | to : |, L, J
            return ['|', 'L', 'J']
        elif dir == 'E':
            # From | to : None
            return []
        elif dir == 'W':
            # From | to : None
            return []
    elif c == '-':
        if dir == 'N':
            # From - to : None
            return []
        elif dir == 'S':
            # From - to : None
            return []
        elif dir == 'E':
            # From - to : -, 7, J
            return ['-', '7', 'J']
        elif dir == 'W':
            # From - to : -, L, F
            return ['-', 'L', 'F']
    elif c == 'L':
        if dir == 'N':
            # From L to : | , 7, F
            return ['|', '7', 'F']
        elif dir == 'S':
            # From L to : None
            return []
        elif dir == 'E':
            # From L to : -, 7, J
            return ['-', '7', 'J']
        elif dir == 'W':
            # From L to : None
            return []
    elif c == 'J':
        if dir == 'N':
            # From J to : |, 7, F
            return ['|', '7', 'F']
        elif dir == 'S':
            # From J to : None
            return []
        elif dir == 'E':
            # From J to : None
            return []
        elif dir == 'W':
            # From J to : -, F, L
            return ['-', 'F', 'L']
    elif c == '7':
        if dir == 'N':
            # From 7 to : None
            return []
        elif dir == 'S':
            # From 7 to : | , L, J
            return ['|', 'L', 'J']
        elif dir == 'E':
            # From 7 to : None
            return []
        elif dir == 'W':
            # From 7 to : -, F, L
            return ['-', 'F', 'L']
    elif c == 'F':
        if dir == 'N':
            # From F to : None
            return []
        elif dir == 'S':
            # From F to : |, L, J
            return ['|', 'L', 'J']
        elif dir == 'E':
            # From F to : -, J, 7
            return ['-', 'J', '7']
        elif dir == 'W':
            # From F to : None
            return []


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    part_1()
