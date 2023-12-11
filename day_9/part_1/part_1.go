package part_1

import (
	"day_9/utils"
	"fmt"
	"slices"
	"strconv"
	"strings"
)

func Part1() {
	fmt.Println("Part 1")
	var fileName = "sample.txt"

	readings, err := utils.ReadFile(fileName)

	if err != nil {
		panic("Error opening file. " + err.Error())
	}

	var extrapolations [][][]int
	for _, r := range readings {
		fmt.Println(r)
		vals := strings.Split(r, " ")
		var nums []int
		for _, v := range vals {
			n, _ := strconv.Atoi(v)
			nums = append(nums, n)
		}
		var extrapolation [][]int
		extrapolation = append(extrapolation, nums)
		extrapolations = append(extrapolations, extrapolation)
	}

	for i, _ := range extrapolations {
		zeroes := false
		j := 0
		for zeroes != true {
			var diffs []int // diferencias entre los valores de una linea
			line := extrapolations[i][j]
			for k := 0; k < len(line)-1; k++ {
				fmt.Printf("%d-%d: %d\n", line[k], line[k+1], line[k+1]-line[k])
				diffs = append(diffs, line[k+1]-line[k])
			}
			extrapolations[i] = append(extrapolations[i], diffs)
			if slices.Min(diffs) == 0 && slices.Max(diffs) == 0 {
				zeroes = true
			}
			j++
		}
		fmt.Println(extrapolations[i])
	}

}
