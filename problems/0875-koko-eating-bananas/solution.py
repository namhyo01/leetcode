"""875. Koko Eating Bananas — https://leetcode.com/problems/koko-eating-bananas/"""


def min_eating_speed(piles: list[int], h: int) -> int:
    """h시간 안에 모든 바나나를 먹을 수 있는 최소 정수 속도 k를 반환한다.

    목표 복잡도: 시간 O(n log(max(piles))), 공간 O(1)
    """
    # TODO: 여기에 풀이를 작성하세요.
    raise NotImplementedError


if __name__ == "__main__":
    print(min_eating_speed([3, 6, 7, 11], 8))        # 4
    print(min_eating_speed([30, 11, 23, 4, 20], 5))  # 30
    print(min_eating_speed([30, 11, 23, 4, 20], 6))  # 23
