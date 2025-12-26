QT += core gui sql network widgets

CONFIG += c++17

SOURCES += main.cpp \
    mainwindow.cpp \
    reminderworker.cpp \
    sqlrepository.cpp \
    fileexporter.cpp

HEADERS += mainwindow.h \
    reminderworker.h \
    sqlrepository.h \
    fileexporter.h

FORMS += mainwindow.ui
