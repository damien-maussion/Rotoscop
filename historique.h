#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#define MAX_HISTO_SIZE 50

#include <QPixmap>
#include <deque>
#include <utility>

#include <QDialog>
#include <QLabel>
#include <QHBoxLayout>

#include <QDebug>

class Historique : public QObject
{
    Q_OBJECT

public:
    Historique();

public slots:

    void clear();
    void add(int i, QPixmap pixB, QPixmap pix);
    void undo();
    void redo();

signals :

    void exec(int i, QPixmap pix);
    void canUndo(bool b);
    void canRedo(bool b);

private :

    int indexHisto;
    std::deque<std::pair<int, std::pair<QPixmap, QPixmap> > > historique;
};

#endif // HISTORIQUE_H
