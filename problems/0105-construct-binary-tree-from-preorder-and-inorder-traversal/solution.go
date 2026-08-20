// 105. Construct Binary Tree from Preorder and Inorder Traversal
// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
package main

import (
	"fmt"
	"strings"
)

// TreeNode 는 LeetCode 가 주는 이진 트리 노드 정의 그대로다.
type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

// buildTree 는 preorder / inorder 순회 결과로부터 원래의 이진 트리를 복원한다.
func buildTree(preorder []int, inorder []int) *TreeNode {
	// TODO: 여기에 풀이를 작성하세요.
	var build func(preStart, preEnd, inStart, inEnd int) *TreeNode
	build = func(preStart, preEnd, inStart, inEnd int) *TreeNode {
		if preStart > preEnd || inStart > inEnd {
			return nil
		}

		rootVal := preorder[preStart]
		root := &TreeNode{Val: rootVal}

		inRootIndex := -1
		for i := inStart; i <= inEnd; i++ {
			if inorder[i] == rootVal {
				inRootIndex = i
				break
			}
		}

		leftTreeSize := inRootIndex - inStart

		root.Left = build(preStart+1, preStart+leftTreeSize, inStart, inRootIndex-1)
		root.Right = build(preStart+leftTreeSize+1, preEnd, inRootIndex+1, inEnd)

		return root
	}

	return build(0, len(preorder)-1, 0, len(inorder)-1)
}

// ── 아래는 놀이터용 출력 헬퍼. 풀이와 무관하니 신경 쓰지 않아도 된다. ──

// dump 는 트리를 LeetCode 출력 형식(레벨 순회, 뒤쪽 null 생략)으로 찍는다.
func dump(root *TreeNode) string {
	if root == nil {
		return "[]"
	}
	var out []string
	queue := []*TreeNode{root}
	for len(queue) > 0 {
		n := queue[0]
		queue = queue[1:]
		if n == nil {
			out = append(out, "null")
			continue
		}
		out = append(out, fmt.Sprint(n.Val))
		queue = append(queue, n.Left, n.Right)
	}
	for len(out) > 0 && out[len(out)-1] == "null" {
		out = out[:len(out)-1]
	}
	return "[" + strings.Join(out, ",") + "]"
}

// draw 는 트리를 옆으로 눕혀서 그린다. 구조를 눈으로 확인할 때 쓴다.
func draw(n *TreeNode, indent string, side string) string {
	if n == nil {
		return ""
	}
	s := draw(n.Right, indent+"    ", "/")
	s += fmt.Sprintf("%s%s%d\n", indent, side, n.Val)
	s += draw(n.Left, indent+"    ", "\\")
	return s
}

// main 은 손으로 굴려보는 놀이터.
// `go run ./problems/0105-construct-binary-tree-from-preorder-and-inorder-traversal/`
func main() {
	root := buildTree([]int{3, 9, 20, 15, 7}, []int{9, 3, 15, 20, 7})
	fmt.Println(dump(root)) // [3,9,20,null,null,15,7]
	fmt.Print(draw(root, "", ""))
}
