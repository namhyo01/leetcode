# LeetCode 풀이 빌드/실행
#
#   make run   DIR=problems/0053-maximum-subarray   # main() 놀이터
#   make test  DIR=problems/0053-maximum-subarray   # 전체 검증 (최적화, 성능 게이트 포함)
#   make check DIR=problems/0053-maximum-subarray   # 새니타이저로 메모리/UB 검사
#
# DIR 을 생략하면 가장 최근에 만들어진 문제 디렉토리를 쓴다.
#
#   make pch     # <bits/stdc++.h> 를 미리 컴파일해 빌드를 절반으로 (선택, 약 250MB)
#   make clean   # 산출물과 PCH 정리

CXX      ?= g++
STD      ?= -std=c++20
WARN     := -Wall -Wextra -Wshadow
FAST     := $(STD) -O2 $(WARN)
SAFE     := $(STD) -O1 -g $(WARN) -fsanitize=address,undefined -DNO_TIMING

DIR ?= $(shell ls -dt problems/*/ 2>/dev/null | head -1)
OUT := /tmp/lc_$(notdir $(patsubst %/,%,$(DIR)))

# ── 미리 컴파일된 헤더 (있으면 자동으로 쓰고, 없으면 그냥 넘어간다) ──────────
# GCC 는 <bits/stdc++.h> 를 찾을 때 같은 경로의 stdc++.h.gch 를 먼저 본다.
# 그래서 .gch 옆에 원본 헤더 심볼릭 링크도 같이 둬야 한다 —
# solution_test.cpp 가 solution.cpp 를 include 하면서 헤더를 한 번 더 찾기 때문.
PCH_SRC := $(firstword $(wildcard \
             /usr/include/*/c++/*/bits/stdc++.h \
             /usr/include/c++/*/bits/stdc++.h))
PCH_DIR := .pch
FAST_PCH := $(PCH_DIR)/fast
SAFE_PCH := $(PCH_DIR)/safe
FAST_I := $(if $(wildcard $(FAST_PCH)/bits/stdc++.h.gch),-I $(FAST_PCH))
SAFE_I := $(if $(wildcard $(SAFE_PCH)/bits/stdc++.h.gch),-I $(SAFE_PCH))

.PHONY: run test check pch clean

run:
	@$(CXX) $(FAST) $(FAST_I) $(DIR)/solution.cpp -o $(OUT)_play && $(OUT)_play

test:
	@$(CXX) $(FAST) $(FAST_I) $(DIR)/solution_test.cpp -o $(OUT)_test && $(OUT)_test

check:
	@$(CXX) $(SAFE) $(SAFE_I) $(DIR)/solution_test.cpp -o $(OUT)_check && $(OUT)_check

pch:
	@test -n "$(PCH_SRC)" || { echo "bits/stdc++.h 를 못 찾았다 (GCC 전용 헤더다)"; exit 1; }
	@echo "원본: $(PCH_SRC)"
	@mkdir -p $(FAST_PCH)/bits $(SAFE_PCH)/bits
	@ln -sf $(PCH_SRC) $(FAST_PCH)/bits/stdc++.h
	@ln -sf $(PCH_SRC) $(SAFE_PCH)/bits/stdc++.h
	@echo "make test/run 용 (-O2) 컴파일 중..."
	@$(CXX) $(FAST) -x c++-header $(PCH_SRC) -o $(FAST_PCH)/bits/stdc++.h.gch
	@echo "make check 용 (새니타이저) 컴파일 중..."
	@$(CXX) $(SAFE) -x c++-header $(PCH_SRC) -o $(SAFE_PCH)/bits/stdc++.h.gch
	@du -sh $(PCH_DIR) | awk '{print "완료. 크기 " $$1 " (.pch/ 는 git 에 올라가지 않는다)"}'

clean:
	@rm -f /tmp/lc_*
	@rm -rf $(PCH_DIR)
	@echo "정리 완료"
