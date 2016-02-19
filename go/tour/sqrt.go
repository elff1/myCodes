package main

import (
	"fmt"
	"math"
)

func Sqrt(x float64) float64 {
	z := 1.0
	y := 0.0
	const e = 1e-10
	for math.Abs(z - y) > e {
		y = z
		z = z - (z * z - x) / 2 / z
	}
	return z
}

func main() {
	fmt.Println(Sqrt(2), math.Sqrt(2))
	//fmt.Printf("%T", 0.0)
}
