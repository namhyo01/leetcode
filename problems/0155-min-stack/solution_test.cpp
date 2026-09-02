// 155. Min Stack 테스트
//   make test  DIR=problems/0155-min-stack
//   make check DIR=problems/0155-min-stack
//
// 이 문제는 함수 하나가 아니라 **상태를 들고 가는 클래스**다.
// 그래서 입출력 한 쌍을 비교하는 게 아니라 **연산열을 흘려보내며** 매 단계를 대조한다.
#include <bits/stdc++.h>   // 첫 줄이어야 미리 컴파일된 헤더(make pch)가 쓰인다
#define TESTING
#include "solution.cpp"

static int failed = 0;

// 참조 구현: 그냥 배열에 쌓고 getMin 은 매번 훑는다 (O(n)).
// 명백히 의도된 풀이가 아니므로 힌트가 되지 않는다.
struct RefStack {
    vector<int> st;
    void push(int v) { st.push_back(v); }
    void pop() { st.pop_back(); }
    int top() const { return st.back(); }
    int getMin() const { return *min_element(st.begin(), st.end()); }
    bool empty() const { return st.empty(); }
};

// 연산열을 사람이 읽을 수 있게 기록해두고, 실패하면 그대로 출력한다.
struct Trace {
    string s;
    void add(const string& op) { if (!s.empty()) s += " "; s += op; }
};

int main() {
    // 1) 지문의 예제 그대로
    {
        MinStack ms;
        ms.push(-2); ms.push(0); ms.push(-3);
        int g1 = ms.getMin();
        ms.pop();
        int t1 = ms.top();
        int g2 = ms.getMin();
        if (g1 != -3 || t1 != 0 || g2 != -2) {
            cout << "✗ 예제: getMin=" << g1 << " (기대 -3), top=" << t1
                 << " (기대 0), getMin=" << g2 << " (기대 -2)\n";
            failed++;
        } else {
            cout << "✓ 예제\n";
        }
    }

    // 2) 손으로 만든 엣지 케이스
    {
        struct Case { string name; vector<pair<string,int>> ops; vector<int> want; };
        vector<Case> cases = {
            {"같은 값이 최솟값으로 두 번",
             {{"push",1},{"push",1},{"getMin",0},{"pop",0},{"getMin",0}}, {1,1}},
            {"최솟값을 pop 하면 그 다음 최솟값",
             {{"push",5},{"push",2},{"push",7},{"getMin",0},{"pop",0},{"getMin",0},
              {"pop",0},{"getMin",0}}, {2,2,5}},
            {"원소 하나",
             {{"push",42},{"top",0},{"getMin",0}}, {42,42}},
            {"오름차순만",
             {{"push",1},{"push",2},{"push",3},{"getMin",0},{"top",0}}, {1,3}},
            {"내림차순만",
             {{"push",3},{"push",2},{"push",1},{"getMin",0},{"pop",0},{"getMin",0}}, {1,2}},
            {"int 양쪽 끝",
             {{"push",INT_MAX},{"getMin",0},{"push",INT_MIN},{"getMin",0},
              {"pop",0},{"getMin",0}}, {INT_MAX, INT_MIN, INT_MAX}},
            {"음수만",
             {{"push",-1},{"push",-5},{"push",-3},{"getMin",0},{"pop",0},{"getMin",0}}, {-5,-5}},
            {"전부 비웠다 다시 채우기",
             {{"push",4},{"pop",0},{"push",9},{"getMin",0},{"push",2},{"getMin",0}}, {9,2}},
        };
        for (auto& c : cases) {
            MinStack ms;
            vector<int> got;
            for (auto& [op, v] : c.ops) {
                if (op == "push") ms.push(v);
                else if (op == "pop") ms.pop();
                else if (op == "top") got.push_back(ms.top());
                else got.push_back(ms.getMin());
            }
            if (got != c.want) {
                cout << "✗ " << c.name << "\n    기대: [";
                for (size_t i=0;i<c.want.size();i++) cout << (i?",":"") << c.want[i];
                cout << "]\n    실제: [";
                for (size_t i=0;i<got.size();i++) cout << (i?",":"") << got[i];
                cout << "]\n";
                failed++;
            } else {
                cout << "✓ " << c.name << "\n";
            }
        }
    }

    // 3) 무작위 연산열 — 참조 구현과 매 단계 대조
    {
        mt19937 rng(155);
        bool ok = true;
        for (int it = 0; it < 3000 && ok; it++) {
            MinStack ms; RefStack ref; Trace tr;
            int len = 5 + (int)(rng() % 60);
            for (int k = 0; k < len && ok; k++) {
                int op = (int)(rng() % 5);
                if (op <= 1 || ref.empty()) {                    // push 를 조금 더 자주
                    int v = (int)(rng() % 41) - 20;
                    tr.add("push(" + to_string(v) + ")");
                    ms.push(v); ref.push(v);
                } else if (op == 2) {
                    tr.add("pop()");
                    ms.pop(); ref.pop();
                } else if (op == 3) {
                    tr.add("top()");
                    int a = ms.top(), b = ref.top();
                    if (a != b) {
                        cout << "✗ 랜덤 top 불일치 — 기대 " << b << ", 실제 " << a
                             << "\n    연산열: " << tr.s << "\n";
                        failed++; ok = false;
                    }
                } else {
                    tr.add("getMin()");
                    int a = ms.getMin(), b = ref.getMin();
                    if (a != b) {
                        cout << "✗ 랜덤 getMin 불일치 — 기대 " << b << ", 실제 " << a
                             << "\n    연산열: " << tr.s << "\n";
                        failed++; ok = false;
                    }
                }
            }
        }
        if (ok) cout << "✓ 무작위 연산열 3000회 (참조 구현과 매 단계 대조)\n";
    }

    // 4) 값 범위를 int 양쪽 끝까지 넓힌 무작위
    {
        mt19937 rng(1550);
        uniform_int_distribution<int> dist(INT_MIN, INT_MAX);
        bool ok = true;
        for (int it = 0; it < 500 && ok; it++) {
            MinStack ms; RefStack ref;
            int len = 5 + (int)(rng() % 30);
            for (int k = 0; k < len && ok; k++) {
                int op = (int)(rng() % 4);
                if (op <= 1 || ref.empty()) { int v = dist(rng); ms.push(v); ref.push(v); }
                else if (op == 2) { ms.pop(); ref.pop(); }
                else if (ms.getMin() != ref.getMin()) {
                    cout << "✗ int 양쪽 끝 값에서 getMin 불일치 — 기대 " << ref.getMin()
                         << ", 실제 " << ms.getMin() << "\n";
                    failed++; ok = false;
                }
            }
        }
        if (ok) cout << "✓ int 전 범위 무작위 500회\n";
    }

    // 5) 성능
    //    제약: 호출이 최대 3*10^4 번.
    //    실측 (push 15000 + getMin 15000):
    //      쌍으로 쌓기        0.09ms
    //      최솟값 스택 따로   0.03ms
    //      getMin 을 매번 훑기 100.55ms
    //    20ms 로 잡는다.
#ifndef NO_TIMING
    {
        const int N = 15000;
        mt19937 rng(15500);
        vector<int> vals(N);
        for (auto& v : vals) v = (int)(rng() % 1000000) - 500000;

        MinStack ms;
        // sink 는 volatile 이어야 한다. 그냥 지역 변수로 두면 컴파일러가
        // "결과를 쓰지 않는다" 고 판단해 getMin 루프를 통째로 지운다.
        // (실제로 처음에 그래서 O(n) 풀이가 0ms 로 통과했다)
        volatile long long sink = 0;
        auto st = chrono::steady_clock::now();
        for (int v : vals) ms.push(v);
        for (int i = 0; i < N; i++) sink = sink + ms.getMin();
        auto el = chrono::duration_cast<chrono::milliseconds>(
                      chrono::steady_clock::now() - st).count();

        int want = *min_element(vals.begin(), vals.end());
        if (ms.getMin() != want) {
            cout << "✗ 대규모 getMin 이 틀림 — 기대 " << want << ", 실제 " << ms.getMin() << "\n";
            failed++;
        } else if (el > 20) {
            cout << "✗ push " << N << " + getMin " << N << " 이 " << el
                 << "ms — 너무 느림 (getMin 이 O(1) 이 아닐 가능성)\n";
            failed++;
        } else {
            cout << "✓ 성능 push " << N << " + getMin " << N << " " << el << "ms\n";
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
