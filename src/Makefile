CC = g++
FLAGS = -Wall -Werror -Wextra
SRC = calcView
TEST = calcTest
TESTFLAGS=-lgtest -lgcov
HTML=lcov -t test -o rep.info -c -d ./
OS := $(shell uname -s)

all: clean gcov_report dist dvi

install: clean
	mkdir build
	cp ./*.cpp ./*.h ./*.ui ./*.hpp ./*.pro ./*.user build
	cd build && qmake && make && make clean
ifeq ($(OS), Linux)
	mv calcView build
	cd build && ./$(SRC)
endif
ifeq ($(OS), Darwin)
	./build/$(SRC).app/Contents/MacOS/$(SRC)
endif

uninstall:
	rm -rf build tgz_calc.tgz

clean: uninstall
	rm -rf *.o *.a *.gc* test.info info.pdf info.dvi info.log info.aux report tgz_calc .clang-format RESULT_VALGRIND.txt build

dvi:
	texi2pdf info.tex
	texi2dvi info.tex

dist: install
	mkdir tgz_calc/ tgz_calc/app
	mv ./build/calcView.app tgz_calc/app/
	tar cvzf tgz_calc.tgz tgz_calc/

tests: clean
	cd $(TEST) && qmake && make && make clean
	./$(TEST)


check: tests
	clang-format -style="{BasedOnStyle: Google}" -i *.cc *.h
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(SRC) *.h
ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif


gcov_report: tests
	./$(TEST)
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/src/index.html
