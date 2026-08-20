package main

import (
	"math/rand"
	"slices"
	"testing"
)

// ── 테스트 전용 헬퍼 (풀이와 독립적으로 다시 구현) ──────────────────

func preorderOf(n *TreeNode, out *[]int) {
	if n == nil {
		return
	}
	*out = append(*out, n.Val)
	preorderOf(n.Left, out)
	preorderOf(n.Right, out)
}

func inorderOf(n *TreeNode, out *[]int) {
	if n == nil {
		return
	}
	inorderOf(n.Left, out)
	*out = append(*out, n.Val)
	inorderOf(n.Right, out)
}

func sameTree(a, b *TreeNode) bool {
	if a == nil || b == nil {
		return a == nil && b == nil
	}
	return a.Val == b.Val && sameTree(a.Left, b.Left) && sameTree(a.Right, b.Right)
}

// countNodes 는 사이클이나 노드 공유가 있으면 무한히 돌지 않도록 상한을 둔다.
func countNodes(n *TreeNode, limit int) int {
	if n == nil || limit <= 0 {
		return 0
	}
	return 1 + countNodes(n.Left, limit-1) + countNodes(n.Right, limit-1)
}

// randomTree 는 노드 n개짜리 임의 모양의 이진 트리를 만든다. 값은 서로 다르다.
func randomTree(rng *rand.Rand, values []int) *TreeNode {
	if len(values) == 0 {
		return nil
	}
	k := rng.Intn(len(values)) // 왼쪽 서브트리에 들어갈 개수
	root := &TreeNode{Val: values[k]}
	root.Left = randomTree(rng, values[:k])
	root.Right = randomTree(rng, values[k+1:])
	return root
}

// ── 검사 본체 ────────────────────────────────────────────────────

// checkBuild 는 만들어진 트리가 두 순회를 그대로 재현하는지 본다.
// 값이 서로 다르면 preorder + inorder 는 트리를 유일하게 결정하므로,
// 이 왕복 검사를 통과하면 트리가 정확하다는 뜻이다.
func checkBuild(t *testing.T, got *TreeNode, pre, ino []int) bool {
	t.Helper()

	if n := countNodes(got, len(pre)+10); n != len(pre) {
		t.Errorf("pre=%v ino=%v\n  노드 수가 %d개 (기대 %d개) — 트리: %s", pre, ino, n, len(pre), dump(got))
		return false
	}
	var gotPre, gotIn []int
	preorderOf(got, &gotPre)
	inorderOf(got, &gotIn)
	if !slices.Equal(gotPre, pre) {
		t.Errorf("pre=%v ino=%v\n  만든 트리의 preorder 가 %v — 입력과 다름\n  트리: %s", pre, ino, gotPre, dump(got))
		return false
	}
	if !slices.Equal(gotIn, ino) {
		t.Errorf("pre=%v ino=%v\n  만든 트리의 inorder 가 %v — 입력과 다름\n  트리: %s", pre, ino, gotIn, dump(got))
		return false
	}
	return true
}

func TestBuildTree(t *testing.T) {
	cases := []struct {
		pre, ino []int
		want     string // LeetCode 출력 형식
	}{
		{[]int{3, 9, 20, 15, 7}, []int{9, 3, 15, 20, 7}, "[3,9,20,null,null,15,7]"},
		{[]int{-1}, []int{-1}, "[-1]"},
		{[]int{1, 2}, []int{2, 1}, "[1,2]"},
		{[]int{1, 2}, []int{1, 2}, "[1,null,2]"},
		{[]int{1, 2, 3}, []int{3, 2, 1}, "[1,2,null,3]"},      // 왼쪽으로만 치우침
		{[]int{1, 2, 3}, []int{1, 2, 3}, "[1,null,2,null,3]"}, // 오른쪽으로만 치우침
		{[]int{1, 2, 4, 5, 3, 6, 7}, []int{4, 2, 5, 1, 6, 3, 7}, "[1,2,3,4,5,6,7]"},
		{[]int{5, 3, 2, 4, 8, 7, 9}, []int{2, 3, 4, 5, 7, 8, 9}, "[5,3,8,2,4,7,9]"},
	}

	for _, c := range cases {
		got := buildTree(slices.Clone(c.pre), slices.Clone(c.ino))
		if !checkBuild(t, got, c.pre, c.ino) {
			continue
		}
		if d := dump(got); d != c.want {
			t.Errorf("pre=%v ino=%v\n  기대: %s\n  실제: %s", c.pre, c.ino, c.want, d)
		}
	}
}

// TestBuildTreeRandom 은 임의의 트리를 만들어 두 순회를 뽑고,
// 그것으로 복원한 트리가 원본과 같은지 본다.
func TestBuildTreeRandom(t *testing.T) {
	rng := rand.New(rand.NewSource(105))
	for i := 0; i < 500; i++ {
		n := 1 + rng.Intn(12)
		values := make([]int, n)
		for j := range values {
			values[j] = j - n/2 // 서로 다른 값, 음수도 섞이게
		}
		want := randomTree(rng, values)

		var pre, ino []int
		preorderOf(want, &pre)
		inorderOf(want, &ino)

		got := buildTree(slices.Clone(pre), slices.Clone(ino))
		if !checkBuild(t, got, pre, ino) {
			t.FailNow()
		}
		if !sameTree(got, want) {
			t.Fatalf("pre=%v ino=%v\n  기대 트리: %s\n  실제 트리: %s", pre, ino, dump(want), dump(got))
		}
	}
}

// TestBuildTreeSkewed 는 최대 입력 크기의 한쪽으로 완전히 치우친 트리를 다룬다.
// 재귀 깊이가 3000까지 내려가고, inorder 를 매번 처음부터 훑는 풀이가 가장 불리한 모양이다.
func TestBuildTreeSkewed(t *testing.T) {
	const n = 3000
	for _, tc := range []struct {
		name string
		left bool
	}{{"왼쪽으로 치우침", true}, {"오른쪽으로 치우침", false}} {
		pre := make([]int, n)
		ino := make([]int, n)
		for i := 0; i < n; i++ {
			pre[i] = i - n/2
		}
		copy(ino, pre)
		if tc.left {
			slices.Reverse(ino) // preorder 오름차순 + inorder 내림차순 = 왼쪽 사슬
		}
		got := buildTree(slices.Clone(pre), slices.Clone(ino))
		if !checkBuild(t, got, pre, ino) {
			t.Fatalf("%s 실패", tc.name)
		}
	}
}

func BenchmarkBuildTreeSkewed(b *testing.B) {
	const n = 3000
	pre := make([]int, n)
	for i := range pre {
		pre[i] = i
	}
	ino := slices.Clone(pre)
	slices.Reverse(ino)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		buildTree(slices.Clone(pre), slices.Clone(ino))
	}
}

func BenchmarkBuildTreeBalanced(b *testing.B) {
	rng := rand.New(rand.NewSource(1))
	values := make([]int, 3000)
	for i := range values {
		values[i] = i
	}
	root := randomTree(rng, values)
	var pre, ino []int
	preorderOf(root, &pre)
	inorderOf(root, &ino)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		buildTree(slices.Clone(pre), slices.Clone(ino))
	}
}
