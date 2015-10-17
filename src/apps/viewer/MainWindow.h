#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include "ViewerView.h"

class QGraphicsView;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createActions();
    void createMenu();
    void createToolBar();
    void createStatusBar();
    void createView();

protected:
    void closeEvent(QCloseEvent *e) Q_DECL_OVERRIDE;
    void dragEnterEvent(QDragEnterEvent *e) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *e) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *e) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *e) Q_DECL_OVERRIDE;

private slots:
    void fileNew();
    void open();
    void openFile(const QString &fileName);
    void print();
    void zoomFit();
private:
    void openImage(const QFileInfo &fileInfo);
    void openSvg(const QFileInfo &fileInfo);
    void openDxf(const QFileInfo &fileInfo);
    void openPsd(const QFileInfo &fileInfo);
    void openHpgl(const QFileInfo &fileInfo);

    bool maybeSave();

private:
    ViewerView *m_view = nullptr;
};

#endif // MAINWINDOW_H
