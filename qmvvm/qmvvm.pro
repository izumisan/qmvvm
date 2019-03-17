# izm.qmvvm.dll

QT -= gui
QT += quickcontrols2

TARGET = izm.qmvvm
TEMPLATE = lib
CONFIG += dll

DEFINES += IZM_QMVVM_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

msvc: include(msvc.pri)
include(qmvvm.pri)

CONFIG(debug, debug|release) {
    DESTDIR = $${QMVVM_LIBDIR}/debug
    DLLDESTDIR = $${QMVVM_BINDIR}/debug
} else {
    DESTDIR = $${QMVVM_LIBDIR}/release
    DLLDESTDIR = $${QMVVM_BINDIR}/release
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += qmvvmlib.pri
