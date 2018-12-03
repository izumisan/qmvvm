# qmvvmlib.pri

include($${PWD}/shared.pri)

INCLUDEPATH += $${INCDIR}

CONFIG(debug, debug|release) {
    msvc: LIBS += $$quote($${LIBDIR}/debug/izm.qmvvm.lib)
} else {
    msvc: LIBS += $$quote($${LIBDIR}/release/izm.qmvvm.lib)
}
