
CC ?= gcc

# ============================================================
# Source files
# ============================================================

SRC_ALL := $(wildcard *.c)

MAIN_SRC := test_mayo.c
KAT_SRC  := test_kat.c

# 普通源文件：排除 main 测试文件
SRC := $(filter-out $(MAIN_SRC) $(KAT_SRC),$(SRC_ALL))

# ============================================================
# Common flags
# ============================================================

CFLAGS := \
	-std=c99 \
	-O3 \
	-Wstrict-prototypes \
	-Wno-error=strict-prototypes \
	-fvisibility=hidden \
	-Wno-error=implicit-function-declaration \
	-Wno-error=attributes \
	-fno-strict-aliasing \
	-Wall -Wextra -Werror -Wno-unused-parameter

CPPFLAGS := -I.

LDFLAGS :=
LDLIBS :=

# ============================================================
# Default target: ref
# ============================================================

all: test

test:
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SRC) $(MAIN_SRC) $(LDFLAGS) $(LDLIBS) -o test.exe
	@echo "Built test.exe using $(MAIN_SRC)"

kat:
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SRC) $(KAT_SRC) $(LDFLAGS) $(LDLIBS) -o kat.exe
	@echo "Built kat.exe using $(KAT_SRC)"

clean:
	rm -f $(wildcard *.exe)

.PHONY: all ref opt kat clean print