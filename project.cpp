#include "project.h"

ThreadBuild::ThreadBuild(QString v, QString out, int f): vPath(v), output(out), fps(f)
{}

void ThreadBuild::run(){
    QProcess process;
    process.start("ffmpeg", QStringList()
                  << "-i" << vPath
                  <<"-r"<< QString::number(fps)
                  <<"-f" << "image2" << output);
    process.waitForFinished(-1);
}


Project::Project(QString vPath, QString pDir, int f): settings(NULL)
{
    QDir dir(pDir);
    dir.mkdir(QFileInfo(vPath).baseName());
    dir.cd(QFileInfo(vPath).baseName());

    settings = new QSettings(dir.absolutePath() + "/settings.ini", QSettings::IniFormat);
    dir.mkdir("in_frames");
    dir.mkdir("out_frames");

    settings->setValue("Generals/projectName", QFileInfo(vPath).baseName());
    settings->setValue("Generals/videoPath", vPath);
    settings->setValue("Generals/projectDirectory", dir.absolutePath());
    settings->setValue("Generals/framerate", f);

    /*
    QProcess process;
    process.start("ffmpeg", QStringList() << "-i" << videoPath <<"-r"<< "1" <<"-f" << "image2" << (dir.absolutePath()+"/in_frames/image-%09d.png"));
    process.waitForFinished(-1);*/

    ThreadBuild th(vPath, dir.absolutePath()+"/in_frames/image-%09d.png", f);

    DialogThread dial("Création en cours", "Veuillez patienter pendant la création du projet. Cela peut prendre du temps.",&th);
    dial.exec();

    //system(("ffmpeg -i \""+ vPath.toStdString() +"\" -r "+ QString::number(f).toStdString() +" -f image2 \""+ dir.absolutePath().toStdString() +"/in_frames/image-%09d.png\"").c_str());

    dir.cd(QFileInfo("in_frames").baseName());
    dir.setFilter(QDir::Files);

    settings->setValue("Generals/numberFrame", dir.count());
    settings->sync();
}

Project::Project(QString path): settings(NULL){
    if ( QDir(path).exists() && QDir(path+"/in_frames").exists() && QDir(path+"/in_frames").exists() && QFile(path+"/settings.ini").exists()){
        settings = new QSettings(path + "/settings.ini", QSettings::IniFormat);
    }
    else
        throw QException();
}

Project::~Project(){
    if (settings != NULL){
        settings->sync();
        delete settings;
    }
}

int Project::getNbFrame(){
    return settings->value("Generals/numberFrame").toInt();
}

int Project::getFramerate(){
    return settings->value("Generals/framerate").toInt();
}

QString Project::getProjectName(){
    return settings->value("Generals/projectName").toString();
}



QString Project::getFramePath(int f){
    QString str;
    str.sprintf((settings->value("Generals/projectDirectory").toString()+ "/in_frames/image-%09d.png").toStdString().c_str(), f);

    return str;
}

QString Project::getDrawnFramePath(int f){
    QString str;
    str.sprintf((settings->value("Generals/projectDirectory").toString() + "/out_frames/image-%09d.png").toStdString().c_str(), f);

    return str;
}

QVariant Project::getSettingValue(QString key){
    return settings->value(key);
}

void Project::setSettingValue(QString key, QVariant value){
    settings->value(key);
}
