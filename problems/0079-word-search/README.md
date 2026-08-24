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

## 내 접근 (2026-08-24, ✅ 스스로 해결)

- **유형:** Backtracking (격자 위 DFS)
- **아이디어:** 모든 칸을 시작점으로 삼아 DFS. 현재 칸이 `word[idx]` 와 맞으면
  네 방향으로 뻗고, 아니면 즉시 실패로 되돌아온다.
- **방문 처리:** 보드에 직접 `'#'` 를 써서 표시하고, **되돌아올 때 원래 글자로 복원**한다.
  별도 `visited` 배열 없이 보드 자체를 상태로 쓴 셈.

```cpp
char temp = board[y][x];
board[y][x] = '#';              // 이 경로에서는 다시 못 쓴다
for (int i = 0; i < 4; ++i)
    if (dfs(y+dy[i], x+dx[i], idx+1)) { board[y][x] = temp; return true; }
board[y][x] = temp;             // 복원 — 다른 경로에서는 다시 쓸 수 있어야 한다
return false;
```

- **시간복잡도:** O(m·n·4^L) (L = 단어 길이) / **공간복잡도:** O(L) 재귀 스택

### 복원이 왜 핵심인가

"같은 칸을 두 번 쓸 수 없다" 는 **한 경로 안에서만** 유효하다.
경로 A 에서 쓴 칸을 경로 B 에서는 다시 쓸 수 있어야 한다.
표시만 하고 복원하지 않으면 첫 경로가 보드를 영구히 오염시켜 뒤의 탐색이 전부 실패한다.

하네스가 **호출 후 보드가 원래대로 돌아왔는지** 따로 검사한다.
복원을 빠뜨리면 답이 우연히 맞아도 여기서 걸린다 — 호출자의 인자를 몰래 망가뜨리는 것이기 때문.

### 39번과의 대비

둘 다 백트래킹인데 **되돌리는 대상이 다르다.**

| 문제 | 상태 | 되돌리는 방법 |
| --- | --- | --- |
| 39. Combination Sum | 지금까지 고른 수의 목록 | `cur.pop_back()` |
| **79. Word Search** | 보드 자체 (공유 자원) | `board[y][x] = temp` |

39 는 내가 들고 다니는 경로를 되돌리고, 79 는 **모두가 공유하는 격자**를 되돌린다.
후자가 더 실수하기 쉽다. 되돌리지 않으면 남의 탐색까지 망가뜨리기 때문.

### 측정 — `std::function` 이 1.8배 느리다

재귀를 `function<bool(int,int,int)>` 로 잡았는데, 같은 로직을 멤버 함수로 옮겨 재봤다
(무작위 3000건에서 두 구현의 답이 같은 것도 확인).

| 구현 | 최악 케이스 (6x6 전부 'a') |
| --- | --- |
| `std::function` 재귀 | 36.4ms |
| 멤버 함수 재귀 | **20.3ms** |

`std::function` 은 **타입 소거** 때문에 호출마다 간접 분기가 생기고 인라인이 막힌다.
평소엔 무시할 수준이지만 이 문제처럼 **수백만 번 재귀하는 핫패스**에서는 드러난다.

대안: 멤버 함수로 빼거나, C++23 이면 `auto dfs = [&](this auto&& self, ...)` 로
람다가 자기를 부르게 할 수 있다.

### 다시 볼 것

- `-Wsign-compare` 경고가 5개 났다. `idx == word.size()`, `i < board.size()` 처럼
  `int` 와 `size_t` 를 비교한 것. `(int)` 캐스팅하거나 `size_t` 를 쓴다.
- `board[y][x] = temp;` 가 두 곳에 중복돼 있다. 루프에서 `break` 하고 한 번만 복원하면 된다.
