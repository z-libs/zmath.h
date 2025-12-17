
CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c11 -O2 -I.
CXXFLAGS = -Wall -Wextra -std=c++11 -O2 -I.

all:

test: test_c

test_c:
	@echo "----------------------------------------"
	@echo "Building C Tests..."
	@$(CC) $(CFLAGS) tests/test_main.c -o tests/runner_c
	@./tests/runner_c
	@rm tests/runner_c

.PHONY: all test test_c
