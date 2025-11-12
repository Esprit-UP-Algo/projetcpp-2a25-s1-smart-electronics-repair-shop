#ifndef APPAREILS_H
#define APPAREILS_H


#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlQueryModel>

class appareils {
private:
    QString reference;
    QString marque;
    QString datedachat;
    QString dernierdateentretien;
    QString etatappareil;


public:
    appareils(Ui::MainWindow *ui);
    appareils(){};
    ~appareils(){};
    // setters
    void setreference(const QString &id) { reference = id; }
    void setmarque(const QString &n) { marque = n; }
    void setdatedachat(const QString &p) { datedachat = p; }
    void setdernierdateentretien(const QString &a) { dernierdateentretien = a; }
    void setetatappareil(const QString &num) { etatappareil = num; }
    // getters
    QString getreference() const { return reference; }
    QString getmarque() const { return marque; }
    QString getdatedachat() const { return datedachat; }
    QString getdernierdateentretien() const { return dernierdateentretien; }
    QString getetatappareil() const { return etatappareil; }
   //database
    bool rechercherParReference(QTableWidget *tableWidget, const QString &reference);
    bool ajouter();
    bool modifier();
    void afficher(Ui::MainWindow *ui);
    bool supprimer(QString id);
    bool existe(QString cin);
    bool rech(QString recherche, Ui::MainWindow *ui);
};
#endif // APPAREILS_H
