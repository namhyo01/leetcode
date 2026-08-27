// 207. Course Schedule https://leetcode.com/problems/course-schedule/
#include <bits/stdc++.h>   // 첫 줄이어야 미리 컴파일된 헤더(make pch)가 쓰인다
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // TODO: 여기에 풀이를 작성하세요.
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses, 0); // 각 노드의 진입 차수
for (const auto& p : prerequisites) {
            graph[p[1]].push_back(p[0]);
            indegree[p[0]]++;
        }



        
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        int count = 0;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            count++;
            for (int nextCourse : graph[course]) {
                indegree[nextCourse]--;
                if (indegree[nextCourse] == 0) {
                    q.push(nextCourse);
                }
            }
        }
        return count == numCourses;
    }
};

// ── 놀이터. 테스트에서 include 할 때는 TESTING 이 정의돼 이 블록이 빠진다. ──
// 이 가드를 지우면 solution_test.cpp 와 main 이 둘이 되어 링크가 깨진다.
// (가드가 있어도 `make run` 은 그대로 main 을 돌린다. 실험을 막지 않는다.)
#ifndef TESTING
int main() {
    Solution s;
    cout << boolalpha;

    vector<vector<int>> a{{1, 0}};
    cout << s.canFinish(2, a) << "\n";          // true

    vector<vector<int>> b{{1, 0}, {0, 1}};
    cout << s.canFinish(2, b) << "\n";          // false

    vector<vector<int>> c{};
    cout << s.canFinish(3, c) << "\n";          // true
}
#endif
