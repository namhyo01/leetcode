# LeetCode 코딩테스트 준비

**Go** 로 푼다. 랜덤 출제 → 직접 풀이 → 리뷰 → 커밋 + 푸시.

## 진행 현황

| # | 문제 | 난이도 | 유형 | 결과 | 재풀이 |
|---|------|--------|------|------|--------|
| 15 | [3Sum](problems/0015-3sum) | Medium | ❓ | 🔁 재풀이 중 | 2026-08-21 |
| 875 | [Koko Eating Bananas](problems/0875-koko-eating-bananas) | Medium | Binary Search | ✅ | - |
| 39 | [Combination Sum](problems/0039-combination-sum) | Medium | Backtracking | ✅ | - |
| 105 | [Construct Binary Tree from Preorder and Inorder](problems/0105-construct-binary-tree-from-preorder-and-inorder-traversal) | Medium | Divide and Conquer | ✅ | - |

> ⬜ 미착수 / ❌ 해설 보고 이해 / 🟡 힌트 받고 해결 / ✅ 스스로 해결
>
> 유형(❓)은 **푼 뒤에** 채운다. 미리 알면 스스로 판별하는 훈련이 안 된다.
>
> ❌는 재풀이 1순위. 3일 뒤 아무것도 안 보고 다시 친다. 🔁 는 재풀이 진행 중.

## 실행 방법

```bash
DIR=problems/0015-3sum   # 오늘 문제 (재풀이)

go run  ./$DIR/                  # main() 놀이터, 출력 찍어보기
go test ./$DIR/                  # 전체 검증
go test -v ./$DIR/               # 케이스별 상세
go test -bench=. -benchmem ./$DIR/   # 성능/할당 측정
```

## 디렉토리 규칙

```
problems/<번호4자리>-<슬러그>/
├── README.md          # 영문 지문 + 제약조건 + 예제 + 한국어 회고
├── solution.go        # 풀이 (package main + main() 놀이터)
└── solution_test.go   # 테스트 (표준 testing)
```

> `problems/0015-3sum/` 에만 초기에 만든 Python 풀이가 남아 있다. 2026-08-19 부터 Go 단독.

## 학습 규칙

1. 문제를 받으면 **먼저 30분** 스스로 고민한다.
2. 막히면 힌트를 요청한다 (정답이 아닌 단계별 힌트).
3. 풀고 나면 시간/공간 복잡도를 스스로 말해본다.
4. 힌트를 받아 푼 문제(🟡)는 1주 뒤, 해설을 본 문제(❌)는 **3일 뒤** 재풀이한다.
5. 매번 커밋하고 **푸시**한다.

[문제 풀 목록](POOL.md)

## 다른 컴퓨터에서 이어서 하기

이 저장소는 **Claude Code 설정을 저장소 안에 담고 있어서**, clone만 하면 어디서든 똑같이 동작한다.

```bash
git clone https://github.com/namhyo01/leetcode
cd leetcode
claude
```

- `CLAUDE.md` — 코치 지침 (자동으로 읽힌다)
- `.claude/commands/today.md` — `/today` : 오늘의 문제 출제
- `.claude/commands/done.md` — `/done` : 검증·리뷰·기록·푸시

새 컴퓨터에서 필요한 준비물은 Claude Code 로그인, `gh auth login`(푸시용), Python 3와 Go뿐이다.
