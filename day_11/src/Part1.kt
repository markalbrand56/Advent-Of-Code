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


    val h = image.size - 1  // Rows
    val w = image[0].size - 1  // Columns
    val imageExpanded: MutableList<MutableList<Char>> = ArrayList()

    // Revisar filas
    for (i in 0..h){
        var hasGalaxy = false
        for (j in 0..w){
            val c = image[i][j]
            if( c != '.'){
                hasGalaxy = true
            }
            println(c)
        }
        val fila = image[i]
        if (!hasGalaxy){ // Si la fila no tenía una galaxia
            imageExpanded.add(fila)
            imageExpanded.add(fila)
        } else{
            imageExpanded.add(fila)
        }

    }
    println()
}