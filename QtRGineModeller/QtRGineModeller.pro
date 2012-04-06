#-------------------------------------------------
#
# Project created by QtCreator 2012-04-06T10:30:17
#
#-------------------------------------------------

QT       += core gui\
            opengl

TARGET = QtRgineModeller
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    material.cpp \
    object.cpp \
    face.cpp \
    vertex.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    material.h \
    object.h \
    face.h \
    vertex.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    filemodel.txt
