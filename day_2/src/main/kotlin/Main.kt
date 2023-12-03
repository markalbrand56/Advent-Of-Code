import java.io.File

class Game(val id: Int){
    var r: Int = 0
    var g: Int = 0
    var b: Int = 0

    var roundPossible = true

    fun possible(): Boolean {
        return roundPossible
    }

    fun check() {
        if ((r > MAX_RED) or (g > MAX_GREEN) or (b > MAX_BLUE)){
            roundPossible = false
        }
    }
}

const val MAX_RED = 12
const val MAX_GREEN = 13
const val MAX_BLUE = 14

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
                    game.r = Integer.parseInt(amount)
                } else if (color == "green"){
                    game.g = Integer.parseInt(amount)
                } else if (color == "blue"){
                    game.b = Integer.parseInt(amount)
                }
                game.check()
            }
        }
        println("${game.id} ${game.possible()} R:${game.r} G:${game.g} B:${game.b}")
        if (game.possible()){
            total += game.id
        }
    }

    println("TOTAL: $total")  // 2439
}