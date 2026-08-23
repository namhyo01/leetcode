# 153. Find Minimum in Rotated Sorted Array

- Difficulty: **Medium**
- Link: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

## Problem

Suppose an array of length `n` sorted in ascending order is **rotated** between `1`
and `n` times. For example, the array `nums = [0,1,2,4,5,6,7]` might become:

- `[4,5,6,7,0,1,2]` if it was rotated `4` times.
- `[0,1,2,4,5,6,7]` if it was rotated `7` times.

Notice that **rotating** an array `[a[0], a[1], a[2], ..., a[n-1]]` 1 time results in
the array `[a[n-1], a[0], a[1], a[2], ..., a[n-2]]`.

Given the sorted rotated array `nums` of **unique** elements, return *the minimum
element of this array*.

You must write an algorithm that runs in `O(log n)` time.

## Examples

```
Example 1:
Input:  nums = [3,4,5,1,2]
Output: 1
Explanation: The original array was [1,2,3,4,5] rotated 3 times.

Example 2:
Input:  nums = [4,5,6,7,0,1,2]
Output: 0
Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.

Example 3:
Input:  nums = [11,13,15,17]
Output: 11
Explanation: The original array was [11,13,15,17] and it was rotated 4 times.
```

## Constraints

```
n == nums.length
1 <= n <= 5000
-5000 <= nums[i] <= 5000
All the integers of nums are unique.
nums is sorted and rotated between 1 and n times.
```

## Questions to sit with

- [ ] "rotated between 1 and n times" 라고 했다. `n` 번 회전하면 어떤 모양인가?
      **회전이 없는 것처럼 보이는 입력**도 들어올 수 있나?
- [ ] 배열을 종이에 그려보라. 최솟값을 기준으로 배열이 몇 개의 구간으로 나뉘는가?
      각 구간은 어떤 성질을 갖는가?
- [ ] 어떤 위치 하나를 집었을 때, 최솟값이 그 **왼쪽에 있는지 오른쪽에 있는지**
      판단할 방법이 있는가? 무엇과 비교해야 하는가?
- [ ] 그 비교 대상으로 **맨 왼쪽 값**을 쓰는 것과 **맨 오른쪽 값**을 쓰는 것 중
      어느 쪽이 더 다루기 쉬운가? 예제 3(`[11,13,15,17]`)에 둘 다 적용해 보라.
- [ ] 원소가 하나뿐이면? 두 개뿐이면?
- [ ] 내 풀이의 시간/공간 복잡도는?

## 내 접근 (풀면서 채우기)

<!--
- 처음 떠올린 방법:
- 막힌 지점:
- 최종 아이디어:
- 시간복잡도:      / 공간복잡도:
-->

## 내 접근 (2026-08-23, ✅ 스스로 해결)

- **유형:** Binary Search
- **처음 낸 답:** `min_element` — 정답은 맞지만 `O(n)` 이라 지문의 `O(log n)` 요구를 어긴다.
  LeetCode 는 `n <= 5000` 이라 통과하지만, 하네스가 `n=10^7` 로 따로 재서 잡아냈다 (14.8ms).
- **최종 아이디어:** 배열을 그려보면 **오름차순 계단 두 개**이고 사이에 한 번 뚝 떨어진다.
  찾아야 할 최솟값은 그 떨어진 직후. `mid` 가 어느 계단에 있는지 알면 절반을 버릴 수 있다.

```cpp
while (1) {
    if (nums[left] > nums[right]) {     // 이 구간이 '회전돼 있는가'
        int mid = (left + right) / 2;
        if (nums[left] > nums[mid]) right = mid;   // mid 가 아래쪽 계단 -> 답은 왼쪽
        else                        left = mid + 1; // mid 가 위쪽 계단 -> 답은 오른쪽
    } else break;                       // 이미 정렬된 구간이면 nums[left] 가 답
}
return nums[left];
```

- **시간복잡도:** O(log n) / **공간복잡도:** O(1)

### 바깥 조건이 예외 처리를 대신한다

정석 풀이는 `nums[mid]` 를 **오른쪽 끝** `nums[hi]` 와 비교한다. 왼쪽 끝과 비교하면
`[11,13,15,17]` 같이 **회전이 안 보이는 입력**에서 깨지기 때문이다.

이 풀이는 왼쪽 끝과 비교하는데도 깨지지 않는다. 바깥의 `nums[left] > nums[right]` 가
**"이 구간이 실제로 회전돼 있는가"** 를 먼저 확인하기 때문이다. 회전이 없으면 그냥 빠져나와
`nums[left]` 를 돌려준다. 조건 하나로 예외 케이스를 통째로 걷어낸 셈이다.

종료도 보장된다. `left < right` 이면서 회전돼 있으면 `left <= mid < right` 이므로
`right = mid`(감소) 또는 `left = mid+1`(증가)로 구간이 반드시 줄고,
`left == right` 가 되면 바깥 조건이 거짓이 되어 멈춘다.

### 측정 — 두 형태의 트레이드오프

n=10^7. 시간은 나노초라 노이즈가 심해서 **배열 접근 횟수**로 쟀다
(두 구현이 n=1..300 의 모든 회전량에서 같은 답을 내는 것도 확인).

| 최솟값 위치 | 내 풀이 | 정석(오른쪽 끝 비교) |
| --- | --- | --- |
| 회전 없음 | **3회** | 49회 |
| 앞쪽 0.1% | 95회 | **47회** |
| 가운데 | **7회** | 49회 |
| 뒤쪽 99.9% | 95회 | **47회** |

- 한 번 도는 데 읽는 값이 **내 풀이는 3개**(`left`, `right`, `mid`), **정석은 2개**(`mid`, `hi`).
  그래서 최악에서 약 2배 더 읽는다.
- 대신 **구간이 정렬 상태가 되는 순간 즉시 빠져나온다.** 최솟값이 가운데 근처면
  몇 번 반으로 접는 것만으로 조건이 풀려서 7~11회에 끝난다.

둘 다 O(log n) 이고 상수만 다르다. 입력 분포에 따라 승자가 바뀐다.

### 다시 볼 것

- **"정답이 맞다"와 "요구된 복잡도를 지켰다"는 다르다.** 처음 낸 `min_element` 가
  정확히 그 경우였다. 제약이 작으면 채점기는 통과시켜 준다.
- `while (1) { if (조건) {...} else break; }` 는 `while (조건) {...}` 으로 바로 쓸 수 있다.
- `(left + right) / 2` 는 이 문제에선 안전하지만 `left + (right - left) / 2` 를 습관으로.
- `int right = nums.size() - 1;` 는 `size_t` → `int` 축소 변환이다.
  `n >= 1` 이 보장돼 안전하지만, 빈 벡터였다면 `size() - 1` 이 거대한 값으로 감싼다.
