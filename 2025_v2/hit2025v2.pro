#-------------------------------------------------
#
# Project created by QtCreator 2017-08-21T15:59:19
#
#-------------------------------------------------

QT       += core gui network serialport
#CONFIG += static
unix {
   QMAKE_CXXFLAGS += -W -std=c++17
}

win32 {
   QMAKE_CXXFLAGS += -Wa,-mbig-obj -std=c++17
}

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets printsupport

TARGET = hit2025v2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    q_debugstream.cpp \
    dialoglogsettings.cpp \
    device.cpp \
    datareceiver.cpp \
    hw.cpp \
    dialoghostip.cpp \
    dialogtriggersettings.cpp \
    dialogdevices.cpp \
    helpers.cpp \
    eventbuilder.cpp \
    display.cpp \
    displayserver.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    Q_DebugStream.h \
    dialoglogsettings.h \
    device.h \
    dev_commands.h \
    datareceiver.h \
    hw.h \
    dialoghostip.h \
    dialogtriggersettings.h \
    dialogdevices.h \
    helpers.h \
    cbuffer.h \
    eventbuilder.h \
    networkthread.h \
    display.h \
    displayserver.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    dialoglogsettings.ui \
    dialoghostip.ui \
    dialogtriggersettings.ui \
    dialogdevices.ui \
    display.ui


