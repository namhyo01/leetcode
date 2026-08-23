// 153. Find Minimum in Rotated Sorted Array
// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
#include <bits/stdc++.h>   // 첫 줄이어야 미리 컴파일된 헤더(make pch)가 쓰인다
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        // TODO: 여기에 풀이를 작성하세요.
        int left = 0;
        int right = nums.size() - 1;
        while (1){
            cout << nums[left] << " " << nums[right] << "\n";
            if (nums[left] > nums[right]){
                int mid = (left + right) / 2;
                if (nums[left] > nums[mid]){
                    right = mid;
                }else{
                    left = mid + 1;
                }
            }else{
                break;
            }
        }
        return nums[left];
    }
};

// ── 놀이터. 테스트에서 include 할 때는 TESTING 이 정의돼 이 블록이 빠진다. ──
// 이 가드를 지우면 solution_test.cpp 와 main 이 둘이 되어 링크가 깨진다.
// (가드가 있어도 `make run` 은 그대로 main 을 돌린다. 실험을 막지 않는다.)
// #ifndef TESTING
int main() {
    Solution s;

    vector<int> a{3, 4, 5, 1, 2};
    cout << s.findMin(a) << "\n";        // 1

    // vector<int> b{4, 5, 6, 7, 0, 1, 2};
    // cout << s.findMin(b) << "\n";        // 0

    // vector<int> c{11, 13, 15, 17};
    // cout << s.findMin(c) << "\n";        // 11
}
// #endif
