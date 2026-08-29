# 57. Insert Interval

- Difficulty: **Medium**
- Link: https://leetcode.com/problems/insert-interval/

## Problem

You are given an array of **non-overlapping** intervals `intervals` where
`intervals[i] = [starti, endi]` represent the start and the end of the `i`th interval
and `intervals` is **sorted in ascending order** by `starti`. You are also given an
interval `newInterval = [start, end]` that represents the start and end of another
interval.

Insert `newInterval` into `intervals` such that `intervals` is still sorted in
ascending order by `starti` and `intervals` still does not have any overlapping
intervals (merge overlapping intervals if necessary).

Return `intervals` *after the insertion*.

**Note** that you don't need to modify `intervals` in-place. You can make a new array
and return it.

## Examples

```
Example 1:
Input:  intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:
Input:  intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
```

## Constraints

```
0 <= intervals.length <= 10^4
intervals[i].length == 2
0 <= starti <= endi <= 10^5
intervals is sorted by starti in ascending order.
newInterval.length == 2
0 <= start <= end <= 10^5
```

## Questions to sit with

- [ ] 입력이 **이미 정렬돼 있고 서로 겹치지 않는다**. 이 두 조건이 각각 무엇을 보장하는가?
      그걸 활용하지 않으면 무엇을 다시 해야 하는가?
- [ ] 기존 구간 하나와 새 구간을 놓고 볼 때, 가능한 위치 관계는 몇 가지인가?
      그림으로 다 그려보라. (완전히 왼쪽 / 완전히 오른쪽 / 겹침)
- [ ] 두 구간 `[a,b]`, `[c,d]` 가 **겹친다**는 걸 부등식 하나로 어떻게 쓰는가?
      `[1,3]` 과 `[3,5]` 는 겹치는가? (예제를 보면 답이 나온다)
- [ ] 여러 구간이 한꺼번에 병합될 때, 결과 구간의 시작과 끝은 각각 무엇인가?
- [ ] `intervals` 가 **비어 있을 수 있다.** 그때는?
- [ ] 새 구간이 모든 기존 구간보다 앞에 올 때는? 뒤에 올 때는?
- [ ] 내 풀이의 시간/공간 복잡도는?

## 내 접근 (풀면서 채우기)

<!--
- 처음 떠올린 방법:
- 막힌 지점:
- 최종 아이디어:
- 시간복잡도:      / 공간복잡도:
-->
