#ifndef PREVIEW_H
#define PREVIEW_H

#include <QDialog>

#include<QLabel>
#include <QMap>
#include <QTest>
#include <QThread>
#include <QPainter>

namespace Ui {
class Preview;
}

class PlayThread : public QThread{
    Q_OBJECT
    public:
        PlayThread(int d, int f, int fps, QMap<int, QPixmap> ds,Ui::Preview *u, QDialog *p);

        void setPix(int i);

        int deb, fin, framerate;
        QMap<int, QPixmap> dessins;

        Ui::Preview *ui;
        QDialog *preview;

    protected:
        void run();
};


namespace Ui {
class Preview;
}

class Preview : public QDialog
{
    Q_OBJECT
    
public:
    explicit Preview(QMap<int, QPixmap> d, int fps, int nbFrames, int deb=1, QWidget *parent = 0);
    ~Preview();

public slots:

    void on_buttonPlay_clicked();
    void on_spinBegin_valueChanged(int i);
    void on_spinEnd_valueChanged(int i);

private:

    Ui::Preview *ui;

    PlayThread play;

};

#endif // PREVIEW_H
