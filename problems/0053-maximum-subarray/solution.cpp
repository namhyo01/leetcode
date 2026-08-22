// 53. Maximum Subarray https://leetcode.com/problems/maximum-subarray/
#include <bits/stdc++.h>   // 첫 줄이어야 미리 컴파일된 헤더(make pch)가 쓰인다

using namespace std;

template<class T>
ostream& operator<<(ostream& stream, const std::vector<T>& values)
{
	copy( begin(values), end(values), ostream_iterator<T>(stream, ", ") );
	return stream;
}


class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // TODO: 여기에 풀이를 작성하세요.
        sort(nums.begin(), nums.end());
        cout << nums << "\n";


        return 0;
    }
};

// ── 놀이터. 테스트에서 include 할 때는 TESTING 이 정의돼 이 블록이 빠진다. ──
// 이 가드를 지우면 solution_test.cpp 와 main 이 둘이 되어 링크가 깨진다.
#ifndef TESTING
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
