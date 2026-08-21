# 15. 3Sum

- Difficulty: **Medium**
- Link: https://leetcode.com/problems/3sum/

> **재풀이 문제.** 2026-08-18 에 스스로 풀지 못하고 해설을 봤다.
> 이전 시도와 그때 적은 회고는 `git log -- problems/0015-3sum/` 에 남아 있으니
> **다 풀기 전에는 열어보지 말 것.**

## Problem

Given an integer array `nums`, return all the triplets `[nums[i], nums[j], nums[k]]`
such that `i != j`, `i != k`, and `j != k`, and `nums[i] + nums[j] + nums[k] == 0`.

Notice that the solution set must not contain **duplicate triplets**.

## Examples

```
Example 1:
Input:  nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation:
  nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
  nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
  nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
  The distinct triplets are [-1,0,1] and [-1,-1,2].
  Notice that the order of the output and the order of the triplets does not matter.

Example 2:
Input:  nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.

Example 3:
Input:  nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
```

## Constraints

```
3 <= nums.length <= 3000
-10^5 <= nums[i] <= 10^5
```

## Questions to sit with

- [ ] 세 수를 전부 훑으면 복잡도가 얼마인가? `n = 3000` 에서 통과하나?
- [ ] 세 수 중 **하나를 고정**하면 남는 문제는 무엇이 되나? 그 문제는 얼마에 풀리나?
- [ ] 출력의 순서가 상관없다고 했다. 이 조건에서 공짜로 얻을 수 있는 게 있나?
- [ ] 중복 삼중항을 **만들어놓고 걸러내는** 대신, 애초에 안 만들 방법이 있나?
- [ ] 중복이 생길 수 있는 자리는 몇 군데인가?
- [ ] 내 풀이의 시간/공간 복잡도는?

## 내 접근 (2026-08-21, ✅ 재풀이 성공 — 힌트 없음)

> 2026-08-18 에는 스스로 풀지 못하고 해설을 봤다(❌). 3일 뒤 백지에서 다시 쳐서 통과.

- **유형:** Two Pointers (+ 정렬)
- **아이디어:** 정렬한 뒤 첫 수 `nums[i]` 를 고정하면, 남은 문제는
  "정렬된 구간에서 합이 `-nums[i]` 인 두 수 찾기" 가 된다. 이건 양끝 포인터로 O(n) 에 풀린다.
  - `sum < 0` → `st++` (가장 큰 짝과 붙여도 모자라니 `nums[st]` 는 가망 없음)
  - `sum > 0` → `end--`
- **중복 제거 두 군데** — `set` 후처리 없이 루프 안에서 처리했다.
  1. 고정값이 직전과 같으면 `continue` (결과가 통째로 중복된다)
  2. 정답을 기록한 뒤 `nums[st] == nums[st-1]` 인 동안 `st++`
  - `end` 쪽은 건드릴 필요가 없다. 고정값과 `st` 가 정해지면 `end` 는 자동으로 하나로 결정되기 때문.
- **조기 종료:** `nums[i] > 0` 이면 뒤는 전부 양수라 합이 0 이 될 수 없다 → `break`
- **시간복잡도:** O(n^2) — 정렬 O(n log n) + 바깥 루프 n × 투 포인터 O(n)
- **공간복잡도:** O(1) — 정렬이 제자리, 출력 제외

### 실측

n=3000 에서 **9.1ms** (16,714 allocs). 성능 게이트 300ms 를 여유롭게 통과.
참고로 세 수를 전부 훑는 풀이는 같은 입력에서 1,038ms 로 100배 이상 차이가 난다.

### 지난번에 막혔던 지점

**"Two Sum 자체가 O(n) 에 풀린다"** 를 몰라서, 안쪽을 브루트포스로 보고 전체가 O(n^3) 이라
판단해 개선이 없다고 결론지었다. 이번엔 그 지점을 바로 넘어갔다.

이후 875(답을 이분탐색), 39(백트래킹), 105(분할정복)를 스스로 풀면서
"부분문제로 쪼갠 뒤 그 부분문제의 최적 복잡도를 따진다" 는 감각이 붙은 것으로 보인다.
