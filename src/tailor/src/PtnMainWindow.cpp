#include "PtnMainWindow.h"
#include "PtnGraphicsView.h"

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QGraphicsView>
#include <QGLWidget>

PtnMainWindow::PtnMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupActions();
    setupMenu();
    setupToolBar();
    setupStatusBar();
    setupView();

    setMinimumSize(600, 400);
    setAcceptDrops(true);
}

PtnMainWindow::~PtnMainWindow()
{
}

void PtnMainWindow::setupActions()
{
    QAction *action;

    action = new QAction(tr("&New"), this);
    action->setObjectName("new");
    action->setShortcut(QKeySequence::New);
    connect(action, SIGNAL(triggered()), this, SLOT(fileNew()));

    action = new QAction(tr("&Open"), this);
    action->setObjectName("open");
    action->setShortcuts(QKeySequence::Open);
    action->setIcon(QIcon(":/icons/document-open.png"));
    connect(action, SIGNAL(triggered()), this, SLOT(open()));
    addAction(action);

    action = new QAction(tr("&Save"), this);
    action->setObjectName("save");
    action->setShortcuts(QKeySequence::Save);
    action->setIcon(QIcon(":/icons/document-save.png"));
    connect(action, SIGNAL(triggered()), this, SLOT(save()));
    addAction(action);

    action = new QAction(tr("Save &As"), this);
    action->setObjectName("saveas");
    //action->setShortcuts(QKeySequence::SaveAs);
    action->setShortcut(Qt::Key_S | Qt::CTRL | Qt::SHIFT);
    action->setIcon(QIcon(":/icons/document-save-as.png"));
    connect(action, SIGNAL(triggered()), this, SLOT(saveAs()));
    addAction(action);

    action = new QAction(tr("&Print"), this);
    action->setObjectName("print");
    action->setShortcuts(QKeySequence::Print);
    action->setIcon(QIcon(":/icons/document-print.png"));
    connect(action, SIGNAL(triggered()), this, SLOT(print()));
    addAction(action);

    action = new QAction(tr("&Close"), this);
    action->setObjectName("close");
    action->setShortcuts(QKeySequence::Close);
    action->setIcon(QIcon(":/icons/document-save-as.png"));
    connect(action, SIGNAL(triggered()), this, SLOT(close()));
    addAction(action);

    action = new QAction(tr("Zoom &In"), this);
    action->setObjectName("zoomin");
    action->setShortcuts(QKeySequence::ZoomIn);
    connect(action, SIGNAL(triggered()), this, SLOT(zoomIn()));
    addAction(action);

    action = new QAction(tr("Zoom &Out"), this);
    action->setObjectName("zoomout");
    action->setShortcuts(QKeySequence::ZoomOut);
    connect(action, SIGNAL(triggered()), this, SLOT(zoomOut()));
    addAction(action);

    action = new QAction(tr("Zoom &Fit"), this);
    action->setObjectName("zoomfit");
    connect(action, SIGNAL(triggered()), this, SLOT(zoomFit()));
    addAction(action);

    action = new QAction(tr("&Options"), this);
    action->setObjectName("options");
    connect(action, SIGNAL(triggered()), this, SLOT(showOptions()));

    action = new QAction(tr("Test&1"), this);
    action->setObjectName("test1");
    connect(action, SIGNAL(triggered()), this, SLOT(test1()));

    action = new QAction(tr("Test&2"), this);
    action->setObjectName("test2");
    connect(action, SIGNAL(triggered()), this, SLOT(test2()));

    action = new QAction(tr("Test&3"), this);
    action->setObjectName("test3");
    connect(action, SIGNAL(triggered()), this, SLOT(test3()));

}

void PtnMainWindow::setupMenu()
{
    QMenu *menu;
    menu = menuBar()->addMenu(tr("&File"));
    menu->addAction(findChild<QAction*>("new"));
    menu->addSeparator();
    menu->addAction(findChild<QAction*>("open"));
    menu->addSeparator();
    menu->addAction(findChild<QAction*>("save"));
    menu->addAction(findChild<QAction*>("saveas"));
    menu->addSeparator();
    menu->addAction(findChild<QAction*>("print"));
    menu->addSeparator();
    menu->addAction(findChild<QAction*>("close"));
    menu = menuBar()->addMenu(tr("&View"));
    menu->addAction(findChild<QAction*>("zoomin"));
    menu->addAction(findChild<QAction*>("zoomout"));
    menu->addAction(findChild<QAction*>("zoomfit"));
    menu = menuBar()->addMenu(tr("&Tools"));
    menu->addAction(findChild<QAction*>("options"));

    menu = menuBar()->addMenu(tr("&Debug"));
    menu->addAction(findChild<QAction*>("test1"));
    menu->addAction(findChild<QAction*>("test2"));
    menu->addAction(findChild<QAction*>("test3"));
}

void PtnMainWindow::setupToolBar()
{
    QToolBar *toolBar;
    toolBar = addToolBar("File");
    toolBar->addAction(findChild<QAction*>("open"));
    toolBar->addAction(findChild<QAction*>("save"));
    toolBar->addAction(findChild<QAction*>("print"));
}

void PtnMainWindow::setupStatusBar()
{
    //auto mousePosLabel = new QLabel("", this);
    //locationLabel->setAlignment(Qt::AlignHCenter);
    //locationLabel->setMinimumSize(locationLabel->sizeHint());
    statusBar()->showMessage("Message");
    //statusBar()->addWidget(mousePosLabel);
    //statusBar()->addPermanentWidget(mousePosLabel);
}

void PtnMainWindow::setupView()
{
    auto view = new PtnGraphicsView(this);
    view->setBackgroundBrush(Qt::white);
    view->setBackgroundBrush(QBrush(QColor(36,14,66)));
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setRenderHint(QPainter::Antialiasing, true);
    //view->setDragMode(QGraphicsView::RubberBandDrag);
    view->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    QGLFormat glFormat(QGL::SampleBuffers | QGL::DirectRendering);
    QGLWidget *glview = new QGLWidget(glFormat, this);
    view->setViewport(glview);

//        QGraphicsScene *scene = new QGraphicsScene(this);
//        m_view->setScene(scene);
//        scene->setBackgroundBrush(Qt::white);
//        m_view->update();
    auto scene = new QGraphicsScene(this);
    view->setScene(scene);
    scene->setBackgroundBrush(Qt::white);
    view->update();
    setCentralWidget(view);

    m_view = view;
    m_scene = scene;
}
