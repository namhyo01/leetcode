package main

import (
	"fmt"
	"math/rand"
	"slices"
	"testing"
)

// key 는 조합 내부 순서를 무시한 비교 키를 만든다.
func key(combo []int) string {
	c := append([]int(nil), combo...)
	slices.Sort(c)
	return fmt.Sprint(c)
}

func normalize(combos [][]int) map[string]bool {
	out := make(map[string]bool, len(combos))
	for _, c := range combos {
		out[key(c)] = true
	}
	return out
}

// bruteForce 는 후보마다 '몇 개 쓸지'를 정하는 참조 구현.
func bruteForce(candidates []int, target int) map[string]bool {
	out := map[string]bool{}
	n := len(candidates)
	var go_ func(i, remain int, cur []int)
	go_ = func(i, remain int, cur []int) {
		if remain == 0 {
			out[key(cur)] = true
			return
		}
		if i == n {
			return
		}
		c := candidates[i]
		for cnt := 0; cnt*c <= remain; cnt++ {
			next := append([]int(nil), cur...)
			for j := 0; j < cnt; j++ {
				next = append(next, c)
			}
			go_(i+1, remain-c*cnt, next)
		}
	}
	go_(0, target, nil)
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

// checkShape 는 반환값이 구조적으로 말이 되는지 본다. 문제가 있으면 사유를 돌려준다.
func checkShape(got [][]int, candidates []int, target int) string {
	allowed := map[int]bool{}
	for _, c := range candidates {
		allowed[c] = true
	}
	for _, combo := range got {
		if len(combo) == 0 {
			return "빈 조합이 들어있음"
		}
		sum := 0
		for _, x := range combo {
			if !allowed[x] {
				return fmt.Sprintf("candidates 에 없는 값이 섞임: %v", combo)
			}
			sum += x
		}
		if sum != target {
			return fmt.Sprintf("합이 target(%d)이 아님: %v -> %d", target, combo, sum)
		}
	}
	if len(normalize(got)) != len(got) {
		return fmt.Sprintf("중복된 조합이 있음 (%d개 중 유일한 건 %d개)", len(got), len(normalize(got)))
	}
	return ""
}

func TestCombinationSum(t *testing.T) {
	cases := []struct {
		candidates []int
		target     int
		want       [][]int
	}{
		{[]int{2, 3, 6, 7}, 7, [][]int{{2, 2, 3}, {7}}},
		{[]int{2, 3, 5}, 8, [][]int{{2, 2, 2, 2}, {2, 3, 3}, {3, 5}}},
		{[]int{2}, 1, [][]int{}},
		{[]int{5}, 5, [][]int{{5}}},
		{[]int{3, 5, 8}, 11, [][]int{{3, 3, 5}, {3, 8}}},
		{[]int{2, 4, 6, 8}, 8, [][]int{{2, 2, 2, 2}, {2, 2, 4}, {2, 6}, {4, 4}, {8}}},
		// 정렬돼 있지 않은 입력 — 제약조건은 정렬을 보장하지 않는다
		{[]int{8, 7, 4, 3}, 11, [][]int{{3, 4, 4}, {3, 8}, {4, 7}}},
		{[]int{7, 3, 2}, 18, [][]int{
			{2, 2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2, 3, 3},
			{2, 2, 2, 2, 3, 7}, {2, 2, 2, 3, 3, 3, 3}, {2, 2, 7, 7},
			{2, 3, 3, 3, 7}, {3, 3, 3, 3, 3, 3},
		}},
	}

	for _, c := range cases {
		got := combinationSum(append([]int(nil), c.candidates...), c.target)
		if why := checkShape(got, c.candidates, c.target); why != "" {
			t.Errorf("candidates=%v target=%d -> %s", c.candidates, c.target, why)
			continue
		}
		if !sameSet(normalize(got), normalize(c.want)) {
			t.Errorf("candidates=%v target=%d\n  기대: %v\n  실제: %v",
				c.candidates, c.target, c.want, got)
		}
	}
}

func TestCombinationSumRandom(t *testing.T) {
	rng := rand.New(rand.NewSource(39))
	for i := 0; i < 300; i++ {
		n := 1 + rng.Intn(5)
		perm := rng.Perm(13) // 0..12 -> +2 하면 2..14, 서로 다른 값
		candidates := make([]int, n)
		for j := 0; j < n; j++ {
			candidates[j] = perm[j] + 2
		}
		target := 1 + rng.Intn(25)

		got := combinationSum(append([]int(nil), candidates...), target)
		if why := checkShape(got, candidates, target); why != "" {
			t.Fatalf("랜덤 실패 candidates=%v target=%d -> %s", candidates, target, why)
		}
		if !sameSet(normalize(got), bruteForce(candidates, target)) {
			t.Fatalf("랜덤 케이스 불일치 candidates=%v target=%d\n  기대: %v\n  실제: %v",
				candidates, target, bruteForce(candidates, target), got)
		}
	}
}

// TestCombinationSumHeavy 는 조합을 만들어놓고 중복 제거하는 방식이면 끝나지 않는다.
func TestCombinationSumHeavy(t *testing.T) {
	candidates, target, wantCount := []int{2, 3, 4, 5}, 40, 145
	got := combinationSum(append([]int(nil), candidates...), target)
	if why := checkShape(got, candidates, target); why != "" {
		t.Fatalf("candidates=%v target=%d -> %s", candidates, target, why)
	}
	if n := len(normalize(got)); n != wantCount {
		t.Fatalf("candidates=%v target=%d -> 조합 %d개 (기대 %d개)", candidates, target, n, wantCount)
	}
}

func BenchmarkCombinationSum(b *testing.B) {
	for i := 0; i < b.N; i++ {
		combinationSum([]int{2, 3, 4, 5}, 40)
	}
}
