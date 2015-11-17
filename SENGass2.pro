QT += core
QT -= gui

TARGET = SENGass2
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
Machine.pb.cc

HEADERS += Machine.pb.h

DISTFILES += \
    Machine.proto

LIBS += -l protobuf -L$$PWD/../Machine.pb.cc

INCLUDEPATH += Machine
