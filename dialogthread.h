#ifndef DIALOGTHREAD_H
#define DIALOGTHREAD_H

#include <QDialog>
#include <QThread>
#include <QDir>

namespace Ui {
class DialogThread;
}

class DialogThread : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogThread(QString title, QString text, QThread *t, QWidget *parent = 0);
    ~DialogThread();

public slots:
    void ok();

private:
    Ui::DialogThread *ui;

    QThread *thread;
};

#endif // DIALOGTHREAD_H
