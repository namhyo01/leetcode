// 155. Min Stack https://leetcode.com/problems/min-stack/
#include <bits/stdc++.h>   // 첫 줄이어야 미리 컴파일된 헤더(make pch)가 쓰인다
using namespace std;

// 이 문제는 함수가 아니라 클래스를 설계한다.
// LeetCode 제출 형태 그대로 이름이 Solution 이 아니라 MinStack 이다.
class MinStack {
public:
    MinStack() {
        // TODO: 여기에 풀이를 작성하세요.
    }

    void push(int val) {
        // TODO
    }

    void pop() {
        // TODO
    }

    int top() {
        // TODO
        return 0;
    }

    int getMin() {
        // TODO
        return 0;
    }
};

// ── 놀이터. 테스트에서 include 할 때는 TESTING 이 정의돼 이 블록이 빠진다. ──
#ifndef TESTING
int main() {
    MinStack s;
    s.push(-2);
    s.push(0);
    s.push(-3);
    cout << s.getMin() << "\n";   // -3
    s.pop();
    cout << s.top() << "\n";      // 0
    cout << s.getMin() << "\n";   // -2
}
#endif
