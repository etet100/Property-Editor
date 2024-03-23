#-------------------------------------------------
#
# Project created by QtCreator 2014-11-28T23:45:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PropertyEditor
TEMPLATE = lib
CONFIG -= debug_and_release

SOURCES += CPropertyEditor.cpp \
    CBoolProperty.cpp \
    CBaseProperty.cpp \
    CIntegerProperty.cpp \
    CStringProperty.cpp \
    CDoubleProperty.cpp \
    CListProperty.cpp \
    CPropertyHeader.cpp \
    CFontProperty.cpp \
    CButtonBasedEditor.cpp \
    CSwitchProperty.cpp \
    QColorComboBox.cpp \
    CColorProperty.cpp \
    CDateProperty.cpp \
    CTimeProperty.cpp \
    CDateTimeProperty.cpp \
    QExtDoubleSpinBox.cpp \
    QExtSpinbox.cpp \
    X_Switch_Button/x_switch_button.cpp

HEADERS  += CPropertyEditor.h \
    CBoolProperty.h \
    CBaseProperty.h \
    CIntegerProperty.h \
    CStringProperty.h \
    CDoubleProperty.h \
    CListProperty.h \
    CPropertyHeader.h \
    CFontProperty.h \
    CButtonBasedEditor.h \
    CSwitchProperty.h \
    Callbacks.h \
    QColorComboBox.h \
    CColorProperty.h \
    CDateProperty.h \
    CTimeProperty.h \
    CDateTimeProperty.h \
    QExtDoubleSpinBox.h \
    QExtSpinBox.h \
    X_Switch_Button/x_switch_button.h

INCLUDEPATH += .

RESOURCES += \
    testwidget.qrc

install_propertyeditor.path = ../../bin
install_propertyeditor.files = PropertyEditor/PropertyEditor.dll

INSTALLS += install_propertyeditor

DISTFILES += \
    X_Switch_Button/x_switch_button.gif
