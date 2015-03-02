#include "threadexportvideo.h"

ThreadExportVideo::ThreadExportVideo(QString fn, QMap<int, QPixmap> d, Project *p):fileName(fn), dessins(d), project(p)
{
}

void ThreadExportVideo::run(){
    if (fileName!=""){
        QDir::current().mkdir("tmp");
        for (int i=1; i<=project->getNbFrame();i++){
            QString str;
            str.sprintf("tmp/image-%09d.png", i);

            QPixmap ref(project->getFramePath(1));
            QPixmap tmp(ref.width(), ref.height());
            tmp.fill(Qt::white);

            if (dessins.contains(i)){
                QPainter paint(&tmp);
                paint.drawPixmap(tmp.rect(), dessins.value(i), ref.rect());
            }

            tmp.save(str, "PNG");
        }

        QProcess process;
        process.setProgram("ffmpeg");
        process.setArguments(QStringList()
                             << "-y"
                             << "-f" << "image2"
                             << "-framerate" << QString::number(project->getFramerate())
                             <<"-i" << QDir::currentPath()+"/tmp/image-%09d.png"
                             << "-r" << QString::number(project->getFramerate())
                             << "-vcodec" << "mpeg4"
                             << fileName);

        process.start();
        process.waitForFinished(-1);

        QDir tmp = QDir::current();
        tmp.cd("tmp");
        tmp.removeRecursively();
    }
}
