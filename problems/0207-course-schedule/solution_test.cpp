// 207. Course Schedule 테스트 — 외부 라이브러리 없이 g++ 만으로 돈다.
//   make test  DIR=problems/0207-course-schedule
//   make check DIR=problems/0207-course-schedule
#include <bits/stdc++.h>   // 첫 줄이어야 미리 컴파일된 헤더(make pch)가 쓰인다
#define TESTING
#include "solution.cpp"

static int failed = 0;

static string show(const vector<vector<int>>& pre, size_t limit = 10) {
    string s = "[";
    for (size_t i = 0; i < pre.size() && i < limit; i++) {
        if (i) s += ",";
        s += "[" + to_string(pre[i][0]) + "," + to_string(pre[i][1]) + "]";
    }
    if (pre.size() > limit) s += ",...(" + to_string(pre.size()) + "개)";
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

static void expectEq(int n, vector<vector<int>> pre, bool want, const string& label) {
    Solution sol;
    vector<vector<int>> copy = pre;          // 풀이가 입력을 바꿔도 원본을 남겨둔다
    bool got = sol.canFinish(n, copy);
    if (got != want) {
        cout << "✗ " << label << " n=" << n << " pre=" << show(pre)
             << "\n    기대: " << boolalpha << want << "\n    실제: " << got << "\n";
        failed++;
        return;
    }
    cout << "✓ " << label << " n=" << n << " pre=" << show(pre) << " -> " << boolalpha << got << "\n";
}

int main() {
    // 1) 예제 + 엣지 케이스
    expectEq(2, {{1,0}},                 true,  "예제1");
    expectEq(2, {{1,0},{0,1}},           false, "예제2(서로를 요구)");
    expectEq(1, {},                      true,  "과목 하나, 선수과목 없음");
    expectEq(5, {},                      true,  "선수과목이 하나도 없음");
    expectEq(4, {{1,0},{2,1},{3,2}},     true,  "일자 사슬");
    expectEq(4, {{1,0},{2,1},{3,2},{1,3}}, false, "사슬이 닫힘");
    expectEq(3, {{0,1},{0,2},{1,2}},     true,  "다이아몬드(사이클 아님)");
    expectEq(3, {{1,0},{1,0},{2,1}},     true,  "같은 쌍이 두 번");
    expectEq(5, {{1,4},{2,4},{3,1},{3,2}}, true, "여러 갈래가 합쳐짐");
    expectEq(20,{{0,10},{3,18},{5,5}},   false, "자기 자신이 선수과목");
    expectEq(4, {{1,0},{3,2}},           true,  "연결 안 된 두 덩어리");
    expectEq(4, {{1,0},{0,1},{3,2}},     false, "한쪽 덩어리에만 사이클");

    // 2) 무작위 그래프 + 참조 구현 대조
    {
        Solution sol;
        mt19937 rng(207);
        bool ok = true;
        for (int it = 0; it < 500 && ok; it++) {
            int n = 1 + (int)(rng() % 12);
            int m = (int)(rng() % 20);
            vector<vector<int>> pre;
            set<pair<int,int>> seen;
            for (int i = 0; i < m; i++) {
                int a = (int)(rng() % n), b = (int)(rng() % n);
                if (seen.insert({a,b}).second) pre.push_back({a,b});  // 제약: 쌍은 유일
            }
            vector<vector<int>> copy = pre;
            bool got = sol.canFinish(n, copy);
            bool want = !hasCycle(n, pre);
            if (got != want) {
                cout << "✗ 랜덤 불일치 n=" << n << " pre=" << show(pre)
                     << "\n    기대: " << boolalpha << want << "\n    실제: " << got << "\n";
                failed++; ok = false;
            }
        }
        if (ok) cout << "✓ 무작위 그래프 500건 (참조 구현과 대조)\n";
    }

    // 3) 반드시 true 인 그래프 — 번호가 커지는 방향으로만 간선을 놓으면 사이클이 못 생긴다
    {
        Solution sol;
        mt19937 rng(2070);
        bool ok = true;
        for (int it = 0; it < 300 && ok; it++) {
            int n = 2 + (int)(rng() % 30);
            vector<int> perm(n);
            for (int i = 0; i < n; i++) perm[i] = i;
            shuffle(perm.begin(), perm.end(), rng);       // 번호를 섞어 순서를 감춘다
            vector<vector<int>> pre;
            set<pair<int,int>> seen;
            int m = (int)(rng() % (n * 2));
            for (int i = 0; i < m; i++) {
                int x = (int)(rng() % n), y = (int)(rng() % n);
                if (x == y) continue;
                int lo = min(x,y), hi = max(x,y);
                if (seen.insert({perm[hi], perm[lo]}).second) pre.push_back({perm[hi], perm[lo]});
            }
            vector<vector<int>> copy = pre;
            if (!sol.canFinish(n, copy)) {
                cout << "✗ 사이클이 없는데 false 를 냈다 n=" << n << " pre=" << show(pre) << "\n";
                failed++; ok = false;
            }
        }
        if (ok) cout << "✓ 사이클 없는 그래프 300건 (전부 true 여야 함)\n";
    }

    // 4) 반드시 false 인 그래프 — 사이클을 일부러 심는다
    {
        Solution sol;
        mt19937 rng(2071);
        bool ok = true;
        for (int it = 0; it < 300 && ok; it++) {
            int n = 3 + (int)(rng() % 30);
            vector<int> perm(n);
            for (int i = 0; i < n; i++) perm[i] = i;
            shuffle(perm.begin(), perm.end(), rng);
            vector<vector<int>> pre;
            set<pair<int,int>> seen;
            int m = (int)(rng() % (n * 2));
            for (int i = 0; i < m; i++) {
                int x = (int)(rng() % n), y = (int)(rng() % n);
                if (x == y) continue;
                int lo = min(x,y), hi = max(x,y);
                if (seen.insert({perm[hi], perm[lo]}).second) pre.push_back({perm[hi], perm[lo]});
            }
            // 길이 len 짜리 사이클을 심는다. perm 의 앞 len 개를 고리로 잇는다.
            int len = 2 + (int)(rng() % (min(n, 6) - 1));
            for (int i = 0; i < len; i++) {
                int from = perm[i], to = perm[(i + 1) % len];
                if (seen.insert({to, from}).second) pre.push_back({to, from});
            }
            for (auto& e : pre)
                if (e[0] < 0 || e[0] >= n || e[1] < 0 || e[1] >= n) {
                    cout << "✗ 테스트 생성기 오류: 범위 밖 과목 번호 n=" << n
                         << " pre=" << show(pre) << "\n";
                    failed++; ok = false; break;
                }
            if (!ok) break;
            if (!hasCycle(n, pre)) {
                cout << "✗ 테스트 생성기 오류: 사이클을 심었는데 참조가 true n=" << n
                     << " pre=" << show(pre) << "\n";
                failed++; ok = false; break;
            }
            vector<vector<int>> copy = pre;
            if (sol.canFinish(n, copy)) {
                cout << "✗ 사이클이 있는데 true 를 냈다 n=" << n << " pre=" << show(pre) << "\n";
                failed++; ok = false;
            }
        }
        if (ok) cout << "✓ 사이클 있는 그래프 300건 (전부 false 여야 함)\n";
    }

    // 5) 성능 게이트
    //
    //    이 문제는 제약 상한(n=2000, 간선 5000)에서도 정답 풀이가 0.36ms 라
    //    **거기서는 느린 풀이를 시간으로 거를 수 없다.**
    //    대신 층층이 촘촘한 DAG 를 주면 경로 수가 폭발한다.
    //    같은 정점을 여러 번 다시 타는 풀이(방문 기록을 정점마다 새로 만드는 등)가 여기서 걸린다.
    //
    //    실측 (16층 x 3, n=48, 간선 135 — 제약 안에 있다):
    //      한 번 본 정점을 기억하는 풀이   0.003ms
    //      시작점마다 다시 훑는 풀이      363ms
    //    100ms 면 정답 대비 3만배 여유, 느린 풀이보다 3.6배 아래라 양쪽 다 안전하다.
#ifndef NO_TIMING
    {
        Solution sol;
        const int layers = 16, w = 3, n = layers * w;
        vector<vector<int>> pre;
        for (int L = 0; L + 1 < layers; L++)
            for (int a = 0; a < w; a++)
                for (int b = 0; b < w; b++)
                    pre.push_back({(L+1)*w + b, L*w + a});

        vector<vector<int>> copy = pre;
        auto st = chrono::steady_clock::now();
        bool got = sol.canFinish(n, copy);
        auto el = chrono::duration_cast<chrono::milliseconds>(
                      chrono::steady_clock::now() - st).count();

        if (!got) {
            cout << "✗ 층층이 쌓인 DAG 는 사이클이 없으므로 true 여야 한다\n";
            failed++;
        } else if (el > 100) {
            cout << "✗ 성능: " << el << "ms — 너무 느림 "
                    "(같은 정점을 여러 번 다시 타고 있을 가능성)\n";
            failed++;
        } else {
            cout << "✓ 성능 " << el << "ms (16층 x 3, n=" << n << ", 간선 " << pre.size() << ")\n";
        }
    }

    // 제약 상한도 한 번 돌려본다 (재귀 풀이의 스택 깊이 확인 겸)
    {
        Solution sol;
        const int n = 2000;
        vector<vector<int>> pre;
        for (int i = 0; i + 1 < n; i++) pre.push_back({i + 1, i});   // 길이 2000 사슬
        vector<vector<int>> copy = pre;
        auto st = chrono::steady_clock::now();
        bool got = sol.canFinish(n, copy);
        auto el = chrono::duration_cast<chrono::milliseconds>(
                      chrono::steady_clock::now() - st).count();
        if (!got) {
            cout << "✗ 길이 " << n << " 일자 사슬은 true 여야 한다\n";
            failed++;
        } else if (el > 100) {
            cout << "✗ 제약 상한 사슬이 " << el << "ms — 너무 느림\n";
            failed++;
        } else {
            cout << "✓ 제약 상한 사슬 n=" << n << " " << el << "ms\n";
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
