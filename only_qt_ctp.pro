#-------------------------------------------------
#
# Project created by QtCreator 2014-10-30T15:44:21
#
#-------------------------------------------------

QT       += core gui
QT += network widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CTP_QUOTE_DISPLAY
TEMPLATE = app

INSTALLS += target

SOURCES += main.cpp\
        mainwindow.cpp \
    ctp_quote.cpp \
    sender.cpp \
    ctp_quote_qthread.cpp \
    ../gpp_qt/bar/bar.cpp \
    ../gpp_qt/bar/bars.cpp \
    ../gpp_qt/bar/bars_manage.cpp \
    ../gpp_qt/cfg/cfg.cpp \
    ../gpp_qt/wfunction/wfunction.cpp \
    ../gpp_qt/wtimer/wtimer.cpp

HEADERS  += mainwindow.h \
    ctp/ThostFtdcMdApi.h \
    ctp/ThostFtdcTraderApi.h \
    ctp_quote.h \
    sender.h \
    ctp_quote_qthread.h \
    ../gpp_qt/bar/bar.h \
    ../gpp_qt/bar/bars.h \
    ../gpp_qt/bar/bars_manage.h \
    ../gpp_qt/cfg/cfg.h \
    ../gpp_qt/wfunction/wfunction.h \
    ../gpp_qt/wtimer/wtimer.h

FORMS    += mainwindow.ui

win32: LIBS += -L$$PWD/ctp/ -lthostmduserapi

INCLUDEPATH += $$PWD/ctp
DEPENDPATH += $$PWD/ctp

win32: LIBS += -L$$PWD/ctp/ -lthosttraderapi

INCLUDEPATH += $$PWD/ctp
DEPENDPATH += $$PWD/ctp
