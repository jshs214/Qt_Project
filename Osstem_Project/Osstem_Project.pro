QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatserverform.cpp \
    chattingform.cpp \
    clientitem.cpp \
    clientmanagerform.cpp \
    logthread.cpp \
    main.cpp \
    mainwindow.cpp \
    orderitem.cpp \
    ordermanagerform.cpp \
    productitem.cpp \
    productmanagerform.cpp

HEADERS += \
    Chat_Status.h \
    chatserverform.h \
    chattingform.h \
    clientitem.h \
    clientmanagerform.h \
    logthread.h \
    mainwindow.h \
    orderitem.h \
    ordermanagerform.h \
    productitem.h \
    productmanagerform.h

FORMS += \
    chatserverform.ui \
    chattingform.ui \
    clientmanagerform.ui \
    mainwindow.ui \
    ordermanagerform.ui \
    productmanagerform.ui

TRANSLATIONS += \
    Osstem_Project_ko_KR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
