QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calcController.cpp \
    calcModel.cpp \
    calcView.cpp \
    credit.cpp \
    debit.cpp \
    graph.cpp \
    main.cpp \
    qcustomplot.cpp

HEADERS += \
    calcController.h \
    calcModel.h \
    calcView.h \
    credit.h \
    debit.h \
    graph.h \
    main.h \
    qcustomplot.h \

FORMS += \
    calcView.ui \
    credit.ui \
    debit.ui \
    graph.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
