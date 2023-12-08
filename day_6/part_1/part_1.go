package part_1

import (
	"day_6/utils"
	"fmt"
	"strconv"
)

func P1() {
	var fileName string = "input.txt"
	var time []string
	var distance []string

	time, distance = utils.ReadInput(fileName)
	fmt.Println(time, distance)

	/*

		Cada columna es una carrera
		time contiene la duración de la carrera
		distance tiene la distancia récord a batir

		de la duración de la carrera, se puede usar un tiempo para cargar en +1mm/ms la velocidad
		vo = 0mm/ms
	*/

	var gamesWon = 1
	for i := 0; i < len(time); i++ {
		var tMax, _ = strconv.Atoi(time[i])
		var dMin, _ = strconv.Atoi(distance[i])

		var combinations = 0
		for t := 0; t <= tMax; t++ {
			var v = t // t increments each ms its held by one

			var d = v * (tMax - t)

			if d > dMin {
				combinations++
			}
		}
		fmt.Printf("%d: %d\n", i, combinations)
		gamesWon *= combinations
	}

	fmt.Printf("Games won %d\n", gamesWon)

}
