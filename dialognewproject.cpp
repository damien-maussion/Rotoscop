#include "dialognewproject.h"
#include "ui_dialognewproject.h"

#include <iostream>

DialogNewProject::DialogNewProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewProject),
    settings(QDir::currentPath()+"/generalSettings.ini", QSettings::IniFormat)
{
    ui->setupUi(this);

    ui->frame->setCurrentText(settings.value("Default/framerate", "1").toString());
    framerate = ui->frame->currentText().toInt();

    dirPath = settings.value("Default/workspace", QDir::homePath()).toString();
    ui->dirPath->setText(dirPath);
};


void DialogNewProject::on_browseVideoPath_clicked(){
    QString defaultVidDirectory = settings.value("Default/videoDirectory", QDir::homePath()).toString();
    videoPath = QFileDialog::getOpenFileName(this, "Ouvrir une vidéo", defaultVidDirectory, "Vidéo (*.avi *.mp4 *.flv)");
    ui->videoPath->setText(videoPath);
}

void DialogNewProject::on_browseDirPath_clicked(){
    dirPath = QFileDialog::getExistingDirectory(this);
    ui->dirPath->setText(dirPath);
}

void DialogNewProject::on_frame_currentTextChanged(QString s){
    framerate = s.toInt();
}

Project* DialogNewProject::getNewProject(QWidget *parent){
    DialogNewProject dialog(parent);

    Project *p(NULL);
    if (dialog.exec() == QDialog::Accepted ) {
        p = new Project(dialog.videoPath, dialog.dirPath, dialog.framerate);
    }

    return p;
}

Project* DialogNewProject::getExistingProject(QWidget *parent){
    QSettings s(QDir::currentPath()+"/generalSettings.ini", QSettings::IniFormat);
    QString dossier = QFileDialog::getExistingDirectory(parent, "Ouvrir un projet", s.value("Default/workspace").toString());
    if (dossier!=""){
        try{
            parent->setCursor(QCursor(QPixmap(":/icons/hourglass-icon.png")));
            Project *p = new Project(dossier);
            parent->setCursor(Qt::ArrowCursor);

            return p;
        }
        catch (QException e){
            parent->setCursor(Qt::ArrowCursor);
            QMessageBox::critical(parent, "Erreur", "Ce dossier ne correspond pas à un projet.");
            return getExistingProject(parent);
        }
    }
    return NULL;
}

void DialogNewProject::on_OKbutton_clicked(){
    if (!QDir(dirPath).exists()){
        QMessageBox::critical(this, "Erreur choix du répertoire de travail", "Veuillez renseignez un répertoire de travail valide !");
    }
    else{
        QFileInfo checkFile(videoPath);
        // check if file exists and if yes: Is it really a file and no directory?
        if (!checkFile.exists() || !checkFile.isFile())
            QMessageBox::critical(this, "Erreur choix de la video", "Veuillez renseignez une vidéo valide !");
        else
            accept();
    }

}

DialogNewProject::~DialogNewProject()
{
    delete ui;
}
