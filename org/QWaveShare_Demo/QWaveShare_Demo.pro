QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../QWaveshare/WS_AnalogInput.cpp \
    ../QWaveshare/WS_Device.cpp \
    ../QWaveshare/WS_RTURelay.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../QWaveshare/Q_CRC16.h \
    ../QWaveshare/WS_AnalogInput.h \
    ../QWaveshare/WS_Device.h \
    ../QWaveshare/WS_RTURelay.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
