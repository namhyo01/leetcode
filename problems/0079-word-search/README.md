# 79. Word Search

- Difficulty: **Medium**
- Link: https://leetcode.com/problems/word-search/

## Problem

Given an `m x n` grid of characters `board` and a string `word`, return `true` *if*
`word` *exists in the grid*.

The word can be constructed from letters of **sequentially adjacent cells**, where
adjacent cells are horizontally or vertically neighboring. **The same letter cell may
not be used more than once.**

## Examples

```
Example 1:
Input:  board = [["A","B","C","E"],
                 ["S","F","C","S"],
                 ["A","D","E","E"]], word = "ABCCED"
Output: true

Example 2:
Input:  board = [["A","B","C","E"],
                 ["S","F","C","S"],
                 ["A","D","E","E"]], word = "SEE"
Output: true

Example 3:
Input:  board = [["A","B","C","E"],
                 ["S","F","C","S"],
                 ["A","D","E","E"]], word = "ABCB"
Output: false
```

## Constraints

```
m == board.length
n == board[i].length
1 <= m, n <= 6
1 <= word.length <= 15
board and word consists of only lowercase and uppercase English letters.
```

## Questions to sit with

- [ ] 예제 3 `"ABCB"` 는 왜 `false` 인가? 글자는 보드에 다 있는데 무엇이 걸리는가?
- [ ] 시작점을 어디로 잡아야 하는가? 몇 군데를 시도해야 하는가?
- [ ] "같은 칸을 두 번 쓸 수 없다" 를 어떻게 기억할 것인가?
      한 경로에서 쓴 칸이 **다른 경로에서는 다시 쓸 수 있어야** 한다는 점에 주의.
- [ ] 그 기록을 남기는 방법이 여러 가지다. 별도 `visited` 배열, 보드에 직접 표시,
      비트마스크 — 각각 무엇을 되돌려야 하는가?
- [ ] 보드가 전부 같은 글자(`aaaa...`)이고 단어를 못 찾는 경우, 얼마나 많은 경로를 보게 되나?
- [ ] 내 풀이의 시간/공간 복잡도는?
