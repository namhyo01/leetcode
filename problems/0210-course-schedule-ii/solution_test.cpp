// 210. Course Schedule II 테스트
//   make test  DIR=problems/0210-course-schedule-ii
//   make check DIR=problems/0210-course-schedule-ii
//
// 이 문제는 **정답이 하나가 아니다** ("return any of them").
// 그래서 기댓값과 비교하지 않고, 돌려받은 순서가 실제로 유효한지 검증한다.
#include <bits/stdc++.h>   // 첫 줄이어야 미리 컴파일된 헤더(make pch)가 쓰인다
#define TESTING
#include "solution.cpp"

static int failed = 0;

static string show(const vector<int>& v, size_t limit = 15) {
    string s = "[";
    for (size_t i = 0; i < v.size() && i < limit; i++) { if (i) s += ","; s += to_string(v[i]); }
    if (v.size() > limit) s += ",...(" + to_string(v.size()) + "개)";
    return s + "]";
}
static string showPre(const vector<vector<int>>& p, size_t limit = 10) {
    string s = "[";
    for (size_t i = 0; i < p.size() && i < limit; i++) {
        if (i) s += ",";
        s += "[" + to_string(p[i][0]) + "," + to_string(p[i][1]) + "]";
    }
    if (p.size() > limit) s += ",...(" + to_string(p.size()) + "개)";
    return s + "]";
}

// 참조 구현: 도달 가능성 행렬을 채워서 자기 자신으로 돌아오는 정점이 있는지 본다.
// 위상정렬과 구조가 전혀 다르므로 풀이의 힌트가 되지 않는다. 작은 n 전용 (O(n^3)).
static bool hasCycle(int n, const vector<vector<int>>& pre) {
    vector<vector<char>> reach(n, vector<char>(n, 0));
    for (auto& p : pre) reach[p[1]][p[0]] = 1;          // b -> a
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (reach[i][k])
                for (int j = 0; j < n; j++)
                    if (reach[k][j]) reach[i][j] = 1;
    for (int i = 0; i < n; i++) if (reach[i][i]) return true;
    return false;
}

// 돌려받은 순서가 유효한 위상정렬인지 검사한다. 문제가 있으면 사유를 돌려준다.
// possible: 완주 가능 여부를 이미 알고 있으면 넘긴다 (-1 이면 여기서 판정).
// 큰 입력에서는 O(n^3) 판정을 돌릴 수 없으므로 생성 방식으로 아는 값을 넘긴다.
static string validate(int n, const vector<vector<int>>& pre, const vector<int>& order,
                       int possible = -1) {
    bool can = (possible >= 0) ? (bool)possible : !hasCycle(n, pre);
    if (!can)
        return order.empty() ? "" : "완주 불가능한데 빈 배열이 아니다";

    if ((int)order.size() != n)
        return "길이가 " + to_string(order.size()) + " (기대 " + to_string(n) + ")";

    vector<int> pos(n, -1);
    for (int i = 0; i < n; i++) {
        int c = order[i];
        if (c < 0 || c >= n) return "범위 밖 과목 번호 " + to_string(c);
        if (pos[c] != -1) return "과목 " + to_string(c) + " 가 두 번 나온다";
        pos[c] = i;
    }
    for (auto& p : pre)
        if (pos[p[1]] > pos[p[0]])
            return "선수과목 위반: " + to_string(p[1]) + " 을(를) " + to_string(p[0])
                 + " 보다 먼저 들어야 하는데 뒤에 있다";
    return "";
}

static void check(int n, vector<vector<int>> pre, const string& label) {
    Solution sol;
    vector<vector<int>> copy = pre;
    vector<int> got = sol.findOrder(n, copy);
    string err = validate(n, pre, got);
    if (!err.empty()) {
        cout << "✗ " << label << " n=" << n << " pre=" << showPre(pre)
             << "\n    받은 순서: " << show(got) << "\n    문제: " << err << "\n";
        failed++;
    } else {
        cout << "✓ " << label << " n=" << n << " -> " << show(got) << "\n";
    }
}

int main() {
    // 1) 예제 + 엣지
    check(2, {{1,0}},                       "예제1");
    check(4, {{1,0},{2,0},{3,1},{3,2}},     "예제2(정답 여러 개)");
    check(1, {},                            "예제3(과목 하나)");
    check(3, {},                            "선수과목 없음");
    check(2, {{1,0},{0,1}},                 "불가능(서로를 요구)");
    check(4, {{1,0},{2,1},{3,2},{1,3}},     "불가능(사슬이 닫힘)");
    check(4, {{1,0},{2,1},{3,2}},           "일자 사슬");
    check(4, {{1,0},{3,2}},                 "끊긴 두 덩어리");
    check(5, {{1,4},{2,4},{3,1},{3,2}},     "여러 갈래가 합쳐짐");
    check(6, {{1,0},{2,0},{3,1},{4,2},{5,3},{5,4}}, "다이아몬드");

    // 2) 무작위 그래프 — 가능/불가능 섞어서
    {
        mt19937 rng(210);
        bool ok = true;
        for (int it = 0; it < 500 && ok; it++) {
            int n = 1 + (int)(rng() % 12);
            int m = (int)(rng() % 20);
            vector<vector<int>> pre;
            set<pair<int,int>> seen;
            for (int i = 0; i < m; i++) {
                int a = (int)(rng() % n), b = (int)(rng() % n);
                if (a == b) continue;                       // 제약: ai != bi
                if (seen.insert({a,b}).second) pre.push_back({a,b});
            }
            Solution sol;
            vector<vector<int>> copy = pre;
            vector<int> got = sol.findOrder(n, copy);
            string err = validate(n, pre, got);
            if (!err.empty()) {
                cout << "✗ 랜덤 n=" << n << " pre=" << showPre(pre)
                     << "\n    받은 순서: " << show(got) << "\n    문제: " << err << "\n";
                failed++; ok = false;
            }
        }
        if (ok) cout << "✓ 무작위 그래프 500건 (순서가 유효한지 검증)\n";
    }

    // 3) 반드시 가능한 그래프 — 번호가 커지는 방향으로만 간선을 놓고 번호를 섞는다
    {
        mt19937 rng(2100);
        bool ok = true;
        for (int it = 0; it < 300 && ok; it++) {
            int n = 2 + (int)(rng() % 40);
            vector<int> perm(n);
            for (int i = 0; i < n; i++) perm[i] = i;
            shuffle(perm.begin(), perm.end(), rng);
            vector<vector<int>> pre;
            set<pair<int,int>> seen;
            int m = (int)(rng() % (n * 3));
            for (int i = 0; i < m; i++) {
                int x = (int)(rng() % n), y = (int)(rng() % n);
                if (x == y) continue;
                int lo = min(x,y), hi = max(x,y);
                if (seen.insert({perm[hi], perm[lo]}).second) pre.push_back({perm[hi], perm[lo]});
            }
            Solution sol;
            vector<vector<int>> copy = pre;
            vector<int> got = sol.findOrder(n, copy);
            if (got.empty()) {
                cout << "✗ 사이클이 없는데 빈 배열을 냈다 n=" << n << " pre=" << showPre(pre) << "\n";
                failed++; ok = false;
                continue;
            }
            string err = validate(n, pre, got);
            if (!err.empty()) {
                cout << "✗ n=" << n << " pre=" << showPre(pre)
                     << "\n    받은 순서: " << show(got) << "\n    문제: " << err << "\n";
                failed++; ok = false;
            }
        }
        if (ok) cout << "✓ 사이클 없는 그래프 300건 (전부 유효한 순서를 내야 함)\n";
    }

    // 4) 성능 — 제약 상한은 간선이 400만까지 온다. n=2000, 간선 50만으로 본다.
    //    임계값은 넉넉하게 1초. O(V+E) 면 여유롭게 통과한다.
#ifndef NO_TIMING
    {
        const int n = 2000, target = 500000;
        vector<vector<int>> pre;
        pre.reserve(target);
        mt19937 rng(21000);
        set<pair<int,int>> seen;
        int guard = 0;
        while ((int)pre.size() < target && guard++ < target * 4) {
            int a = (int)(rng() % n), b = (int)(rng() % n);
            if (a == b) continue;
            int hi = max(a,b), lo = min(a,b);              // 번호가 커지는 방향 = 사이클 없음
            if (seen.insert({hi,lo}).second) pre.push_back({hi,lo});
        }
        Solution sol;
        vector<vector<int>> copy = pre;
        auto st = chrono::steady_clock::now();
        vector<int> got = sol.findOrder(n, copy);
        auto el = chrono::duration_cast<chrono::milliseconds>(
                      chrono::steady_clock::now() - st).count();

        string err = validate(n, pre, got, 1);   // 사이클 없게 만들었다
        if (!err.empty()) {
            cout << "✗ 대규모 입력 실패 (n=" << n << ", 간선 " << pre.size() << "): " << err << "\n";
            failed++;
        } else if (el > 1000) {
            cout << "✗ n=" << n << " 간선 " << pre.size() << " 이 " << el << "ms — 너무 느림\n";
            failed++;
        } else {
            cout << "✓ 대규모 입력 n=" << n << " 간선 " << pre.size() << " " << el << "ms\n";
        }
    }
#endif
#ifdef NO_TIMING
    cout << "· 성능 체크는 이 빌드에서 생략됨 (새니타이저는 느려서 측정이 무의미하다)\n"
            "  복잡도 확인은 `make test` 로 해야 한다\n";
#endif

    cout << "\n" << (failed ? "실패 " + to_string(failed) + "건" : "전체 통과 🎉") << "\n";
    return failed ? 1 : 0;
}
