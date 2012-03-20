#-------------------------------------------------
#
# Project created by QtCreator 2012-03-09T06:49:24
#
#-------------------------------------------------

QT       += core gui

TARGET = KnightsTourSolver
TEMPLATE = app


SOURCES +=\
    src/main.cpp \
    src/mainwindow.cpp \
    src/chessboardscene.cpp \
    src/textfunctions.cpp \
    src/squaregraphicsitem.cpp \
    src/fontloader.cpp \
    src/solver.cpp \
    src/node.cpp \
    src/point.cpp \
    src/vector2b.cpp

HEADERS  += \
    include/mainwindow.hpp \
    include/chessboardscene.hpp \
    include/textfunctions.hpp \
    include/squaregraphicsitem.hpp \
    include/fontloader.hpp \
    include/solver.hpp \
    include/node.hpp \
    include/point.hpp \
    include/vector2b.hpp

FORMS    += \
    forms/mainwindow.ui

INCLUDEPATH += include
DEPENDPATH += include

RESOURCES += \
    resources/KnightsTourSolver.qrc
