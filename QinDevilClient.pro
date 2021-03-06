QT       += core gui
QT += network

LIBS += -lUser32
LIBS += -lGdi32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../QinDevilCommonStructure/QinDevilCommonStructure.pri)

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES +="WINVER = 0x0500"
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#QMAKE_LFLAGS += /MANIFESTUAC:"level='requireAdministrator' uiAccess='false'"

SOURCES += \
    aes.cpp \
    buffer.cpp \
    bufferlist.cpp \
    colorlabel.cpp \
    colorlabelgroup.cpp \
    devicecontext.cpp \
    dialog.cpp \
    doubleclicklineedit.cpp \
    lesskeyvalidator.cpp \
    logdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    password.cpp \
    qaesencryption.cpp \
    tcpsocket.cpp \
    windowshook.cpp \
    windowsmethod.cpp

HEADERS += \
    aes.h \
    buffer.h \
    bufferlist.h \
    colorlabel.h \
    colorlabelgroup.h \
    devicecontext.h \
    dialog.h \
    doubleclicklineedit.h \
    lesskeyvalidator.h \
    logdialog.h \
    mainwindow.h \
    password.h \
    qaesencryption.h \
    tcpsocket.h \
    windowshook.h \
    windowsmethod.h

FORMS += \
    dialog.ui \
    logdialog.ui \
    mainwindow.ui \
    password.ui

TRANSLATIONS += \
    QinDevilClient_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    pictrue.qrc
RC_FILE = uac.rc
