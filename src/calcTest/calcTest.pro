QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(gtest_dependency.pri)

CONFIG += c++17

TEMPLATE = app
CONFIG += console
#CONFIG -= app_bundle
#CONFIG += thread
#CONFIG += debug
#CONFIG += testlib
#CONFIG += debug
#CONFIG += testlib
#QMAKE_CXXFLAGS += --coverage
#LIBS += -L/opt/goinfre/janiecee/homebrew/Cellar/gcovr/6.0 -lgcov

SOURCES += \
        ../calcModel.cpp \
        main.cpp         tst_calculate.cpp

HEADERS += \
    ../calcModel.h
