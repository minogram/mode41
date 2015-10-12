#ifndef DXFMODEL_H
#define DXFMODEL_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

namespace dxf
{

//! DXF Entity's type.
enum EntityType
{
    UNKNOWN,
    E3DFACE,
    //        E3DSOLID, //encripted propietry data
    //        ACAD_PROXY_ENTITY,
    ARC,
    //        ATTDEF,
    //        ATTRIB,
    BLOCK,// and ENDBLK
    //        BODY, //encripted propietry data
    CIRCLE,
    DIMENSION,
    DIMALIGNED,
    DIMLINEAR,
    DIMRADIAL,
    DIMDIAMETRIC,
    DIMANGULAR,
    DIMANGULAR3P,
    DIMORDINATE,
    ELLIPSE,
    HATCH,
    //        HELIX,
    IMAGE,
    INSERT,
    LEADER,
    //        LIGHT,
    LINE,
    LWPOLYLINE,
    //        MESH,
    //        MLINE,
    //        MLEADERSTYLE,
    //        MLEADER,
    MTEXT,
    //        OLEFRAME,
    //        OLE2FRAME,
    POINT,
    POLYLINE,
    RAY,
    //        REGION, //encripted propietry data
    //        SECTION,
    //        SEQEND,//not needed?? used in polyline and insert/attrib and dwg
    //        SHAPE,
    SOLID,
    SPLINE,
    //        SUN,
    //        SURFACE, //encripted propietry data can be four types
    //        TABLE,
    TEXT,
    //        TOLERANCE,
    TRACE,
    UNDERLAY,
    VERTEX,
    VIEWPORT,
    //        WIPEOUT, //WIPEOUTVARIABLE
    //     XLINE,
 };

/**
 * @brief DXF AAMA layer definition
 */
enum AAMALayer
{
    Unknown = 0,
    Cut = 1,            //!<< CUT, OUTLINE (Rotary Blade)
    Notch = 4,          //!<< NOTCH
    Draw = 8,           //!<< DRAW, INK (Marker tool)
    Marker = 10,        //!<< MARKER
    InternalCut = 11,   //!<< INTCUT
    Drill = 13,         //!<< DRILL
    TextAlt = 15,       //!<< TEXT (Annotations)
    Text = 19,          //!<< TEXT (Marker)
    Reference = 26,
};

class DxfVertex;
class DxfEntity;
class DxfBlock;

typedef QList<QSharedPointer<DxfEntity>> DxfEntityList;
typedef QList<QSharedPointer<DxfVertex>> DxfVertexList;
typedef QList<QSharedPointer<DxfBlock>> DxfBlockList;

/**
 * @brief The DxfObject class
 */
class DxfObject
{
protected:
    DxfObject();
};

/**
 * @brief The DxfEntity class
 */
class DxfEntity : public DxfObject
{
protected:
    DxfEntity(EntityType type = EntityType::UNKNOWN);

public:
    EntityType type;
};

/**
 * @brief The DxfBlock class
 */
class DxfBlock : public DxfObject
{
public:
    DxfBlock();

public:
    QString name;
    DxfEntityList entities;

    QString layer; //!< code 8
    int flags = 0; //!< code 70 block-type-flags
    double x = 0.0; //!< code 10
    double y = 0.0; //!< code 20
    double z = 0.0; //!< code 30
};

/**
 * @brief The DxfModel class
 */
class DxfModel : public DxfObject
{
public:
    DxfModel();
    DxfBlockList blocks;
    DxfEntityList entities;
    DxfVertexList vertices;
};

/**
 * @brief The DxfInsert class
 */
class DxfInsert : public DxfEntity
{
public:
    DxfInsert();
    QString block;
    QString layer;
    double x = 0;
    double y = 0;
    double z = 0;
};

class DxfText : public DxfEntity
{
public:
    DxfText();
    QString text;
    QString layer;
    double x = 0;
    double y = 0;
    double z = 0;
    double size = 0; // 0.25 ?
    double rotation = 0; // default = 0;
};

/**
 * @brief dxf point entity
 */
class DxfPoint : public DxfEntity
{
public:
    DxfPoint();

    double x = 0.0;   //!< code 10
    double y = 0.0;   //!< code 20
    double z = 0.0;   //!< code 30
    double thickness = 0.0; //!< code 39

    QString layer;    //!< code 8
    //QVector3D extPoint; //!< extrusion normal vector, code 210, 220, 230
};

/**
 * @brief The DxfLine class
 */
class DxfLine : public DxfEntity
{
public:
    DxfLine();
    QString layer;

    double x1 = 0.0;  //!< code 10
    double y1 = 0.0;  //!< code 20
    double z1 = 0.0;  //!< code 30
    double x2 = 0.0;  //!< code 11
    double y2 = 0.0;  //!< code 21
    double z2 = 0.0;  //!< code 31
};

/**
 * @brief The DxfPolyline class
 */
class DxfPolyline : public DxfEntity
{
public:
    DxfPolyline();
    DxfVertexList vertices;
    QString layer;
    int flags = 0;
    bool isClosed() { return (flags & 1) != 0; }
};

class DxfVertex : public DxfEntity
{
public:
    DxfVertex();
    double x = 0.0;
    double y = 0.0;
    int flags = 0; //!< code 70 vertex flags
    QString layer;
};

}

#endif // DXFMODEL_H

