# 39. Combination Sum

- Difficulty: **Medium**
- Link: https://leetcode.com/problems/combination-sum/

## Problem

Given an array of **distinct** integers `candidates` and a target integer `target`,
return *a list of all **unique combinations** of* `candidates` *where the chosen
numbers sum to* `target`. You may return the combinations in **any order**.

The **same** number may be chosen from `candidates` an **unlimited number of times**.
Two combinations are unique if the frequency of at least one of the chosen numbers
is different.

The test cases are generated such that the number of unique combinations that sum
up to `target` is less than `150` combinations for the given input.

## Examples

```
Example 1:
Input:  candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
  2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
  7 is a candidate, and 7 = 7.
  These are the only two combinations.

Example 2:
Input:  candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]

Example 3:
Input:  candidates = [2], target = 1
Output: []
```

## Constraints

```
1 <= candidates.length <= 30
2 <= candidates[i] <= 40
All elements of candidates are distinct.
1 <= target <= 40
```

## Questions to sit with

- [ ] `[2,2,3]` 과 `[2,3,2]` 는 같은 조합인가, 다른 조합인가? 문제 문장 어디에 답이 있나?
- [ ] 같은 수를 무제한으로 쓸 수 있다는 조건이 탐색 구조를 어떻게 바꾸나?
- [ ] 중복 조합을 **만들어놓고 걸러내는** 대신, 애초에 안 만들 방법이 있나?
- [ ] 언제 탐색을 멈춰야 하나? 가지치기할 수 있는 지점은?
- [ ] 입력이 정렬돼 있다고 가정해도 되나? (예제 1은 정렬돼 있지만 제약조건은 뭐라고 하나)
- [ ] 내 풀이의 시간/공간 복잡도는?

## 내 접근 (풀면서 채우기)

<!--
- 처음 떠올린 방법:
- 막힌 지점:
- 최종 아이디어:
- 시간복잡도:      / 공간복잡도:
-->

## 내 접근 (2026-08-19, ✅ Go 스스로 해결)

- **유형:** Backtracking (DFS + 상태 되돌리기)
- **아이디어:** 정렬한 뒤 시작 후보를 하나씩 고정하고, 재귀에서 `candidates[idx:]` 로 범위를
  좁혀가며 같은 수를 무제한으로 다시 고를 수 있게 했다. `sum == target` 이면 기록,
  `sum > target` 이면 중단.
- **중복 제거:** 조합을 만들어놓고 걸러내는 게 아니라, **뒤로만 진행**(`cands[idx:]`)해서
  애초에 순열이 생기지 않게 했다. `[2,3]` 은 나오지만 `[3,2]` 는 나올 수 없다.
- **결과 저장:** `slices.Clone(apply)` — 참조를 그대로 넣으면 백킹 배열을 공유해서
  결과가 전부 같은 값이 된다. 이번에 따로 파본 내용을 바로 적용했다.

### 왜 DP가 아닌가

처음에 DP를 의심했다. 부분문제가 겹치는 건 맞다 (`target=8` 을 풀다 보면 "합 5 만들기" 가
여러 경로에서 반복된다). 하지만 DP가 힘을 쓰려면 **부분문제의 답이 하나의 값으로 요약**돼야
하는데, 이 문제가 요구하는 건 개수가 아니라 **조합 목록 그 자체**다. 메모이제이션을 해도
저장하는 게 리스트 덩어리라 아끼는 것보다 복사·병합 비용이 더 든다.

같은 뼈대에 요구만 다른 문제들과 비교하면 선명하다:

| 문제 | 요구 | 접근 |
|---|---|---|
| 322. Coin Change | 최소 동전 **개수** | DP |
| 377. Combination Sum IV | 경우의 **수** | DP |
| **39. Combination Sum** | 모든 조합의 **목록** | Backtracking |

### 벤치마크로 확인한 개선 여지

`[2,3,4,5,6,7,8,9]`, target=40 (조합 1690개) 기준:

| 버전 | ns/op | allocs/op |
|---|---|---|
| 내 풀이 | 350,612 | 7,824 |
| + 가지치기(`sum+c > target` 이면 `break`) | 196,417 | 4,676 |
| + 공유 `cur` 재사용 | 106,572 | 1,703 |

두 가지가 각각 1.8배씩 기여했다.

1. **가지치기를 안 썼다.** 정렬해놓고 정작 활용을 안 했다. 정렬된 배열에서
   `sum + cands[idx] > target` 이면 뒤쪽은 전부 더 크므로 `break` 해도 된다.
2. **`append(apply, x)` 를 매번 넘겼다.** 결과는 맞다 (잎에서 clone 하므로 형제 호출이
   덮어쓰기 전에 이미 복사본이 떠진다). 다만 레벨마다 재할당이 일어나 할당이 4.6배 많다.
   슬라이스 하나를 공유하며 `append` / `cur[:len(cur)-1]` 로 밀고 당기면 줄어든다.

### 다시 볼 것

- 정렬을 했으면 **가지치기까지 해야** 값을 뽑는다. 정렬만 하고 안 쓰면 O(n log n) 만 지불한 셈
- `slices.Sort(candidates)` 는 호출자의 슬라이스를 변형시킨다 (875 에서도 같은 지적)
- 오타: `candidaes` → `candidates`
