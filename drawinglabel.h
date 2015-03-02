#ifndef DRAWINGLABEL_H
#define DRAWINGLABEL_H

#include <QLabel>
#include <QPixmap>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
#include <QDir>

#include <QDebug>
#include <QMessageBox>
#include <QHBoxLayout>

class DrawingLabel : public QLabel
{
    Q_OBJECT
public:
    DrawingLabel(QPixmap p, QWidget * parent = 0);
    DrawingLabel(QWidget *parent=0);

    QPixmap getPixmap();
    void changePixmap(const QPixmap &pix);

    void setColor(QColor color);
    void setPenSize(int size);

    void setGomme(bool b=true);

signals:

    void drawingHasChanged(QPixmap,QPixmap);

protected:

    void mouseMoveEvent ( QMouseEvent * ev );
    void mousePressEvent ( QMouseEvent * ev );
    void mouseReleaseEvent ( QMouseEvent * ev);

private :

    QPixmap pixmap;
    QPixmap pixmapBack;

    QPen crayon;
    QPixmap cursor;

    bool isGomme;
    int x,y;

    void draw(QMouseEvent * ev);
};

#endif // DRAWINGLABEL_H
