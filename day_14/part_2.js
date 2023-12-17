console.log("Part 2")

const fs = require("fs")
const fileName = "sample.txt"
const cycles = 1
// a cycle is 4 tilts
// 1. tilt north
// 2. tilt west
// 3. tilt south
// 4. tilt east

fs.readFile(fileName, "utf-8", (error, datos) => {
    if (error){
        console.error("Error al leer el archivo", error)
    }

    const lines = datos.split("\r\n")
    lines.filter(line => line !== "")
    let rocks = []

    for(let c = 0; c < cycles; c++){

        // Tilt the platform north
        for (let i = 1; i < lines.length; i++){
            let currentLine = lines[i]

            for (let j = 0; j < currentLine.length; j++) {
                let currentChar = currentLine[j]

                if(currentChar === "O"){
                    let prevIndex = i-1
                    let prevChar = lines[prevIndex][j]

                    if (prevChar !== "O" && prevChar !== "#"){ // it can move
                        while(prevIndex > 0 && lines[prevIndex-1][j] !== "O" && lines[prevIndex-1][j] !== "#"){ // Moves further up
                            prevIndex--
                            prevChar = lines[prevIndex][j]
                        }
                        lines[prevIndex] = lines[prevIndex].substring(0, j) + "O" + lines[prevIndex].substring(j+1, lines[prevIndex].length)
                        lines[i] = lines[i].substring(0, j) + "." + lines[i].substring(j+1, lines[prevIndex].length)
                    }
                }
            }
        }

        // Tilt the platform west
        for (let i = 0; i < lines.length; i++){
            let currentLine = lines[i]

            for (let j = currentLine.length - 1; j > 0; j--) {
                let currentChar = currentLine[j]

                if(currentChar === "O"){
                    let prevIndex = j-1
                    let prevChar = lines[i][prevIndex]

                    if (prevChar !== "O" && prevChar !== "#"){ // it can move
                        while(prevIndex > 0 && lines[i][prevIndex-1] !== "O" && lines[i][prevIndex-1] !== "#"){ // Moves further up
                            prevIndex--
                            prevChar = lines[i][prevIndex]
                        }
                        lines[i] = lines[i].substring(0, prevIndex) + "O" + lines[i].substring(prevIndex+1, lines[i].length)
                        lines[i] = lines[i].substring(0, j) + "." + lines[i].substring(j+1, lines[i].length)
                    }
                }
            }
        }
    }

    for(let i = 0; i < lines.length; i++){
        for (let j = 0; j < lines[i].length; j++){
            if (lines[i][j] === "O"){
                rocks.push([i,j])
            }
        }
    }

    lines.forEach(line => {
        console.log(line)
    })

    let total = 0

    // sort rocks by row
    rocks.sort((a,b) => {
        return a[0] - b[0]
    })

    rocks.forEach(rock => {
        total += lines.length - rock[0]
    })

    console.log("Total", total)
})

