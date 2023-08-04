CC = clang++
FLAGS = -Wall -Werror -Wextra -std=c++17 -ggdb -pedantic -lstdc++
GCOV = --coverage
TEST = calcTests
STLIB = s21_smartcalc.a
OS := $(shell uname -s)

ifeq ($(OS), Linux)
	LIBS := -lgtest -lpthread -lrt -lm -lsubunit -lgtest_main -lQt5Core -lQt5Widgets
endif
ifeq ($(OS), Darwin)
	LIBS := -lgtest -lgtest_main -lpthread -lQt5Core -lQt5Widgets
endif

all: clean gcov_report dist dvi

install: clean
	mkdir build
	cp ./*.cpp ./*.h ./*.ui ./*.hpp ./*.pro ./*.user build
	cd build && qmake && make && make clean
ifeq ($(OS), Linux)
	mv calcView build
	cd build && ./calcView
endif
ifeq ($(OS), Darwin)
	./build/calcView.app/Contents/MacOS/calcView
endif

uninstall:
	rm -rf build tgz_smartcalc.tgz

clean: uninstall
	rm -rf *.o *.a *.gc* test.info info.pdf info.dvi info.log info.aux report $(TEST) tgz_smartcalc .clang-format RESULT_VALGRIND.txt build

dvi:
	texi2pdf info.tex
	texi2dvi info.tex

dist: install
	mkdir tgz_smartcalc/ tgz_smartcalc/app
	mv ./build/* tgz_smartcalc/app/
	tar cvzf tgz_smartcalc.tgz tgz_smartcalc/

tests: clean
if [-f ./build/calcModel.o]
	# clang++ -c -pipe -stdlib=libc++ -O2 -std=gnu++1z  -arch x86_64 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.1.sdk -mmacosx-version-min=11 -Wall -Wextra -fPIC -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -I/usr/local/lib/QtWidgets.framework/Headers -I/usr/local/lib/QtGui.framework/Headers -I/usr/local/lib/QtCore.framework/Headers -I. -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.1.sdk/System/Library/Frameworks/OpenGL.framework/Headers -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.1.sdk/System/Library/Frameworks/AGL.framework/Headers -I. -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.1.sdk/System/Library/Frameworks/OpenGL.framework/Headers -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.1.sdk/System/Library/Frameworks/AGL.framework/Headers -I/usr/local/share/qt/mkspecs/macx-clang -F/usr/local/lib -o calcModel.o calcModel.cpp
	$(CC) $(FLAGS) calcTests.сс $(STLIB) -o $(TEST) $(LIBS)
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
	$(CC) $(FLAGS) $(GCOV) calcTests.cc calcModel.cpp -o $(TEST) $(LIBS)
	./$(TEST)
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/src/index.html