const fs = require("fs")


console.log("Hello world")

fs.readFile("input.txt", "utf8", (error, datos) => {
  if (error) {
    console.error("Error al leer el archivo ", error)
    return
  }

  //console.log("Contenido: \n", datos)

  const lineas = datos.split('\n')

  lineas.forEach((linea, i) => {
    console.log(i, linea)
  })
  
})


