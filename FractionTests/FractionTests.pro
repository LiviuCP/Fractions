include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread

HEADERS += \
        tst_testfractions.h

SOURCES += \
        main.cpp

QMAKE_LFLAGS = "-Wl,-rpath,\'$$top_builddir/FractionLib\'"

LIBS += -L$$top_builddir/FractionLib -lFractionLib
