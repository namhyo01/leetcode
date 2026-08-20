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

## 내 접근 (2026-08-20, ✅ 스스로 해결)

- **유형:** Divide and Conquer (재귀 분할 + 트리 구성)
- **핵심 관찰 두 가지**
  1. `preorder` 의 첫 원소가 곧 **루트**다.
  2. 그 루트 값을 `inorder` 에서 찾으면, **왼쪽이 전부 왼쪽 서브트리 / 오른쪽이 전부 오른쪽 서브트리**다.
     즉 한 번의 위치 확인으로 문제가 두 개의 같은 모양 부분문제로 쪼개진다.
- **구현:** 두 배열의 구간을 인덱스 4개(`preStart, preEnd, inStart, inEnd`)로 들고 재귀.
  `leftTreeSize = inRootIndex - inStart` 로 왼쪽 크기를 구해 `preorder` 구간을 나눴다.
  - 왼쪽: `build(preStart+1, preStart+leftTreeSize, inStart, inRootIndex-1)`
  - 오른쪽: `build(preStart+leftTreeSize+1, preEnd, inRootIndex+1, inEnd)`
- **시간복잡도:** O(n^2) 최악 / O(n log n) 균형 — `inorder` 에서 루트를 매번 선형 탐색하기 때문
- **공간복잡도:** O(h) 재귀 스택 (최악 O(n)), 출력 제외

### `unique values` 조건이 왜 필요한가

값이 중복되면 `inorder` 에서 루트 위치를 특정할 수 없다. 위치가 갈리면 왼쪽/오른쪽 서브트리의
크기가 달라지므로 **트리가 유일하게 결정되지 않는다.** 값이 서로 다르기 때문에
preorder + inorder 두 개로 트리가 하나로 정해지고, 그래서 이 문제가 성립한다.
(테스트 하네스도 이 성질을 이용해서, 만든 트리를 다시 순회해 입력과 대조하는 것만으로
정답 검사를 끝낸다.)

### 벤치마크 — 맵이 항상 이기지는 않는다

n=3000, 세 구현이 같은 트리를 만드는 것을 확인한 뒤 측정:

| 구현 | 치우친 트리 | 균형 트리 | allocs |
|---|---|---|---|
| 선형 탐색 (내 풀이) | 1,587µs | **90µs** | 3,002 |
| 위치를 맵에 미리 저장 | **138µs** | 150µs | 3,011 |
| 맵 + preorder 커서 하나 | **129µs** | 142µs | 3,011 |

- **치우친 트리에서는 맵이 11.5배 빠르다.** 구간이 줄지 않아 선형 탐색이 매번 n에 가깝다.
- **균형 트리에서는 오히려 내 풀이가 1.7배 빠르다.** 구간이 절반씩 줄어 탐색이 짧고,
  맵을 만드는 비용(해시 + 195KB 할당)을 회수하지 못한다.

**결론: 코딩테스트에서는 맵을 쓴다.** 채점 입력에 최악 케이스가 반드시 들어있기 때문이다.
평균적으로 손해라는 것도 알고 쓰는 것과 모르고 쓰는 것은 다르다.

### 다시 볼 것

- 인덱스 4개를 들고 다니면 산술 실수가 나기 쉽다. `preorder` 를 **커서 하나로 소비**하면
  인자가 `(lo, hi)` 둘로 줄어 실수 여지가 준다 (성능 차이는 미미).
- `inRootIndex := -1` 로 시작해 못 찾으면 -1 인 채로 진행한다. 제약조건상 항상 찾지만,
  깨진 입력이 오면 조용히 잘못된 트리를 만든다.
- `preStart > preEnd || inStart > inEnd` 는 둘이 항상 같이 성립하므로 하나만 봐도 된다.
