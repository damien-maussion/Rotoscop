#include <QApplication>
#include <QtWidgets>
#include "fenprincipale.h"
#include "mainwindow.h"

#include <QDir>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mw;
    mw.show();

    return app.exec();
}
