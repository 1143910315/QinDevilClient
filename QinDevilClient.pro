QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../QinDevilCommonStructure/QinDevilCommonStructure.pri)

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aes.cpp \
    buffer.cpp \
    bufferlist.cpp \
    colorlabel.cpp \
    colorlabelgroup.cpp \
    dialog.cpp \
    lesskeyvalidator.cpp \
    main.cpp \
    mainwindow.cpp \
    qaesencryption.cpp \
    tcpsocket.cpp \
    windowshook.cpp

HEADERS += \
    aes.h \
    buffer.h \
    bufferlist.h \
    colorlabel.h \
    colorlabelgroup.h \
    dialog.h \
    lesskeyvalidator.h \
    mainwindow.h \
    qaesencryption.h \
    tcpsocket.h \
    windowshook.h

FORMS += \
    dialog.ui \
    mainwindow.ui

TRANSLATIONS += \
    QinDevilClient_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
