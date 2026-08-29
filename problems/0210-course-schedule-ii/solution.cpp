// 210. Course Schedule II https://leetcode.com/problems/course-schedule-ii/
#include <bits/stdc++.h>   // 첫 줄이어야 미리 컴파일된 헤더(make pch)가 쓰인다
using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // TODO: 여기에 풀이를 작성하세요.
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses, 0); // 각 노드의 진입

        for (const auto& p : prerequisites) {
            graph[p[1]].push_back(p[0]);
            indegree[p[0]]++; // 진입 차수 증가
        }

        queue<int> q;
        for (int i=0;i<numCourses;i++){
            if (indegree[i] == 0) { // 진입 된 적이 없는 애들은 따로 빼기
                q.push(i); // q에 추가
            }
        }
        int cnt = 0;
        vector<int> res;
        while (!q.empty()){
            int course = q.front();
            q.pop();
            res.push_back(course);
            cnt++;
            for (int i : graph[course]){
                indegree[i]--;
                if (indegree[i] == 0){
                    q.push(i);
                }
            }
        }
        if (numCourses == cnt) {
            return res;
        }
        return {};
    }
};

// ── 놀이터. 테스트에서 include 할 때는 TESTING 이 정의돼 이 블록이 빠진다. ──
#ifndef TESTING
static void print(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << (i ? "," : "") << v[i];
    cout << "]\n";
}

int main() {
    Solution s;

    vector<vector<int>> a{{1, 0}};
    print(s.findOrder(2, a));                       // [0,1]

    vector<vector<int>> b{{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    print(s.findOrder(4, b));                       // [0,1,2,3] 또는 [0,2,1,3]

    vector<vector<int>> c{};
    print(s.findOrder(1, c));                       // [0]

    vector<vector<int>> d{{1, 0}, {0, 1}};
    print(s.findOrder(2, d));                       // [] (불가능)
}
#endif
