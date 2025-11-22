#ifndef VENTE_H
#define VENTE_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableWidget>

class Ui_MainWindow;
class vente
{
private:
    QString idvente;
    int tauxtva;
    int remise;
    QString datedevente;
    int montanttotal;
    QString modedepaiment;

public:
    vente();
    // Constructeur
    vente(Ui::MainWindow *ui);
    ~vente();

    // Getters
    QString getidvente() const { return idvente; }
    int gettauxtva() const { return tauxtva; }
    int getremise() const { return remise; }
    QString getdatedevente() const { return datedevente; }
    int getmontanttotal() const { return montanttotal; }
    QString getmodedepaiment() const { return modedepaiment; }


    // Setters
    void setidvente(QString idvente) { this->idvente = idvente; }
    void settauxtva(int tauxtva) { this->tauxtva = tauxtva; }
    void setremise(int remise ) { this->remise = remise; }
    void setdatedevente(QString datedevente) { this->datedevente = datedevente; }
    void setmontanttotal(int montanttotal) { this->montanttotal = montanttotal; }
    void setmodedepaiment(QString modedepaiment) { this->modedepaiment = modedepaiment; }


    // Fonctions
    bool existe(QString idvente);
    bool ajouter();
    bool supprimer(QString idvente);
    bool modifier(QString idvente);
    void afficher(Ui::MainWindow *ui);
    bool modifier();                 // utilisée par ton bouton "Modifier"
    void afficher(Ui_MainWindow *ui);
    bool rechercherParId(QTableWidget *tableWidget, const QString &idvente);
    bool trierParDate(QTableWidget *tableWidget);
};

#endif

