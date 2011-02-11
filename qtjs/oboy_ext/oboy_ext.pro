TEMPLATE = app
QT += script network sql
QT -= gui
CONFIG += debug

SOURCES = *.cpp
HEADERS = *.h
INCLUDEPATH += /home/nikhil/workspace/qhttpserver/src
LIBS += -L/home/nikhil/workspace/qhttpserver/lib -lqhttpserver
