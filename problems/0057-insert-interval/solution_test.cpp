// 57. Insert Interval 테스트
//   make test  DIR=problems/0057-insert-interval
//   make check DIR=problems/0057-insert-interval
#include <bits/stdc++.h>   // 첫 줄이어야 미리 컴파일된 헤더(make pch)가 쓰인다
#define TESTING
#include "solution.cpp"

using VV = vector<vector<int>>;
static int failed = 0;

static string show(const VV& v, size_t limit = 10) {
    string s = "[";
    for (size_t i = 0; i < v.size() && i < limit; i++) {
        if (i) s += ",";
        s += "[" + to_string(v[i][0]) + "," + to_string(v[i][1]) + "]";
    }
    if (v.size() > limit) s += ",...(" + to_string(v.size()) + "개)";
    return s + "]";
}

// 참조 구현: 전부 모아놓고 겹치는 쌍을 찾아 합치기를 더 합칠 게 없을 때까지 반복한다.
// O(n^2) 브루트포스라 의도된 풀이가 아니고, 한 번 훑기/정렬 병합 어느 쪽과도 구조가 다르다.
static VV reference(VV v, const vector<int>& ni) {
    v.push_back(ni);
    for (bool changed = true; changed; ) {
        changed = false;
        for (size_t i = 0; i < v.size() && !changed; i++)
            for (size_t j = i + 1; j < v.size() && !changed; j++)
                // [a,b] 와 [c,d] 가 겹친다  <=>  a <= d && c <= b
                if (v[i][0] <= v[j][1] && v[j][0] <= v[i][1]) {
                    v[i][0] = min(v[i][0], v[j][0]);
                    v[i][1] = max(v[i][1], v[j][1]);
                    v.erase(v.begin() + j);
                    changed = true;
                }
    }
    sort(v.begin(), v.end());
    return v;
}

// 반환값이 문제 조건을 지키는지 본다 (정렬됨 + 서로 안 겹침)
static string wellFormed(const VV& v) {
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i].size() != 2) return "구간의 원소가 2개가 아니다";
        if (v[i][0] > v[i][1]) return "시작이 끝보다 크다: " + show({v[i]});
        if (i && v[i-1][0] > v[i][0]) return "시작 기준 정렬이 깨졌다";
        if (i && v[i-1][1] >= v[i][0]) return "인접한 두 구간이 겹치거나 맞닿아 있다: "
                                            + show({v[i-1], v[i]});
    }
    return "";
}

static void expectEq(VV a, vector<int> ni, VV want, const string& label) {
    Solution sol;
    VV ac = a; vector<int> nc = ni;
    VV got = sol.insert(ac, nc);
    string ill = wellFormed(got);
    if (!ill.empty()) {
        cout << "✗ " << label << " " << show(a) << " + [" << ni[0] << "," << ni[1] << "]"
             << "\n    받은 값: " << show(got) << "\n    문제: " << ill << "\n";
        failed++; return;
    }
    if (got != want) {
        cout << "✗ " << label << " " << show(a) << " + [" << ni[0] << "," << ni[1] << "]"
             << "\n    기대: " << show(want) << "\n    실제: " << show(got) << "\n";
        failed++; return;
    }
    cout << "✓ " << label << " " << show(a) << " + [" << ni[0] << "," << ni[1]
         << "] -> " << show(got) << "\n";
}

int main() {
    // 1) 예제 + 엣지
    expectEq({{1,3},{6,9}}, {2,5}, {{1,5},{6,9}}, "예제1");
    expectEq({{1,2},{3,5},{6,7},{8,10},{12,16}}, {4,8}, {{1,2},{3,10},{12,16}}, "예제2");
    expectEq({}, {5,7}, {{5,7}}, "빈 배열");
    expectEq({{1,5}}, {2,3}, {{1,5}}, "새 구간이 완전히 안에");
    expectEq({{1,5}}, {6,8}, {{1,5},{6,8}}, "맞닿지 않고 뒤에");
    expectEq({{1,5}}, {0,0}, {{0,0},{1,5}}, "맞닿지 않고 앞에");
    expectEq({{3,5},{8,10}}, {1,2}, {{1,2},{3,5},{8,10}}, "맨 앞에 삽입");
    expectEq({{3,5},{8,10}}, {11,12}, {{3,5},{8,10},{11,12}}, "맨 뒤에 삽입");
    expectEq({{1,2},{5,6}}, {3,4}, {{1,2},{3,4},{5,6}}, "가운데 빈틈에 삽입");
    expectEq({{1,2},{3,4},{5,6}}, {0,10}, {{0,10}}, "전부 삼킴");
    expectEq({{1,3}}, {3,5}, {{1,5}}, "끝점이 맞닿음(겹침으로 본다)");
    expectEq({{2,4}}, {0,2}, {{0,4}}, "시작점이 맞닿음");
    expectEq({{0,0}}, {0,0}, {{0,0}}, "길이 0 구간");
    expectEq({{1,5}}, {1,5}, {{1,5}}, "완전히 같은 구간");

    // 2) 무작위 + 참조 구현 대조 (참조가 O(n^2) 라 작은 입력만)
    {
        mt19937 rng(57);
        const int MAXC = 60;   // 좌표 상한
        bool ok = true;
        for (int it = 0; it < 800 && ok; it++) {
            // 겹치지 않고 정렬된 구간들을 만든다
            VV a;
            int cur = (int)(rng() % 4);
            while (cur <= MAXC) {
                int len = (int)(rng() % 5);
                if (cur + len > MAXC) break;
                a.push_back({cur, cur + len});
                cur += len + 1 + (int)(rng() % 4);   // 최소 1칸 띄운다
            }
            int s = (int)(rng() % (MAXC + 1));
            int e = min(MAXC, s + (int)(rng() % 15));
            vector<int> ni{s, e};

            Solution sol;
            VV ac = a; vector<int> nc = ni;
            VV got = sol.insert(ac, nc);
            string ill = wellFormed(got);
            VV want = reference(a, ni);
            if (!ill.empty() || got != want) {
                cout << "✗ 랜덤 " << show(a) << " + [" << ni[0] << "," << ni[1] << "]"
                     << "\n    기대: " << show(want) << "\n    실제: " << show(got);
                if (!ill.empty()) cout << "\n    문제: " << ill;
                cout << "\n";
                failed++; ok = false;
            }
        }
        if (ok) cout << "✓ 무작위 800건 (참조 구현과 대조)\n";
    }

    // 3) 성능
    //    실측 (n=10^4, 새 구간이 전부를 삼키는 최악 모양):
    //      한 번 훑기      0.205ms
    //      정렬 후 병합    0.910ms
    //      O(n^2) 형태    33.687ms
    //    10ms 면 정렬 방식까지는 통과하고 O(n^2) 만 걸린다.
#ifndef NO_TIMING
    {
        const int n = 10000;
        VV big; big.reserve(n);
        for (int i = 0; i < n; i++) big.push_back({i * 10, i * 10 + 5});
        vector<int> wide{0, 100000};

        Solution sol;
        VV ac = big; vector<int> nc = wide;
        auto st = chrono::steady_clock::now();
        VV got = sol.insert(ac, nc);
        auto el = chrono::duration_cast<chrono::milliseconds>(
                      chrono::steady_clock::now() - st).count();

        VV want{{0, 100000}};
        if (got != want) {
            cout << "✗ 대규모 입력 답이 틀림 — 기대 [[0,100000]], 실제 " << show(got) << "\n";
            failed++;
        } else if (el > 10) {
            cout << "✗ n=" << n << " 이 " << el << "ms — 너무 느림\n";
            failed++;
        } else {
            cout << "✓ 대규모 입력 n=" << n << " " << el << "ms\n";
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
