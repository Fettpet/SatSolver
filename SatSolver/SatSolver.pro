TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Formula/clauses.cpp \
    Formula/literal.cpp \
    Formula/formula.cpp \
    IO/io.cpp \
    Solver/stcalculus.cpp \
    Solver/solverbaseclass.cpp \
    Solver/dpllsolver.cpp \
    Solver/cdclsolver.cpp

HEADERS += \
    Formula/clauses.h \
    Formula/literal.h \
    Formula/formula.h \
    IO/io.h \
    Solver/stcalculus.h \
    Solver/solverbaseclass.h \
    Solver/dpllsolver.h \
    Solver/cdclsolver.h

QMAKE_CXXFLAGS += -std=c++11

