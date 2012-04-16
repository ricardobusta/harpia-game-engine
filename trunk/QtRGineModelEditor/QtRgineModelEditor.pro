#-------------------------------------------------
#
# Project created by QtCreator 2012-04-08T16:44:06
#
#-------------------------------------------------

QT       += core gui\
            opengl

TARGET = QtRgineModelEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    material.cpp \
    model.cpp \
    normal.cpp \
    texture.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    material.h \
    model.h \
    normal.h \
    texture.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    testfile.txt \
    savedtestfile.txt
