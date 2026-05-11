# ============================================================
# Standalone Makefile for MAYO
#
# Usage:
#   make        -> build ref version using test_mayo.c
#   make ref    -> build ref version using test_mayo.c
#   make opt    -> build opt version using test_mayo.c
#   make kat    -> build KAT test using test_kat.c
#   make clean
#
# Output:
#   test_mayo.exe
# ============================================================

CC ?= gcc

TARGET := test.exe

ENABLE_STRICT ?= ON

# ============================================================
# Source files
# ============================================================

SRC_ALL := $(wildcard *.c)

MAIN_SRC := test_mayo.c randombytes_system.c
KAT_SRC  := test_kat.c randombytes_ctrdrbg.c

# 普通源文件：排除 main 测试文件
SRC := $(filter-out $(MAIN_SRC) $(KAT_SRC),$(SRC_ALL))

# AES-NI / AVX2 / NEON / M4 are not supported
SRC := $(filter-out %aesni%.c %AESNI%.c,$(SRC))
SRC := $(filter-out %avx2%.c %AVX2%.c,$(SRC))
SRC := $(filter-out %neon%.c %NEON%.c,$(SRC))
SRC := $(filter-out %m4%.c %M4%.c,$(SRC))

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
	-fno-strict-aliasing

CPPFLAGS := -I.

LDFLAGS :=
LDLIBS :=

# ============================================================
# ENABLE_STRICT
# ============================================================

ifeq ($(ENABLE_STRICT),ON)
	CFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter
else ifeq ($(ENABLE_STRICT),OFF)
	CFLAGS += -Wall -Wextra -Wno-unused-parameter
else
	$(error ENABLE_STRICT must be ON or OFF)
endif

# ============================================================
# Default target: ref
# ============================================================

all: ref

ref:
	$(CC) $(CPPFLAGS) -DENABLE_PARAMS_DYNAMIC -DMAYO_BUILD_TYPE_REF $(CFLAGS) $(SRC) $(MAIN_SRC) $(LDFLAGS) $(LDLIBS) -o $(TARGET)
	@echo "Built $(TARGET) with MAYO_BUILD_TYPE=ref using $(MAIN_SRC)"

opt:
	$(CC) $(CPPFLAGS) -DMAYO_BUILD_TYPE_OPT $(CFLAGS) $(SRC) $(MAIN_SRC) $(LDFLAGS) $(LDLIBS) -o $(TARGET)
	@echo "Built $(TARGET) with MAYO_BUILD_TYPE=opt using $(MAIN_SRC)"

kat:
	$(CC) $(CPPFLAGS) -DMAYO_BUILD_TYPE_OPT $(CFLAGS) $(SRC) $(KAT_SRC) $(LDFLAGS) $(LDLIBS) -o $(TARGET)
	@echo "Built $(TARGET) for KAT testing using $(KAT_SRC)"

clean:
	rm -f $(TARGET)

print:
	@echo "CC            = $(CC)"
	@echo "TARGET        = $(TARGET)"
	@echo "SRC           = $(SRC)"
	@echo "MAIN_SRC      = $(MAIN_SRC)"
	@echo "KAT_SRC       = $(KAT_SRC)"
	@echo "CPPFLAGS      = $(CPPFLAGS)"
	@echo "CFLAGS        = $(CFLAGS)"
	@echo "ENABLE_STRICT = $(ENABLE_STRICT)"

.PHONY: all ref opt kat clean print