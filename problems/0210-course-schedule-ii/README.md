# 210. Course Schedule II

- Difficulty: **Medium**
- Link: https://leetcode.com/problems/course-schedule-ii/

## Problem

There are a total of `numCourses` courses you have to take, labeled from `0` to
`numCourses - 1`. You are given an array `prerequisites` where
`prerequisites[i] = [ai, bi]` indicates that you **must** take course `bi` first
if you want to take course `ai`.

- For example, the pair `[0, 1]` indicates that to take course `0` you have to
  first take course `1`.

Return *the ordering of courses you should take to finish all courses*.
**If there are many valid answers, return any of them.**
If it is impossible to finish all courses, return **an empty array**.

## Examples

```
Example 1:
Input:  numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should
  have finished course 0. So the correct course order is [0,1].

Example 2:
Input:  numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should
  have finished both courses 1 and 2. Both courses 1 and 2 should be taken after
  you finished course 0. So one correct course order is [0,1,2,3].
  Another correct ordering is [0,2,1,3].

Example 3:
Input:  numCourses = 1, prerequisites = []
Output: [0]
```

## Constraints

```
1 <= numCourses <= 2000
0 <= prerequisites.length <= numCourses * (numCourses - 1)
prerequisites[i].length == 2
0 <= ai, bi < numCourses
ai != bi
All the pairs [ai, bi] are distinct.
```

> 207 과 제약이 다르다. 간선이 최대 `numCourses * (numCourses - 1)` 개까지 온다
> (n=2000 이면 약 400만). 그리고 `ai != bi` 라 자기 자신을 선수과목으로 두는 경우는 없다.

## Questions to sit with

- [ ] 207 은 "가능한가?" 를 물었고 이 문제는 "순서를 내놔라" 다.
      207 을 풀던 과정에서 **이미 만들어지고 있던 것**이 무엇인가?
- [ ] 정답이 여러 개일 수 있다. 그래도 상관없는 이유는?
      내 답이 맞는지 스스로 확인하려면 무엇을 검사해야 하는가?
- [ ] 불가능할 때 무엇을 반환해야 하는가? 그걸 어떻게 알아채는가?
- [ ] 간선이 400만 개까지 온다. 인접 리스트를 만드는 비용은 얼마인가?
- [ ] 내 풀이의 시간/공간 복잡도는?

## 내 접근 (풀면서 채우기)

<!--
- 처음 떠올린 방법:
- 막힌 지점:
- 최종 아이디어:
- 시간복잡도:      / 공간복잡도:
-->
