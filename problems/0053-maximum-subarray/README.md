# 53. Maximum Subarray

- Difficulty: **Medium**
- Link: https://leetcode.com/problems/maximum-subarray/

## Problem

Given an integer array `nums`, find the **subarray** with the largest sum,
and return *its sum*.

> A **subarray** is a contiguous **non-empty** sequence of elements within an array.

## Examples

```
Example 1:
Input:  nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.

Example 2:
Input:  nums = [1]
Output: 1
Explanation: The subarray [1] has the largest sum 1.

Example 3:
Input:  nums = [5,4,-1,7,8]
Output: 23
Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.
```

## Constraints

```
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
```

## Questions to sit with

- [ ] **subarray** 와 subsequence 의 차이는? 이 문제는 어느 쪽인가?
      (정의가 지문에 인용문으로 따로 적혀 있는 데는 이유가 있다)
- [ ] 가능한 부분배열은 전부 몇 개인가? 그걸 다 확인하면 `n = 10^5` 에서 통과하나?
- [ ] 배열이 **전부 음수**면 답은 무엇인가? 0 이 될 수 있나?
- [ ] 앞에서부터 한 번만 훑는다면, 각 위치에서 **무엇을 들고 있어야** 하는가?
- [ ] 합이 `int` 범위를 넘을 수 있나? 제약조건으로 최댓값을 계산해 보라.
- [ ] 내 풀이의 시간/공간 복잡도는?

## 내 접근 (풀면서 채우기)

<!--
- 처음 떠올린 방법:
- 막힌 지점:
- 최종 아이디어:
- 시간복잡도:      / 공간복잡도:
-->

## 내 접근 (2026-08-22, ✅ 스스로 해결)

- **유형:** Dynamic Programming (Kadane's algorithm)
- **정의:** `dp[i]` = **i 에서 끝나는** 부분배열 중 합이 가장 큰 것의 합
- **점화식:** `dp[i] = max(nums[i], dp[i-1] + nums[i])`
  - 앞의 덩어리를 이어붙이는 게 이득이면 잇고, 아니면 i 에서 새로 시작한다
  - 답은 `dp` 전체의 최댓값. `dp[n-1]` 이 아니다 — 최대 부분배열이 어디서 끝나는지 모르기 때문
- **시간복잡도:** O(n) / **공간복잡도:** O(n) (dp 배열)

### 왜 DP 인가 — 39번과 비교하면 선명하다

[39. Combination Sum](https://leetcode.com/problems/combination-sum/) 때는 DP 를 의심했다가
아니었다. 이번엔 진짜 DP 다. 갈리는 지점은 하나다.

> 부분문제의 답이 **하나의 값으로 요약되는가?**

- 39번: 부분문제의 답이 "조합 **목록**" 이라 요약이 안 됐다 → 백트래킹
- 53번: 부분문제의 답이 "i 에서 끝나는 최대 합" 이라는 **정수 하나** → DP

그리고 `dp[i]` 를 "i 까지의 최대 합" 이 아니라 **"i 에서 끝나는 최대 합"** 으로 잡는 게 핵심이다.
전자로 잡으면 점화식이 서지 않는다. 이어붙일 수 있는지 판단하려면 직전 덩어리가
**i-1 에서 끝나 있어야** 하기 때문이다.

### 측정 — dp 배열은 없어도 된다

`dp[i]` 는 `dp[i-1]` 만 참조한다. 배열 전체를 들고 있을 이유가 없다.
n=10^5 기준 (두 구현의 답이 같은 것도 확인):

| 구현 | 시간 | 추가 메모리 |
| --- | --- | --- |
| dp 배열 + `max_element` | 0.106ms | **390KB** |
| 값 하나만 굴리기 | 0.074ms | 0 |

1.4배 차이고 공간이 O(n) → O(1) 이 된다.
**"직전 것만 참조하는 DP 는 배열을 걷어낼 수 있다"** 는 건 DP 문제에서 반복해서 나오는 패턴이다.

### 다시 볼 것

- `dp[i-1] + nums[i] > nums[i]` 는 양변에서 `nums[i]` 를 지우면 그냥 `dp[i-1] > 0` 이다.
  "앞 덩어리가 플러스면 잇는다" 라는 뜻이 그대로 드러난다.
- `for (int i = 1; i < nums.size(); ++i)` 는 `-Wsign-compare` 경고가 난다.
  `nums.size()` 는 `size_t`(부호 없음)라 비교할 때 `int` 가 승격된다.
  `size_t i` 를 쓰거나 `(int)nums.size()` 로 캐스팅한다.
- 디버그용 `cout << nums` 를 풀이 안에 두면 **성능 측정이 망가진다.**
  하네스가 잰 5ms 중 대부분이 출력이었다 (실제 계산은 0.1ms).
  놀이터 `main()` 쪽에서 찍고 풀이 함수는 깨끗하게 둔다.
