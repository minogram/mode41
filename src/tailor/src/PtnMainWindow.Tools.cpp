#include "PtnMainWindow.h"
#include "TAOptionsWidget.h"

void PtnMainWindow::showOptions()
{
    auto dialog = new TAOptionsWidget(this);
    dialog->show();
}

