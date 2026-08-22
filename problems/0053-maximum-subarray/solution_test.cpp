// 53. Maximum Subarray 테스트 — 외부 라이브러리 없이 g++ 만으로 돈다.
//   make test  DIR=problems/0053-maximum-subarray   (-O2, 성능 게이트 포함)
//   make check DIR=problems/0053-maximum-subarray   (ASan/UBSan, 성능 게이트 제외)
#define TESTING
#include "solution.cpp"

#include <chrono>
#include <iostream>
#include <random>
#include <string>

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

// 참조 구현: 모든 부분배열을 직접 훑는다. 작은 입력 전용.
static int bruteForce(const vector<int>& nums) {
    int best = nums[0];
    for (size_t i = 0; i < nums.size(); i++) {
        int sum = 0;
        for (size_t j = i; j < nums.size(); j++) {
            sum += nums[j];
            if (sum > best) best = sum;
        }
    }
    return best;
}

static void expectEq(vector<int> nums, int want, const string& label) {
    Solution sol;
    vector<int> copy = nums;          // 풀이가 입력을 바꿔도 원본을 남겨둔다
    int got = sol.maxSubArray(copy);
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
    expectEq({-2, 1, -3, 4, -1, 2, 1, -5, 4}, 6, "예제1");
    expectEq({1}, 1, "예제2");
    expectEq({5, 4, -1, 7, 8}, 23, "예제3");
    expectEq({-1}, -1, "원소 하나(음수)");
    expectEq({0}, 0, "원소 하나(0)");
    expectEq({-5}, -5, "원소 하나(최소)");
    expectEq({-2, -1, -3}, -1, "전부 음수");
    expectEq({1, 2, 3, 4}, 10, "전부 양수");
    expectEq({-2, -3, 4, -1, -2, 1, 5, -3}, 7, "섞임");
    expectEq({8, -19, 5, -4, 20}, 21, "가운데를 건너뛰는 게 손해");

    // 2) 참조 구현과 대조하는 랜덤 테스트
    {
        Solution sol;
        mt19937 rng(53);
        bool ok = true;
        for (int it = 0; it < 500; it++) {
            int n = 1 + (int)(rng() % 12);
            vector<int> nums(n);
            for (int& v : nums) v = (int)(rng() % 21) - 10;

            vector<int> copy = nums;
            int got = sol.maxSubArray(copy);
            int want = bruteForce(nums);
            if (got != want) {
                cout << "✗ 랜덤 케이스 실패 " << show(nums)
                     << "\n    기대: " << want << "\n    실제: " << got << "\n";
                failed++;
                ok = false;
                break;
            }
        }
        if (ok) cout << "✓ 랜덤 대조 테스트 500건\n";
    }

    // 3) 전부 음수만 나오는 랜덤 — 0 을 답으로 내보내는 실수를 잡는다
    {
        Solution sol;
        mt19937 rng(531);
        bool ok = true;
        for (int it = 0; it < 200; it++) {
            int n = 1 + (int)(rng() % 10);
            vector<int> nums(n);
            for (int& v : nums) v = -1 - (int)(rng() % 50);

            vector<int> copy = nums;
            int got = sol.maxSubArray(copy);
            int want = bruteForce(nums);
            if (got != want) {
                cout << "✗ 전부 음수 케이스 실패 " << show(nums)
                     << "\n    기대: " << want << "\n    실제: " << got
                     << (got == 0 ? "   (빈 부분배열은 허용되지 않는다)" : "") << "\n";
                failed++;
                ok = false;
                break;
            }
        }
        if (ok) cout << "✓ 전부 음수 랜덤 200건\n";
    }

    // 4) 최대 입력 성능 체크
    //    임계값은 실측으로 정했다 (n=10^5, -O2, 두 풀이의 답이 같은 것도 확인):
    //      모든 부분배열을 훑는 풀이  2,150ms
    //      한 번만 훑는 풀이             0.073ms
    //    50ms 면 정답 대비 685배 여유, 느린 풀이보다 43배 아래라 양쪽 다 안전하다.
#ifndef NO_TIMING
    {
        Solution sol;
        mt19937 rng(100000);
        const int n = 100000;
        vector<int> nums(n);
        for (int& v : nums) v = (int)(rng() % 20001) - 10000;

        vector<int> copy = nums;
        auto st = chrono::steady_clock::now();
        int got = sol.maxSubArray(copy);
        auto el = chrono::duration_cast<chrono::milliseconds>(
                      chrono::steady_clock::now() - st).count();

        if (got < -10000) {
            cout << "✗ n=" << n << " 결과가 이상함: " << got << "\n";
            failed++;
        } else if (el > 50) {
            cout << "✗ n=" << n << " 이 " << el
                 << "ms — 너무 느림 (모든 부분배열을 훑고 있을 가능성)\n";
            failed++;
        } else {
            cout << "✓ n=" << n << " 성능 " << el << "ms\n";
        }
    }
#endif

    cout << "\n" << (failed ? "실패 " + to_string(failed) + "건" : "전체 통과 🎉") << "\n";
    return failed ? 1 : 0;
}
