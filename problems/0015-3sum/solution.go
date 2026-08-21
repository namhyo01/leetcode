// 15. 3Sum https://leetcode.com/problems/3sum/
package main

import (
	"fmt"
	"slices"
)

// threeSum 은 합이 0인 중복 없는 삼중항을 모두 반환한다.
func threeSum(nums []int) [][]int {
	// TODO: 여기에 풀이를 작성하세요.
	slices.Sort(nums)
	var res [][]int
	for i := 0; i < len(nums)-2; i++ {
		num := nums[i]
		if num > 0 { // 더 이상은 불가
			break
		}
		if i > 0 && num == nums[i-1] { // 중복 제거
			continue
		}

		st := i + 1
		end := len(nums) - 1
		for st < end {
			sum := num + nums[st] + nums[end]
			if sum == 0 {
				res = append(res, []int{num, nums[st], nums[end]})
				st++
				for st < end && nums[st] == nums[st-1] { // 중복 제거
					st++
				}
			} else if sum < 0 {
				st++
			} else {
				end--
			}
		}

	}

	return res
}

// main 은 손으로 굴려보는 놀이터. `go run ./problems/0015-3sum/`
func main() {
	fmt.Println(threeSum([]int{-1, 0, 1, 2, -1, -4})) // [[-1 -1 2] [-1 0 1]]
	fmt.Println(threeSum([]int{0, 1, 1}))             // []
	fmt.Println(threeSum([]int{0, 0, 0}))             // [[0 0 0]]
}
