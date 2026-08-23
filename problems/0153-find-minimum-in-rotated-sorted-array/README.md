# 153. Find Minimum in Rotated Sorted Array

- Difficulty: **Medium**
- Link: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

## Problem

Suppose an array of length `n` sorted in ascending order is **rotated** between `1`
and `n` times. For example, the array `nums = [0,1,2,4,5,6,7]` might become:

- `[4,5,6,7,0,1,2]` if it was rotated `4` times.
- `[0,1,2,4,5,6,7]` if it was rotated `7` times.

Notice that **rotating** an array `[a[0], a[1], a[2], ..., a[n-1]]` 1 time results in
the array `[a[n-1], a[0], a[1], a[2], ..., a[n-2]]`.

Given the sorted rotated array `nums` of **unique** elements, return *the minimum
element of this array*.

You must write an algorithm that runs in `O(log n)` time.

## Examples

```
Example 1:
Input:  nums = [3,4,5,1,2]
Output: 1
Explanation: The original array was [1,2,3,4,5] rotated 3 times.

Example 2:
Input:  nums = [4,5,6,7,0,1,2]
Output: 0
Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.

Example 3:
Input:  nums = [11,13,15,17]
Output: 11
Explanation: The original array was [11,13,15,17] and it was rotated 4 times.
```

## Constraints

```
n == nums.length
1 <= n <= 5000
-5000 <= nums[i] <= 5000
All the integers of nums are unique.
nums is sorted and rotated between 1 and n times.
```

## Questions to sit with

- [ ] "rotated between 1 and n times" 라고 했다. `n` 번 회전하면 어떤 모양인가?
      **회전이 없는 것처럼 보이는 입력**도 들어올 수 있나?
- [ ] 배열을 종이에 그려보라. 최솟값을 기준으로 배열이 몇 개의 구간으로 나뉘는가?
      각 구간은 어떤 성질을 갖는가?
- [ ] 어떤 위치 하나를 집었을 때, 최솟값이 그 **왼쪽에 있는지 오른쪽에 있는지**
      판단할 방법이 있는가? 무엇과 비교해야 하는가?
- [ ] 그 비교 대상으로 **맨 왼쪽 값**을 쓰는 것과 **맨 오른쪽 값**을 쓰는 것 중
      어느 쪽이 더 다루기 쉬운가? 예제 3(`[11,13,15,17]`)에 둘 다 적용해 보라.
- [ ] 원소가 하나뿐이면? 두 개뿐이면?
- [ ] 내 풀이의 시간/공간 복잡도는?

## 내 접근 (풀면서 채우기)

<!--
- 처음 떠올린 방법:
- 막힌 지점:
- 최종 아이디어:
- 시간복잡도:      / 공간복잡도:
-->
