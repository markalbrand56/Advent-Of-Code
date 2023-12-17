console.log("Part 1")

// Tilt the platform north

const fs = require("fs")
const fileName = "input.txt"

fs.readFile(fileName, "utf-8", (error, datos) => {
    if (error){
        console.error("Error al leer el archivo", error)
    }

    const lines = datos.split("\r\n")
    lines.filter(line => line !== "")
    let rocks = []

    for (let i = 1; i < lines.length; i++){
        let currentLine = lines[i]

        for (let j = 0; j < currentLine.length; j++) {
            let currentChar = currentLine[j]

            if(currentChar === "O"){
                let prevIndex = i-1
                let prevChar = lines[prevIndex][j]

                if (prevChar !== "O" && prevChar !== "#"){ // it can move
                    while(prevIndex > 0 && lines[prevIndex-1][j] !== "O" && lines[prevIndex-1][j] !== "#"){
                        prevIndex--
                        prevChar = lines[prevIndex][j]
                    }
                    lines[prevIndex] = lines[prevIndex].substring(0, j) + "O" + lines[prevIndex].substring(j+1, lines[prevIndex].length)
                    lines[i] = lines[i].substring(0, j) + "." + lines[i].substring(j+1, lines[prevIndex].length)
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

