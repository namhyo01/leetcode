# LeetCode 코딩테스트 준비

Python + Go 병행 풀이. 유형별 랜덤 출제 → 직접 풀이 → 리뷰 → 커밋.

## 진행 현황

| # | 문제 | 난이도 | 유형 | Python | Go | 재풀이 |
|---|------|--------|------|--------|-----|--------|
| 15 | [3Sum](problems/0015-3sum) | Medium | Two Pointers | ❌ | ❌ | **2026-08-21** |
| 875 | [Koko Eating Bananas](problems/0875-koko-eating-bananas) | Medium | ❓ | ⬜ | ⬜ | - |

> ⬜ 미착수 / ❌ 해설 보고 이해 / 🟡 힌트 받고 해결 / ✅ 스스로 해결
>
> 유형(❓)은 **푼 뒤에** 채운다. 미리 알면 스스로 판별하는 훈련이 안 된다.
>
> ❌는 재풀이 1순위. 3일 뒤 아무것도 안 보고 다시 친다.

## 실행 방법

```bash
DIR=problems/0875-koko-eating-bananas   # 오늘 문제

# Python
python3 $DIR/solution.py         # main 놀이터 (출력 찍어보기)
python3 $DIR/solution_test.py    # 전체 검증

# Go
go run  ./$DIR/                  # main() 놀이터
go test ./$DIR/                  # 전체 검증
go test -v ./$DIR/               # 케이스별 상세
```

## 디렉토리 규칙

```
problems/<번호4자리>-<슬러그>/
├── README.md          # 문제 설명, 제약조건, 내 접근 메모
├── solution.py        # Python 풀이
├── solution_test.py   # Python 테스트 (의존성 없음)
├── solution.go        # Go 풀이
└── solution_test.go   # Go 테스트
```

## 학습 규칙

1. 문제를 받으면 **먼저 30분** 스스로 고민한다.
2. 막히면 힌트를 요청한다 (정답이 아닌 단계별 힌트).
3. 풀고 나면 시간/공간 복잡도를 스스로 말해본다.
4. Python으로 먼저 풀고, 같은 로직을 Go로 옮긴다.
5. 힌트를 받아 푼 문제(🟡)는 **1주 뒤 재풀이**한다.

[문제 풀 목록](POOL.md)
