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

  // Encontrar los adyacentes
  let total = 0 

  nums.forEach(num => {

    symbols.forEach(symbol => {
      let valid = false

      for(let i = num.xi; i <= num.xf; i++){
        diffX = i - symbol.x 
        diffY = num.y - symbol.y

        if((diffY <= 1) && (diffY >= -1) && (diffX <= 1) && (diffX >= -1) && !valid){
          console.log(num.n, symbol.s)
          valid = true
          total += num.n
        }

      }

    })
    
  })

  console.log("TOTAL", total)
})
