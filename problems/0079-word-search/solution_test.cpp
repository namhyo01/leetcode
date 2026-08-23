// 79. Word Search 테스트 — 외부 라이브러리 없이 g++ 만으로 돈다.
//   make test  DIR=problems/0079-word-search
//   make check DIR=problems/0079-word-search
#include <bits/stdc++.h>   // 첫 줄이어야 미리 컴파일된 헤더(make pch)가 쓰인다
#define TESTING
#include "solution.cpp"

static int failed = 0;

static string showBoard(const vector<vector<char>>& b) {
    string s;
    for (auto& row : b) { s += "\n      "; for (char c : row) { s += c; s += ' '; } }
    return s;
}

// 참조 구현: (칸, 방문 비트마스크, 진행 위치) 상태를 큐로 훑는다.
// 재귀 백트래킹과 구조가 달라서 같은 버그를 공유하지 않는다. 작은 보드 전용.
static bool referenceExist(const vector<vector<char>>& b, const string& w) {
    int m = b.size(), n = b[0].size();
    if (m * n > 16) return false;                 // 비트마스크 한계
    struct State { int cell; int mask; int k; };
    auto key = [&](State s) { return ((long long)s.cell * 65536 + s.mask) * 32 + s.k; };
    set<long long> seen;
    deque<State> q;
    for (int i = 0; i < m * n; i++)
        if (b[i / n][i % n] == w[0]) {
            State s{i, 1 << i, 1};
            if (seen.insert(key(s)).second) q.push_back(s);
        }
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    while (!q.empty()) {
        State s = q.front(); q.pop_front();
        if (s.k == (int)w.size()) return true;
        int r = s.cell / n, c = s.cell % n;
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
            int ni = nr * n + nc;
            if (s.mask & (1 << ni)) continue;      // 이미 쓴 칸
            if (b[nr][nc] != w[s.k]) continue;
            State t{ni, s.mask | (1 << ni), s.k + 1};
            if (seen.insert(key(t)).second) q.push_back(t);
        }
    }
    return false;
}

static void expectEq(vector<vector<char>> board, string word, bool want, const string& label) {
    Solution sol;
    vector<vector<char>> copy = board;      // 풀이가 보드를 바꿔도 원본을 남겨둔다
    bool got = sol.exist(copy, word);
    if (got != want) {
        cout << "✗ " << label << " word=\"" << word << "\"" << showBoard(board)
             << "\n    기대: " << boolalpha << want << "\n    실제: " << got << "\n";
        failed++;
        return;
    }
    // 보드를 되돌려놓지 않으면 호출자 입장에서 부작용이 된다
    if (copy != board) {
        cout << "✗ " << label << " word=\"" << word
             << "\" — 보드가 변형된 채로 남았다 (표시한 칸을 되돌리지 않았다)"
             << showBoard(copy) << "\n";
        failed++;
        return;
    }
    cout << "✓ " << label << " word=\"" << word << "\" -> " << boolalpha << got << "\n";
}

int main() {
    vector<vector<char>> ex = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'},
    };

    // 1) 예제 + 엣지 케이스
    expectEq(ex, "ABCCED", true,  "예제1");
    expectEq(ex, "SEE",    true,  "예제2");
    expectEq(ex, "ABCB",   false, "예제3(같은 칸 재사용 금지)");
    expectEq(ex, "A",      true,  "한 글자");
    expectEq(ex, "Z",      false, "보드에 없는 글자");
    expectEq(ex, "ASA",    true,  "위아래로 꺾기");
    expectEq(ex, "ABCESEEEFS",   false, "긴 단어(불가)");
    expectEq(ex, "ABCEFSADEESE", false, "보드 전체를 훑는 경로");
    expectEq({{'a'}},     "a",   true,  "1x1 일치");
    expectEq({{'a'}},     "b",   false, "1x1 불일치");
    expectEq({{'a','b'}}, "ba",  true,  "1x2 역방향");
    expectEq({{'a','a'}}, "aaa", false, "칸보다 단어가 길다");

    // 2) 무작위 보드 + 참조 구현 대조 (작은 보드 전용)
    {
        Solution sol;
        mt19937 rng(79);
        bool ok = true;
        for (int it = 0; it < 400 && ok; it++) {
            int m = 1 + (int)(rng() % 4), n = 1 + (int)(rng() % 4);
            int alpha = 2 + (int)(rng() % 3);          // 글자 종류를 좁혀 충돌을 늘린다
            vector<vector<char>> b(m, vector<char>(n));
            for (auto& row : b) for (char& c : row) c = 'a' + (char)(rng() % alpha);
            int len = 1 + (int)(rng() % 6);
            string w;
            for (int i = 0; i < len; i++) w += 'a' + (char)(rng() % alpha);

            vector<vector<char>> copy = b;
            bool got = sol.exist(copy, w);
            bool want = referenceExist(b, w);
            if (got != want) {
                cout << "✗ 랜덤 불일치 word=\"" << w << "\"" << showBoard(b)
                     << "\n    기대: " << boolalpha << want << "\n    실제: " << got << "\n";
                failed++; ok = false;
            } else if (copy != b) {
                cout << "✗ 랜덤: 보드가 변형된 채로 남았다 word=\"" << w << "\""
                     << showBoard(b) << "\n";
                failed++; ok = false;
            }
        }
        if (ok) cout << "✓ 무작위 보드 400건 (참조 구현과 대조)\n";
    }

    // 3) 반드시 찾을 수 있는 단어 — 실제 경로를 걸어서 만든다
    {
        Solution sol;
        mt19937 rng(790);
        bool ok = true;
        const int dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1};
        for (int it = 0; it < 300 && ok; it++) {
            int m = 2 + (int)(rng() % 5), n = 2 + (int)(rng() % 5);
            vector<vector<char>> b(m, vector<char>(n));
            for (auto& row : b) for (char& c : row) c = 'a' + (char)(rng() % 6);

            int r = (int)(rng() % m), c = (int)(rng() % n);
            vector<vector<bool>> used(m, vector<bool>(n, false));
            used[r][c] = true;
            string w(1, b[r][c]);
            int want = 1 + (int)(rng() % 14);
            while ((int)w.size() < want) {
                vector<int> cand;
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr>=0 && nr<m && nc>=0 && nc<n && !used[nr][nc]) cand.push_back(d);
                }
                if (cand.empty()) break;
                int d = cand[rng() % cand.size()];
                r += dr[d]; c += dc[d];
                used[r][c] = true;
                w += b[r][c];
            }

            vector<vector<char>> copy = b;
            if (!sol.exist(copy, w)) {
                cout << "✗ 실제로 존재하는 경로를 못 찾음 word=\"" << w << "\""
                     << showBoard(b) << "\n";
                failed++; ok = false;
            }
        }
        if (ok) cout << "✓ 경로를 직접 걸어 만든 단어 300건 (전부 true 여야 함)\n";
    }

    // 4) 최악 케이스 성능
    //
    //    임계값은 실측으로 정했다 (6x6 전부 'a', word = 14*'a' + 'b', 답 false):
    //      표시하고 되돌리기      23ms
    //      재귀마다 보드 복사    860ms
    //    300ms 면 정답 대비 13배 여유, 느린 풀이보다 2.9배 아래라 양쪽 다 안전하다.
#ifndef NO_TIMING
    {
        Solution sol;
        vector<vector<char>> worst(6, vector<char>(6, 'a'));
        string w(14, 'a'); w += 'b';

        vector<vector<char>> copy = worst;
        auto st = chrono::steady_clock::now();
        bool got = sol.exist(copy, w);
        auto el = chrono::duration_cast<chrono::milliseconds>(
                      chrono::steady_clock::now() - st).count();

        if (got) {
            cout << "✗ 최악 케이스 답이 틀림 — 'b' 는 보드에 없으므로 false 여야 한다\n";
            failed++;
        } else if (el > 300) {
            cout << "✗ 최악 케이스가 " << el << "ms — 너무 느림 "
                    "(재귀마다 보드를 복사하고 있을 가능성)\n";
            failed++;
        } else {
            cout << "✓ 최악 케이스 성능 " << el << "ms (6x6 전부 'a')\n";
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
