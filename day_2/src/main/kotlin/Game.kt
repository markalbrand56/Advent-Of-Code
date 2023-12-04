class Game(val id: Int){
    var r: Int = 0
    var g: Int = 0
    var b: Int = 0

    private val MAX_RED = 12
    private val MAX_GREEN = 13
    private val MAX_BLUE = 14

    private var roundPossible = true

    fun possible(): Boolean {
        return roundPossible
    }

    fun check() {
        if ((r > MAX_RED) or (g > MAX_GREEN) or (b > MAX_BLUE)){
            roundPossible = false
        }
    }
}