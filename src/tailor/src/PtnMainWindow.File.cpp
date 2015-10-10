#include "PtnMainWindow.h"
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

void PtnMainWindow::fileNew()
{
    auto wnd = new PtnMainWindow();
    wnd->show();
}

void PtnMainWindow::open()
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

void PtnMainWindow::openFile(const QString &fileName)
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
            PtnSceneBuilder builder;
            builder.buildScene(ptn, m_scene);
            zoomFit();

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

void PtnMainWindow::save()
{
}

void PtnMainWindow::saveAs()
{
}

bool PtnMainWindow::maybeSave()
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

void PtnMainWindow::print()
{
    auto scene = m_view->scene();
    QPrinter printer;
    if (QPrintDialog(&printer).exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        painter.setRenderHint(QPainter::Antialiasing);
        scene->render(&painter);
    }
}

