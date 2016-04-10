package main

import (
	"golang.org/x/tour/wc"
	"strings"
)

func WordCount(s string) map[string]int {
	ans := make(map[string]int)
	for _, word := range strings.Fields(s) {
		ans[word]++
	}
	return ans
}

func main() {
	wc.Test(WordCount)
}
