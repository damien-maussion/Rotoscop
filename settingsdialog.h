#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QColorDialog>
#include <QColor>
#include <QSettings>
#include <QMessageBox>


namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();


public slots :

    void on_videoBrowse_clicked();
    void on_workspaceBrowse_clicked();
    void on_buttonColor_clicked();
    void on_buttonOk_clicked();
    
private:
    Ui::SettingsDialog *ui;
    QColor color;
    QSettings settings;
};

#endif // SETTINGSDIALOG_H
