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
    modelobject.cpp \
    modelface.cpp \
    modelvertex.cpp \
    modelnormal.cpp \
    modeltexcoord.cpp \
    modelanimation.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    material.h \
    model.h \
    modelobject.h \
    modelface.h \
    modelvertex.h \
    modelnormal.h \
    modeltexcoord.h \
    modelanimation.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    examplemodel.txt
