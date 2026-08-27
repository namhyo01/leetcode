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

## 내 접근 (2026-08-27, ✅ 스스로 해결)

- **유형:** 위상정렬 (Topological Sort — Kahn's algorithm)
- **핵심 번역:** "모든 과목을 들을 수 있는가" = **"이 방향그래프에 사이클이 없는가"**
- **간선 방향:** `[a, b]` 는 "a 를 들으려면 b 를 먼저" 이므로 `b → a` 로 놓는다.
  `graph[p[1]].push_back(p[0])` — 선수과목에서 후속과목으로 향한다.
- **아이디어:** 진입차수가 0 인 과목 = **지금 당장 들을 수 있는 과목**.
  그걸 듣고 나면 그 과목을 선수로 요구하던 과목들의 진입차수가 하나씩 줄어든다.
  더 이상 들을 게 없을 때까지 반복하고, **들은 과목 수가 전체와 같은지** 본다.

```cpp
int cnt = 0;
while (!q.empty()) {
    int course = q.front(); q.pop(); cnt++;
    for (int next : graph[course])
        if (--indegree[next] == 0) q.push(next);
}
return cnt == numCourses;
```

- **시간복잡도:** O(V + E) / **공간복잡도:** O(V + E)

### `cnt == numCourses` 가 왜 사이클 판정이 되는가

사이클에 속한 과목은 **진입차수가 절대 0 이 되지 않는다.** 서로가 서로를 요구하므로
아무리 걷어내도 남는다. 그래서 큐가 비었는데 아직 안 센 과목이 있다면 그게 곧 사이클이다.

"사이클을 찾는다" 가 아니라 **"끝까지 걷어낼 수 있는가"** 로 뒤집은 게 이 알고리즘의 요령이다.

### 색칠 DFS 와의 대비 — 이 문제의 진짜 함정

DFS 로 풀면 방문 상태를 **세 가지**로 나눠야 한다.

| 상태 | 의미 |
| --- | --- |
| 0 | 아직 안 봄 |
| 1 | **지금 따라가는 중** (재귀 스택에 올라와 있음) |
| 2 | 다 봤고 사이클 없었음 |

`1` 을 만나면 사이클이지만 `2` 를 만나면 그냥 건너뛰면 된다.
이 둘을 `visited` 하나로 합치면 **다이아몬드 모양**(`0→1, 0→2, 1→2`)에서
사이클이 아닌데 사이클로 오판한다. 반대로 `2` 를 기억하지 않으면 같은 정점을
여러 번 다시 타서 경로 수만큼 폭발한다.

진입차수 방식은 이 구분 자체가 필요 없다. 상태를 "숫자 하나" 로 관리하기 때문.

### 측정 — 세 형태가 사실상 같다

같은 답을 내는 것을 무작위 20000건으로 확인한 뒤 측정.

| 그래프 | 큐 (내 풀이) | 색칠 DFS | 벡터 스택 |
| --- | --- | --- | --- |
| n=2000, 간선 5000 (무작위 DAG) | 0.148ms | 0.135ms | 0.141ms |
| n=2000 일자 사슬 (깊이 2000) | 0.045ms | 0.047ms | 0.048ms |

**차이가 없다.** 셋 다 O(V+E) 이고 상수도 비슷하다.

> 처음 쟀을 때는 색칠 DFS 가 6배 빠르게 나왔는데, **측정이 틀렸다.**
> DFS 쪽만 전역 벡터를 `assign` 으로 재사용해서 반복 측정에서 할당 비용이 빠졌던 것.
> 양쪽 다 호출마다 새로 만들게 고치니 차이가 사라졌다.

그래도 갈리는 지점이 하나 있다. **진입차수 방식은 재귀를 쓰지 않는다.**
깊이 2000 짜리 사슬에서 DFS 는 2000 단계를 내려간다. 이 문제는 제약이 작아 괜찮지만,
정점이 10^5 급이면 스택이 터진다. **반복문으로 도는 쪽이 깊이에 안전하다.**

### 다시 볼 것

- 간선 방향을 뒤집어 놓으면 답이 그럴듯하게 틀린다. `[a, b]` 에서 누가 먼저인지
  한 번 더 확인하는 습관.
- `for (const auto& p : prerequisites)` 줄의 들여쓰기가 어긋나 있다.
