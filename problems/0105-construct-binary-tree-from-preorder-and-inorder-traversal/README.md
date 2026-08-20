# 105. Construct Binary Tree from Preorder and Inorder Traversal

- Difficulty: **Medium**
- Link: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

## Problem

Given two integer arrays `preorder` and `inorder` where `preorder` is the preorder
traversal of a binary tree and `inorder` is the inorder traversal of the same tree,
construct and return *the binary tree*.

## Examples

```
Example 1:
Input:  preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]

        3
       / \
      9  20
        /  \
       15   7

Example 2:
Input:  preorder = [-1], inorder = [-1]
Output: [-1]
```

## Constraints

```
1 <= preorder.length <= 3000
inorder.length == preorder.length
-3000 <= preorder[i], inorder[i] <= 3000
preorder and inorder consist of unique values.
Each value of inorder also appears in preorder.
preorder is guaranteed to be the preorder traversal of the tree.
inorder is guaranteed to be the inorder traversal of the tree.
```

## Questions to sit with

- [ ] 두 순회의 정의를 정확히 쓸 수 있나? preorder 는 어떤 순서로, inorder 는 어떤 순서로 방문하나?
- [ ] `preorder` 의 **첫 원소**가 알려주는 것은 무엇인가?
- [ ] 어떤 값이 `inorder` 의 몇 번째 자리에 있는지 알면, 그 값에 대해 무엇을 알 수 있나?
- [ ] 두 순회 중 **하나만** 주어지면 트리를 복원할 수 있나? 왜 둘이 필요한가?
- [ ] 제약조건에 `unique values` 가 붙어 있다. 값이 중복되면 무엇이 무너지나?
- [ ] `inorder` 에서 값의 위치를 매번 처음부터 훑으면 전체 복잡도가 얼마가 되나?
- [ ] 내 풀이의 시간/공간 복잡도는?

## 내 접근 (풀면서 채우기)

<!--
- 처음 떠올린 방법:
- 막힌 지점:
- 최종 아이디어:
- 시간복잡도:      / 공간복잡도:
-->
