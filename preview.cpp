#include "preview.h"
#include "ui_preview.h"

Preview::Preview(QMap<int, QPixmap> d,int fps, int nbFrames, int deb, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preview),
    play(deb, nbFrames, fps, d, ui, this)
{
    ui->setupUi(this);

    ui->spinEnd->setMaximum(nbFrames);
    ui->spinEnd->setValue(nbFrames);
    ui->spinBegin->setValue(deb);
    play.setPix(deb);
}

void Preview::on_buttonPlay_clicked(){
    play.terminate();
    play.wait();
    play.start();
}

void Preview::on_spinBegin_valueChanged(int i){
    play.terminate();
    play.wait();
    ui->spinEnd->setMinimum(i);
    play.deb=i;
    play.setPix(i);
}

void Preview::on_spinEnd_valueChanged(int i){
    play.terminate();
    play.wait();
    play.fin=i;
    ui->spinBegin->setMaximum(i);
}

void PlayThread::setPix(int i){
    preview->setWindowTitle("Image "+QString::number(i));
    QPixmap tmp(500, 400);
    tmp.fill(Qt::white);

    if (dessins.contains(i)){
        QPainter paint(&tmp);
        paint.drawPixmap(tmp.rect(), dessins.value(i), dessins.value(i).rect());
    }
    ui->labelFrame->setPixmap(tmp);
}

PlayThread::PlayThread(int d, int f, int fps, QMap<int, QPixmap> ds, Ui::Preview *u, QDialog *p):
    deb(d),fin(f), framerate(fps), dessins(ds), ui(u), preview(p)
{}

void PlayThread::run(){
    int sleepTime = 1000/framerate;
    for (int i = deb; i <= fin; ++i) {
        setPix(i);
        QTest::qSleep(sleepTime);
    }
}

Preview::~Preview()
{
    delete ui;
    play.terminate();
    play.wait();
}
