// 153. Find Minimum in Rotated Sorted Array 테스트 — 외부 라이브러리 없이 g++ 만으로 돈다.
//   make test  DIR=problems/0153-find-minimum-in-rotated-sorted-array
//   make check DIR=problems/0153-find-minimum-in-rotated-sorted-array
#include <bits/stdc++.h>   // 첫 줄이어야 미리 컴파일된 헤더(make pch)가 쓰인다
#define TESTING
#include "solution.cpp"

static int failed = 0;

static string show(const vector<int>& v, size_t limit = 12) {
    string s = "[";
    for (size_t i = 0; i < v.size() && i < limit; i++) {
        if (i) s += ",";
        s += to_string(v[i]);
    }
    if (v.size() > limit) s += ",...(" + to_string(v.size()) + "개)";
    return s + "]";
}

// 정렬된 배열을 k 칸 회전시킨다. 지문의 정의대로
// 1 회전 = [a[n-1], a[0], ..., a[n-2]] 이므로 오른쪽으로 민다.
static vector<int> rotateRight(vector<int> a, int k) {
    int n = (int)a.size();
    k %= n;
    rotate(a.begin(), a.begin() + (n - k) % n, a.end());
    return a;
}

// 입력이 실제로 '정렬 후 회전' 모양인지 확인한다 (테스트 생성기 자체의 검증).
static bool isRotatedSorted(const vector<int>& a) {
    int drops = 0;
    for (size_t i = 1; i < a.size(); i++)
        if (a[i - 1] > a[i]) drops++;
    return drops <= 1;
}

static void expectEq(vector<int> nums, int want, const string& label) {
    Solution sol;
    vector<int> copy = nums;             // 풀이가 입력을 바꿔도 원본을 남겨둔다
    int got = sol.findMin(copy);
    if (got != want) {
        cout << "✗ " << label << " " << show(nums)
             << "\n    기대: " << want << "\n    실제: " << got << "\n";
        failed++;
    } else {
        cout << "✓ " << label << " " << show(nums) << " -> " << got << "\n";
    }
}

int main() {
    // 1) 예제 + 엣지 케이스
    expectEq({3, 4, 5, 1, 2}, 1, "예제1");
    expectEq({4, 5, 6, 7, 0, 1, 2}, 0, "예제2");
    expectEq({11, 13, 15, 17}, 11, "예제3(회전이 안 보이는 입력)");
    expectEq({1}, 1, "원소 하나");
    expectEq({2, 1}, 1, "원소 둘(회전됨)");
    expectEq({1, 2}, 1, "원소 둘(회전 안 보임)");
    expectEq({5, 1, 2, 3, 4}, 1, "최솟값이 두 번째");
    expectEq({2, 3, 4, 5, 1}, 1, "최솟값이 맨 뒤");
    expectEq({3, 1, 2}, 1, "가운데가 최솟값");
    expectEq({-5000, 5000}, -5000, "제약 경계값");

    // 2) 모든 회전량을 전부 확인 — 회전 0(=n)회 포함
    {
        Solution sol;
        bool ok = true;
        for (int n = 1; n <= 60 && ok; n++) {
            vector<int> base(n);
            for (int i = 0; i < n; i++) base[i] = i * 3 - n;   // 서로 다른 값
            for (int k = 0; k < n; k++) {
                vector<int> nums = rotateRight(base, k);
                if (!isRotatedSorted(nums)) {
                    cout << "✗ 테스트 생성기 오류: " << show(nums) << "\n";
                    failed++; ok = false; break;
                }
                vector<int> copy = nums;
                int got = sol.findMin(copy);
                if (got != base[0]) {
                    cout << "✗ 회전 " << k << "회 실패 " << show(nums)
                         << "\n    기대: " << base[0] << "\n    실제: " << got << "\n";
                    failed++; ok = false; break;
                }
            }
        }
        if (ok) cout << "✓ n=1..60 의 모든 회전량 전수 확인\n";
    }

    // 3) 제약 상한 근처 랜덤
    {
        Solution sol;
        mt19937 rng(153);
        bool ok = true;
        for (int it = 0; it < 300; it++) {
            int n = 1 + (int)(rng() % 5000);
            set<int> uniq;
            while ((int)uniq.size() < n) uniq.insert((int)(rng() % 10001) - 5000);
            vector<int> base(uniq.begin(), uniq.end());   // 정렬 + 중복 없음
            vector<int> nums = rotateRight(base, (int)(rng() % n));

            vector<int> copy = nums;
            int got = sol.findMin(copy);
            if (got != base[0]) {
                cout << "✗ 랜덤 실패 (n=" << n << ") " << show(nums)
                     << "\n    기대: " << base[0] << "\n    실제: " << got << "\n";
                failed++; ok = false; break;
            }
        }
        if (ok) cout << "✓ 랜덤 테스트 300건 (n 최대 5000)\n";
    }

    // 4) O(log n) 게이트
    //
    //    이 문제는 제약 상한이 n=5000 이라 **거기서는 시간으로 거를 수 없다.**
    //    실측: n=5000 에서 선형 스캔 0.002ms, 이분 탐색 0.000ms — 구분이 불가능하다.
    //    그래서 제약을 넘는 n=10^7 을 일부러 쓴다. 지문이 O(log n) 을 요구하므로
    //    알고리즘은 이 크기도 감당해야 한다.
    //
    //    실측 (n=10^7):
    //      전부 훑는 풀이  5.087ms
    //      절반씩 줄이는 풀이  0.002ms
    //    1ms 면 정답 대비 500배 여유, 느린 풀이보다 5배 아래라 양쪽 다 안전하다.
#ifndef NO_TIMING
    {
        Solution sol;
        const int n = 10000000;
        vector<int> base(n);
        for (int i = 0; i < n; i++) base[i] = i - n / 2;
        vector<int> nums = rotateRight(base, n / 3);

        auto st = chrono::steady_clock::now();
        int got = sol.findMin(nums);
        auto el = chrono::duration_cast<chrono::microseconds>(
                      chrono::steady_clock::now() - st).count();

        if (got != base[0]) {
            cout << "✗ n=" << n << " 답이 틀림 — 기대 " << base[0] << ", 실제 " << got << "\n";
            failed++;
        } else if (el > 1000) {
            cout << "✗ n=" << n << " 이 " << el / 1000.0
                 << "ms — 너무 느림 (배열을 전부 훑고 있을 가능성)\n";
            failed++;
        } else {
            cout << "✓ n=" << n << " 성능 " << el << "us (O(log n) 확인)\n";
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
