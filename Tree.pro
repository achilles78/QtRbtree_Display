#-------------------------------------------------
#
# Project created by QtCreator 2018-10-25T21:28:51
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tree
TEMPLATE = app

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
    drawingwidget.cpp \
    ibintree.cpp \
        main.cpp \
        mainwindow.cpp \
    binarytree.cpp \
    mydialog.cpp \
    rbtree/rb_common.cpp \
    rbtree/rb_delete.cpp \
    rbtree/rb_insert.cpp \
    rbtree/travel.cpp \
    rbtree/queue.cpp

HEADERS += \
    drawingwidget.h \
    ibintree.h \
        mainwindow.h \
    binarytree.h \
    mydialog.h \
    rbtree/include/head4rb.h \
    rbtree/include/head4tree.h \
    rbtree/include/commonheader.h \
    rbtree/include/head4queue.h

FORMS += \
        mainwindow.ui \
    mydialog.ui
CONFIG +=C++11
