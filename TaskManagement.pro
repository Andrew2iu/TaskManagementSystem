QT += core gui sql network printsupport
# 启用 C++17 标准
CONFIG += c++17

# 源文件列表
SOURCES += main.cpp \
    mainwindow.cpp \
    reminderworker.cpp \
    sqlrepository.cpp \
    fileexporter.cpp

# 头文件列表
HEADERS += mainwindow.h \
    reminderworker.h \
    sqlrepository.h \
    fileexporter.h

# 界面文件
FORMS += mainwindow.ui

# 建议：防止路径中存在空格导致编译失败，设置输出目录
DESTDIR = bin
