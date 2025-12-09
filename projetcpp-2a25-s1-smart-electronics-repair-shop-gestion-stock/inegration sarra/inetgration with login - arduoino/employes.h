#ifndef EMPLOYES_H
#define EMPLOYES_H

#include <QString>
#include <QDate>

namespace Ui {
class MainWindow;
}

class Employee
{
private:
    int id;
    QString nom;
    QString prenom;
    int absence;
    int numtel;
    QString sexe;
    QString adresse;
    QString poste;
    QString date_naissance;
    double salaire;
    QString pwd;
    QString card_uid;  // ADDED for RFID card

public:
    Employee();
    Employee(Ui::MainWindow *ui);
    ~Employee();

    // Getters
    int getid() const { return id; }
    QString getnom() const { return nom; }
    QString getprenom() const { return prenom; }
    int getabsence() const { return absence; }
    int getnumtel() const { return numtel; }
    QString getsexe() const { return sexe; }
    QString getadresse() const { return adresse; }
    QString getposte() const { return poste; }
    QString getdatenaissance() const { return date_naissance; }
    double getsalaire() const { return salaire; }
    QString getpwd() const { return pwd; }
    QString getcard_uid() const { return card_uid; }  // ADDED

    // Setters
    void setid(int id) { this->id = id; }
    void setnom(QString nom) { this->nom = nom; }
    void setprenom(QString prenom) { this->prenom = prenom; }
    void setabsence(int absence) { this->absence = absence; }
    void setnumtel(int numtel) { this->numtel = numtel; }
    void setsexe(QString sexe) { this->sexe = sexe; }
    void setadresse(QString adresse) { this->adresse = adresse; }
    void setposte(QString poste) { this->poste = poste; }
    void setdatenaissance(QString date_naissance) { this->date_naissance = date_naissance; }
    void setsalaire(double salaire) { this->salaire = salaire; }
    void setpwd(QString pwd) { this->pwd = pwd; }
    void setcard_uid(QString card_uid) { this->card_uid = card_uid; }  // ADDED

    // Methods
    void setsexe(Ui::MainWindow *ui);
    bool modifier();
    bool ajouter();
    bool supprimer(int id);
    void afficher(Ui::MainWindow *ui);
    bool rech(QString recherche, Ui::MainWindow *ui);
    Employee getEmployeeById(int id);
};

#endif // EMPLOYES_H
