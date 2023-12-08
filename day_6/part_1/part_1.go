package part_1

import (
	"day_6/utils"
	"fmt"
)

func P1() {
	var fileName string = "sample.txt"
	var time []string
	var distance []string

	time, distance = utils.ReadInput(fileName)
	fmt.Println(time, distance)

}
