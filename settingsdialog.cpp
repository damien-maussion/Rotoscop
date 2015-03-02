#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    settings(QDir::currentPath()+"/generalSettings.ini", QSettings::IniFormat)
{
    ui->setupUi(this);

    ui->videoPath->setText(settings.value("Default/videoDirectory", QDir::homePath()).toString());
    ui->workspacePath->setText(settings.value("Default/workspace", QDir::homePath()).toString());
    ui->framerate->setValue(settings.value("Default/framerate", 1).toInt());
    ui->displayVid->setChecked(settings.value("Default/displayVideo", true).toBool());
    ui->displayCalque->setChecked(settings.value("Default/displayCalque", true).toBool());
    ui->nbCalque->setValue(settings.value("Default/nbCalque", 3).toInt());
    ui->penSize->setValue(settings.value("Default/penSize", 12).toInt());
    ui->subFreq->setCurrentText(settings.value("Default/subFreq", "1").toString());
    color.setRgba(settings.value("Default/penColor", QColor(Qt::black).rgba()).toUInt());

    QPixmap pix(32,32);
    pix.fill(color);
    ui->buttonColor->setIcon(QIcon(pix));
}

void SettingsDialog::on_videoBrowse_clicked(){
    ui->videoPath->setText(QFileDialog::getExistingDirectory(this));
}

void SettingsDialog::on_workspaceBrowse_clicked(){
    ui->workspacePath->setText(QFileDialog::getExistingDirectory(this));
}

void SettingsDialog::on_buttonColor_clicked(){
    QColor c = QColorDialog::getColor(color, this);
    if (c.isValid()){
        color = c;
        QPixmap pix(32,32);
        pix.fill(color);
        ui->buttonColor->setIcon(QIcon(pix));
    }
}

void SettingsDialog::on_buttonOk_clicked(){
    if (QDir(ui->videoPath->text()).exists() && QDir(ui->workspacePath->text()).exists()){
        settings.setValue("Default/videoDirectory",ui->videoPath->text());
        settings.setValue("Default/workspace",ui->workspacePath->text());
    }
    else
        QMessageBox::warning(this,"Erreur dans le choix des dossiers", "Le chemin du dossier de vidéo ou du répertoire de travail n'est pas valide.\nLes autres changements ont été pris en compte.");

    settings.setValue("Default/framerate",ui->framerate->value());
    settings.setValue("Default/displayVideo",ui->displayVid->isChecked());
    settings.setValue("Default/displayCalque",ui->displayCalque->isChecked());
    settings.setValue("Default/nbCalque",ui->nbCalque->value());
    settings.setValue("Default/penSize",ui->penSize->value());
    settings.setValue("Default/subFreq",ui->subFreq->currentText().toInt());
    settings.setValue("Default/penColor", color.rgba());

    accept();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
