// 15. 3Sum https://leetcode.com/problems/3sum/
package main

import "fmt"

// threeSum 은 합이 0인 중복 없는 삼중항을 모두 반환한다.
func threeSum(nums []int) [][]int {
	// TODO: 여기에 풀이를 작성하세요.
	return nil
}

// main 은 손으로 굴려보는 놀이터. `go run ./problems/0015-3sum/`
func main() {
	fmt.Println(threeSum([]int{-1, 0, 1, 2, -1, -4})) // [[-1 -1 2] [-1 0 1]]
	fmt.Println(threeSum([]int{0, 1, 1}))             // []
	fmt.Println(threeSum([]int{0, 0, 0}))             // [[0 0 0]]
}
