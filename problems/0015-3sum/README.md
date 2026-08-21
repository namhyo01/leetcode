# 15. 3Sum

- Difficulty: **Medium**
- Link: https://leetcode.com/problems/3sum/

> **재풀이 문제.** 2026-08-18 에 스스로 풀지 못하고 해설을 봤다.
> 이전 시도와 그때 적은 회고는 `git log -- problems/0015-3sum/` 에 남아 있으니
> **다 풀기 전에는 열어보지 말 것.**

## Problem

Given an integer array `nums`, return all the triplets `[nums[i], nums[j], nums[k]]`
such that `i != j`, `i != k`, and `j != k`, and `nums[i] + nums[j] + nums[k] == 0`.

Notice that the solution set must not contain **duplicate triplets**.

## Examples

```
Example 1:
Input:  nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation:
  nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
  nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
  nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
  The distinct triplets are [-1,0,1] and [-1,-1,2].
  Notice that the order of the output and the order of the triplets does not matter.

Example 2:
Input:  nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.

Example 3:
Input:  nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
```

## Constraints

```
3 <= nums.length <= 3000
-10^5 <= nums[i] <= 10^5
```

## Questions to sit with

- [ ] 세 수를 전부 훑으면 복잡도가 얼마인가? `n = 3000` 에서 통과하나?
- [ ] 세 수 중 **하나를 고정**하면 남는 문제는 무엇이 되나? 그 문제는 얼마에 풀리나?
- [ ] 출력의 순서가 상관없다고 했다. 이 조건에서 공짜로 얻을 수 있는 게 있나?
- [ ] 중복 삼중항을 **만들어놓고 걸러내는** 대신, 애초에 안 만들 방법이 있나?
- [ ] 중복이 생길 수 있는 자리는 몇 군데인가?
- [ ] 내 풀이의 시간/공간 복잡도는?

## 내 접근 (풀면서 채우기)

<!--
- 지난번에 막힌 지점을 기억하는가:
- 이번엔 어디까지 스스로 갔는가:
- 최종 아이디어:
- 시간복잡도:      / 공간복잡도:
-->
