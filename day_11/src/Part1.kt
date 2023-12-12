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
    for (i in 0..imageExpanded.size - 1){
        for (j in 0..imageExpanded[0].size - 1){
            print(imageExpanded[i][j])
        }
        println()
    }
}