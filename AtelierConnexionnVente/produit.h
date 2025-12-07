#ifndef PRODUIT_H
#define PRODUIT_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableWidget>

class Produit
{
private:
    QString reference;
    QString nom;
    QString categorie;
    QString marque;
    double prix;
    int quantite;
    QString dateAchat;
    QString dateExpiration;

public:
    // Constructeur
    Produit(Ui::MainWindow *ui);
    ~Produit();

    // Getters
    QString getreference() const { return reference; }
    QString getnom() const { return nom; }
    QString getcategorie() const { return categorie; }
    QString getmarque() const { return marque; }
    double getprix() const { return prix; }
    int getquantite() const { return quantite; }
    QString getdateAchat() const { return dateAchat; }
    QString getdateExpiration() const { return dateExpiration; }

    // Setters
    void setreference(QString reference) { this->reference = reference; }
    void setnom(QString nom) { this->nom = nom; }
    void setcategorie(QString categorie) { this->categorie = categorie; }
    void setmarque(QString marque) { this->marque = marque; }
    void setprix(double prix) { this->prix = prix; }
    void setquantite(int quantite) { this->quantite = quantite; }
    void setdateAchat(QString dateAchat) { this->dateAchat = dateAchat; }
    void setdateExpiration(QString dateExpiration) { this->dateExpiration = dateExpiration; }

    // Fonctions
    bool existe(QString reference);
    bool ajouter();
    bool supprimer(QString reference);
    bool modifier(QString reference);
    void afficher(Ui::MainWindow *ui);
};

#endif
