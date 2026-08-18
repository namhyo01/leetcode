package main

import (
	"math/rand"
	"testing"
)

func hoursNeeded(piles []int, k int) int {
	total := 0
	for _, p := range piles {
		total += (p + k - 1) / k // ceil(p / k)
	}
	return total
}

func bruteForce(piles []int, h int) int {
	max := 0
	for _, p := range piles {
		if p > max {
			max = p
		}
	}
	for k := 1; k <= max; k++ {
		if hoursNeeded(piles, k) <= h {
			return k
		}
	}
	return max
}

func TestMinEatingSpeed(t *testing.T) {
	cases := []struct {
		piles []int
		h     int
		want  int
	}{
		{[]int{3, 6, 7, 11}, 8, 4},
		{[]int{30, 11, 23, 4, 20}, 5, 30},
		{[]int{30, 11, 23, 4, 20}, 6, 23},
		{[]int{1}, 1, 1},
		{[]int{1000000000}, 2, 500000000},
		{[]int{312884470}, 968709470, 1},
		{[]int{332484035, 524908576, 855865114, 632922376, 222257295}, 823855818, 4},
		{[]int{1, 1, 1, 1}, 4, 1},
		{[]int{5, 5, 5}, 3, 5},
		{[]int{1, 2, 3, 4, 5}, 15, 1},
	}

	for _, c := range cases {
		got := minEatingSpeed(append([]int(nil), c.piles...), c.h)
		if got != c.want {
			t.Errorf("piles=%v h=%d\n  기대: %d\n  실제: %d", c.piles, c.h, c.want, got)
		}
	}
}

func TestMinEatingSpeedRandom(t *testing.T) {
	rng := rand.New(rand.NewSource(875))
	for i := 0; i < 500; i++ {
		n := 1 + rng.Intn(6)
		piles := make([]int, n)
		for j := range piles {
			piles[j] = 1 + rng.Intn(25)
		}
		h := n + rng.Intn(n*7+1)
		got := minEatingSpeed(append([]int(nil), piles...), h)
		want := bruteForce(piles, h)
		if got != want {
			t.Fatalf("랜덤 케이스 실패 piles=%v h=%d\n  기대: %d\n  실제: %d", piles, h, want, got)
		}
	}
}

// TestMinEatingSpeedMinimality 는 큰 값에서 답이 유효하고 최소인지 직접 검증한다.
func TestMinEatingSpeedMinimality(t *testing.T) {
	rng := rand.New(rand.NewSource(1))
	for i := 0; i < 200; i++ {
		n := 1 + rng.Intn(40)
		piles := make([]int, n)
		for j := range piles {
			piles[j] = 1 + rng.Intn(1000000000)
		}
		h := n + rng.Intn(n*3+1)
		k := minEatingSpeed(append([]int(nil), piles...), h)
		if k < 1 {
			t.Fatalf("k가 1 미만: n=%d h=%d -> %d", n, h, k)
		}
		if hoursNeeded(piles, k) > h {
			t.Fatalf("k=%d로는 h=%d시간 안에 못 먹음 (n=%d)", k, h, n)
		}
		if k > 1 && hoursNeeded(piles, k-1) <= h {
			t.Fatalf("k=%d가 최소가 아님. k-1로도 가능 (n=%d h=%d)", k, n, h)
		}
	}
}

func BenchmarkMinEatingSpeed(b *testing.B) {
	rng := rand.New(rand.NewSource(2))
	piles := make([]int, 10000)
	for i := range piles {
		piles[i] = 1 + rng.Intn(1000000000)
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		minEatingSpeed(piles, 20000)
	}
}
