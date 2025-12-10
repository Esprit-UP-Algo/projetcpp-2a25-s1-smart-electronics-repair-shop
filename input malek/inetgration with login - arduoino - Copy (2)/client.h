#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlQueryModel>

class Client {
private:
    QString cin;
    QString nom;
    QString prenom;
    QString adresse;
    QString nt;
    QString sexe,birth,creationdate,avis;

public:
    int supprimerDoublonsAmelioree();
    int supprimerDoublonsSimple();
    void afficherRapportDoublons();
    void nettoyerDoublonsAvecRapport();
    Client(Ui::MainWindow *ui);
    Client(){};
    ~Client();
    // setters
    void setidclient(const QString &id) { cin = id; }
    void setnom(const QString &n) { nom = n; }
    void setprenom(const QString &p) { prenom = p; }
    void setadresse(const QString &a) { adresse = a; }
    void setnt(const QString &num) { nt = num; }
    void setbirth(const QString &num) { birth = num; }
    void setsexe(Ui::MainWindow *ui);
    void setcreationdate(const QString &num) { creationdate = num; }
    // getters
    QString getavis() const { return avis; }
    QString getidclient() const { return cin; }
    QString getnom() const { return nom; }
    QString getprenom() const { return prenom; }
    QString getadresse() const { return adresse; }
    QString getnt() const { return nt; }
    QString getbirth() const { return birth; }
    QString getsexe() const { return sexe; }
     QString getcreationdate() const { return creationdate; }
    //database
     Client getclientByCin(QString cin);
    bool ajouter();
    bool modifier();
    void afficher(Ui::MainWindow *ui);
    bool supprimer(QString id);
    bool existe(QString cin);
    bool rech(QString recherche, Ui::MainWindow *ui);
};

#endif // CLIENT_H
