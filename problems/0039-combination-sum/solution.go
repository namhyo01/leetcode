// 39. Combination Sum https://leetcode.com/problems/combination-sum/
package main

import "fmt"

// combinationSum 은 candidates 의 수를 무제한으로 골라 합이 target 이 되는 모든 조합을 반환한다.
func combinationSum(candidates []int, target int) [][]int {
	// TODO: 여기에 풀이를 작성하세요.
	return nil
}

// main 은 손으로 굴려보는 놀이터. `go run ./problems/0039-combination-sum/`
func main() {
	fmt.Println(combinationSum([]int{2, 3, 6, 7}, 7)) // [[2 2 3] [7]]
	fmt.Println(combinationSum([]int{2, 3, 5}, 8))    // [[2 2 2 2] [2 3 3] [3 5]]
	fmt.Println(combinationSum([]int{2}, 1))          // []
}
