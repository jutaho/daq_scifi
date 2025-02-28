QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += moc


SOURCES += \
    datareceiver.cpp \
    device.cpp \
    display.cpp \
    hw.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    cbuffer.h \
    datareceiver.h \
    device.h \
    deviceconfig.h \
    display.h \
    hw.h \
    mainwindow.h \
    ui_mainwindow.h


FORMS += mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
