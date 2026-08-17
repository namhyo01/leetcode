// 15. 3Sum https://leetcode.com/problems/3sum/
package main

import (
	"fmt"
	"slices"
)

// threeSum 은 합이 0인 중복 없는 삼중항을 모두 반환한다.
//
// 시간 O(n^2) — 정렬 O(n log n) + 바깥 루프 n * 투 포인터 O(n)
// 공간 O(1) — 정렬이 제자리, 출력 제외
func threeSum(nums []int) [][]int {
	slices.Sort(nums)
	res := [][]int{}
	n := len(nums)

	for i := 0; i < n-2; i++ {
		// 정렬돼 있으므로 고정값이 양수면 뒤는 전부 양수 → 합 0 불가
		if nums[i] > 0 {
			break
		}
		// 고정값이 직전과 같으면 결과가 통째로 중복된다
		if i > 0 && nums[i] == nums[i-1] {
			continue
		}

		// 남은 구간에서 합이 -nums[i]인 두 수 찾기 (Two Sum)
		l, r := i+1, n-1
		for l < r {
			s := nums[i] + nums[l] + nums[r]
			switch {
			case s < 0:
				// 가장 큰 짝과 붙여도 모자라니 nums[l]은 가망 없음
				l++
			case s > 0:
				r--
			default:
				res = append(res, []int{nums[i], nums[l], nums[r]})
				l++
				// 같은 l 값은 같은 삼중항을 또 만든다
				for l < r && nums[l] == nums[l-1] {
					l++
				}
			}
		}
	}
	return res
}

// main 은 손으로 굴려보는 놀이터. `go run ./problems/0015-3sum/`
func main() {
	nums := []int{-1, 0, 1, 2, -1, -4}
	fmt.Println(threeSum(nums)) // [[-1 -1 2] [-1 0 1]]
}
