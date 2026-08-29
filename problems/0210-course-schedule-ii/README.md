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

## 내 접근 (2026-08-30, ✅ 스스로 해결)

- **유형:** 위상정렬 (Topological Sort — Kahn's algorithm)
- **핵심:** [207](../0207-course-schedule/) 에서 이미 순서를 만들고 있었다.
  거기서는 **몇 개 걷어냈는지만 세고 버렸는데**, 여기서는 **걷어낸 순서를 그대로 기록**하면 된다.

```cpp
while (!q.empty()) {
    int course = q.front(); q.pop();
    res.push_back(course);          // ← 207 과 다른 건 이 한 줄뿐
    cnt++;
    for (int i : graph[course]) {
        indegree[i]--;
        if (indegree[i] == 0) q.push(i);
    }
}
return numCourses == cnt ? res : vector<int>{};
```

- **시간복잡도:** O(V + E) / **공간복잡도:** O(V + E)

### 왜 큐에서 꺼낸 순서가 곧 답인가

큐에 들어간다는 건 **그 과목의 선수과목이 전부 이미 처리됐다**는 뜻이다.
즉 큐에서 꺼내는 순간 그 과목은 "지금 들어도 되는" 상태이고,
꺼낸 순서대로 나열하면 모든 선수과목 조건이 저절로 만족된다.

정답이 여러 개인 이유도 여기서 나온다. 큐에 동시에 여러 개가 들어 있으면
**어느 걸 먼저 꺼내도 상관없다.** 그래서 `queue` 대신 `stack` 을 써도,
`priority_queue` 로 사전순 최소를 뽑아도 전부 유효한 답이다.
(사전순으로 가장 빠른 답을 요구하는 변형 문제가 실제로 있다.)

### 207 과의 관계

| | 207. Course Schedule | **210. Course Schedule II** |
| --- | --- | --- |
| 묻는 것 | 완주 **가능한가** | 완주 **순서** |
| 반환 | `bool` | `vector<int>` (불가능하면 빈 배열) |
| 코드 차이 | — | `res.push_back(course)` 한 줄 |
| 제약 | 간선 ≤ 5,000 | 간선 ≤ `n(n-1)` ≈ **400만** |

**제약이 크게 다르다.** 210 은 간선이 훨씬 많이 올 수 있어서 인접 리스트를 만드는
비용 자체가 지배적이 된다.

DFS 색칠로도 풀 수 있지만 이 문제에서는 진입차수 쪽이 확실히 유리하다.
DFS 는 **후위 순회 결과를 뒤집어야** 답이 나오는데, 그 한 단계를 빠뜨리기 쉽다.

### 측정 — 순서를 기록하는 비용은 사실상 0

n=2000, 간선 50만. 세 구현이 같은 결과를 내는 것을 무작위 20000건으로 확인한 뒤 측정.

| 구현 | 시간 |
| --- | --- |
| 순서 쌓기 (내 풀이) | 4.336ms |
| 개수만 세기 (207 방식) | 4.394ms |
| `res.reserve(n)` 추가 | 4.294ms |

**차이가 없다.** `push_back` 은 `O(1)` 상환이고 총 n번뿐인데, 간선 50만 개를 훑는
비용이 압도적이라 묻힌다. `reserve` 도 의미가 없다.

### 다시 볼 것

- `cnt` 와 `res.size()` 가 항상 같다. 하나는 없어도 된다 —
  `return (int)res.size() == numCourses ? res : vector<int>{};`
- 큐에서 꺼내는 순서를 바꾸면 다른 유효한 답이 나온다.
  "사전순으로 가장 빠른 순서" 를 요구하면 `priority_queue` 로 바꾸면 된다.
