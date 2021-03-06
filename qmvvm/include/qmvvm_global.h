#ifndef IZM_QMVVM_GLOBAL_H
#define IZM_QMVVM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(IZM_QMVVM_LIBRARY)
#  define IZMQMVVMSHARED_EXPORT Q_DECL_EXPORT
#elif !defined(IZM_QMVVM_BUILT_IN)
#  define IZMQMVVMSHARED_EXPORT Q_DECL_IMPORT
#else
#  define IZMQMVVMSHARED_EXPORT
#endif

#endif // IZM_QMVVM_GLOBAL_H
