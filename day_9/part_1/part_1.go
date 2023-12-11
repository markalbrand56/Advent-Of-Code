package part_1

import (
	"day_9/utils"
	"fmt"
)

func Part1() {
	fmt.Println("Part 1")
	var fileName = "sample.txt"
	var readings []string

	readings, err := utils.ReadFile(fileName)

	if err != nil {
		panic("Error opening file. " + err.Error())
	}

	for _, r := range readings {
		fmt.Println(r)
	}

}
