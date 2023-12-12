import java.io.File

fun main() {
    println("Part 1")

    val lines = File("src/sample.txt").readLines()
    val image: MutableList<MutableList<Char>> = ArrayList()

    lines.forEach { line ->
        println(line)

        val l: MutableList<Char> = ArrayList()
        line.forEach {char ->
            l.add(char)
        }
        image.add(l)
    }


    var h = image.size - 1  // Rows
    var w = image[0].size - 1  // Columns
    val imageColExpanded: MutableList<MutableList<Char>> = ArrayList()
    val imageExpanded: MutableList<MutableList<Char>> = ArrayList()

    for (i in 0..h){
        // añadir arraylist vacio
        imageColExpanded.add(ArrayList())
    }

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
            for (i in 0..h){
                imageColExpanded[i].add(image[i][j])
            }
        }
        for (i in 0..h){
            imageColExpanded[i].add(image[i][j])
        }
    }

    // Expandir filas
    // Si en la fila no se encuentra un "#" esta fila se debe duplicar
    h = imageColExpanded.size - 1
    w = imageColExpanded[0].size - 1
    for (i in 0..h){
        var hasGalaxy = false
        for (j in 0..w){
            val c = imageColExpanded[i][j]
            if( c != '.'){
                hasGalaxy = true
            }
            println(c)
        }
        val fila = imageColExpanded[i]
        if (!hasGalaxy){ // Si la fila no tenía una galaxia
            imageExpanded.add(fila)
        }
        imageExpanded.add(fila)
    }

    // Imprimir imagen expandida
    println("Imagen expandida")
    for (i in 0..<imageExpanded.size){
        for (j in 0..<imageExpanded[0].size){
            print(imageExpanded[i][j])
        }
        println()
    }

    // Guardar las coordenadas X,Y de cada "#" en un arraylist
    val galaxies: MutableList<MutableList<Int>> = ArrayList()
    for (i in 0..<imageExpanded.size){
        for (j in 0..<imageExpanded[0].size){
            if (imageExpanded[i][j] == '#'){
                val galaxy: MutableList<Int> = ArrayList()
                galaxy.add(i)
                galaxy.add(j)
                galaxies.add(galaxy)
            }
        }
    }

    // Imprimir coordenadas de las galaxias
    println("Coordenadas de las galaxias")
    for (i in 0..<galaxies.size){
        println(galaxies[i])
    }

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