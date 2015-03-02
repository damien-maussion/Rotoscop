#include "historique.h"

Historique::Historique(): indexHisto(-1)
{
    emit canRedo(false);
    emit canUndo(false);
}

void Historique::clear(){
    historique.clear();
    indexHisto = -1;

    emit canRedo(false);
    emit canUndo(false);
}

void Historique::add(int i, QPixmap pixB, QPixmap pix){
    //qDebug()<< "addHisto "<< indexHisto+1 <<" : "<<i<<" "<< pix;

    if (indexHisto < (int)historique.size()-1)
        historique.erase(historique.begin()+indexHisto+1, historique.end());

    if (historique.size()+1 == MAX_HISTO_SIZE){
        historique.pop_front();
        indexHisto--;
    }

    historique.push_back(std::pair<int, std::pair<QPixmap, QPixmap > >(i,std::pair<QPixmap, QPixmap >(pixB, pix)));
    indexHisto = historique.size()-1;
    emit canUndo(true);
    emit canRedo(false);
}

void Historique::undo(){
    //qDebug()<< "undo "<< indexHisto <<" : "<<historique[indexHisto].first<< " " << historique[indexHisto].second.first ;

    emit exec(historique[indexHisto].first, historique[indexHisto].second.first);
    indexHisto--;

    emit canUndo(indexHisto >= 0);
    emit canRedo(true);
}

void Historique::redo(){
    indexHisto++;
    //qDebug()<< "redo "<< indexHisto+1 <<" : "<<historique[indexHisto].first<< " " << historique[indexHisto].second.second ;
    emit exec(historique[indexHisto].first, historique[indexHisto].second.second);
    emit canUndo(true);
    emit canRedo(indexHisto < (int)historique.size()-1);
}
