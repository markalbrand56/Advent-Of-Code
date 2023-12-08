package utils

import (
	"os"
	"slices"
	"strings"
)

func ReadInput(filename string) ([]string, []string) {
	data, err := os.ReadFile(filename)

	if err != nil {
		panic("Error al abrir el archivo: " + err.Error())
	}

	var lines []string = strings.Split(string(data), "\r\n")

	var t string = strings.Split(lines[0], ":")[1]
	var d string = strings.Split(lines[1], ":")[1]

	var time []string = strings.Split(t, " ")
	var distance []string = strings.Split(d, " ")

	time = slices.DeleteFunc(time, func(e string) bool {
		return e == ""
	})

	distance = slices.DeleteFunc(distance, func(e string) bool {
		return e == ""
	})

	return time, distance
}
