#-------------------------------------------------
#
# Project created by QtCreator 2018-10-06T15:59:48
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = QIMengine
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        qimengine.cpp \
    imoptions.cpp \
    imclient.cpp \
    imerror.cpp \
    immessage.cpp \
    qclient.cpp \
    qmqtt_client.cpp \
    qmqtt_client_p.cpp \
    qmqtt_frame.cpp \
    qmqtt_message.cpp \
    qmqtt_network.cpp \
    qmqtt_router.cpp \
    qmqtt_routesubscription.cpp \
    qmqtt_socket.cpp \
    qmqtt_ssl_socket.cpp \
    qmqtt_timer.cpp \
    qmqtt_websocket.cpp \
    qmqtt_websocketiodevice.cpp

HEADERS += \
        qimengine.h \
    imoptions.h \
    imclient.h \
    imerror.h \
    immessage.h \
    qclient.h \
    qmqtt.h \
    qmqtt_client.h \
    qmqtt_client_p.h \
    qmqtt_frame.h \
    qmqtt_global.h \
    qmqtt_message.h \
    qmqtt_message_p.h \
    qmqtt_networkinterface.h \
    qmqtt_network_p.h \
    qmqtt_routedmessage.h \
    qmqtt_router.h \
    qmqtt_routesubscription.h \
    qmqtt_socketinterface.h \
    qmqtt_socket_p.h \
    qmqtt_ssl_socket_p.h \
    qmqtt_timerinterface.h \
    qmqtt_timer_p.h \
    qmqtt_websocketiodevice_p.h \
    qmqtt_websocket_p.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
