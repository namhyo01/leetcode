// 39. Combination Sum https://leetcode.com/problems/combination-sum/
package main

import (
	"fmt"
	"slices"
)

// combinationSum 은 candidates 의 수를 무제한으로 골라 합이 target 이 되는 모든 조합을 반환한다.
func combinationSum(candidates []int, target int) [][]int {
	// TODO: 여기에 풀이를 작성하세요.
	var result [][]int
	slices.Sort(candidates)

	for idx := range candidates {
		recursive(candidates[idx], target, candidates[idx:], []int{candidates[idx]}, &result)
	}

	return result
}

func recursive(sum, target int, candidaes []int, apply []int, res *[][]int) {
	if sum == target {
		*res = append(*res, slices.Clone(apply))
		return
	}
	if sum > target {
		return
	}
	for idx := range candidaes {
		recursive(sum+candidaes[idx], target, candidaes[idx:], append(apply, candidaes[idx]), res)
	}
}

// main 은 손으로 굴려보는 놀이터. `go run ./problems/0039-combination-sum/`
func main() {
	// fmt.Println(combinationSum([]int{2, 3, 6, 7}, 7)) // [[2 2 3] [7]]
	// fmt.Println(combinationSum([]int{2, 3, 5}, 8))    // [[2 2 2 2] [2 3 3] [3 5]]
	fmt.Println(combinationSum([]int{2, 3, 8, 4}, 6)) // [[2 2 2] [2 4]]
	// fmt.Println(combinationSum([]int{2}, 1))          // []
}
