package main

import (
	"fmt"
	"math/rand"
	"sort"
	"testing"
)

// normalize 는 삼중항/전체 순서를 무시하고 비교할 수 있는 키 집합으로 바꾼다.
func normalize(triplets [][]int) map[string]bool {
	out := make(map[string]bool, len(triplets))
	for _, t := range triplets {
		c := append([]int(nil), t...)
		sort.Ints(c)
		out[fmt.Sprint(c)] = true
	}
	return out
}

func bruteForce(nums []int) map[string]bool {
	out := map[string]bool{}
	n := len(nums)
	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			for k := j + 1; k < n; k++ {
				if nums[i]+nums[j]+nums[k] == 0 {
					c := []int{nums[i], nums[j], nums[k]}
					sort.Ints(c)
					out[fmt.Sprint(c)] = true
				}
			}
		}
	}
	return out
}

func sameSet(a, b map[string]bool) bool {
	if len(a) != len(b) {
		return false
	}
	for k := range a {
		if !b[k] {
			return false
		}
	}
	return true
}

func TestThreeSum(t *testing.T) {
	cases := []struct {
		nums []int
		want [][]int
	}{
		{[]int{-1, 0, 1, 2, -1, -4}, [][]int{{-1, -1, 2}, {-1, 0, 1}}},
		{[]int{0, 1, 1}, [][]int{}},
		{[]int{0, 0, 0}, [][]int{{0, 0, 0}}},
		{[]int{0, 0, 0, 0}, [][]int{{0, 0, 0}}},
		{[]int{-2, 0, 1, 1, 2}, [][]int{{-2, 0, 2}, {-2, 1, 1}}},
		{[]int{3, 0, -2, -1, 1, 2}, [][]int{{-2, -1, 3}, {-2, 0, 2}, {-1, 0, 1}}},
		{[]int{1, 2, 3}, [][]int{}},
	}

	for _, c := range cases {
		got := threeSum(append([]int(nil), c.nums...))
		for _, tr := range got {
			if len(tr) != 3 {
				t.Fatalf("nums=%v: 삼중항 길이가 3이 아님: %v", c.nums, tr)
			}
		}
		if len(normalize(got)) != len(got) {
			t.Errorf("nums=%v: 중복된 삼중항이 있음: %v", c.nums, got)
			continue
		}
		if !sameSet(normalize(got), normalize(c.want)) {
			t.Errorf("nums=%v\n  기대: %v\n  실제: %v", c.nums, c.want, got)
		}
	}
}

func TestThreeSumRandom(t *testing.T) {
	rng := rand.New(rand.NewSource(42))
	for i := 0; i < 300; i++ {
		n := 3 + rng.Intn(10)
		nums := make([]int, n)
		for j := range nums {
			nums[j] = rng.Intn(13) - 6
		}
		got := normalize(threeSum(append([]int(nil), nums...)))
		want := bruteForce(nums)
		if !sameSet(got, want) {
			t.Fatalf("랜덤 케이스 실패 nums=%v\n  기대: %v\n  실제: %v", nums, want, got)
		}
	}
}

func BenchmarkThreeSum(b *testing.B) {
	rng := rand.New(rand.NewSource(1))
	nums := make([]int, 3000)
	for i := range nums {
		nums[i] = rng.Intn(200001) - 100000
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		threeSum(append([]int(nil), nums...))
	}
}
