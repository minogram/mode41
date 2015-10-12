#ifndef PGM_GLOBAL_H
#define PGM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PGM_LIBRARY)
#  define PGMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PGMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PGM_GLOBAL_H
