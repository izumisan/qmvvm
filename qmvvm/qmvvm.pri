# qmvvm.pri

include($${PWD}/shared.pri)

INCLUDEPATH += \
    $${INCDIR} \
    $${SRCDIR}

HEADERS += \
    $${INCDIR}/*.h \
    $${SRCDIR}/*.h

SOURCES += \
    $${SRCDIR}/*.cpp

QML_IMPORT_PATH += $${PWD}/qml
RESOURCES += $${PWD}/qmvvm.qrc
