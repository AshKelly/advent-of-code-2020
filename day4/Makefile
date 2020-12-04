DEBUG_FLAGS = -g -pedantic -Wall -Wextra -Wcast-align -Wcast-qual \
			  -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 \
			  -Winit-self -Wlogical-op  -Wmissing-include-dirs -Wnoexcept \
			  -Wold-style-cast -Woverloaded-virtual -Wredundant-decls \
			  -Wshadow -Wsign-promo -Wstrict-null-sentinel \
			  -Wswitch-default -Wundef -Wno-unused

OPT_FLAGS = -O3
CC = g++
CPP_FLAGS = -std=c++14

solution: solution.cpp
	$(CC) $(CPP_FLAGS) $(DEBUG_FLAGS) solution.cpp -o solution

solution_fast: solution.cpp
	$(CC) $(CPP_FLAGS) $(OPT_FLAGS) solution.cpp -o solution_fast

clean:
	@echo " Cleaning..."; rm solution solution_fast 2> /dev/null || true

all: solution_fast solution

.PHONY: clean
