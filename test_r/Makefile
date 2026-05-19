
CC ?= gcc

TARGET := test.exe

# ============================================================
# Source files
# ============================================================

SRC_ALL := $(wildcard *.c)

MAIN_SRC := test_mayo.c randombytes_system.c
KAT_SRC  := test_kat.c randombytes_ctrdrbg.c

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
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SRC) $(MAIN_SRC) $(LDFLAGS) $(LDLIBS) -o $(TARGET)
	@echo "Built $(TARGET) using $(MAIN_SRC)"

kat:
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SRC) $(KAT_SRC) $(LDFLAGS) $(LDLIBS) -o $(TARGET)
	@echo "Built $(TARGET) using $(KAT_SRC)"

clean:
	rm -f $(TARGET)

.PHONY: all ref opt kat clean print