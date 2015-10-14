#include "MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QException>
#include <QPrinter>
#include <QPrintDialog>
#include <QGraphicsview>
#include <QGraphicsScene>
#include <QLabel>
#include <QStringList>
#include <QGraphicsSvgItem>
#include <QDebug>
#include "DxfModelReader.h"
#include "DxfPtnConvert.h"
#include "PtnModel.h"
#include "QXGraphicsPictureItem.h"
#include "FreeImage2QImage.h"
#include "Hpgl.h"

void MainWindow::fileNew()
{
    auto wnd = new MainWindow();
    wnd->show();
}

void MainWindow::open()
{
    try
    {
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::AnyFile);
        dialog.setViewMode (QFileDialog :: Detail);
        QStringList filters;
        filters.append(tr("All files (*.*)"));
        filters.append(tr("Bitmap (*.png *.jpg *.bmp)"));
        filters.append(tr("SVG (*.svg *.svgz)"));
        filters.append(tr("DXF (*.dxf)"));
        filters.append(tr("Photoshop (*.psd)"));
        filters.append(tr("Macintosh PICT (*.pct *.pict)"));
        filters.append(tr("TruevVision TARGA (*.tga *.targa)"));
        filters.append(tr("Hpgl (*.hpgl *.plt *.gl *.hpg *.hp2)"));
        dialog.setNameFilters(filters);

#ifdef QT_DEBUG
        dialog.setDirectory("c:/dev/mode41/test");
#endif

        if (dialog.exec()) {
            auto fileName = dialog.selectedFiles().first();
            openFile(fileName);
        }
    }
    catch (int errCode)
    {
        Q_UNUSED(errCode);
        QMessageBox::information(this, "ERROR", "Error: read dxf");
    }
}

void MainWindow::openFile(const QString &fileName)
{
    try
    {
        if (maybeSave())
        {
            bool loaded = false;
            QFileInfo fileInfo(fileName);
            auto extension = fileInfo.suffix().toLower();
            if (extension == "png" || extension == "jpg" || extension == "bmp" || extension == "psd")
            {
                openImage(fileInfo);
                loaded = true;
            }
            else if (extension == "svg" || extension == "svgz")
            {
                openSvg(fileInfo);
                loaded = true;
            }
            else if (extension == "dxf")
            {
                openDxf(fileInfo);
                loaded = true;
            }
            else if (extension == "hpgl" || extension == "plt" || extension == "gl" || extension == "hpg" || extension == "hp2")
            {
                openHpgl(fileInfo);
                loaded = true;
            }
//            else if (extension == "psd" || extension == "pct" || extension == "pict" || extension == "tga" || extension == "targa")
//            {
//                openPsd(fileInfo);
//                loaded = true;
//            }

            if (loaded) {
                setWindowTitle(fileInfo.fileName());
                m_view->update();
                zoomFit();
            }
        }
    } catch (QException &) {
        QMessageBox::information(this, "ERROR", "Error: read dxf");
    }
}

void MainWindow::openImage(const QFileInfo &fileInfo)
{
    auto scene = m_view->scene();
    scene->setBackgroundBrush(Qt::white);
    QImage image(fileInfo.absoluteFilePath());
    QPixmap pixmap = QPixmap::fromImage(image);
    scene->clear();
    scene->addPixmap(pixmap);
}

void MainWindow::openSvg(const QFileInfo &fileInfo)
{
    auto scene = m_view->scene();
    scene->clear();
    scene->setBackgroundBrush(Qt::white);
    auto svgItem = new QGraphicsSvgItem(fileInfo.absoluteFilePath());
    svgItem->setFlag(QGraphicsItem::ItemClipsToShape);
    //svgItem->setCacheMode(QGraphicsItem::NoCache);
    scene->addItem(svgItem);
}

void MainWindow::openDxf(const QFileInfo &fileInfo)
{
    DxfModelReader r;
    auto dxf = r.load(fileInfo.absoluteFilePath());
    DxfPtnConvert dxf2ptn;
    auto ptn = dxf2ptn.convert(dxf);

    QPicture picture;
    QPainter painter;
    painter.begin(&picture);

    QPen pen;
    pen.setColor(Qt::cyan);
    pen.setWidth(2);
    pen.setCosmetic(true);

    foreach (auto piece, ptn->pieces) {
        foreach (auto entity, piece->entities) {
            if (entity->type == PtnEntityType::Line) {
                auto line = entity.staticCast<PtnLine>();
                QLineF geom(line->x1, line->y1, line->x2, line->y2);
                painter.setPen(pen);
                painter.drawLine(geom);
            }
            else if (entity->type == PtnEntityType::Polyline)
            {
                auto polyline = entity.staticCast<PtnPolyline>();
                auto first = polyline->vertices.first();
                QPainterPath path(QPointF(first->x, first->y));
                for (int i=1; i<polyline->vertices.size(); ++i) {
                    auto vertex = polyline->vertices.at(i);
                    path.lineTo(vertex->x, vertex->y);
                }
                if (polyline->isClosed()) path.closeSubpath();

                painter.setPen(pen);
                painter.drawPath(path);
            }
        }
    }
    painter.end();

    auto scene = m_view->scene();
    scene->setBackgroundBrush(Qt::gray);
    scene->clear();
    auto item = new QXGraphicsPictureItem(picture);
    scene->addItem(item);
}

void MainWindow::openPsd(const QFileInfo &fileInfo)
{
    auto image = QFreeImage::load(fileInfo.absoluteFilePath());
    auto pixmap = QPixmap::fromImage(image);

    auto scene = m_view->scene();
    scene->clear();
    scene->addPixmap(pixmap);
}

void MainWindow::openHpgl(const QFileInfo &fileInfo)
{
    HpglTextReader reader;
    auto doc = reader.load(fileInfo.absoluteFilePath());

    QPicture picture;
    QPainter painter;
    painter.begin(&picture);
    HpglPaintable paintable(doc.data());
    paintable.paint(&painter);
    painter.end();

    auto scene = m_view->scene();
    scene->clear();
    auto item = new QXGraphicsPictureItem(picture);
    scene->addItem(item);

//    HpglReader r;
//    auto hpgl = r.load(fileInfo.filePath());

//    QPainterPath ppath;
//    foreach (auto item, hpgl->items) {
//        auto itemPoints = qSharedPointerCast<HpglPoints>(item);
//        if (itemPoints.isNull()) break;
//        foreach (auto point, itemPoints->m_points) {
//            ppath.lineTo(point);
//        }
//    }

//    QPen pen;
//    pen.setColor(Qt::red); //color);
//    pen.setWidth(1);
//    pen.setCosmetic(true);

//    auto scene = m_view->scene();
//    scene->addPath(ppath, pen);
}

bool MainWindow::maybeSave()
{
    return true;
}

void MainWindow::print()
{
    auto scene = m_view->scene();
    QPrinter printer;
    if (QPrintDialog(&printer).exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        painter.setRenderHint(QPainter::Antialiasing);
        scene->render(&painter);
    }
}
