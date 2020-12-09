DEBUG_FLAGS = -O0 -Wall -Wextra -pedantic -Wcast-align -Wcast-qual \
			  -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 \
			  -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept \
			  -Wold-style-cast -Woverloaded-virtual -Wredundant-decls \
			  -Wshadow -Wsign-promo -Wstrict-null-sentinel \
			  -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros \
			  -Wno-parentheses -fdiagnostics-show-option

CC = g++
CPP_FLAGS = -std=c++11
.DEFAULT_GOAL := stdlib

default:
	@echo default stdlib

stdlib: aoc.h
	$(CC) $(CPP_FLAGS) $(DEBUG_FLAGS) aoc.h

all: stdlib

.PHONY: clean
