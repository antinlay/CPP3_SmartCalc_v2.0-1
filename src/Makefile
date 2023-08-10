SRC = calcView
TEST = calcTest
OS := $(shell uname -s)

all: clean gcov_report dist dvi

install: clean
	mkdir build
	cd build && qmake .. && make && make clean
ifeq ($(OS), Linux)
	mv calcView build
	cd build && ./$(SRC)
endif
ifeq ($(OS), Darwin)
	build/$(SRC).app/Contents/MacOS/$(SRC)
endif

uninstall:
	rm -rf build $(TEST)/build tgz_calc.tgz

clean:
	rm -rf *.o *.a *.gc* test.info info.pdf info.dvi info.log info.aux tgz_calc .clang-format RESULT_VALGRIND.txt

dvi:
	texi2pdf info.tex
	texi2dvi info.tex

dist: install
	mkdir tgz_calc/ tgz_calc/app
	mv ./build/calcView.app tgz_calc/app/
	tar cvzf tgz_calc.tgz tgz_calc/

tests: uninstall
	mkdir $(TEST)/build
	cd $(TEST)/build && cmake .. && make
	$(TEST)/build/calculate

check: tests
	clang-format -style="{BasedOnStyle: Google}" -i *.cpp *.h $(TEST)/*.cpp
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(SRC) *.h
ifeq ($(OS), Darwin)
	leaks --atExit -- $(TEST)/build/calculate
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt $(TEST)/build/calculate
endif

gcov_report: tests
	cd $(TEST)/build && make gcov && make lcov
