// 875. Koko Eating Bananas https://leetcode.com/problems/koko-eating-bananas/
package main

import "fmt"

// minEatingSpeed 는 h시간 안에 모든 바나나를 먹을 수 있는 최소 정수 속도 k를 반환한다.
func minEatingSpeed(piles []int, h int) int {
	// TODO: 여기에 풀이를 작성하세요.
	return 0
}

// main 은 손으로 굴려보는 놀이터. `go run ./problems/0875-koko-eating-bananas/`
func main() {
	fmt.Println(minEatingSpeed([]int{3, 6, 7, 11}, 8))        // 4
	fmt.Println(minEatingSpeed([]int{30, 11, 23, 4, 20}, 5))  // 30
	fmt.Println(minEatingSpeed([]int{30, 11, 23, 4, 20}, 6))  // 23
}
