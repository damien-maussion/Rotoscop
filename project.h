#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QDir>
#include <QProcess>
#include <QSettings>
#include <QException>
#include <QThread>

#include "dialogthread.h"

class ThreadBuild : public QThread{

public:
    ThreadBuild(QString v, QString out, int f);

protected:
    void run();

private:

    QString vPath, output;
    int fps;

};

class Project
{
    public:
        Project(QString vPath, QString pDir, int f);
        Project(QString path);

        ~Project();

        QVariant getSettingValue(QString key);
        void setSettingValue(QString key, QVariant value);

        int getNbFrame();
        int getFramerate();

        QString getProjectName();

        QString getFramePath(int f);
        QString getDrawnFramePath(int f);


private :

        QSettings *settings;
};

#endif // PROJECT_H
