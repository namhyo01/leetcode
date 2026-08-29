// 57. Insert Interval https://leetcode.com/problems/insert-interval/
#include <bits/stdc++.h>   // 첫 줄이어야 미리 컴파일된 헤더(make pch)가 쓰인다
using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        // TODO: 여기에 풀이를 작성하세요.
        return {};
    }
};

// ── 놀이터. 테스트에서 include 할 때는 TESTING 이 정의돼 이 블록이 빠진다. ──
#ifndef TESTING
static void print(const vector<vector<int>>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++)
        cout << (i ? "," : "") << "[" << v[i][0] << "," << v[i][1] << "]";
    cout << "]\n";
}

int main() {
    Solution s;

    vector<vector<int>> a{{1, 3}, {6, 9}};
    vector<int> na{2, 5};
    print(s.insert(a, na));                     // [[1,5],[6,9]]

    vector<vector<int>> b{{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    vector<int> nb{4, 8};
    print(s.insert(b, nb));                     // [[1,2],[3,10],[12,16]]

    vector<vector<int>> c{};
    vector<int> nc{5, 7};
    print(s.insert(c, nc));                     // [[5,7]]
}
#endif
