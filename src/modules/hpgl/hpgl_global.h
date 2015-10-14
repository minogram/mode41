#ifndef HPGL_GLOBAL_H
#define HPGL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HPGL_LIBRARY)
#  define HPGLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define HPGLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // HPGL_GLOBAL_H
