// 53. Maximum Subarray https://leetcode.com/problems/maximum-subarray/
#include <vector>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // TODO: 여기에 풀이를 작성하세요.
        return 0;
    }
};

// ── 놀이터. 테스트에서 include 할 때는 TESTING 이 정의돼 이 블록이 빠진다. ──
#ifndef TESTING
#include <iostream>

int main() {
    Solution s;

    vector<int> a{-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << s.maxSubArray(a) << "\n";   // 6

    vector<int> b{1};
    cout << s.maxSubArray(b) << "\n";   // 1

    vector<int> c{5, 4, -1, 7, 8};
    cout << s.maxSubArray(c) << "\n";   // 23
}
#endif
