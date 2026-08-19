"""39. Combination Sum — https://leetcode.com/problems/combination-sum/"""


def combination_sum(candidates: list[int], target: int) -> list[list[int]]:
    """candidates 의 수를 무제한으로 골라 합이 target 이 되는 모든 조합을 반환한다."""
    # TODO: 여기에 풀이를 작성하세요.
    raise NotImplementedError


if __name__ == "__main__":
    print(combination_sum([2, 3, 6, 7], 7))  # [[2, 2, 3], [7]]
    print(combination_sum([2, 3, 5], 8))     # [[2, 2, 2, 2], [2, 3, 3], [3, 5]]
    print(combination_sum([2], 1))           # []
