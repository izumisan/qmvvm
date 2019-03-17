# qmvvmlib.pri

msvc: include($${PWD}/msvc.pri)
include($${PWD}/qmvvmdir.pri)

INCLUDEPATH += $${QMVVM_INCDIR}

CONFIG(debug, debug|release) {
    LIBS += -L$$quote($${QMVVM_LIBDIR}/debug)
} else {
    LIBS += -L$$quote($${QMVVM_LIBDIR}/release)
}

LIBS += -lizm.qmvvm

QML_IMPORT_PATH += $${PWD}/qml
RESOURCES += $${PWD}/qmvvm.qrc

defineReplace(qmvvmCopyCommand) {
    src = $$1
    dest = $$2

    arg1 = \"$$replace(src, /, $$QMAKE_DIR_SEP)\"
    arg2 = \"$$replace(dest, /, $$QMAKE_DIR_SEP)\"

    command = ""
    !equals(arg1, $$arg2) {
        command = $(COPY_FILE) $${arg1} $${arg2}
    }
    return($$command)
}

# qmvvmCopyCommand example
#qmvvm.depends = path/to/src/izm.qmvvm.dll
#qmvvm.target = path/to/dest/izm.qmvvm.dll
#qmvvm.commands = $$qmvvmCopyCommand($$qmvvm.depends, $$qmvvm.target)
#QMAKE_EXTRA_TARGETS += qmvvm
#PRE_TARGETDEPS += $$qmvvm.target
