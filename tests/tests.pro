QT += testlib
QT -= gui

CONFIG += qt console testcase
CONFIG -= app_bundle

INCLUDEPATH += ../src

TEMPLATE = app

SOURCES += \
  test_board.cpp \
  ../src/chess_board.cpp \
  ../src/chess_logic.cpp \

HEADERS += \
  test_board.h \
  ../src/chess_board.h \
  ../src/chess_logic.h \
