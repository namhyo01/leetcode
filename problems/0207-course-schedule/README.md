# 207. Course Schedule

- Difficulty: **Medium**
- Link: https://leetcode.com/problems/course-schedule/

## Problem

There are a total of `numCourses` courses you have to take, labeled from `0` to
`numCourses - 1`. You are given an array `prerequisites` where
`prerequisites[i] = [ai, bi]` indicates that you **must** take course `bi` first
if you want to take course `ai`.

- For example, the pair `[0, 1]` indicates that to take course `0` you have to
  first take course `1`.

Return `true` if you can finish all courses. Otherwise, return `false`.

## Examples

```
Example 1:
Input:  numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take.
  To take course 1 you should have finished course 0. So it is possible.

Example 2:
Input:  numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take.
  To take course 1 you should have finished course 0, and to take course 0 you
  should also have finished course 1. So it is impossible.
```

## Constraints

```
1 <= numCourses <= 2000
0 <= prerequisites.length <= 5000
prerequisites[i].length == 2
0 <= ai, bi < numCourses
All the pairs prerequisites[i] are unique.
```

## Questions to sit with

- [ ] 예제 2 가 왜 불가능한지 한 문장으로 설명해 보라. 그 상황에 이름을 붙인다면?
- [ ] `prerequisites` 를 그림으로 그리면 무엇이 되는가? 화살표를 어느 쪽으로 그릴 것인가?
      (`[a, b]` 는 "a 를 들으려면 b 를 먼저" 다 — `a → b` 인가 `b → a` 인가?)
- [ ] "모든 과목을 들을 수 있다" 는 그 그림의 어떤 성질과 같은 말인가?
- [ ] 지금 **당장 들을 수 있는** 과목은 어떤 과목인가? 그걸 듣고 나면 무엇이 달라지는가?
- [ ] 어떤 과목에서 출발해 따라가다가 **출발점으로 돌아왔다면** 무슨 뜻인가?
      그런데 "이미 확인해 본 과목" 과 "지금 따라가는 중인 과목" 을 구분해야 하는 이유는?
- [ ] 간선이 하나도 없으면? 자기 자신이 선수과목이면(`[5, 5]`)?
- [ ] 내 풀이의 시간/공간 복잡도는?
