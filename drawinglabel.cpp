#include "drawinglabel.h"

DrawingLabel::DrawingLabel(QPixmap p, QWidget *parent) : QLabel(parent),isGomme(false),x(-1),y(-1)
{
    changePixmap(p);
    crayon.setCapStyle(Qt::RoundCap);

    cursor = QPixmap(":/icons/pen.png");
    setCursor(QCursor(cursor.scaledToWidth(12),0,12));
}

DrawingLabel::DrawingLabel(QWidget *parent): QLabel(parent),isGomme(false),x(-1),y(-1)
{
    crayon.setCapStyle(Qt::RoundCap);

    cursor = QPixmap(":/icons/pen.png");
}

QPixmap DrawingLabel::getPixmap(){
    return pixmap;
}

void DrawingLabel::changePixmap(const QPixmap &pix){
    pixmap = pix;
    setPixmap(pixmap);
}


void DrawingLabel::setColor(QColor color) {
    crayon.setColor(color);
}

void DrawingLabel::setPenSize(int size){
    setCursor(QCursor(cursor.scaledToWidth(10+size),0,10+size));

    crayon.setWidth(size);
}

void DrawingLabel::setGomme(bool b){
    if (b)
        cursor = QPixmap(":/icons/rubber.png");
    else
        cursor = QPixmap(":/icons/pen.png");
    qDebug()<< cursor.isNull();
    setCursor(QCursor(cursor.scaledToWidth(10+crayon.width()),0, 10+crayon.width()));

    isGomme=b;
}

void DrawingLabel::draw(QMouseEvent * ev){
    if (!pixmap.isNull()){

        QPainter painter(&pixmap);

        if (isGomme){
            crayon.setColor(Qt::transparent);
            painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        }

        painter.setPen(crayon);

        int x2(ev->x()/((double) width()) * pixmap.width()), y2(ev->y()/((double)height()) * pixmap.height());
        if (x==-1 || y==-1)
            painter.drawPoint(x2,y2);
        else
            painter.drawLine(x,y,x2,y2);

        x=x2;
        y=y2;

        setPixmap(pixmap);
    }
}

void DrawingLabel::mousePressEvent ( QMouseEvent * ev ){
    pixmapBack=pixmap;
    draw(ev);
}

void DrawingLabel::mouseMoveEvent ( QMouseEvent * ev ){
    draw(ev);
}

void DrawingLabel::mouseReleaseEvent ( QMouseEvent * ev){
    draw(ev);
    x=-1;
    y=-1;
    emit drawingHasChanged(pixmapBack, pixmap);
}
