# 875. Koko Eating Bananas

- Difficulty: **Medium**
- Link: https://leetcode.com/problems/koko-eating-bananas/

## Problem

Koko loves to eat bananas. There are `n` piles of bananas, the `i`th pile has
`piles[i]` bananas. The guards have gone and will come back in `h` hours.

Koko can decide her bananas-per-hour eating speed of `k`. Each hour, she chooses
some pile of bananas and eats `k` bananas from that pile. If the pile has less
than `k` bananas, she eats all of them instead and will not eat any more bananas
during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before
the guards return.

Return **the minimum integer `k` such that she can eat all the bananas within `h` hours**.

## Examples

```
Example 1:
Input:  piles = [3,6,7,11], h = 8
Output: 4

Example 2:
Input:  piles = [30,11,23,4,20], h = 5
Output: 30

Example 3:
Input:  piles = [30,11,23,4,20], h = 6
Output: 23
```

## Constraints

```
1 <= piles.length <= 10^4
piles.length <= h <= 10^9
1 <= piles[i] <= 10^9
```

## Questions to sit with

- [ ] What is the range of possible values for `k` — lowest and highest?
- [ ] Given a speed `k`, how do you compute the total hours needed? (watch the `ceil`)
- [ ] If you tried every possible `k`, what would the complexity be? Does it pass
      the constraints above?
- [ ] Can the hour total overflow? (`k=1`, `n=10^4`, `piles[i]=10^9`)
- [ ] What is the time/space complexity of your solution?

## 내 접근 (풀면서 채우기)

<!--
- 처음 떠올린 방법:
- 막힌 지점:
- 최종 아이디어:
- 시간복잡도:      / 공간복잡도:
-->

## 내 접근 (2026-08-18, ✅ Go 스스로 해결)

- **아이디어:** 답 `k` 자체를 이분탐색. `k`가 커지면 걸리는 시간은 단조 감소하므로,
  "h시간 안에 되는가?"를 판정 함수로 두고 **조건을 만족하는 최소 k**(lower bound)를 찾는다.
- **탐색 범위:** `st = 1`, `end = max(piles)` — 속도가 최대 더미보다 커봐야 의미가 없다.
- **판정:** `howManyEatingHours(piles, k) = Σ ceil(piles[i] / k)`
  - 시간 초과면 `st = mid + 1` (더 빨리 먹어야 함)
  - 여유가 있으면 `end = mid - 1` (더 느려도 되나 확인)
  - 루프 종료 후 `st`가 답 (`st <= end` 형태의 lower bound 관용구)
- **시간복잡도:** O(n log(max(piles))) / **공간복잡도:** O(1)

### 측정 기록 — `math.Ceil` vs 정수 나눗셈

n=10^4 벤치마크에서 `math.Ceil(float64(p)/float64(c))`가 `(p+c-1)/c`보다 **2.2배 빨랐다**
(288μs vs 637μs). x86에서 64비트 정수 나눗셈 `DIV`가 부동소수점 `DIVSD`보다 느리기 때문.

정밀도도 이 제약조건에서는 안전하다: `p/c`가 정수가 아니면 가장 가까운 정수와의 간격이 `1/c` 이상인데,
float64의 절대 오차는 대략 `(p/c) * 1.1e-16` 이라 `p < 9e15`이면 간격보다 작다. `p <= 1e9`이므로 여유.
단, 제약이 커지면(`p > 9e15`) 깨지므로 무조건 float을 쓰는 습관은 위험.
