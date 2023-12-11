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

    """
    -L|F7
    7S-7|
    L|7||
    -L-J|
    L|-JF
    
    S: inicio
    1. Encontrar que valor de S conecta con el siguiente pipe
    2. Verificar que se cree un loop
    3. Encontrar las distancias de cada pipe en el loop respecto a S
    
    """

    f = open("sample.txt", "r")
    lines = []

    for line in f:
        if line != "\n":
            lines.append([x for x in line.strip()])

    f.close()

    # Encontrar S
    s = None
    for i in range(len(lines)):
        for j in range(len(lines[i])):
            if lines[i][j] == 'S':
                s = (i, j)
                break
        if s:
            break
    print(f"S: {s}")

    # Encontrar las siguientes pipes que pueda ser visitado desde S
    next_pipes = []
    if s[1] - 1 >= 0:  # Buscar a la izquierda
        izq = lines[s[0]][s[1]-1]
        if izq in next_pipe(izq, 'W'):
            next_pipes.append((s[0] - 1, s[1]))
    if s[1] + 1 < len(lines[s[0]]):  # Buscar a la derecha
        der = lines[s[0]][s[1]+1]
        if der in next_pipe(der, 'E'):
            next_pipes.append((s[0] + 1, s[1]))
    if s[0] - 1 >= 0:  # Buscar arriba
        arr = lines[s[0]-1][s[1]]
        if arr in next_pipe(arr, 'N'):
            next_pipes.append((s[0], s[1] - 1))
    if s[0] + 1 < len(lines):  # Buscar abajo
        aba = lines[s[0]+1][s[1]]
        if aba in next_pipe(aba, 'S'):
            next_pipes.append((s[0], s[1] + 1))

    print(f"Next pipe: {next_pipes}")

    # Encontrar el loop
    loop = []
    loop.append(s)
    current = next_pipes[0]
    while current != s:
        loop.append(current)
        next_pipes_inner = []
        current_symbol = lines[current[1]][current[0]]
        if current[0] - 1 >= 0:  # Buscar a la izquierda
            izq = lines[current[1]][current[0]-1]
            izq_coords = (current[0] - 1, current[1])
            if izq in next_pipe(current_symbol, 'W') and izq_coords not in loop:
                next_pipes_inner.append((current[0] - 1, current[1]))
        if current[0] + 1 < len(lines[current[1]]):  # Buscar a la derecha
            der = lines[current[1]][current[0]+1]
            der_coords = (current[0] + 1, current[1])
            if der in next_pipe(current_symbol, 'E') and der_coords not in loop:
                next_pipes_inner.append((current[0] + 1, current[1]))
        if current[1] - 1 >= 0:  # Buscar arriba
            arr = lines[current[1]-1][current[0]]
            arr_coords = (current[0], current[1] - 1)
            if arr in next_pipe(current_symbol, 'N') and arr_coords not in loop:
                next_pipes_inner.append((current[0], current[1] - 1))
        if current[1] + 1 < len(lines):  # Buscar abajo
            aba = lines[current[1]+1][current[0]]
            aba_coords = (current[0], current[1] + 1)
            if aba in next_pipe(current_symbol, 'S') and aba_coords not in loop:
                next_pipes_inner.append((current[0], current[1] + 1))

        if len(next_pipes_inner) == 0:
            # Verificar que S sea adyacente a current
            if s[0] - 1 >= 0:  # Buscar a la izquierda
                izq = lines[s[1]][s[0] - 1]
                if izq in next_pipe(izq, 'W') and (s[0] - 1, s[1]) == current:
                    loop.append(s)
                    break
            if s[0] + 1 < len(lines[s[1]]):  # Buscar a la derecha
                der = lines[s[1]][s[0] + 1]
                if der in next_pipe(der, 'E') and (s[0] + 1, s[1]) == current:
                    loop.append(s)
                    break
            if s[1] - 1 >= 0:  # Buscar arriba
                arr = lines[s[1] - 1][s[0]]
                if arr in next_pipe(arr, 'N') and (s[0], s[1] - 1) == current:
                    loop.append(s)
                    break
            if s[1] + 1 < len(lines):  # Buscar abajo
                aba = lines[s[1] + 1][s[0]]
                if aba in next_pipe(aba, 'S') and (s[0], s[1] + 1) == current:
                    loop.append(s)

            if loop[-1] == s:
                break
            else:
                print("No se encontro el loop")
                exit()
        else:
            current = next_pipes_inner[0]

    print(f"Loop: {loop}")


def next_pipe(c: str, direction: str) -> list[str]:
    # Dir: N, S, E, W

    if c == '|':
        if direction == 'N':
            # From | to : |, 7, F
            return ['|', '7', 'F', 'S']
        elif direction == 'S':
            # From | to : |, L, J
            return ['|', 'L', 'J', 'S']
        elif direction == 'E':
            # From | to : None
            return []
        elif direction == 'W':
            # From | to : None
            return []
    elif c == '-':
        if direction == 'N':
            # From - to : None
            return []
        elif direction == 'S':
            # From - to : None
            return []
        elif direction == 'E':
            # From - to : -, 7, J
            return ['-', '7', 'J', 'S']
        elif direction == 'W':
            # From - to : -, L, F
            return ['-', 'L', 'F', 'S']
    elif c == 'L':
        if direction == 'N':
            # From L to : | , 7, F
            return ['|', '7', 'F', 'S']
        elif direction == 'S':
            # From L to : None
            return []
        elif direction == 'E':
            # From L to : -, 7, J
            return ['-', '7', 'J', 'S']
        elif direction == 'W':
            # From L to : None
            return []
    elif c == 'J':
        if direction == 'N':
            # From J to : |, 7, F
            return ['|', '7', 'F', 'S']
        elif direction == 'S':
            # From J to : None
            return []
        elif direction == 'E':
            # From J to : None
            return []
        elif direction == 'W':
            # From J to : -, F, L
            return ['-', 'F', 'L', 'S']
    elif c == '7':
        if direction == 'N':
            # From 7 to : None
            return []
        elif direction == 'S':
            # From 7 to : | , L, J
            return ['|', 'L', 'J', 'S']
        elif direction == 'E':
            # From 7 to : None
            return []
        elif direction == 'W':
            # From 7 to : -, F, L
            return ['-', 'F', 'L', 'S']
    elif c == 'F':
        if direction == 'N':
            # From F to : None
            return []
        elif direction == 'S':
            # From F to : |, L, J
            return ['|', 'L', 'J', 'S']
        elif direction == 'E':
            # From F to : -, J, 7
            return ['-', 'J', '7', 'S']
        elif direction == 'W':
            # From F to : None
            return []
    else:
        return []


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    part_1()
