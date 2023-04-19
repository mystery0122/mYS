#-------------------------------------------------
#
# Project created by QtCreator 2022-12-13T17:20:34
#
#-------------------------------------------------

QT       += core gui network
QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS +=  -fpermissive -lm -lrt
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = engine
TEMPLATE = app

CONFIG += c++11
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

include($$PWD/../QSsh/QSsh.pri)

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    CConnectionForSshClient.cpp \
    global.cpp \
        main.cpp \
        mainwindow.cpp \
    myscreen1.cpp \
    myscreen2.cpp \
    myscreen3.cpp \
    myscreen4.cpp \
    qcustomplot.cpp \
    controller.c \
    controller_data.c \
    model.c \
    model_data.c \
    model_thread.cpp \
    Burner_TMATS_body.c \
    calc_PsvsMN_TMATS.c \
    calc_WvsMN_TMATS.c \
    Compressor_TMATS_body.c \
    functions_TMATS.c \
    h2tc_TMATS.c \
    interp1Ac_TMATS.c \
    interp2Ac_TMATS.c \
    interp3Ac_TMATS.c \
    Nozzle_TMATS_body.c \
    PcalcStat_TMATS.c \
    pt2sc_TMATS.c \
    rt_nonfinite.c \
    rtGetInf.c \
    rtGetNaN.c \
    sp2tc_TMATS.c \
    t2hc_TMATS.c \
    Turbine_TMATS_body.c \
    file.cpp \
    opt_file.cpp \
    JT9D_Model_Dyn_old1.cpp \
    JT9D_Model_Dyn_old1_data.cpp

HEADERS += \
    CConnectionForSshClient.h \
    global.h \
        mainwindow.h \
    myscreen1.h \
    myscreen2.h \
    myscreen3.h \
    myscreen4.h \
    qcustomplot.h \
    controller.h \
    controller_private.h \
    controller_types.h \
    model.h \
    model_private.h \
    model_types.h \
    rt_nonfinite.h \
    rtGetInf.h \
    rtGetNaN.h \
    rtwtypes.h \
    zero_crossing_types.h \
    model_thread.h \
    types_TMATS.h \
    functions_TMATS.h \
    file.h \
    opt_file.h \
    JT9D_Model_Dyn_old1.h \
    JT9D_Model_Dyn_old1_private.h \
    JT9D_Model_Dyn_old1_types.h \
    rtw_continuous_1.h \
    rtw_solver_1.h

FORMS += \
        mainwindow.ui \
    file.ui \
    myscreen1.ui \
    myscreen2.ui \
    myscreen3.ui \
    myscreen4.ui \
    opt_file.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
