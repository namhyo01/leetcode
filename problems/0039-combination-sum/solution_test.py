#!/usr/bin/env python3
"""39. Combination Sum 테스트 — 외부 의존성 없음."""

import random
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

from solution import combination_sum

CASES: list[tuple[list[int], int, list[tuple[int, ...]]]] = [
    ([2, 3, 6, 7], 7, [(2, 2, 3), (7,)]),
    ([2, 3, 5], 8, [(2, 2, 2, 2), (2, 3, 3), (3, 5)]),
    ([2], 1, []),
    ([5], 5, [(5,)]),
    ([3, 5, 8], 11, [(3, 3, 5), (3, 8)]),
    ([2, 4, 6, 8], 8, [(2, 2, 2, 2), (2, 2, 4), (2, 6), (4, 4), (8,)]),
    # 정렬돼 있지 않은 입력 — 제약조건은 정렬을 보장하지 않는다
    ([8, 7, 4, 3], 11, [(3, 4, 4), (3, 8), (4, 7)]),
    ([7, 3, 2], 18, [
        (2, 2, 2, 2, 2, 2, 2, 2, 2), (2, 2, 2, 2, 2, 2, 3, 3),
        (2, 2, 2, 2, 3, 7), (2, 2, 2, 3, 3, 3, 3), (2, 2, 7, 7),
        (2, 3, 3, 3, 7), (3, 3, 3, 3, 3, 3),
    ]),
]


def normalize(combos) -> set[tuple[int, ...]]:
    """조합 내부/전체 순서를 무시하고 비교할 수 있게 정규화."""
    return {tuple(sorted(c)) for c in combos}


def brute_force(candidates: list[int], target: int) -> set[tuple[int, ...]]:
    """참조 구현: 후보마다 '몇 개 쓸지'를 정하는 방식."""
    out = set()
    n = len(candidates)

    def go(i: int, remain: int, cur: list[int]) -> None:
        if remain == 0:
            out.add(tuple(sorted(cur)))
            return
        if i == n:
            return
        c = candidates[i]
        for cnt in range(remain // c + 1):
            go(i + 1, remain - c * cnt, cur + [c] * cnt)

    go(0, target, [])
    return out


def check_shape(got, candidates, target, label) -> str | None:
    """반환값이 구조적으로 말이 되는지 검사. 문제가 있으면 사유를 돌려준다."""
    if not isinstance(got, list):
        return f"list 가 아님: {type(got).__name__}"
    allowed = set(candidates)
    for combo in got:
        if not combo:
            return f"빈 조합이 들어있음: {got!r}"
        if any(x not in allowed for x in combo):
            return f"candidates 에 없는 값이 섞임: {combo!r}"
        if sum(combo) != target:
            return f"합이 target({target})이 아님: {combo!r} -> {sum(combo)}"
    if len(got) != len(normalize(got)):
        return f"중복된 조합이 있음 ({len(got)}개 중 유일한 건 {len(normalize(got))}개)"
    return None


def main() -> int:
    failed = 0

    for candidates, target, expected in CASES:
        got = combination_sum(list(candidates), target)
        why = check_shape(got, candidates, target, "예제")
        if why:
            print(f"✗ candidates={candidates} target={target} -> {why}")
            failed += 1
            continue
        if normalize(got) != set(expected):
            print(f"✗ candidates={candidates} target={target}"
                  f"\n    기대: {sorted(expected)}"
                  f"\n    실제: {sorted(normalize(got))}")
            failed += 1
            continue
        print(f"✓ candidates={candidates} target={target} -> {len(got)}개")

    # 랜덤 대조 테스트
    rng = random.Random(39)
    for _ in range(300):
        n = rng.randint(1, 5)
        candidates = rng.sample(range(2, 15), n)   # 제약조건: 원소는 서로 다르다
        target = rng.randint(1, 25)
        got = combination_sum(list(candidates), target)
        why = check_shape(got, candidates, target, "랜덤")
        if why:
            print(f"✗ 랜덤 실패 candidates={candidates} target={target} -> {why}")
            failed += 1
            break
        if normalize(got) != brute_force(candidates, target):
            print(f"✗ 랜덤 케이스 불일치 candidates={candidates} target={target}"
                  f"\n    기대: {sorted(brute_force(candidates, target))}"
                  f"\n    실제: {sorted(normalize(got))}")
            failed += 1
            break
    else:
        print("✓ 랜덤 대조 테스트 300건")

    # 성능 체크: 조합을 만들어놓고 중복 제거하는 방식이면 여기서 못 끝난다
    candidates, target, expect_count = [2, 3, 4, 5], 40, 145
    start = time.perf_counter()
    got = combination_sum(list(candidates), target)
    elapsed = time.perf_counter() - start
    if len(normalize(got)) != expect_count:
        print(f"✗ candidates={candidates} target={target}"
              f" -> 조합 {len(normalize(got))}개 (기대 {expect_count}개)")
        failed += 1
    elif elapsed > 5.0:
        print(f"✗ 성능: {elapsed:.2f}s — 너무 느림")
        failed += 1
    else:
        print(f"✓ 성능 체크 {elapsed*1000:.1f}ms (조합 {expect_count}개)")

    print("\n" + ("실패 %d건" % failed if failed else "전체 통과 🎉"))
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
