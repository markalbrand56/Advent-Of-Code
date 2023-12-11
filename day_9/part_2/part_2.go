package part_2

import (
	"day_9/utils"
	"fmt"
	"slices"
	"strconv"
	"strings"
)

func Part2() {
	fmt.Println("Part 2")
	var fileName = "input.txt"

	readings, err := utils.ReadFile(fileName)

	if err != nil {
		panic("Error opening file. " + err.Error())
	}

	var extrapolations [][][]int
	for _, r := range readings {
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

	for i := range extrapolations {
		zeroes := false
		j := 0
		for zeroes != true {
			var diffs []int // diferencias entre los valores de una linea
			line := extrapolations[i][j]
			for k := 0; k < len(line)-1; k++ {
				//fmt.Printf("%d-%d: %d\n", line[k], line[k+1], line[k+1]-line[k])
				diffs = append(diffs, line[k+1]-line[k])
			}
			extrapolations[i] = append(extrapolations[i], diffs)
			if slices.Min(diffs) == 0 && slices.Max(diffs) == 0 {
				zeroes = true
			}
			j++
		}
		//fmt.Println(extrapolations[i])
	}

	for i := range extrapolations {
		slices.Reverse(extrapolations[i])

		for j := 0; j < len(extrapolations[i])-1; j++ {
			line := extrapolations[i][j]
			k := 0
			v := line[0]

			e := extrapolations[i][j+1][k] - v

			extrapolations[i][j+1] = slices.Insert(extrapolations[i][j+1], 0, e)
		}
	}

	var resultado int
	for _, ex := range extrapolations {
		line := ex[len(ex)-1]
		v := line[0]
		//fmt.Printf("\t%d\n", v)
		resultado += v
	}

	fmt.Printf("Resultado: %d\n", resultado)
}
