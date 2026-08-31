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

## 내 접근 (2026-08-31, ✅ 스스로 해결)

- **유형:** 해시 집합 (Array & Hashing)
- **핵심 두 가지**
  1. **`unordered_set` 으로 O(1) 조회를 만든다.** 정렬하면 `O(n log n)` 이라 지문의
     `O(n)` 요구를 어긴다. "이 값이 있나?" 를 상수 시간에 답하는 게 전부다.
  2. **수열의 시작점에서만 걷는다.** `x-1` 이 집합에 없으면 `x` 가 시작점이다.
     이 검사를 빼면 같은 수열을 원소 수만큼 다시 걷는다.

```cpp
for (const auto &num : um) {                 // 집합을 순회 (중복이 이미 제거됨)
    if (!um.contains(num-1)) {               // 시작점인가
        int current = num, current_length = 1;
        while (um.contains(current+1)) { current++; current_length++; }
        max_length = max(max_length, current_length);
    }
}
```

- **시간복잡도:** O(n) / **공간복잡도:** O(n)

### 왜 O(n) 인가 — while 이 중첩돼 있는데도

겉보기엔 이중 루프지만, **각 값은 while 안에서 평생 딱 한 번만 방문된다.**
`x` 가 while 로 방문된다는 건 `x-1` 이 집합에 있다는 뜻이고, 그러면 `x` 는
바깥 `if` 를 통과하지 못하므로 `x` 에서 새로 걷는 일이 없다.
전체 while 실행 횟수의 합이 `n` 을 넘지 않는다.

### 처음 틀렸던 지점 — 순회 대상

두 번째 루프를 `um` 이 아니라 **원본 `nums`** 로 돌았다. 이러면 중복이 그대로 살아난다.

```
nums = [1,1,1,...,1(5만개), 2,3,...,50000]
```

값 `1` 이 5만 번 나오는데 매번 `!um.contains(0)` 이 참이라,
**길이 5만짜리 수열을 5만 번 다시 걷는다.**

| 순회 대상 | 소요 |
| --- | --- |
| 원본 `nums` | **5,501ms** |
| 집합 `um` | **2ms** |

`unordered_set` 이 중복을 합쳐주는데 정작 순회를 원본에서 해서 그 이점을 버린 셈이다.
DB 로 치면 인덱스를 잘 만들어놓고 `SELECT DISTINCT` 대신 원본 테이블을 풀스캔한 것.

> 하네스가 처음엔 이걸 못 잡았다. 성능 케이스를 `[1..n]` 셔플로만 만들어서
> **중복이 없었다.** 중복이 많은 케이스를 따로 추가했다.

### O(n) 요구가 뜻하는 것 — 정렬이 더 빠른데도

`n` 을 키워가며 재봤다. 전부 `[1..n]` 을 섞은 배열.

| n | 집합 | 집합(`reserve`) | 정렬 |
| --- | --- | --- | --- |
| 10^5 | 6ms | 5ms | **4ms** |
| 10^6 | 148ms | 97ms | **50ms** |
| 10^7 | 3,291ms | 1,193ms | **574ms** |

**정렬이 계속 이기고, 격차가 오히려 벌어진다** (1.5배 → 5.7배).
`unordered_set` 은 조회마다 해시 계산 + 버킷 포인터 추적이라 캐시를 놓치고,
정렬은 연속 메모리를 훑어 캐시 친화적이기 때문이다.
`reserve` 로 재해싱을 없애도 절반만 회복된다.

그러니 지문의 `O(n)` 요구는 **"더 빠르게 만들라"** 가 아니다.
**"정렬이 주는 순서라는 구조에 기대지 말고 풀 수 있느냐"** 를 묻는 것이다.

### 다시 볼 것

- 자료구조를 잘 골라놓고 **그걸 쓰는 방식**에서 이점을 버릴 수 있다.
  중복 제거를 위해 집합을 만들었으면 순회도 집합에서 해야 한다.
- 점근 복잡도가 낮은 게 항상 빠른 건 아니다.
  105 에서도 해시맵이 최악에서만 이기고 균형 입력에서는 졌다.
