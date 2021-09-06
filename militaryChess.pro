######################################################################
# Automatically generated by qmake (3.1) Wed Aug 18 07:52:40 2021
######################################################################

QT += gui widgets core network
TEMPLATE = app
TARGET = militaryChess
INCLUDEPATH += .
CONFIG += console c++14

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += connect_server.h create_server.h mainwindow.h \
    mybutton.h \
    myresult.h
FORMS += connect_server.ui create_server.ui mainwindow.ui \
    myresult.ui
SOURCES += connect_server.cpp create_server.cpp main.cpp mainwindow.cpp \
    mybutton.cpp \
    myresult.cpp
RESOURCES += icon/icon.qrc \
    cross/cross.qrc \
    icon/icon.qrc \
    light/light.qrc \
    pic/png/png.qrc \
    wrong/wrong.qrc \
    wrongWarn/warn.qrc