# 128. Longest Consecutive Sequence

- Difficulty: **Medium**
- Link: https://leetcode.com/problems/longest-consecutive-sequence/

## Problem

Given an unsorted array of integers `nums`, return *the length of the longest
consecutive elements sequence.*

You must write an algorithm that runs in `O(n)` time.

## Examples

```
Example 1:
Input:  nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4].
             Therefore its length is 4.

Example 2:
Input:  nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
```

## Constraints

```
0 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
```

> 배열이 **비어 있을 수 있다.** 그리고 예제 2 를 보면 `0` 이 두 번 나온다 —
> **중복이 들어온다.**

## Questions to sit with

- [ ] "consecutive" 가 뜻하는 게 정확히 무엇인가? 값이 연속이라는 것인가,
      배열에서 위치가 붙어 있다는 것인가? 예제 1 을 보면 답이 나온다.
- [ ] 지문이 `O(n)` 을 요구한다. 정렬하면 얼마인가? 그게 왜 요구를 어기는가?
- [ ] 어떤 값 `x` 가 있을 때, `x` 로 시작하는 수열의 길이를 재려면 무엇을 반복해서 물어봐야 하는가?
      그 질문에 **상수 시간**으로 답하려면 무엇이 필요한가?
- [ ] 모든 원소에서 수열을 따라가면 같은 수열을 몇 번이나 다시 걷게 되는가?
      `[1,2,3,...,n]` 을 섞어놓은 배열이라면?
- [ ] 그러면 **어떤 원소에서만** 걷기 시작해야 하는가? 그 원소를 어떻게 알아보는가?
- [ ] 중복이 들어와도 괜찮은가? 빈 배열은?
- [ ] 내 풀이의 시간/공간 복잡도는?

## 내 접근 (풀면서 채우기)

<!--
- 처음 떠올린 방법:
- 막힌 지점:
- 최종 아이디어:
- 시간복잡도:      / 공간복잡도:
-->
