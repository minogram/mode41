#ifndef DXF_GLOBAL_H
#define DXF_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DXF_LIBRARY)
#  define DXFSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DXFSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DXF_GLOBAL_H
