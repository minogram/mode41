#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

class PtnMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    PtnMainWindow(QWidget *parent = 0);
    ~PtnMainWindow();

protected:
    void closeEvent(QCloseEvent *e);
    void dragEnterEvent(QDragEnterEvent *e);
    void dragMoveEvent(QDragMoveEvent *e);
    void dragLeaveEvent(QDragLeaveEvent *e);
    void dropEvent(QDropEvent *e);

private:
    void setupActions();
    void setupMenu();
    void setupToolBar();
    void setupStatusBar();
    void setupView();
    bool maybeSave();
    void openFile(const QString &fileName);

private slots:
    void fileNew();
    void open();
    void save();
    void saveAs();
    void print();
    void zoomIn();
    void zoomOut();
    void zoomFit();
    void showOptions();

    void test1();
    void test2();
    void test3();

private:
    QGraphicsView *m_view;
    QGraphicsScene *m_scene;
};

#endif // MAINWINDOW_H
