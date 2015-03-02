#include "dialogthread.h"
#include "ui_dialogthread.h"

DialogThread::DialogThread(QString title, QString text, QThread *t, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogThread),
    thread(t)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    setWindowTitle(title);
    ui->label->setText(text);

    connect(t, SIGNAL(finished ()), this, SLOT(ok()));

    QApplication::setOverrideCursor(QCursor(QPixmap(QDir::currentPath()+":/icons/hourglass-icon.png")));
    t->start();
}

void DialogThread::ok(){
    QApplication::restoreOverrideCursor();
    accept();
}

DialogThread::~DialogThread()
{
    delete ui;
    thread->quit();
    thread->wait();
}
