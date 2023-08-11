SRC = calcView
TEST = calcTest
OS := $(shell uname -s)

all: clean gcov_report dist dvi

install: uninstall
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
	rm -rf build tgz_calc.tgz

clean:
	rm -rf *.o *.a *.gc* tgz_calc RESULT_VALGRIND.txt $(TEST)/build

dvi:
	open info.pdf

dist: install
	cd build && mkdir tgz_calc/ tgz_calc/app
	mv build/calcView.app build/tgz_calc/app/
	tar cvzf tgz_calc.tgz build/tgz_calc/

tests: clean
	mkdir $(TEST)/build
	cd $(TEST)/build && cmake .. && make
	$(TEST)/build/calculate

gcov_report: tests
	cd $(TEST)/build && make gcov && make lcov
