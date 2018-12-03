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
