# LeetCode 풀이 빌드/실행
#
#   make run   DIR=problems/0015-3sum   # main() 놀이터
#   make test  DIR=problems/0015-3sum   # 전체 검증 (최적화, 성능 게이트 포함)
#   make check DIR=problems/0015-3sum   # 새니타이저로 메모리/UB 검사 (성능 게이트 제외)
#
# DIR 을 생략하면 가장 최근에 만들어진 문제 디렉토리를 쓴다.

CXX      ?= g++
STD      ?= -std=c++20
WARN     := -Wall -Wextra -Wshadow
FAST     := $(STD) -O2 $(WARN)
SAFE     := $(STD) -O1 -g $(WARN) -fsanitize=address,undefined -DNO_TIMING

DIR ?= $(shell ls -dt problems/*/ 2>/dev/null | head -1)
OUT := /tmp/lc_$(notdir $(patsubst %/,%,$(DIR)))

.PHONY: run test check clean

run:
	@$(CXX) $(FAST) $(DIR)/solution.cpp -o $(OUT)_play && $(OUT)_play

test:
	@$(CXX) $(FAST) $(DIR)/solution_test.cpp -o $(OUT)_test && $(OUT)_test

check:
	@$(CXX) $(SAFE) $(DIR)/solution_test.cpp -o $(OUT)_check && $(OUT)_check

clean:
	@rm -f /tmp/lc_*
