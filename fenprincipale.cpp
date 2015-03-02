#include "fenprincipale.h"

FenPrincipale::FenPrincipale()
{
    buildMenu();
}


void buildMenu(){
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QMenu *menuEdition = menuBar()->addMenu("&Edition");
    QMenu *menuParams = menuBar()->addMenu("&Paramètres");
    QMenu *menuNavigation = menuBar()->addMenu("&Navigation");
    
    QAction *actionNewProject = new QAction("Nouveau projet", this);
    actionNewProject->setShortcut(QKeySequence("Ctrl+N"));
    menuFichier->addAction(actionNewProject);
    
    QAction *actionOpenProject = new QAction("Ouvrir un projet", this);
    actionOpenProject->setShortcut(QKeySequence("Ctrl+O"));
    menuFichier->addAction(actionOpenproject);
    
    QAction *actionSaveProject = new QAction("Sauvegarder projet", this);
    actionSaveProject->setShortcut(QKeySequence("Ctrl+S"));
    menuFichier->addAction(actionSaveAutomate);
    
    QAction *actionQuitter = new QAction("&Quitter", this);
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    menuAutomate->addAction(actionQuitter);
}
