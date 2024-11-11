#-------------------------------------------------
#
# Project created by QtCreator 2014-11-28T23:45:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = PropertyEditor
TEMPLATE = lib
CONFIG -= debug_and_release

include(PropertyEditor.pri)

INCLUDEPATH += .

RESOURCES += \
    testwidget.qrc

install_propertyeditor.path = ../../bin
install_propertyeditor.files = PropertyEditor/PropertyEditor.dll

INSTALLS += install_propertyeditor

DISTFILES += \
    PropertyEditor.pri \
    X_Switch_Button/x_switch_button.gif
