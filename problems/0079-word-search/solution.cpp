// 79. Word Search https://leetcode.com/problems/word-search/
#include <bits/stdc++.h>   // 첫 줄이어야 미리 컴파일된 헤더(make pch)가 쓰인다
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        // TODO: 여기에 풀이를 작성하세요.
        return false;
    }
};

// ── 놀이터. 테스트에서 include 할 때는 TESTING 이 정의돼 이 블록이 빠진다. ──
// 이 가드를 지우면 solution_test.cpp 와 main 이 둘이 되어 링크가 깨진다.
// (가드가 있어도 `make run` 은 그대로 main 을 돌린다. 실험을 막지 않는다.)
#ifndef TESTING
int main() {
    Solution s;
    vector<vector<char>> board = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'},
    };
    cout << boolalpha;
    cout << s.exist(board, "ABCCED") << "\n";   // true
    cout << s.exist(board, "SEE")    << "\n";   // true
    cout << s.exist(board, "ABCB")   << "\n";   // false
}
#endif
