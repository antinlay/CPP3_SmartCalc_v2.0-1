CC = clang++
FLAGS = -Wall -Werror -Wextra -pipe -stdlib=libc++ -O2 -std=gnu++1z -arch x86_64 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.1.sdk -mmacosx-version-min=11 -fPIC
QTFLAGS = -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -I/usr/local/lib/QtWidgets.framework/Headers -I/usr/local/lib/QtGui.framework/Headers -I/usr/local/lib/QtCore.framework/Headers -I/usr/local/share/qt/mkspecs/macx-clang -F/usr/local/lib
OPENGLFLAGS = -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.1.sdk/System/Library/Frameworks/OpenGL.framework/Headers 
GCOV = --coverage
TEST = calcTests
STLIB = libcalcModel.a
OS := $(shell uname -s)

ifeq ($(OS), Linux)
	GLIBS := -lgtest -lpthread -lrt -lm -lsubunit -lgtest_main
endif
ifeq ($(OS), Darwin)
	GLIBS := -lgtest -lgtest_main -lpthread
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
	rm -rf build tgz_calc.tgz

clean: uninstall
	rm -rf *.o *.a *.gc* test.info info.pdf info.dvi info.log info.aux report $(TEST) tgz_calc .clang-format RESULT_VALGRIND.txt build

dvi:
	texi2pdf info.tex
	texi2dvi info.tex

dist: install
	mkdir tgz_calc/ tgz_calc/app
	mv ./build/* tgz_calc/app/
	tar cvzf tgz_calc.tgz tgz_calc/

tests: clean
	if [ ! -f ./$(STLIB) ]; then \
		$(CC) $(FLAGS) $(QTFLAGS) $(OPENGLFLAGS) -o calcModel.o calcModel.cpp; \
		ar rcs $(STLIB) calcModel.cpp; \
		g++ -O2 -fPIC -fno-diagnostics-show-caret -I/usr/local/lib -I/usr/local/lib/QtCore -I/usr/local/lib/QtWidgets -I/usr/local/lib/QtGui calcModel.cpp -s -lQt5Core -lQt5Widgets -lQt5Gui -lQt5Xml -o prog
	fi
	$(CC) $(FLAGS) $(QTFLAGS) calcTests.cc $(STLIB) -o $(TEST) $(GLIBS)
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
	$(CC) $(FLAGS) $(QTFLAGS) $(GCOV) calcTests.cc calcModel.cpp -o $(TEST) $(GLIBS)
	./$(TEST)
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/src/index.html