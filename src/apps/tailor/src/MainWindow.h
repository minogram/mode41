#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *e) Q_DECL_OVERRIDE;
    void dragEnterEvent(QDragEnterEvent *e) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *e) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *e) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *e) Q_DECL_OVERRIDE;

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
