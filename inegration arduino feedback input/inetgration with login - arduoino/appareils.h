#ifndef APPAREILS_H
#define APPAREILS_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QList>
#include <QDate>

class Intervention {
public:
    int id;
    QString referenceAppareil;
    QDate dateIntervention;
    QString typePanne;
    QString description;
    QString gravite;
    QString statut;
    double coutEstime;
    QString technicien;
    int dureeIntervention;

    Intervention() : id(0), coutEstime(0.0), dureeIntervention(0) {}
};

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

    // CRUD database existant
    bool rechercherParReference(QTableWidget *tableWidget, const QString &reference);
    bool ajouter();
    bool modifier();
    void afficher(Ui::MainWindow *ui);
    bool supprimer(QString id);
    bool existe(QString cin);
    bool rech(QString recherche, Ui::MainWindow *ui);

    // === NOUVELLES MÉTHODES POUR LES INTERVENTIONS ===
    bool ajouterIntervention(const Intervention& intervention);
    QList<Intervention> getInterventionsParAppareil(const QString& reference);
    QList<QString> getTypesPanneFrequents(const QString& reference);
    QMap<QString, int> getStatistiquesTypesPanne();
    bool supprimerIntervention(int idIntervention);

    // Méthode utilitaire pour les types de pannes prédéfinis
    static QStringList getTypesPannePredefinis();
};

#endif // APPAREILS_H
