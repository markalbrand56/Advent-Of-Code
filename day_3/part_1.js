const fs = require("fs")

console.log("Hello world")

function isCharNumber(c) {
  return typeof c === 'string' && c.length == 1 && c >= '0' && c <= '9';
}

fs.readFile("sample.txt", "utf8", (error, datos) => {
  if (error) {
    console.error("Error al leer el archivo ", error)
    return
  }

  //console.log("Contenido: \n", datos)

  const lineas = datos.split('\n')
  console.log("Len", lineas.length)
  const nums = []
  const symbols = []

  for (let i = 0; i < (lineas.length); i++) {
    // por cada linea 
    const linea = lineas[i]
    var tempNum = ""

    for (let j = 0; j < (linea.length); j++) {
      const char = linea[j];  // char 
      
      if (isCharNumber(char)){
        console.log("Num", char)
        tempNum += char.trim()

      } else {
        const n = parseInt(tempNum)

        if(!isNaN(n)){  // Guarda el número temporal independiente de qué lea
          nums.push({
            n: n,  // Numero
            xi: j-tempNum.length,  // Columna inicial
            xf: j-1,  // Columna final
            y: i  // Fila
          })
          tempNum = ""
        }

        if (char != ".") {
          console.log("Symbol", char)

          symbols.push({
            s: char, 
            x: j,
            y: i
          })
        }
      }
    }
  }

  console.log("Nums: ", nums)
  console.log("Symbols", symbols)
})
