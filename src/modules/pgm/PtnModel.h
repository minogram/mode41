#ifndef PTNMODEL_H
#define PTNMODEL_H

#include <QObject>
#include <QList>
#include <QPointF>
#include <QSharedPointer>

class PtnEntity;
class PtnVertex;
class PtnPiece;

//typedef QList<PtnEntity *> PtnEntityList;
//typedef QList<PtnVertex *> PtnVertexList;
//typedef QList<PtnPiece *> PtnPieceList;
typedef QList<QSharedPointer<PtnEntity>> PtnEntityList;
typedef QList<QSharedPointer<PtnVertex>> PtnVertexList;
typedef QList<QSharedPointer<PtnPiece>> PtnPieceList;

enum PtnEntityType {
    Unknown = 0,
    Line = 1,
    Polyline = 2,
    Text = 3,
};

class PtnObject
{
public:
    explicit PtnObject();
};

class PtnVertex : PtnObject
{
public:
    explicit PtnVertex();
    double x = 0;
    double y = 0;
};

class PtnDesign : public PtnObject
{
public:
    explicit PtnDesign();
    QList<QString> sizes;
    QString baseSize;
    PtnPieceList pieces;
    PtnEntityList entities;
signals:

public slots:
};

class PtnEntity : public PtnObject
{
public:
    explicit PtnEntity(PtnEntityType type);
    PtnEntityType type;
};

class PtnText : public PtnEntity
{
public:
    explicit PtnText();
    double x;
    double y;
    double size;
    QString text;
};

class PtnLine : public PtnEntity
{
public:
    explicit PtnLine();
    double x1 = 0;
    double y1 = 0;
    double x2 = 0;
    double y2 = 0;
};

class PtnPolyline : public PtnEntity
{
public:
    explicit PtnPolyline();
    PtnVertexList vertices;
    bool isClosed();
    void setClosed(bool closed);
private:
    bool closed = false;
};

class PtnPiece : public PtnObject
{
public:
    explicit PtnPiece();
    PtnEntityList entities;
    QString name;
    QString size;
    int quantity = 0;
    QString material;
};

#endif // PTNMODEL_H
