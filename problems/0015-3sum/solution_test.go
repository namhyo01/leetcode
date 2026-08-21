package main

import (
	"fmt"
	"math/rand"
	"slices"
	"testing"
	"time"
)

// normalize 는 삼중항/전체 순서를 무시하고 비교할 수 있는 키 집합으로 바꾼다.
func normalize(triplets [][]int) map[string]bool {
	out := make(map[string]bool, len(triplets))
	for _, t := range triplets {
		c := append([]int(nil), t...)
		slices.Sort(c)
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
					slices.Sort(c)
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

// TestThreeSumStructure 는 반환값이 구조적으로 말이 되는지 본다.
// 답이 우연히 맞아도 중복이 섞였거나 합이 0이 아니면 여기서 걸린다.
func TestThreeSumStructure(t *testing.T) {
	rng := rand.New(rand.NewSource(7))
	for i := 0; i < 200; i++ {
		n := 3 + rng.Intn(30)
		nums := make([]int, n)
		for j := range nums {
			nums[j] = rng.Intn(21) - 10
		}
		got := threeSum(slices.Clone(nums))

		have := map[int]int{}
		for _, v := range nums {
			have[v]++
		}
		seen := map[string]bool{}
		for _, tr := range got {
			if len(tr) != 3 {
				t.Fatalf("nums=%v: 길이가 3이 아닌 삼중항 %v", nums, tr)
			}
			if tr[0]+tr[1]+tr[2] != 0 {
				t.Fatalf("nums=%v: 합이 0이 아님 %v", nums, tr)
			}
			// 원본에 그만큼의 개수가 실제로 있어야 한다 (같은 원소 재사용 금지)
			need := map[int]int{}
			for _, v := range tr {
				need[v]++
			}
			for v, c := range need {
				if have[v] < c {
					t.Fatalf("nums=%v: %v 는 원본에 없는 조합 (%d 가 %d개 필요한데 %d개뿐)", nums, tr, v, c, have[v])
				}
			}
			if k := key(tr); seen[k] {
				t.Fatalf("nums=%v: 중복된 삼중항 %v", nums, tr)
			} else {
				seen[k] = true
			}
		}
	}
}

func key(tr []int) string {
	c := slices.Clone(tr)
	slices.Sort(c)
	return fmt.Sprint(c)
}

// TestThreeSumLarge 는 최대 입력에서 제한 시간 안에 끝나는지 본다.
//
// 임계값은 실측으로 정했다 (n=3000, 삼중항 16507개):
//
//	세 수를 전부 훑는 풀이  1038ms
//	한 수를 고정하는 풀이      10ms
//
// 300ms 면 정답 대비 30배 여유, 느린 풀이보다 3.5배 아래라 양쪽 다 안전하다.
func TestThreeSumLarge(t *testing.T) {
	const n = 3000
	rng := rand.New(rand.NewSource(3000))
	nums := make([]int, n)
	for i := range nums {
		nums[i] = rng.Intn(200001) - 100000
	}

	done := make(chan [][]int, 1)
	go func() { done <- threeSum(slices.Clone(nums)) }()

	select {
	case got := <-done:
		for _, tr := range got {
			if tr[0]+tr[1]+tr[2] != 0 {
				t.Fatalf("n=%d: 합이 0이 아닌 삼중항 %v", n, tr)
			}
		}
		if len(normalize(got)) != len(got) {
			t.Fatalf("n=%d: 중복된 삼중항이 있음 (%d개 중 유일한 건 %d개)", n, len(got), len(normalize(got)))
		}
	case <-time.After(300 * time.Millisecond):
		t.Fatalf("n=%d 이 300ms 안에 끝나지 않음 — 세 수를 전부 훑고 있을 가능성 (정답 풀이는 10ms 정도)", n)
	}
}
