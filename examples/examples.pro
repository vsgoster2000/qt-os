#-------------------------------------------------
#
# Project created by QtCreator 2017-11-14T15:52:14
#
#-------------------------------------------------
include(../os_global.pri)

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = examples
TEMPLATE = app
CONFIG += c++11
#INCLUDEPATH += D:\software\dev\qt\platform\include
#INCLUDEPATH += D:\software\dev\qt\platform\include\platform

#LIBS += -LD:\software\dev\qt\platform\lib -l$$qtLibraryTarget(platform_os)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        maindialog.cpp \
    handlertestdialog.cpp \
    servicetestdialog.cpp \
    clienttestdialog.cpp \
    $$PROJECT_SRC/asynctask.cpp \
    $$PROJECT_SRC/asynctaskexecutor.cpp \
    $$PROJECT_SRC/handler.cpp \
    $$PROJECT_SRC/message.cpp \
    $$PROJECT_SRC/localconnection.cpp \
    $$PROJECT_SRC/localmessage.cpp \
    $$PROJECT_SRC/localservice.cpp \
    $$PROJECT_SRC/servicemanager.cpp \
    $$PROJECT_SRC/internal/localserver.cpp \
    $$PROJECT_SRC/internal/localsocket.cpp \
    $$PROJECT_SRC/internal/localsocketconnector.cpp \
    asynctasktestdialog.cpp

HEADERS += \
        maindialog.h \
    handlertestdialog.h \
    servicetestdialog.h \
    clienttestdialog.h \
    $$PROJECT_SRC/asynctask.h \
    $$PROJECT_SRC/asynctaskexecutor.h \
    $$PROJECT_SRC/handler.h \
    $$PROJECT_SRC/message.h \
    $$PROJECT_SRC/handlerdefine.h \
    $$PROJECT_SRC/localconnection.h \
    $$PROJECT_SRC/localmessage.h \
    $$PROJECT_SRC/localservice.h \
    $$PROJECT_SRC/localconnectiondefine.h \
    $$PROJECT_SRC/servicemanager.h \
    $$PROJECT_SRC/internal/localserver.h \
    $$PROJECT_SRC/internal/localsocket.h \
    $$PROJECT_SRC/internal/localsocketconnector.h \
    chattingservice.h \
    asynctasktestdialog.h


FORMS += \
        maindialog.ui \
    handlertestdialog.ui \
    servicetestdialog.ui \
    clienttestdialog.ui \
    asynctasktestdialog.ui
