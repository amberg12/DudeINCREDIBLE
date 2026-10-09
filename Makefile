.RECIPEPREFIX = >

BUILD_DIR := build
export BUILD_DIR

# OS
ifeq ($(OS), Windows_NT)
  override DETECTED_OS := Windows
else
  override DETECTED_OS := $(shell uname -s)
endif

export DETECTED_OS

# VERSION
ifeq ($(DETECTED_OS), Darwin)
  override VERSION := $(shell cat src/version.txt)
else
  override VERSION := $(file < src/version.txt)
endif

# GIT INFO
GIT_COMMIT_HASH := $(shell git rev-parse --short=7 HEAD)
export GIT_COMMIT_HASH

export VERSION

# EXE NAME
#
# Openbench requires us to be able to override the exe name
ifndef EXE
  ifeq ($(DETECTED_OS), Windows)
  	EXE := DudeINCREDIBLE.exe
  else
    EXE := DudeINCREDIBLE
  endif
endif

export EXE

# RM may be different over different platforms
ifeq ($(DETECTED_OS), Windows)
  override RMDIR := rmdir /s /q
else
  override RMDIR := rm -rf
endif

# Clang only
CC := clang
CXX := clang++

export CC
export CXX

# Default targets
.PHONY: all
all: native

# Build targets
.PHONY: native
native:
> $(MAKE) -f scripts/build.mk TYPE=$@ VALID_CALL=1

# Other targets
.PHONY: help
help:
> @echo "To compile DudeINCREDIBLE, call"
> @echo ""
> @echo "make -j [target]"
> @echo ""
> @echo "Supported targets:"
> @echo "\thelp"
> @echo "\tclean"
> @echo "Along with build targets as follows:"
> @echo "\tnative (default)"

.PHONY: clean
clean:
> $(RMDIR) $(BUILD_DIR)
> rm $(EXE)

.PHONY: fmt
fmt:
> clang-format -i $$(find src -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' \))