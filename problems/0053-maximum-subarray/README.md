# 53. Maximum Subarray

- Difficulty: **Medium**
- Link: https://leetcode.com/problems/maximum-subarray/

## Problem

Given an integer array `nums`, find the **subarray** with the largest sum,
and return *its sum*.

> A **subarray** is a contiguous **non-empty** sequence of elements within an array.

## Examples

```
Example 1:
Input:  nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.

Example 2:
Input:  nums = [1]
Output: 1
Explanation: The subarray [1] has the largest sum 1.

Example 3:
Input:  nums = [5,4,-1,7,8]
Output: 23
Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.
```

## Constraints

```
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
```

## Questions to sit with

- [ ] **subarray** 와 subsequence 의 차이는? 이 문제는 어느 쪽인가?
      (정의가 지문에 인용문으로 따로 적혀 있는 데는 이유가 있다)
- [ ] 가능한 부분배열은 전부 몇 개인가? 그걸 다 확인하면 `n = 10^5` 에서 통과하나?
- [ ] 배열이 **전부 음수**면 답은 무엇인가? 0 이 될 수 있나?
- [ ] 앞에서부터 한 번만 훑는다면, 각 위치에서 **무엇을 들고 있어야** 하는가?
- [ ] 합이 `int` 범위를 넘을 수 있나? 제약조건으로 최댓값을 계산해 보라.
- [ ] 내 풀이의 시간/공간 복잡도는?

## 내 접근 (풀면서 채우기)

<!--
- 처음 떠올린 방법:
- 막힌 지점:
- 최종 아이디어:
- 시간복잡도:      / 공간복잡도:
-->
