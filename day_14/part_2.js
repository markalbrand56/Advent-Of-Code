console.log("Part 2")

const fs = require("fs")
const fileName = "input.txt"
const cycles = 1000000000
// a cycle is 4 tilts
// 1. tilt north: move all rocks up as far as possible
// 2. tilt west: move all rocks left as far as possible
// 3. tilt south: move all rocks down as far as possible
// 4. tilt east: move all rocks right as far as possible

fs.readFile(fileName, "utf-8", (error, datos) => {
    if (error){
        console.error("Error al leer el archivo", error)
    }

    const lines = datos.split("\r\n")
    lines.filter(line => line !== "")
    let rocks = []

    for(let c = 0; c < cycles; c++){
        // every million cycles print
        if (c % 1000000 === 0){
            console.log("Cycle", c+1)
        }

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
        for (let j = 1; j < lines[0].length; j++){
            for (let i = 0; i < lines.length; i++){
                let currentChar = lines[i][j]

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

        // Tilt the platform south
        for (let i = lines.length-2; i >= 0; i--){
            let currentLine = lines[i]

            for (let j = 0; j < currentLine.length; j++) {
                let currentChar = currentLine[j]

                if(currentChar === "O"){
                    let prevIndex = i+1
                    let prevChar = lines[prevIndex][j]

                    if (prevChar !== "O" && prevChar !== "#"){ // it can move
                        while(prevIndex < lines.length-1 && lines[prevIndex+1][j] !== "O" && lines[prevIndex+1][j] !== "#"){ // Moves further up
                            prevIndex++
                            prevChar = lines[prevIndex][j]
                        }
                        lines[prevIndex] = lines[prevIndex].substring(0, j) + "O" + lines[prevIndex].substring(j+1, lines[prevIndex].length)
                        lines[i] = lines[i].substring(0, j) + "." + lines[i].substring(j+1, lines[prevIndex].length)
                    }
                }
            }
        }

        // Tilt the platform east
        for (let j = lines[0].length-2; j >= 0; j--){
            for (let i = 0; i < lines.length; i++){
                let currentChar = lines[i][j]

                if(currentChar === "O"){
                    let prevIndex = j+1
                    let prevChar = lines[i][prevIndex]

                    if (prevChar !== "O" && prevChar !== "#"){ // it can move
                        while(prevIndex < lines[0].length-1 && lines[i][prevIndex+1] !== "O" && lines[i][prevIndex+1] !== "#"){ // Moves further up
                            prevIndex++
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

