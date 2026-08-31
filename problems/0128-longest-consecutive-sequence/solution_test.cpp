// 128. Longest Consecutive Sequence 테스트
//   make test  DIR=problems/0128-longest-consecutive-sequence
//   make check DIR=problems/0128-longest-consecutive-sequence
#include <bits/stdc++.h>   // 첫 줄이어야 미리 컴파일된 헤더(make pch)가 쓰인다
#define TESTING
#include "solution.cpp"

static int failed = 0;

static string show(const vector<int>& v, size_t limit = 12) {
    string s = "[";
    for (size_t i = 0; i < v.size() && i < limit; i++) { if (i) s += ","; s += to_string(v[i]); }
    if (v.size() > limit) s += ",...(" + to_string(v.size()) + "개)";
    return s + "]";
}

// 참조 구현: 값을 정렬해 중복을 걷어낸 뒤 이웃끼리 이어지는 최대 길이를 센다.
// 해시 집합을 쓰는 방식과 구조가 달라 풀이의 힌트가 되지 않는다.
static int reference(vector<int> a) {
    if (a.empty()) return 0;
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    int best = 1, cur = 1;
    for (size_t i = 1; i < a.size(); i++) {
        if (a[i] == a[i-1] + 1) cur++;
        else cur = 1;
        if (cur > best) best = cur;
    }
    return best;
}

static void expectEq(vector<int> nums, int want, const string& label) {
    Solution sol;
    vector<int> copy = nums;                 // 풀이가 입력을 바꿔도 원본을 남긴다
    int got = sol.longestConsecutive(copy);
    if (got != want) {
        cout << "✗ " << label << " " << show(nums)
             << "\n    기대: " << want << "\n    실제: " << got << "\n";
        failed++;
    } else {
        cout << "✓ " << label << " " << show(nums) << " -> " << got << "\n";
    }
}

int main() {
    // 1) 예제 + 엣지
    expectEq({100,4,200,1,3,2}, 4, "예제1");
    expectEq({0,3,7,2,5,8,4,6,0,1}, 9, "예제2(중복 포함)");
    expectEq({}, 0, "빈 배열");
    expectEq({1}, 1, "원소 하나");
    expectEq({1,1,1}, 1, "전부 같은 값");
    expectEq({1,2,0,1}, 3, "중복이 섞인 짧은 수열");
    expectEq({-1,0,1}, 3, "음수를 건너 0 을 지남");
    expectEq({2,2,3,3,4,4}, 3, "각 값이 두 번씩");
    expectEq({1000000000,-1000000000}, 1, "제약 양끝 값");
    expectEq({1,3,5,7}, 1, "이어지는 게 없음");
    expectEq({5,4,3,2,1}, 5, "역순으로 들어온 하나의 수열");
    expectEq({9,1,4,7,3,-1,0,5,8,-1,6}, 7, "흩어진 수열");

    // 2) 무작위 + 참조 구현 대조
    {
        mt19937 rng(128);
        bool ok = true;
        for (int it = 0; it < 1000 && ok; it++) {
            int n = (int)(rng() % 25);
            int span = 5 + (int)(rng() % 20);        // 값 범위를 좁혀 수열이 자주 생기게
            vector<int> a(n);
            for (int& x : a) x = (int)(rng() % span) - (int)(span / 2);

            Solution sol;
            vector<int> copy = a;
            int got = sol.longestConsecutive(copy);
            int want = reference(a);
            if (got != want) {
                cout << "✗ 랜덤 " << show(a) << "\n    기대: " << want
                     << "\n    실제: " << got << "\n";
                failed++; ok = false;
            }
        }
        if (ok) cout << "✓ 무작위 1000건 (참조 구현과 대조)\n";
    }

    // 3) 음수/큰 값이 섞인 무작위
    {
        mt19937 rng(1280);
        bool ok = true;
        for (int it = 0; it < 300 && ok; it++) {
            int n = (int)(rng() % 40);
            vector<int> a(n);
            for (int& x : a) {
                if (rng() % 2) x = (int)(rng() % 30) - 15;              // 촘촘한 구간
                else x = (int)(rng() % 2000000000) - 1000000000;        // 흩어진 큰 값
            }
            Solution sol;
            vector<int> copy = a;
            int got = sol.longestConsecutive(copy);
            int want = reference(a);
            if (got != want) {
                cout << "✗ 큰 값 섞인 랜덤 " << show(a) << "\n    기대: " << want
                     << "\n    실제: " << got << "\n";
                failed++; ok = false;
            }
        }
        if (ok) cout << "✓ 음수·큰 값 섞인 무작위 300건\n";
    }

    // 4) 성능
    //    최악은 1..n 을 섞어놓은 배열 — 전체가 하나의 긴 수열이다.
    //    실측 (n=10^5):
    //      집합 + 시작점 검사        6.24ms
    //      정렬 후 훑기              4.33ms
    //      집합만 (시작점 검사 없음) 15,357ms
    //    200ms 면 정렬 방식까지 통과하고, 같은 수열을 매번 다시 걷는 풀이만 걸린다.
#ifndef NO_TIMING
    {
        const int n = 100000;
        vector<int> big(n);
        iota(big.begin(), big.end(), 1);
        mt19937 rng(1281);
        shuffle(big.begin(), big.end(), rng);

        Solution sol;
        vector<int> copy = big;
        auto st = chrono::steady_clock::now();
        int got = sol.longestConsecutive(copy);
        auto el = chrono::duration_cast<chrono::milliseconds>(
                      chrono::steady_clock::now() - st).count();

        if (got != n) {
            cout << "✗ 1..n 을 섞은 배열이면 답이 " << n << " 이어야 하는데 " << got << "\n";
            failed++;
        } else if (el > 200) {
            cout << "✗ n=" << n << " 이 " << el
                 << "ms — 너무 느림 (같은 수열을 여러 번 다시 걷고 있을 가능성)\n";
            failed++;
        } else {
            cout << "✓ 성능 n=" << n << " " << el << "ms (전체가 하나의 수열)\n";
        }
    }

    // 5) 중복이 많은 최악 케이스
    //    같은 값이 수만 번 반복되는데 그 값이 긴 수열의 시작점이면,
    //    **원본 배열을 순회하는 풀이**는 같은 수열을 중복 횟수만큼 다시 걷는다.
    //    실측 (n=10^5, 값 1 이 5만 번 + 2..50000):
    //      집합을 순회하는 풀이      2ms
    //      원본 배열을 순회하는 풀이 5,501ms
    //    200ms 로 잡는다.
    {
        const int half = 50000;
        vector<int> a;
        a.reserve(half * 2);
        for (int i = 0; i < half; i++) a.push_back(1);          // 같은 값이 5만 번
        for (int v = 2; v <= half; v++) a.push_back(v);         // 그 값에서 시작하는 긴 수열

        Solution sol;
        vector<int> copy = a;
        auto st = chrono::steady_clock::now();
        int got = sol.longestConsecutive(copy);
        auto el = chrono::duration_cast<chrono::milliseconds>(
                      chrono::steady_clock::now() - st).count();

        if (got != half) {
            cout << "✗ 중복 많은 케이스 답이 틀림 — 기대 " << half << ", 실제 " << got << "\n";
            failed++;
        } else if (el > 200) {
            cout << "✗ 중복 많은 케이스가 " << el << "ms — 너무 느림 "
                    "(같은 값을 만날 때마다 수열을 다시 걷고 있을 가능성)\n";
            failed++;
        } else {
            cout << "✓ 중복 많은 케이스 " << el << "ms (같은 값 " << half << "번 반복)\n";
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
