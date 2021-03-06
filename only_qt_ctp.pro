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
    ctp_quote_qthread.cpp \
    ../gpp_qt/bar/bar.cpp \
    ../gpp_qt/bar/bars.cpp \
    ../gpp_qt/bar/bars_manage.cpp \
    ../gpp_qt/cfg/cfg.cpp \
    ../gpp_qt/wfunction/wfunction.cpp \
    ../gpp_qt/log_info/log_info.cpp \
    ctp_trade_qthread.cpp\
    ctp_trade.cpp \
    ctp_log.cpp \
    ctp_order.cpp \
    ctp_order_manager.cpp \
    tactic.cpp \
    ctp_manager.cpp \
    need_to_do.cpp \
    ../gpp_qt/cmd_line/cmd_line.cpp

HEADERS  += mainwindow.h \
    ../libs/ctp/ThostFtdcMdApi.h \
    ../libs/ctp/ThostFtdcTraderApi.h \
    ctp_quote.h \
    ctp_quote_qthread.h \
    ../gpp_qt/bar/bar.h \
    ../gpp_qt/bar/bars.h \
    ../gpp_qt/bar/bars_manage.h \
    ../gpp_qt/cfg/cfg.h \
    ../gpp_qt/wfunction/wfunction.h \
    ../gpp_qt/wtimer/wtimer.h \
    ../gpp_qt/log_info/log_info.h \
    ctp_trade.h \
    ctp_log.h \
    ctp_trade_qthread.h\
    ../libs/ctp/ThostFtdcTraderApi.h \
    ../libs/ctp/ThostFtdcMdApi.h \
    ctp_order.h \
    ctp_order_manager.h \
    tactic.h \
    ctp_manager.h \
    need_to_do.h \
    ../gpp_qt/cmd_line/cmd_line.h

FORMS    += mainwindow.ui


win32: LIBS += -L$$PWD/../libs/ctp/ -lthostmduserapi

INCLUDEPATH += $$PWD/../libs/ctp
DEPENDPATH += $$PWD/../libs/ctp

win32: LIBS += -L$$PWD/../libs/ctp/ -lthosttraderapi

INCLUDEPATH += $$PWD/../libs/ctp
DEPENDPATH += $$PWD/../libs/ctp

