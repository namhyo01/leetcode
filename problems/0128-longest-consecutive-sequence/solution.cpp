// 128. Longest Consecutive Sequence
// https://leetcode.com/problems/longest-consecutive-sequence/
#include <bits/stdc++.h>   // 첫 줄이어야 미리 컴파일된 헤더(make pch)가 쓰인다
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        // TODO: 여기에 풀이를 작성하세요.
        unordered_set<int> um;
        int max_length = 0;

        for (const auto &num : nums ){
            um.insert(num);
        }

        for (const auto &num : um){
            if (!um.contains(num-1)) { // 이전 값이 없는가
                int current = num;
                int current_length = 1;
                while (um.contains(current+1)){ // 다음 값이 존재하면
                    current++;
                    current_length++;
                }
                max_length = max(max_length, current_length);
            }
        }
        return max_length;
    }
};

// ── 놀이터. 테스트에서 include 할 때는 TESTING 이 정의돼 이 블록이 빠진다. ──
#ifndef TESTING
int main() {
    Solution s;

    vector<int> a{100, 4, 200, 1, 3, 2};
    cout << s.longestConsecutive(a) << "\n";              // 4

    vector<int> b{0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    cout << s.longestConsecutive(b) << "\n";              // 9

    vector<int> c{};
    cout << s.longestConsecutive(c) << "\n";              // 0
}
#endif
