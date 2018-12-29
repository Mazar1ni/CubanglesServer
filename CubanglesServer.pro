QT -= gui
QT += network sql

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += ACTUAL_VERSION_MAJOR=1 \
           ACTUAL_VERSION_MINOR=0

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# ¬ыбираем директорию сборки исполн€емого файла
# в зависимости от режима сборки проекта
CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/../../CubanglesServer/Debug
} else {
    DESTDIR = $$OUT_PWD/../../CubanglesServer/Release
}
# раздел€ем по директори€м все выходные файлы проекта
MOC_DIR = ../common/build/moc
RCC_DIR = ../common/build/rcc
UI_DIR = ../common/build/ui
unix:OBJECTS_DIR = ../common/build/o/unix
win32:OBJECTS_DIR = ../common/build/o/win32
macx:OBJECTS_DIR = ../common/build/o/mac

# в зависимости от режима сборки проекта
# запускаем win deploy приложени€ в целевой директории, то есть собираем все dll
CONFIG(debug, debug|release) {
    QMAKE_POST_LINK = $$(QTDIR)/bin/windeployqt $$OUT_PWD/../../CubanglesServer/Debug
} else {
    QMAKE_POST_LINK = $$(QTDIR)/bin/windeployqt $$OUT_PWD/../../CubanglesServer/Release
}

SOURCES += \
        main.cpp \
    server.cpp \
    socket.cpp \
    task.cpp \
    tcpsocket.cpp \
    room.cpp \
    roommanager.cpp \
    searchgame.cpp

HEADERS += \
    server.h \
    socket.h \
    task.h \
    tcpsocket.h \
    room.h \
    roommanager.h \
    searchgame.h
