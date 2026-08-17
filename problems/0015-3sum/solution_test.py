#!/usr/bin/env python3
"""15. 3Sum 테스트 — 외부 의존성 없음. `python3 solution_test.py` 로 실행."""

import random
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

from solution import three_sum

CASES: list[tuple[list[int], list[list[int]]]] = [
    ([-1, 0, 1, 2, -1, -4], [[-1, -1, 2], [-1, 0, 1]]),
    ([0, 1, 1], []),
    ([0, 0, 0], [[0, 0, 0]]),
    ([0, 0, 0, 0], [[0, 0, 0]]),
    ([-2, 0, 1, 1, 2], [[-2, 0, 2], [-2, 1, 1]]),
    ([3, 0, -2, -1, 1, 2], [[-2, -1, 3], [-2, 0, 2], [-1, 0, 1]]),
    ([1, 2, 3], []),
    ([-4, -2, -2, -2, 0, 1, 2, 2, 2, 3, 3, 4, 4, 6, 6],
     [[-4, -2, 6], [-4, 0, 4], [-4, 1, 3], [-4, 2, 2], [-2, -2, 4], [-2, 0, 2]]),
]


def normalize(triplets) -> set[tuple[int, ...]]:
    """삼중항/전체 순서를 무시하고 비교할 수 있는 형태로 정규화."""
    return {tuple(sorted(t)) for t in triplets}


def brute_force(nums: list[int]) -> set[tuple[int, ...]]:
    n = len(nums)
    out = set()
    for i in range(n):
        for j in range(i + 1, n):
            for k in range(j + 1, n):
                if nums[i] + nums[j] + nums[k] == 0:
                    out.add(tuple(sorted((nums[i], nums[j], nums[k]))))
    return out


def main() -> int:
    failed = 0

    for nums, expected in CASES:
        got = three_sum(list(nums))
        if not isinstance(got, list) or any(len(t) != 3 for t in got):
            print(f"✗ {nums} -> 반환 형식이 잘못됨: {got!r}")
            failed += 1
            continue
        if len(got) != len(normalize(got)):
            print(f"✗ {nums} -> 중복된 삼중항이 있음: {got!r}")
            failed += 1
            continue
        if normalize(got) != normalize(expected):
            print(f"✗ {nums}\n    기대: {sorted(normalize(expected))}\n    실제: {sorted(normalize(got))}")
            failed += 1
            continue
        print(f"✓ {nums}")

    # 랜덤 대조 테스트 (브루트포스와 결과 비교)
    rng = random.Random(42)
    for _ in range(300):
        nums = [rng.randint(-6, 6) for _ in range(rng.randint(3, 12))]
        got = normalize(three_sum(list(nums)))
        want = brute_force(nums)
        if got != want:
            print(f"✗ 랜덤 케이스 실패 nums={nums}\n    기대: {sorted(want)}\n    실제: {sorted(got)}")
            failed += 1
            break
    else:
        print("✓ 랜덤 대조 테스트 300건")

    # 성능 체크 (n=3000)
    nums = [rng.randint(-10**5, 10**5) for _ in range(3000)]
    import time
    start = time.perf_counter()
    three_sum(nums)
    elapsed = time.perf_counter() - start
    if elapsed > 5.0:
        print(f"✗ n=3000 이 {elapsed:.2f}s — 너무 느림 (O(n^3)일 가능성)")
        failed += 1
    else:
        print(f"✓ n=3000 성능 {elapsed:.2f}s")

    print("\n" + ("실패 %d건" % failed if failed else "전체 통과 🎉"))
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
