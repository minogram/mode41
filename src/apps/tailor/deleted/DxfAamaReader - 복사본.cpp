#include <iostream>

#include "DxfAamaReader.h"
#include "DxfModel.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

//HEADER section – General information about the drawing. Each parameter has a variable name and an associated value.
//CLASSES section – Holds the information for application-defined classes whose instances appear in the BLOCKS, ENTITIES, and OBJECTS sections of the database. Generally does not provide sufficient information to allow interoperability with other programs.
//TABLES section – This section contains definitions of named items.
//Application ID (APPID) table
//Block Record (BLOCK_RECORD) table
//Dimension Style (DIMSTYPE) table
//Layer (LAYER) table
//Linetype (LTYPE) table
//Text style (STYLE) table
//User Coordinate System (UCS) table
//View (VIEW) table
//Viewport configuration (VPORT) table
//BLOCKS section – This section contains Block Definition entities describing the entities comprising each Block in the drawing.
//ENTITIES section – This section contains the drawing entities, including any Block References.
//OBJECTS section – Contains the data that apply to nongraphical objects, used by AutoLISP and ObjectARX applications.
//THUMBNAILIMAGE section – Contains the preview image for the DXF file.
//END OF FILE

//using namespace dxf;

DxfAamaReader::DxfAamaReader(QObject *parent)
    : QObject(parent)
{
}

dxf::DxfModel *DxfAamaReader::load(QString fileName)
{
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", file.errorString());
    }

    in.setDevice(&file);
    //in = new QTextStream(&file);
    m_model = new dxf::DxfModel(parent());
    readSECTIONS();

    //delete in;
    file.close();

    //foreach(auto it, m_model->blocks) qDebug() << it->name;

    return m_model;
}

bool DxfAamaReader::readNext()
{
    //if (in->atEnd()) return false;
    if (in.atEnd()) return false;
    //QString line1 = in->readLine().trimmed();
    QString line1 = in.readLine().trimmed();
    m_lineCount++;

    if (in.atEnd()) return false;
   // QString line2 = in->readLine().trimmed();
    QString line2 = in.readLine().trimmed();
    m_lineCount++;

    m_code = line1.toInt();
    m_value = line2;

    return true;
}

//bool DxfAamaReader::readUntil(int code)
//{
//    return readNext() && m_code != code;
//}

///**
// * @brief read dxf record and return true, if meet code & value, returns false
// * @param code
// * @param value
// * @return
// */
//bool DxfAamaReader::readUntil(int code, const QString &value)
//{
//    return readNext() && m_code != code && m_value != value;
//}

//bool DxfAamaReader::Check(int code, const QString &value)
//{
//    if (m_code == code && m_value == value) return true;
//    return false;
//}

void DxfAamaReader::skipTo(int code)
{
    //for (readNext(); m_code != 0; readNext());

    do { readNext(); } while (m_code != code);

    //while (readUntil(code));
}

void DxfAamaReader::skipTo(int code, const QString &value)
{
    //while (readUntil(code, value));

    do { readNext(); } while (m_code != code || m_value != value);
}

void DxfAamaReader::readSECTIONS()
{
    while (readNext())
    {
        Q_ASSERT(m_code == 0);

        if (is(0, "EOF")) break;

        if (is(0, "SECTION"))
        {
            readSECTION();
        }
        else
        {
            qDebug() << "ERR1";
        }
    }

//    while (readNext())
//    {
//        //if (m_code != 0) { qDebug() <<"OOOOOPS" << m_value; }
//        Q_ASSERT(m_code == 0);

//        if (m_code == 0)
//        {
//            if (m_value == "EOF")
//            {
//                qDebug() << "EOF";
//                addEOF();
//                return;
//            }
//            else if (m_value == "SECTION")
//            {
//                readSECTION();
//            }
//        }
//    }

//    while (readUntil(0, "EOF"))
//    {
//        if (m_code == 0 && m_value == "SECTION")
//        {
//            readSECTION();
//        }
//        else
//        {
//            qDebug() << "ERR";
//        }
//    }
}

void DxfAamaReader::readSECTION()
{
    Q_ASSERT(m_code == 0);
    Q_ASSERT(m_value == "SECTION");

    readNext();

    if (m_code == 2)
    {
        m_section = m_value;

        if (m_value == "HEADER")
        {
            readHEADER();
        }
        else if (m_value == "CLASSES")
        {
            qDebug() << "SKIP " << m_code << ", " << m_value;
            skipTo(0, "ENDSEC");
        }
        else if (m_value == "TABLESS")
        {
            qDebug() << "SKIP " << m_code << ", " << m_value;
            skipTo(0, "ENDSEC");
        }
        else if (m_value == "BLOCKS")
        {
            readBLOCKS(m_model->blocks);
        }
        else if (m_value == "ENTITIES")
        {
            readENTITIES();
        }
        else if (m_value == "OBJECTS")
        {
            qDebug() << "SKIP " << m_code << ", " << m_value;
            skipTo(0, "ENDSEC");
        }
        else if (m_value == "THUMBNAILIMAGE")
        {
            qDebug() << "SKIP " << m_code << ", " << m_value;
            skipTo(0, "ENDSEC");
        }
        else
        {
            qDebug() << "SKIP " << m_code << ", " << m_value;
            skipTo(0, "ENDSEC");
        }
    }
}

void DxfAamaReader::readHEADER()
{
    Q_ASSERT(m_code == 2);
    Q_ASSERT(m_value == "HEADER");

    skipTo(0, "ENDSEC");
}

void DxfAamaReader::readBLOCKS(dxf::DxfBlockList &list)
{
    Q_ASSERT(m_code == 2);
    Q_ASSERT(m_value == "BLOCKS");

    while (readNext())
    {
        if (m_code == 0 && m_value == "BLOCK")
        {
            readBLOCK(list);
        }
        else if (m_code == 0 && m_value == "ENDSEC")
        {
            return;
        }
    }
}

void DxfAamaReader::readBLOCK(dxf::DxfBlockList &list)
{
    Q_ASSERT(m_code == 0);
    Q_ASSERT(m_value == "BLOCK");

    auto block = new dxf::DxfBlock(m_model->parent());

    for (readNext(); m_code != 0; readNext())
    {
        if (m_code == 8) // layer name
        {
            block->layer = m_value;
        }
        else if (m_code == 2) // block name
        {
            block->name = m_value;
        }
        else if (m_code == 70) // block flags
        {
            block->flags = m_value.toInt();
            // todo;
//            Block-type flags (bit coded values, may be combined):
//            1 = This is an anonymous block generated by hatching, associative dimensioning, other internal operations, or an application
//            2 = This block has attribute definitions
//            4 = This block is an external reference (xref)
//            8 = This block is an xref overlay
//            16 = This block is externally dependent
//            32 = This is a resolved external reference, or dependent of an external reference (ignored on input)
//            64 = This definition is a referenced external reference (ignored on input)
        }
        else if (m_code == 10)
        {
            block->x = m_value.toDouble();
        }
        else if (m_code == 20)
        {
            block->y = m_value.toDouble();
        }
        else if (m_code == 30)
        {
            block->z = m_value.toDouble();
        }
        else
        {
            qDebug() << "UNKNOWN: " << m_code << ", " << m_value;
        }
    }

    Q_ASSERT(m_code == 0);

    while (true)
    {
        Q_ASSERT(m_code == 0);

        if (m_value == "ENDBLK")
        {
            list.append(block);
            break;
        }
        else
        {
            readENTITY(block->entities);
        }
    }
}

void DxfAamaReader::readENTITIES()
{
    Q_ASSERT(m_code == 2);
    Q_ASSERT(m_value == "ENTITIES");

    skipTo(0, "ENDSEC");

//    while (readUntil(0, "ENDSEC"))
//    {

//    }
}

void DxfAamaReader::readENTITY(dxf::DxfEntityList &list)
{
    Q_ASSERT(m_code == 0);
    Q_ASSERT(m_value != "ENDSEC");

    if (m_value == "LINE")
    {
        readLINE(list);
    }
    else if (m_value == "POLYLINE")
    {
        readPOLYLINE(list);
    }
    else if (m_value == "CIRCLE")
    {
        skipTo(0);
    }
    else if (m_value == "TEXT")
    {
        readTEXT(list);
    }
    else if (m_value == "POINT")
    {
        readPOINT(list);
    }
    else
    {
        //skipTo(0);
        qDebug() << "unknown entity: " << m_value;
    }
}

void DxfAamaReader::readPOINT(dxf::DxfEntityList &list)
{
    Q_ASSERT(m_code == 0);
    Q_ASSERT(m_value == "POINT");

    auto point = new dxf::DxfPoint(m_model->parent());

    for (readNext(); m_code != 0; readNext())
    {
        if (m_code == 8) // layer name
        {
            point->layer = m_value;
        }
        else if (m_code == 10) // x1
        {
            point->x = m_value.toDouble();
        }
        else if (m_code == 20) // y1
        {
            point->y = m_value.toDouble();
        }
        else if (m_code == 30) // z1
        {
            point->z = m_value.toDouble();
        }
        else if (m_code == 38)
        {
            // todo: notch length
        }
        else if (m_code == 39)
        {
            // todo: notch width
        }
        else if (m_code == 50)
        {
            // todo: angle
        }
        else
        {
            qDebug() << "POINT UNKNOWN: " << m_code << ", " << m_code;
        }
    }

    if (point) list.append(point);

//    switch (layer)
//                {
//                    case 0:
//                        break;
//                    case 2:
//                        //if (design.Author == "SCANVEC GARMENT SYSTEMS")
//                        //{
//                              //SetTurnPoint(paths, point);
//                        //}
//                        SetCuspPoint(paths, point);
//                        break;
//                    case 4:
//                        PatternNotch notch = new PatternNotch();
//                        notch.Length = notchLength;
//                        notch.Angle = angle;
//                        notch.Location = point;
//                        //if (lastPath != null)
//                        //    lastPath.Notchs.Add(notch);
//                        if (paths != null)
//                            SetNotchPoint(paths, notch);
//                        break;
//                    case 13:
//                        PatternDrillHole hole = new PatternDrillHole();
//                        hole.Location = point;
//                        piece.Entities.Add(hole);
//                        break;
//                    case 3:
//                        //if (!(design.Author == "SCANVEC GARMENT SYSTEMS"))
//                        //{
//                        //    if (lastPath != null)
//                        //        SetCurvePoint(lastPath, point);
//                        //}
//                        //else
//                        //{
//                        if (paths != null)
//                            SetCurvePoint(paths, point);
//                        //}
//                        break;
//                    default:
//                        //TODO :
//                        break;
//                }

    //MoveNext();


//    100
//    Subclass marker (AcDbPoint)
//    10
//    Point location (in WCS)
//    DXF: X value; APP: 3D point
//    20, 30
//    DXF: Y and Z values of point location (in WCS)
//    39
//    Thickness (optional; default = 0)
//    210
//    Extrusion direction (optional; default = 0, 0, 1)
//    DXF: X value; APP: 3D vector
//    220, 230
//    DXF: Y and Z values of extrusion direction (optional)
//    50
//    Angle of the X axis for the UCS in effect when the point was drawn (optional, default = 0); used when PDMODE is nonzero
}


void DxfAamaReader::readTEXT(dxf::DxfEntityList &list)
{
    Q_ASSERT(m_code == 0);
    Q_ASSERT(m_value == "TEXT");

    auto entity = new dxf::DxfText(m_model->parent());
    for (readNext(); m_code != 0; readNext())
    {
        if (m_code == 1)
        {
            entity->text = m_value;
            //qDebug() << entity->text;
        }
        else if (m_code == 8)
        {
            entity->layer = m_value;
            //qDebug() << entity->layer;
        }
        else if (m_code == 10) // x1
        {
            entity->x = m_value.toDouble();
        }
        else if (m_code == 20) // y1
        {
            entity->y = m_value.toDouble();
        }
        else if (m_code == 30) // z1
        {
            entity->z = m_value.toDouble();
        }
        else if (m_code == 40) // size
        {
            entity->size = m_value.toDouble();
        }
    }
    list.append(entity);
}

void DxfAamaReader::readLINE(dxf::DxfEntityList &list)
{
    Q_ASSERT(m_code == 0);
    Q_ASSERT(m_value == "LINE");

    auto line = new dxf::DxfLine(m_model->parent());

    for (readNext(); m_code != 0; readNext())
    {
        if (m_code == 8) // layer name
        {
            line->layer = m_value;
        }
        else if (m_code == 10) // x1
        {
            line->x1 = m_value.toDouble();
        }
        else if (m_code == 20) // y1
        {
            line->y1 = m_value.toDouble();
        }
        else if (m_code == 30) // z1
        {
            line->z1 = m_value.toDouble();
        }
        else if (m_code == 11) // x2
        {
            line->x2 = m_value.toDouble();
        }
        else if (m_code == 21) // y2
        {
            line->y2 = m_value.toDouble();
        }
        else if (m_code == 31) // z2
        {
            line->z2 = m_value.toDouble();
        }
        else
        {
            qDebug() << "POINT UNKNOWN: " << m_code << ", " << m_code;
        }
    }

    Q_ASSERT(line != nullptr);
    list.append(line);
}

void DxfAamaReader::readPOLYLINE(dxf::DxfEntityList &list)
{
    Q_ASSERT(m_code == 0);
    Q_ASSERT(m_value == "POLYLINE");

    auto polyline = new dxf::DxfPolyline(m_model->parent());

    for (readNext(); m_code != 0; readNext())
    {
        if (m_code == 66)
        {

        }
        else if (m_code == 8)
        {
            polyline->layer = m_value;
        }
        else if (m_code == 70)
        {
//            Polyline flag (bit-coded); default is 0:
//            1 = This is a closed polyline (or a polygon mesh closed in the
//            M direction).
//            2 = Curve-fit vertices have been added.
//            4 = Spline-fit vertices have been added.
//            8 = This is a 3D polyline.
//            16 = This is a 3D polygon mesh.
//            32 = The polygon mesh is closed in the N direction.
//            64 = The polyline is a polyface mesh.
//            128 = The linetype pattern is generated continuously around the vertices of this polyline.
            polyline->flags = m_value.toInt();
        }
        else
        {
            qDebug() << "POLYLINE UNKNOWN: " << m_code << ", " << m_code;
        }
    }

    Q_ASSERT(m_code == 0);

    for (;;)
    {
        if (m_value == "SEQEND")
        {
            readENDSEQ();
            break;
        }
        else if (m_value == "VERTEX")
        {
            readVERTEX(polyline->vertices);
        }
        else
        {
            qDebug() << "expected: vertex, endseq";
        }
    }

    if (polyline)
    {
        list.append(polyline);
    }
}

// 0 POLYLINE
// 10 <X>
// 20 <Y>
// 0 VERTEX
// 10 <X>
// 20 <Y>
// 0 VERTEX
// 10 <X>
// 20 <Y>
// 0 SEQEND
// 8 1
// -- expect 0 POLYLINE
void DxfAamaReader::readVERTEX(dxf::DxfVertexList &list)
{
    Q_ASSERT(m_code == 0);
    Q_ASSERT(m_value == "VERTEX");

    dxf::DxfVertex *vertex = nullptr;

    if (m_value == "VERTEX")
    {
        vertex = new dxf::DxfVertex(m_model->parent());
    }

    for (readNext(); m_code != 0; readNext())
    {
        if (m_code == 8)
        {
            vertex->layer = m_value;
        }
        else if (m_code == 10)
        {
            vertex->x = m_value.toDouble();
        }
        else if (m_code == 20)
        {
            vertex->y = m_value.toDouble();
        }
        else if (m_code == 70)
        {
            vertex->flags = m_value.toInt();
        }
        else
        {
            qDebug() << "UNEXPECTEd in vertex:???? " << m_code << ", " << m_value;
        }
    }

    if (vertex)
    {
        list.append(vertex);
    }

    Q_ASSERT(m_code == 0);
}

void DxfAamaReader::readENDSEQ()
{
    Q_ASSERT(m_code == 0);
    Q_ASSERT(m_value == "SEQEND");

    for (readNext(); m_code != 0; readNext())
    {
        if (m_code == 8)
        {
            // todo:
        }
        else
        {
            qDebug() << "UNEXPECted in seqend: " << m_code << ", " << m_value;
        }
    }

    Q_ASSERT(m_code == 0);
}


//HEADER section – General information about the drawing. Each parameter has a variable name and an associated value.
//CLASSES section – Holds the information for application-defined classes whose instances appear in the BLOCKS, ENTITIES, and OBJECTS sections of the database. Generally does not provide sufficient information to allow interoperability with other programs.
//TABLES section – This section contains definitions of named items.
//Application ID (APPID) table
//Block Record (BLOCK_RECORD) table
//Dimension Style (DIMSTYPE) table
//Layer (LAYER) table
//Linetype (LTYPE) table
//Text style (STYLE) table
//User Coordinate System (UCS) table
//View (VIEW) table
//Viewport configuration (VPORT) table
//BLOCKS section – This section contains Block Definition entities describing the entities comprising each Block in the drawing.
//ENTITIES section – This section contains the drawing entities, including any Block References.
//OBJECTS section – Contains the data that apply to nongraphical objects, used by AutoLISP and ObjectARX applications.
//THUMBNAILIMAGE section – Contains the preview image for the DXF file.
//END OF FILE


//void DxfReader::addBlock(const DRW_Block& data)
//{
//    std::cout << "addBlock()\n";
//}

//void DxfReader::endBlock()
//{
//    std::cout << "endBlock()\n";
//}

//void DxfReader::addLine(const DRW_Line &data) {
//    /*
//		std::cout << "-------Line-------\n";
//    std::cout << "Start \n X\t Y\n";
//    std::cout << data.basePoint.x;
//    std::cout << "\t";
//    std::cout << data.basePoint.y;
//    std::cout << "\n";
//    std::cout << "End \n X\t Y\n";
//    std::cout << data.secPoint.x;
//    std::cout << "\t";
//    std::cout << data.secPoint.y;
//    std::cout << "\n";
//    */
//}

//void DxfReader::addCircle(const DRW_Circle& data) {
//    /*
//		std::cout << "-------Circle-------\n";
//		std::cout << "Radius:"<<data.radious;
//		std::cout << "\nCenter\n";
//		std::cout << "X\t Y\n";
//		std::cout << data.basePoint.x;
//		std::cout << "\t";
//		std::cout << data.basePoint.y;
//		std::cout << "\n";
//        */
//}


//void DxfReader::addPolyline(const DRW_Polyline& data)
//{
//    //std::cout << "Polyline";
//}
