#include "MainWindow.h"
#include "TAOptionsWidget.h"

void MainWindow::showOptions()
{
    auto dialog = new TAOptionsWidget(this);
    dialog->show();
}

