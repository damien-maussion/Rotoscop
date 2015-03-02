#ifndef DIALOGNEWPROJECT_H
#define DIALOGNEWPROJECT_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

#include "project.h"

namespace Ui {
class DialogNewProject;
}

class DialogNewProject : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogNewProject(QWidget *parent = 0);
    ~DialogNewProject();

    static Project* getNewProject(QWidget *parent=0);
    static Project* getExistingProject(QWidget *parent=0);

    QString videoPath, dirPath;
    int framerate;

public slots :

    void on_browseVideoPath_clicked();
    void on_browseDirPath_clicked();
    void on_OKbutton_clicked();
    void on_frame_currentTextChanged(QString s);

private:
    Ui::DialogNewProject *ui;
    QSettings settings;
};

#endif // DIALOGNEWPROJECT_H
