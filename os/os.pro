#-------------------------------------------------
#
# Project created by QtCreator 2017-11-14T15:36:22
#
#-------------------------------------------------
include(../os_global.pri)
QT       -= gui
QT += network

TARGET = $$qtLibraryTarget(platform_os)
TEMPLATE = lib
CONFIG += staticlib c++11 debug_and_release build_all

DESTDIR = D:\software\dev\qt\platform\lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(internal/internal.pri)

HEADERS += \
    handler.h \
    message.h \
    handlerdefine.h \
    localconnection.h \
    localmessage.h \
    localconnectiondefine.h \
    servicemanager.h \
    localservice.h \
    asynctask.h \
    asynctaskexecutor.h

SOURCES += \
    handler.cpp \
    message.cpp \
    localconnection.cpp \
    localmessage.cpp \
    servicemanager.cpp \
    localservice.cpp \
    asynctask.cpp \
    asynctaskexecutor.cpp


