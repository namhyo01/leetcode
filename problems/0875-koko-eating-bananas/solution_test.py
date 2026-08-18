#!/usr/bin/env python3
"""875. Koko Eating Bananas 테스트 — 외부 의존성 없음."""

import random
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

from solution import min_eating_speed

CASES: list[tuple[list[int], int, int]] = [
    ([3, 6, 7, 11], 8, 4),
    ([30, 11, 23, 4, 20], 5, 30),
    ([30, 11, 23, 4, 20], 6, 23),
    ([1], 1, 1),
    ([1000000000], 2, 500000000),
    ([312884470], 968709470, 1),          # h가 매우 크면 k=1로 충분
    ([332484035, 524908576, 855865114, 632922376, 222257295], 823855818, 4),
    ([1, 1, 1, 1], 4, 1),
    ([5, 5, 5], 3, 5),                     # 시간이 딱 더미 개수 = 최대값이 답
    ([1, 2, 3, 4, 5], 15, 1),
]


def hours_needed(piles: list[int], k: int) -> int:
    return sum(-(-p // k) for p in piles)   # ceil(p / k)


def brute_force(piles: list[int], h: int) -> int:
    """k를 1부터 선형 탐색. 작은 입력 전용 참조 구현."""
    for k in range(1, max(piles) + 1):
        if hours_needed(piles, k) <= h:
            return k
    return max(piles)


def main() -> int:
    failed = 0

    for piles, h, expected in CASES:
        got = min_eating_speed(list(piles), h)
        if got != expected:
            print(f"✗ piles={piles if len(piles) < 8 else '...'} h={h}\n    기대: {expected}\n    실제: {got}")
            failed += 1
        else:
            print(f"✓ piles={piles if len(piles) < 8 else '...'} h={h} -> {got}")

    # 랜덤 대조 테스트
    rng = random.Random(875)
    for _ in range(500):
        n = rng.randint(1, 6)
        piles = [rng.randint(1, 25) for _ in range(n)]
        h = rng.randint(n, n * 8)
        got = min_eating_speed(list(piles), h)
        want = brute_force(piles, h)
        if got != want:
            print(f"✗ 랜덤 케이스 실패 piles={piles} h={h}\n    기대: {want}\n    실제: {got}")
            failed += 1
            break
    else:
        print("✓ 랜덤 대조 테스트 500건")

    # 답이 유효한지 직접 검증 (k시간 안에 되고, k-1은 안 되는가)
    for _ in range(200):
        n = rng.randint(1, 40)
        piles = [rng.randint(1, 10**9) for _ in range(n)]
        h = rng.randint(n, n * 4)
        k = min_eating_speed(list(piles), h)
        if k < 1:
            print(f"✗ k가 1 미만: piles(n={n}) h={h} -> {k}")
            failed += 1
            break
        if hours_needed(piles, k) > h:
            print(f"✗ k={k}로는 h={h}시간 안에 못 먹음 (n={n})")
            failed += 1
            break
        if k > 1 and hours_needed(piles, k - 1) <= h:
            print(f"✗ k={k}가 최소가 아님. k-1={k-1}로도 가능 (n={n}, h={h})")
            failed += 1
            break
    else:
        print("✓ 최소성 검증 200건 (큰 값 포함)")

    # 성능 체크: n=10^4, piles[i]=10^9 — 선형 탐색이면 절대 못 끝남
    piles = [rng.randint(1, 10**9) for _ in range(10**4)]
    h = 2 * 10**4
    start = time.perf_counter()
    min_eating_speed(piles, h)
    elapsed = time.perf_counter() - start
    if elapsed > 5.0:
        print(f"✗ n=10^4 이 {elapsed:.2f}s — 너무 느림 (k를 1부터 훑고 있을 가능성)")
        failed += 1
    else:
        print(f"✓ n=10^4 성능 {elapsed:.2f}s")

    print("\n" + ("실패 %d건" % failed if failed else "전체 통과 🎉"))
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
