import java.io.File

fun main(args: Array<String>) {
    println("Hello World!")

    val lines = File("input.txt").readLines()
    var total = 0

    lines.forEach{line ->
        val first = line.split(":")

        val id = first[0].split(" ")[1]
        val rounds = first[1].split(";")

        val game = Game(Integer.parseInt(id))

        rounds.forEach { set ->
            val round = set.split(", ")

            round.forEach { cubes ->
                val cubesSplit = cubes.trim().split(" ")
                val amount = cubesSplit[0]
                val color = cubesSplit[1]

                if (color == "red"){
                    val red = Integer.parseInt(amount)

                    if (red > game.r) {
                        game.r = red
                    }
                } else if (color == "green"){
                    val green = Integer.parseInt(amount)

                    if (green > game.g) {
                        game.g = green
                    }
                } else if (color == "blue"){
                    val blue = Integer.parseInt(amount)

                    if (blue > game.b) {
                        game.b = blue
                    }
                }
            }
        }
        total += game.r * game.g * game.b
    }

    println("TOTAL: $total")  // 2439
}