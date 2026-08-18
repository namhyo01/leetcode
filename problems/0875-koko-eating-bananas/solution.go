// 875. Koko Eating Bananas https://leetcode.com/problems/koko-eating-bananas/
package main

import (
	"fmt"
	"math"
	"slices"
)

// minEatingSpeed 는 h시간 안에 모든 바나나를 먹을 수 있는 최소 정수 속도 k를 반환한다.
func minEatingSpeed(piles []int, h int) int {
	// TODO: 여기에 풀이를 작성하세요.
	slices.Sort(piles)
	st := 1
	num := len(piles) - 1
	end := piles[num]
	if num+1 == h {
		return end
	}
	for st <= end {
		mid := (st + end) / 2
		if howManyEatingHours(piles, mid) > h { // h가 더 작은 경우 => 현재 숫자가 너무 작다
			st = mid + 1
		} else {
			end = mid - 1
		}
	}

	return st
}

func howManyEatingHours(piles []int, c int) int {
	cnt := 0
	for _, pile := range piles {
		cnt += int(math.Ceil(float64(pile) / float64(c)))
	}
	return cnt
}

// main 은 손으로 굴려보는 놀이터. `go run ./problems/0875-koko-eating-bananas/`
func main() {
	fmt.Println(minEatingSpeed([]int{3, 6, 7, 11}, 8))       // 4
	fmt.Println(minEatingSpeed([]int{30, 11, 23, 4, 20}, 5)) // 30
	fmt.Println(minEatingSpeed([]int{30, 11, 23, 4, 20}, 6)) // 23
	fmt.Println(minEatingSpeed([]int{312884470}, 312884469)) // 2
}
