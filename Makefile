GCC = gcc -Wall -Werror -Wextra
# LIBS= $(shell pkg-config --cflags --libs check)
GCOV_FLAGS= -fprofile-arcs -ftest-coverage
OS := $(shell uname)

FRONT = gui/cli/*.c
BACK = brick_game/tetris/*.c


ifeq ($(OS), Linux)
		CHECK_FLAGS = -lcheck -lpthread -lsubunit -lrt -lm  
else
        CHECK_FLAGS = -lcheck 
endif

#  all, install, uninstall, clean, dvi, dist, test, gcov_report

all: install

build:
	@$(GCC) $(BACK) $(FRONT) tetris.c -o tetris -lncurses  -lrt

install: build
	@touch score.txt
	@echo 0 > score.txt
	@echo "Installation completed"
	@echo "Privetik minibro :D"
	@echo "'make run' to start the game"

run:
	./tetris

uninstall: clean
	rm -rf score.txt
	@echo "Uninstallation completed"

test: clean
	$(GCC) tests/*.c $(BACK) -o test $(CHECK_FLAGS)
	./test

gcov_report: 
	$(GCC) tests/*.c $(BACK) -o test $(CHECK_FLAGS) $(GCOV_FLAGS) 
	./test
	rm -rf tests.gcda
	lcov -t "report" -o report.info --no-external -c -d .
	genhtml  -o ./report report.info
	rm -rf *.gcda *.gcno *.info

clang: 
	clang-format -n *.c brick_game/tetris/*.c brick_game/tetris/*.h gui/cli/*.c gui/cli/*.h

valgrind: test
	valgrind --tool=memcheck --leak-check=yes  ./test

clean:
	rm -rf *.gcda *.gcno *.info
	rm -rf ./test ./tetris 
