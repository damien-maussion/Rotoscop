#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    project(NULL),
    currentFrame(0),
    settings(QDir::currentPath()+"/generalSettings.ini", QSettings::IniFormat)
{
    ui->setupUi(this);

    ui->dockNavigation->setVisible(false);
    ui->dockTools->setVisible(false);

    connect(&histo,SIGNAL(canRedo(bool)), this, SLOT(onCanRedo(bool)));
    connect(&histo,SIGNAL(canUndo(bool)), this, SLOT(onCanUndo(bool)));
    connect(&histo,SIGNAL(exec(int,QPixmap)), this, SLOT(onExec(int,QPixmap)));

    buildImgArea();
}


void MainWindow::on_actionNewProject_triggered(){

    //Save ???

    Project *p = DialogNewProject::getNewProject(this);
    if (p!=NULL){
        if (project!=NULL)
            delete project;
        project = p;
        onOpenProject();
    }

}

void MainWindow::on_actionOpenProject_triggered(){

    //Save ??

    Project *p = DialogNewProject::getExistingProject(this);
    if (p!=NULL){
        if (project!=NULL)
            delete project;
        project = p;
        onOpenProject();
    }

}

void MainWindow::on_actionSave_triggered(){
    QMap<int, QPixmap>::iterator i;
    for (i = dessins.begin(); i != dessins.end(); ++i)
        i.value().save(project->getDrawnFramePath(i.key()),"PNG");
}


void MainWindow::onOpenProject(){

    dessins.clear();
    histo.clear();

    for (int i=1; i<project->getNbFrame()+1; i++){
        QPixmap pix(project->getDrawnFramePath(i));
        if (!pix.isNull()){
            dessins.insert(i, pix);
        }
    }

    color.setRgba(settings.value("Default/penColor", QColor(Qt::black).rgba()).toUInt());
    ((DrawingLabel*) labels[labels.size()-1])->setColor(color);

    ui->actionSave->setEnabled(true);
    ui->actionExportImg->setEnabled(true);
    ui->actionExportVideo->setEnabled(true);
    ui->actionPreview->setEnabled(true);
    ui->actionGo->setEnabled(true);

    QPixmap pix(16,16);
    pix.fill(color);
    ui->buttonColor->setIcon(QIcon(pix));

    ui->dockNavigation->setVisible(true);
    ui->dockTools->setVisible(true);

    ui->sliderNavigation->setMaximum(project->getNbFrame());
    ui->spinPenSize->setValue(settings.value("Default/penSize", 11).toInt());
    ui->spinNbCalque->setValue(settings.value("Default/nbCalque", 3).toInt());
    ui->checkDisplayImgVideo->setChecked(settings.value("Default/displayVideo", true).toBool());

    currentFrame=0;
    setCurrentFrame(1);

    ui->comboSubFreq->setCurrentText(settings.value("Default/subFreq", 1).toString());
    ui->checkDisplayCalque->setChecked(settings.value("Default/displayCalque", true).toBool());
}



void MainWindow::on_actionExportImg_triggered(){
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter l'image "+QString::number(currentFrame),
                                                    QDir::currentPath()+"/image-"+QString::number(currentFrame)+".png",
                                                    tr("Images (*.png)"));

    if (fileName!="")
        ((DrawingLabel*) labels[labels.size()-1])->getPixmap().save(fileName,"PNG");
}

void MainWindow::on_actionExportVideo_triggered(){

    QString fileName = QFileDialog::getSaveFileName(this, "Exporter la vidéo "+QString::number(currentFrame),
                                                    QDir::currentPath()+"/Rotoscop - "+project->getProjectName()+".mp4",
                                                    tr("Vidéo (*.mp4)"));
    if (fileName != ""){
        ThreadExportVideo th(fileName, dessins, project);
        DialogThread dial("Export en cours", "Veuillez patienter pendant la création de votre vidéo.", &th, this);

        if (dial.exec() == QDialog::Accepted ) {
            QMessageBox::information(this, "Export réussi", "Votre film a été exporté correctement.");
        }
        else{
            QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de l'export.");
        }
    }
}

void MainWindow::on_actionUndo_triggered(){
    histo.undo();
}

void MainWindow::on_actionRedo_triggered(){
    histo.redo();
}

void MainWindow::on_actionGo_triggered(){
    QDialog dial(this);
    dial.setWindowTitle("Aller à");

    QHBoxLayout *layout = new QHBoxLayout();

    QLabel *label = new QLabel("Image: ");
    layout->addWidget(label);

    QSpinBox *spin = new QSpinBox();
    spin->setRange(1, project->getNbFrame());
    spin->setValue(currentFrame);
    layout->addWidget(spin);

    QPushButton *button = new QPushButton("OK");
    layout->addWidget(button);

    connect(button, SIGNAL(clicked()), &dial, SLOT(accept()));

    dial.setLayout(layout);
    if (dial.exec()==QDialog::Accepted)
        setCurrentFrame(spin->value());
}

void MainWindow::on_buttonCrayon_clicked(bool checked){
    ui->buttonGomme->setChecked(false);
    DrawingLabel *draw = ((DrawingLabel*) labels[labels.size()-1]);
    draw->setGomme(false);
    draw->setColor(color);
    ui->buttonCrayon->setChecked(true);
}

void MainWindow::on_buttonGomme_clicked(bool checked){
    ui->buttonCrayon->setChecked(false);
    DrawingLabel *draw = ((DrawingLabel*) labels[labels.size()-1]);
    draw->setGomme();
    ui->buttonGomme->setChecked(true);
}

void MainWindow::on_buttonColor_clicked(){
    QColor c = QColorDialog::getColor(color, this);
    if (c.isValid()){
        color = c;
        if (ui->buttonCrayon->isChecked()){
            QPixmap pix(32,32);
            pix.fill(color);
            ui->buttonColor->setIcon(QIcon(pix));
            ((DrawingLabel*) labels[labels.size()-1])->setColor(color);
        }
    }

}

void MainWindow::on_spinNbCalque_valueChanged(int i){
    displayCalques(i, ui->checkDisplayCalque->isChecked());
}

void MainWindow::on_checkDisplayCalque_toggled(bool checked){
    displayCalques(ui->spinNbCalque->value(), checked);
}

void MainWindow::displayCalques(int nbCalques, bool b){
    for (unsigned int i=1;i< labels.size()-1-nbCalques; i++){
        labels[i]->setVisible(false);
    }
    for (unsigned int i=labels.size()-1-nbCalques; i< labels.size()-1; i++){
        labels[i]->setVisible(b);
    }
    refreshOpacity();
}


void MainWindow::on_spinPenSize_valueChanged(int i){
    if (labels.size()>0)
        ((DrawingLabel*) labels[labels.size()-1])->setPenSize(i);
}


void MainWindow::on_checkDisplayImgVideo_toggled(bool checked){
    if (labels.size()>0){
        labels[0]->setVisible(checked);
        refreshOpacity();
    }
}

void MainWindow::on_comboSubFreq_currentIndexChanged(QString s){
    if (labels.size()>0){
        int subFreq = ui->comboSubFreq->currentText().toInt();
        //qDebug()<< "cur : "<<currentFrame;
        for (unsigned int i=1; i<labels.size()-1; i++){
            //qDebug()<< "ind : "<< (labels.size()-1-i)<< "=> frame :"<< (currentFrame - i*subFreq);
            QPixmap pix(getDessin(currentFrame - (i*subFreq)));
            labels[labels.size()-1-i]->setPixmap(pix);
        }
    }
}

void MainWindow::on_actionPreferences_triggered(){
    SettingsDialog dial;
    dial.exec();
}

void MainWindow::on_actionPreview_triggered(){
    Preview preview(dessins,project->getFramerate() ,project->getNbFrame(), 1, this);
    preview.exec();
}


void MainWindow::on_actionImgSuiv_triggered(){
    setCurrentFrame(currentFrame+1);
}

void MainWindow::on_actionImgPrec_triggered(){
    setCurrentFrame(currentFrame-1);
}

void MainWindow::on_sliderNavigation_valueChanged(int i){
    setCurrentFrame(i);
}

void MainWindow::setCurrentFrame(int idFrame){
    if (idFrame != currentFrame && (idFrame>0 || idFrame<=project->getNbFrame())){

        DrawingLabel *draw = ((DrawingLabel*) labels[labels.size()-1]);

        currentFrame = idFrame;
        ui->labelNav->setText("Image: "+ QString::number(currentFrame)+"/"+QString::number(project->getNbFrame()));

        ui->actionImgPrec->setEnabled(currentFrame != 1);
        ui->buttonPrec->setEnabled(currentFrame != 1);

        ui->actionImgSuiv->setEnabled(currentFrame != project->getNbFrame());
        ui->buttonSuiv->setEnabled(currentFrame != project->getNbFrame());

        if (ui->sliderNavigation->value() != currentFrame)
            ui->sliderNavigation->setValue(currentFrame);

        labels[0]->setPixmap(project->getFramePath(currentFrame));
        draw->changePixmap(getDessin(currentFrame));

        on_comboSubFreq_currentIndexChanged();  //setCalques
        displayCalques(ui->spinNbCalque->value(), ui->checkDisplayCalque->isChecked());

    }
}


QPixmap MainWindow::getDessin(int i){
    if (dessins.contains(i))
        return dessins.value(i);

    QPixmap imgVid(project->getFramePath(1));
    QPixmap pix(imgVid.width(), imgVid.height());
    pix.fill(Qt::transparent);
    return pix;
}

void MainWindow::buildImgArea(){

    QGridLayout *grid = new QGridLayout;

    QLabel *labelImgVid = new QLabel();
    labelImgVid->setScaledContents(true);
    grid->addWidget(labelImgVid,0,0,0,0);
    labels.push_back(labelImgVid);

    for (int i=0;i<5;i++){
        QLabel *label = new QLabel();
        label->setScaledContents(true);
        grid->addWidget(label,0,0,0,0);
        labels.push_back(label);
    }

    DrawingLabel *draw = new DrawingLabel();
    draw->setScaledContents(true);
    grid->addWidget(draw,0,0,0,0);
    labels.push_back(draw);
    connect(draw, SIGNAL(drawingHasChanged(QPixmap,QPixmap)), this, SLOT(onDrawingChanged(QPixmap,QPixmap)));

    ui->centralwidget->setLayout(grid);
}

void MainWindow::refreshOpacity(){
    if (labels.size()>1){
        std::vector<QLabel*> vis;
        for (unsigned int i=1; i<labels.size()-1;i++){
            if(labels[i]->isVisible())
                vis.push_back(labels[i]);
        }

        for (unsigned int i=0; i<vis.size();i++){
            QGraphicsOpacityEffect *eff= new QGraphicsOpacityEffect(vis[i]);
            eff->setOpacity( (i+1) / (double)(vis.size()+1));
            vis[i]->setGraphicsEffect(eff);
        }
    }
}

void MainWindow::onDrawingChanged(QPixmap pixB, QPixmap pix){
    //qDebug()<< "onDrawingChanged " <<currentFrame;
    dessins.insert(currentFrame, pix);
    histo.add(currentFrame, pixB, pix);
}

void MainWindow::onCanUndo(bool b){
    //qDebug()<< "onCanUndo";
    ui->actionUndo->setEnabled(b);
}

void MainWindow::onCanRedo(bool b){
    //qDebug()<< "onCanRedo";
    ui->actionRedo->setEnabled(b);
}

void MainWindow::onExec(int i, QPixmap pix){
    //qDebug()<< "onExec "<<i <<" - "<<pix;

    dessins.insert(i, pix);
    currentFrame=0;
    setCurrentFrame(i);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (project!=NULL)
        delete project;
}
