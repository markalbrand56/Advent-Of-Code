package utils

import (
	"os"
	"strings"
)

func ReadFile(filename string) ([]string, error) {
	data, err := os.ReadFile(filename)

	if err != nil {
		return nil, err
	}

	var lines = strings.Split(string(data), "\r\n")

	return lines, nil
}
