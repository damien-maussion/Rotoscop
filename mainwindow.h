#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsOpacityEffect>
#include <QSettings>

#include <vector>
#include <QMap>
#include <QPushButton>

#include <QDebug>

#include "dialognewproject.h"
#include "drawinglabel.h"
#include "settingsdialog.h"
#include "preview.h"

#include "dialogthread.h"
#include "threadexportvideo.h"

#include "historique.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void onDrawingChanged(QPixmap pixB, QPixmap pix);

    void onCanUndo(bool b);
    void onCanRedo(bool b);
    void onExec(int i, QPixmap pix);

protected slots:

    void on_actionNewProject_triggered();
    void on_actionOpenProject_triggered();

    void on_actionImgPrec_triggered();
    void on_actionImgSuiv_triggered();
    void on_sliderNavigation_valueChanged(int i);

    void on_actionSave_triggered();

    void on_actionPreview_triggered();
    void on_actionExportImg_triggered();
    void on_actionExportVideo_triggered();

    void on_actionGo_triggered();

    void on_actionPreferences_triggered();

    void on_actionUndo_triggered();
    void on_actionRedo_triggered();

    void on_spinNbCalque_valueChanged(int i);
    void on_spinPenSize_valueChanged(int i);

    void on_buttonCrayon_clicked(bool checked);
    void on_buttonGomme_clicked(bool checked);

    void on_checkDisplayCalque_toggled(bool checked);
    void on_checkDisplayImgVideo_toggled(bool checked);

    void on_comboSubFreq_currentIndexChanged(QString s="");

    void on_buttonColor_clicked();

    void setCurrentFrame(int idFrame);

private:

    void onOpenProject();
    void buildImgArea();
    void refreshOpacity();

    QPixmap getDessin(int i);

    void displayCalques(int nbCalques,bool b);

    QColor color;
    Ui::MainWindow *ui;

    Project *project;

    std::vector<QLabel*> labels;
    int currentFrame;

    QSettings settings;
    QMap<int, QPixmap> dessins;

    Historique histo;

};

#endif // MAINWINDOW_H
