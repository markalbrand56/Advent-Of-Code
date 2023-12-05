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

        if(!isNaN(n)){
          nums.push({
            n: n,
            xi: j-tempNum.length,
            xf: j-1,
            y: i
          })
          tempNum = ""
        }

      }
    }
  }

  console.log("Nums: ", nums)
})
