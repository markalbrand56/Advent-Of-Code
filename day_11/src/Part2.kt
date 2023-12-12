import java.io.File

fun main() {
    println("Part 2")

    val lines = File("src/input.txt").readLines()
    val image: MutableList<MutableList<Char>> = ArrayList()
    val reps = 1000000


    lines.forEach { line ->
        val l: MutableList<Char> = ArrayList()
        line.forEach {char ->
            l.add(char)
        }
        image.add(l)
    }


    var h = image.size - 1  // Rows
    var w = image[0].size - 1  // Columns
    val rowsExpanded: MutableList<Int> = ArrayList() // Holds the indexes of the rows that don't have a galaxy
    val colsExpanded: MutableList<Int> = ArrayList() // Holds the indexes of the columns that don't have a galaxy

    // Expandir columnas
    // Si en la columna no se encuentra un "#" esta columna se debe duplicar
    for (j in 0..w){
        var hasGalaxy = false
        for (i in 0..h){
            val c = image[i][j]
            if( c != '.'){
                hasGalaxy = true
            }
        }
        if (!hasGalaxy){ // Si la columna no tenía una galaxia
            colsExpanded.add(j)
        }
    }

    // Expandir filas
    // Si en la fila no se encuentra un "#" esta fila se debe duplicar
    for (i in 0..h){
        var hasGalaxy = false
        for (j in 0..w){
            val c = image[i][j]
            if( c != '.'){
                hasGalaxy = true
            }
        }
        if (!hasGalaxy){ // Si la fila no tenía una galaxia
            rowsExpanded.add(i)
        }
    }

    // Imprimir imagen expandida
    println("Imagen expandida")


    // Guardar las coordenadas X,Y de cada "#" en un arraylist
    val galaxies: MutableList<MutableList<Int>> = ArrayList()
    for (i in 0..<image.size){
        var iEx = i
        for (r in 0..<rowsExpanded.size){
            if (rowsExpanded[r] < i){
                iEx += reps - 1
            }

        }
        for (j in 0..<image[0].size){
            var jEx = j
            for (c in 0..<colsExpanded.size){
                if (colsExpanded[c] < j){
                    jEx += reps - 1
                }
            }
            if (image[i][j] == '#'){
                val galaxy: MutableList<Int> = ArrayList()
                galaxy.add(iEx)
                galaxy.add(jEx)
                galaxies.add(galaxy)
            }
        }
    }

    // Imprimir coordenadas de las galaxias
    println("Coordenadas de las galaxias")


    // Generar todas las combinaciones de galaxias, sin importar el orden de las galaxias, sin repetir parejas
    val combinations: MutableList<MutableList<MutableList<Int>>> = ArrayList()
    for (i in 0..<galaxies.size){
        for (j in i+1..<galaxies.size){
            val combination: MutableList<MutableList<Int>> = ArrayList()
            combination.add(galaxies[i])
            combination.add(galaxies[j])
            combinations.add(combination)
        }
    }

    // Imprimir combinaciones
    println("Combinaciones")
    println(combinations.size)

    // Calcular la distancia entre cada par de galaxias y sumar las distancias
    var totalDistance = 0
    for (i in 0..<combinations.size){
        val combination = combinations[i]
        val galaxy1 = combination[0]
        val galaxy2 = combination[1]
        val x1 = galaxy1[0]
        val y1 = galaxy1[1]
        val x2 = galaxy2[0]
        val y2 = galaxy2[1]
        val distance = Math.abs(x1 - x2) + Math.abs(y1 - y2)
        totalDistance += distance
    }

    // Imprimir distancia total
    println("Distancia total")
    println(totalDistance)
}