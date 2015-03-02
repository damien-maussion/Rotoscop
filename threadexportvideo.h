#ifndef THREADEXPORTVIDEO_H
#define THREADEXPORTVIDEO_H

#include <QThread>
#include <QMap>
#include <QPixmap>
#include <QPainter>

#include "project.h"

class ThreadExportVideo : public QThread
{
public:
    ThreadExportVideo(QString fn, QMap<int, QPixmap> d, Project *p);

protected:
    void run();

    QString fileName;
    QMap<int, QPixmap> dessins;
    Project *project;

};

#endif // THREADEXPORTVIDEO_H
