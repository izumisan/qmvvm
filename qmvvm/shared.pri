# shared.pri

msvc: include(msvc.pri)

INCDIR = $${PWD}/include
SRCDIR = $${PWD}/src
LIBDIR = $${PWD}/lib
BINDIR = $${PWD}/bin

QML_IMPORT_PATH += $${PWD}/qml
RESOURCES += $${PWD}/qmvvm.qrc
