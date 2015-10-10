#ifndef QXUIBUILDER
#define QXUIBUILDER

#include <QString>
#include <QAction>

class QXUiBuilder
{
    static QAction *createAction(QWidget *parent, const QString &text, const QString &name) {
        QAction *action = new QAction(text, parent);
        action->setObjectName(name);

    };
};

#endif // QXUIBUILDER

