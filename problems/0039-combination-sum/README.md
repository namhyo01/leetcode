# 39. Combination Sum

- Difficulty: **Medium**
- Link: https://leetcode.com/problems/combination-sum/

## Problem

Given an array of **distinct** integers `candidates` and a target integer `target`,
return *a list of all **unique combinations** of* `candidates` *where the chosen
numbers sum to* `target`. You may return the combinations in **any order**.

The **same** number may be chosen from `candidates` an **unlimited number of times**.
Two combinations are unique if the frequency of at least one of the chosen numbers
is different.

The test cases are generated such that the number of unique combinations that sum
up to `target` is less than `150` combinations for the given input.

## Examples

```
Example 1:
Input:  candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
  2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
  7 is a candidate, and 7 = 7.
  These are the only two combinations.

Example 2:
Input:  candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]

Example 3:
Input:  candidates = [2], target = 1
Output: []
```

## Constraints

```
1 <= candidates.length <= 30
2 <= candidates[i] <= 40
All elements of candidates are distinct.
1 <= target <= 40
```

## Questions to sit with

- [ ] `[2,2,3]` 과 `[2,3,2]` 는 같은 조합인가, 다른 조합인가? 문제 문장 어디에 답이 있나?
- [ ] 같은 수를 무제한으로 쓸 수 있다는 조건이 탐색 구조를 어떻게 바꾸나?
- [ ] 중복 조합을 **만들어놓고 걸러내는** 대신, 애초에 안 만들 방법이 있나?
- [ ] 언제 탐색을 멈춰야 하나? 가지치기할 수 있는 지점은?
- [ ] 입력이 정렬돼 있다고 가정해도 되나? (예제 1은 정렬돼 있지만 제약조건은 뭐라고 하나)
- [ ] 내 풀이의 시간/공간 복잡도는?

## 내 접근 (풀면서 채우기)

<!--
- 처음 떠올린 방법:
- 막힌 지점:
- 최종 아이디어:
- 시간복잡도:      / 공간복잡도:
-->
