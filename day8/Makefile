DEBUG_FLAGS = -O0 -Wall -Wextra -pedantic -Wcast-align -Wcast-qual \
			  -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 \
			  -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept \
			  -Wold-style-cast -Woverloaded-virtual -Wredundant-decls \
			  -Wshadow -Wsign-promo -Wstrict-null-sentinel \
			  -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros \
			  -Wno-parentheses -fdiagnostics-show-option

OPT_FLAGS = -O3
CC = g++
CPP_FLAGS = -std=c++14
.DEFAULT_GOAL := all

default:
	@echo default all

solution: solution.cpp
	$(CC) $(CPP_FLAGS) $(DEBUG_FLAGS) solution_optimal.cpp -o solution

solution_fast: solution.cpp
	$(CC) $(CPP_FLAGS) $(OPT_FLAGS) solution_optimal.cpp -o solution_fast

clean:
	@echo " Cleaning..."; rm solution solution_fast 2> /dev/null || true

all: solution_fast solution

.PHONY: clean
