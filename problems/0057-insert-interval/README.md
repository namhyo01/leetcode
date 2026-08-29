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

## 내 접근 (2026-08-30, ✅ 스스로 해결)

- **유형:** 구현 / 배열 (Intervals)
- **핵심:** 입력이 **이미 정렬돼 있고 서로 겹치지 않으므로** 앞에서부터 한 번만 훑으면 된다.
  각 기존 구간을 새 구간과 비교해 세 부류로 나눈다.
  1. 새 구간보다 **완전히 앞** (`e < ns`) → 그대로 결과에 넣는다
  2. **겹침** → 새 구간에 흡수시킨다 (`ns = min(...)`, `ne = max(...)`)
  3. 새 구간보다 **완전히 뒤** (`s > ne`) → 이때 비로소 새 구간을 결과에 넣고, 기존 것도 넣는다
- **시간복잡도:** O(n) / **공간복잡도:** O(n) (출력)

### 처음 틀렸던 지점

`new_insert` 를 "한 번이라도 병합했는가" 로만 썼다가, **아무것과도 겹치지 않는 새 구간**이
중간이나 앞에 들어가야 할 때 넣을 곳을 못 찾고 맨 뒤로 밀렸다.

```
[[3,5],[8,10]] + [1,2]  ->  [[3,5],[8,10],[1,2]]    # 정렬이 깨진다
[[1,2],[5,6]] + [3,4]   ->  [[1,2],[5,6],[3,4]]
```

`if (new_insert && s > ne)` 가 아니라 `if (new_insert != 2 && ...)` 여야 했다.
플래그의 의미가 **"병합했는가"** 가 아니라 **"결과에 이미 넣었는가"** 이기 때문이다.
0/1/2 세 상태가 각각 "아직 안 넣음 / 병합 중 / 넣음" 을 뜻한다.

### 지문이 요구하는 것

> Insert `newInterval` into `intervals` such that `intervals` is **still sorted
> in ascending order by `starti`** and still does not have any overlapping intervals.

`still sorted` — **결과도 정렬돼 있어야 한다.** 제약조건의 `intervals is sorted` 는
입력 조건이고, 이건 출력 조건이다. 입력이 정렬돼 있으니 새 구간을 **제자리에** 끼우면
저절로 지켜지지만, 맨 뒤에 붙이면 깨진다.

### 겹침 판정은 대칭이다

두 구간 `[a,b]`, `[c,d]` 가 겹칠 조건은 `a <= d && c <= b` 하나다.
처음에 `s <= ns && e >= ns` 로 **한 방향만** 봐서 `[[2,4]] + [0,2]` 를 놓쳤다
(새 구간이 기존 구간의 시작을 품는 반대 경우).

`[1,3]` 과 `[3,5]` 는 **겹치는 것으로 본다.** 예제 2 에서 `[4,8]` 과 `[8,10]` 이
합쳐져 `[3,10]` 이 되는 게 근거다. 부등호를 `<` 로 쓰면 여기서 틀린다.

### 측정

n=10^4. 세 구현이 같은 답을 내는 것을 무작위 30000건으로 확인한 뒤 측정.

| 구현 | 전부 삼킴 | 병합 없음 |
| --- | --- | --- |
| 내 풀이 | 0.207ms | 0.393ms |
| 정석 한 번 훑기 | 0.212ms | 0.383ms |
| 정렬 후 병합 | 1.006ms | 0.668ms |

정석과 **차이가 없다.** 분기를 4개로 나눈 것과 3구간(before/merge/after)으로 나눈 것이
결국 같은 일을 한다. 정렬 방식은 `O(n log n)` 이라 3~5배 느리지만 제약 안에서는 통과한다.

### 다시 볼 것

- **LeetCode 통과가 정답 보증이 아니다.** 이 문제도 처음 제출 버전은 통과했는데
  로컬 하네스에서 5건 걸렸다 (엣지 케이스가 채점 세트에 없었다).
- 플래그를 만들 때 **이름이 뜻하는 바를 정확히 정한다.** `new_insert` 가
  "병합했는가" 인지 "넣었는가" 인지 헷갈린 게 버그의 원인이었다.
- `for (int i = 0; i < intervals.size(); ...)` 에서 `-Wsign-compare` 경고.
- 루프 안의 `vector<int> new_interval;` 은 쓰이지 않는다.
