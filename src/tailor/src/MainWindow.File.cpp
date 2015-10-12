#include "MainWindow.h"
#include "DxfSceneBuilder.h"
#include "DxfPtnConvert.h"
#include "PtnSceneBuilder.h"
#include "DxfReader.h"
#include "DxfModelReader.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QException>
#include <QPicture>
#include <QPainter>
#include <QLineF>
#include "QXGraphicsPictureItem.h"

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
#ifdef QT_DEBUG
        dialog.setDirectory("c:/dev/DxfViewer/tests");
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
            DxfModelReader r;
            auto dxf = r.load(fileName);
            //auto ptn = new PtnDesign();
            DxfPtnConvert dxf2ptn;
            auto ptn = dxf2ptn.convert(dxf);

//            PtnSceneBuilder builder;
//            builder.buildScene(ptn, m_scene);
//            zoomFit();

//            QPicture picture;
//                   QPainter painter;
//                   painter.begin(&picture);           // paint in picture
//                   painter.drawEllipse(10,20, 80,70); // draw an ellipse
//                   painter.end();                     // painting done
//                   picture.save("drawing.pic");       // save picture

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
            scene->clear();
            auto item = new QXGraphicsPictureItem(picture);
            scene->addItem(item);

//            DxfAamaReader reader(this);
//            auto dxf = reader.load(fileName);
//            auto ptn = new PtnDesign();
//            DxfPtnConvert dxf2ptn;
//            dxf2ptn.convert(dxf, ptn);
//            PtnSceneBuilder builder;
//            builder.buildScene(ptn, m_scene);
//            zoomFit();
        }
    } catch (QException &) {
        QMessageBox::information(this, "ERROR", "Error: read dxf");
    }
}

void MainWindow::save()
{
}

void MainWindow::saveAs()
{
}

bool MainWindow::maybeSave()
{
    if (isWindowModified()) {

        QMessageBox dialog;
        dialog.setText("The document has been modified.");
        dialog.setInformativeText("Do you want to save your changes?");
        dialog.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        dialog.setDefaultButton(QMessageBox::Save);

        switch (dialog.exec()) {
        case QMessageBox::Save:
            // Save was clicked
            //qDebug() << "save docuemnt";
            return true;
            break;
        case QMessageBox::Discard:
            // Don't Save was clicked
            return true;
            break;
        case QMessageBox::Cancel:
        default:
            return false;
            break;
        }

//        auto reply = QMessageBox::question(this, "Test", "Save?",
//            QMessageBox::Yes|QMessageBox::No);
//        switch (reply) {
//        case QMessageBox::Yes:
//            // todo: save changes
//        case QMessageBox::No:
//            return true;
//        case QMessageBox::Cancel:
//            return false;
//        }
    }
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

