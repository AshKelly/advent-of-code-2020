DEBUG_FLAGS = -O0 -Wall -Wextra -pedantic -Wcast-align -Wcast-qual \
			  -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 \
			  -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept \
			  -Wold-style-cast -Woverloaded-virtual -Wredundant-decls \
			  -Wshadow -Wsign-promo -Wstrict-null-sentinel \
			  -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros \
			  -Wno-parentheses -fdiagnostics-show-option

OPT_FLAGS = -O3
CC = g++
CPP_FLAGS = -std=c++11
.DEFAULT_GOAL := solution

default:
	@echo default solution

solution: solution.cpp
	$(CC) $(CPP_FLAGS) $(DEBUG_FLAGS) solution.cpp -o solution

solution_opt: solution.cpp
	$(CC) $(CPP_FLAGS) $(OPT_FLAGS) solution.cpp -o solution_opt

clean:
	@echo " Cleaning..."; rm solution solution_opt 2> /dev/null || true

all: solution_opt solution

.PHONY: clean
