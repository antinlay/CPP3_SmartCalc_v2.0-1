CC = g++
FLAGS = -Wall -Werror -Wextra -std=c++17 -ggdb -pedantic -lstdc++
GCOV = --coverage
TEST = smartcalc_test
STLIB = s21_smartcalc.a
OS := $(shell uname -s)

ifeq ($(OS), Linux)
	LIBS := -lgtest -lpthread -lrt -lm -lsubunit
endif
ifeq ($(OS), Darwin)
	LIBS := -lgtest
endif

all: clean gcov_report dist dvi

install: clean
	cp -r --parents ./* ./build/
	cd build && qmake && make && make clean
ifeq ($(OS), Linux)
	mv calcView build
	cd build && ./calcView
endif
ifeq ($(OS), Darwin)
	# mv calcView.app build
	# chmod 755 build/calcView.app/Contents/MacOS/calcView
	./build/calcView.app/Contents/MacOS/calcView
endif

uninstall:
	rm -rf build tgz_smartcalc.tgz

clean: uninstall
	rm -rf *.o *.a *.gc* test.info info.pdf info.dvi info.log info.aux report $(TEST) tgz_smartcalc .clang-format RESULT_VALGRIND.txt build* s21_smartcalc/s21_smartcalc s21_smartcalc/s21_smartcalc.app s21_smartcalc/Makefile s21_smartcalc/*.o

dvi:
	texi2pdf info.tex
	texi2dvi info.tex

dist: install
	mkdir tgz_smartcalc/ tgz_smartcalc/app
	mv ./build/* tgz_smartcalc/app/
	tar cvzf tgz_smartcalc.tgz tgz_smartcalc/

tests: clean
	$(CC) -c *.cpp
	ar rcs $(STLIB) smartCalc.o
	ranlib $(STLIB)
	$(CC) $(FLAGS) calcTests.c $(STLIB) -o $(TEST) $(LIBS)
	./$(TEST)

check: tests
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h s21_smartcalc/*.ui s21_smartcalc/*.c* s21_smartcalc/*.h
	cppcheck --suppress=missingIncludeSystem *.c
ifeq ($(OS), Linux)
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./$(TEST)
else
	CK_FORK=no leaks --atExit -- ./$(TEST)
endif

gcov_report: tests
	$(CC) $(FLAGS) $(GCOV) smartcalc_test.c s21_smartcalc.c -o $(TEST) $(LIBS)
	./$(TEST)
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/src/index.html