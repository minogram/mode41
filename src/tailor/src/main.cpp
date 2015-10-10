#include "PtnMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PtnMainWindow wnd;
    wnd.show();

    return app.exec();
}
