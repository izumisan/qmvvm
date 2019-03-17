# qmvvm.pri

include($${PWD}/qmvvmdir.pri)

INCLUDEPATH += \
    $${QMVVM_INCDIR} \
    $${QMVVM_SRCDIR}

HEADERS += \
    $${QMVVM_INCDIR}/*.h \
    $${QMVVM_SRCDIR}/*.h

SOURCES += \
    $${QMVVM_SRCDIR}/*.cpp

QML_IMPORT_PATH += $${PWD}/qml
RESOURCES += $${PWD}/qmvvm.qrc
