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
        if izq in next_pipe("S", 'W'):
            next_pipes.append((s[0], s[1] - 1))
    if s[1] + 1 < len(lines[s[0]]):  # Buscar a la derecha
        der = lines[s[0]][s[1]+1]
        if der in next_pipe("S", 'E'):
            next_pipes.append((s[0], s[1] + 1))
    if s[0] - 1 >= 0:  # Buscar arriba
        arr = lines[s[0]-1][s[1]]
        if arr in next_pipe("S", 'N'):
            next_pipes.append((s[0] - 1, s[1]))
    if s[0] + 1 < len(lines):  # Buscar abajo
        aba = lines[s[0]+1][s[1]]
        if aba in next_pipe("S", 'S'):
            next_pipes.append((s[0] + 1, s[1]))

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
            izq_coords = (current[0] - 1, current[1])
            izq = lines[izq_coords[1]][izq_coords[0]]
            if izq in next_pipe(current_symbol, 'W') and izq_coords not in loop:
                next_pipes_inner.append((current[0] - 1, current[1]))
        if current[0] + 1 < len(lines[current[1]]):  # Buscar a la derecha
            der_coords = (current[0] + 1, current[1])
            der = lines[der_coords[1]][der_coords[0]]
            if der in next_pipe(current_symbol, 'E') and der_coords not in loop:
                next_pipes_inner.append((current[0] + 1, current[1]))
        if current[1] - 1 >= 0:  # Buscar arriba
            arr_coords = (current[0], current[1] - 1)
            arr = lines[arr_coords[1]][arr_coords[0]]
            if arr in next_pipe(current_symbol, 'N') and arr_coords not in loop:
                next_pipes_inner.append((current[0], current[1] - 1))
        if current[1] + 1 < len(lines):  # Buscar abajo
            aba_coords = (current[0], current[1] + 1)
            aba = lines[aba_coords[1]][aba_coords[0]]
            if aba in next_pipe(current_symbol, 'S') and aba_coords not in loop:
                next_pipes_inner.append((current[0], current[1] + 1))

        if len(next_pipes_inner) == 0:
            # Verificar que S sea adyacente a current
            if current[0] - 1 >= 0:  # Buscar a la izquierda
                izq_coords = (current[0] - 1, current[1])
                izq = lines[izq_coords[1]][izq_coords[0]]
                if izq == 'S':
                    loop.append(izq_coords)
                    break
            if current[0] + 1 < len(lines[current[1]]): # Buscar a la derecha
                der_coords = (current[0] + 1, current[1])
                der = lines[der_coords[1]][der_coords[0]]
                if der == 'S':
                    loop.append(der_coords)
                    break
            if current[1] - 1 >= 0: # Buscar arriba
                arr_coords = (current[0], current[1] - 1)
                arr = lines[arr_coords[1]][arr_coords[0]]
                if arr == 'S':
                    loop.append(arr_coords)
                    break
            if current[1] + 1 < len(lines): # Buscar abajo
                aba_coords = (current[0], current[1] + 1)
                aba = lines[aba_coords[1]][aba_coords[0]]
                if aba == 'S':
                    loop.append(aba_coords)
                    break
            else:
                print("No se encontro el loop")
                exit()
        else:
            current = next_pipes_inner[0]

    print(f"Loop: {loop}")

    # Encontrar las distancias de cada pipe en el loop respecto a S
    distances = {}
    for i in range(len(loop)):
        # la distancia son las casillas que hay entre S y el pipe
        # (1,1) -> (2,1) = 1
        # (1,1) -> (2,2) = 2
        distances[loop[i]] = abs(loop[i][0] - s[0]) + abs(loop[i][1] - s[1])

    print(f"Distances: {distances}")


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
    elif c == 'S':
        if direction == 'N':
            # From S to : |, 7, F
            return ['|', '7', 'F', 'S']
        elif direction == 'S':
            # From S to : |, L, J
            return ['|', 'L', 'J', 'S']
        elif direction == 'E':
            # From S to : -, 7, J
            return ['-', '7', 'J', 'S']
        elif direction == 'W':
            # From S to : -, F, L
            return ['-', 'F', 'L', 'S']
    else:
        return []


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    part_1()
