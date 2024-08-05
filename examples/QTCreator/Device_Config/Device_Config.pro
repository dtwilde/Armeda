QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../../src/LibSerialPortWrapper.cpp \
    ../../../src/WS_Device.cpp \
    ../../../src/WS_RTURelay.cpp \
    baudratedialog.cpp \
    main.cpp \
    mainwindow.cpp \
    scanthread.cpp

HEADERS += \
    ../../../inc/WS_Device.h \
    ../../../inc/WS_RTURelay.h \
    baudratedialog.h \
    mainwindow.h \
    scanthread.h

FORMS += \
    baudratedialog.ui \
    mainwindow.ui

INCLUDEPATH += \
    ../../../inc/ \
    ../../../src/ \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += libserialport
