#include "employes.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QTableWidget>
#include <QTableWidgetItem>

// CONSTRUCTEUR PAR DÉFAUT
Employee::Employee()
    : id(0), nom(""), prenom(""), absence(0), numtel(0), sexe(""),
    adresse(""), poste(""), date_naissance(""), salaire(0.0)
{
}

void Employee::setsexe(Ui::MainWindow *ui)
{
    if (ui->radioButton_3->isChecked()) {
        sexe = "Homme";
    } else if (ui->radioButton_4->isChecked()) {
        sexe = "Femme";
    } else {
        sexe = "∅";
    }
}

Employee::Employee(Ui::MainWindow *ui)
{
    this->id = ui->lineEdit_40->text().toInt();
    this->nom = ui->lineEdit_42->text();
    this->prenom = ui->lineEdit_41->text();
    this->numtel = ui->lineEdit_39->text().toInt();
    this->adresse = ui->lineEdit_38->text();
    this->salaire = ui->lineEdit_44->text().toDouble();
    this->absence = ui->spinBox->value();
    this->date_naissance = ui->dateEdit->date().toString("dd/MM/yyyy");
    this->poste = ui->lineEdit_43->text();
    this->setsexe(ui);
}

Employee::~Employee() {}

void Employee::afficher(Ui::MainWindow *ui)
{
    QSqlQuery query;
    query.prepare("SELECT ID, NOM, PRENOM, NUMTEL, ADRESSE, SALAIRE, ABSENCE, POST, TO_CHAR(DATE_NAISSANCE, 'DD/MM/YYYY') as DATE_NAISSANCE, SEXE FROM EMPLOYES");

    if (query.exec())
    {
        ui->tableWidgetemployer->setRowCount(0);
        int row = 0;

        while (query.next())
        {
            ui->tableWidgetemployer->insertRow(row);
            ui->tableWidgetemployer->setItem(row, 0, new QTableWidgetItem(query.value("ID").toString()));
            ui->tableWidgetemployer->setItem(row, 1, new QTableWidgetItem(query.value("NOM").toString()));
            ui->tableWidgetemployer->setItem(row, 2, new QTableWidgetItem(query.value("PRENOM").toString()));
            ui->tableWidgetemployer->setItem(row, 3, new QTableWidgetItem(query.value("NUMTEL").toString()));
            ui->tableWidgetemployer->setItem(row, 4, new QTableWidgetItem(query.value("ADRESSE").toString()));
            ui->tableWidgetemployer->setItem(row, 5, new QTableWidgetItem(query.value("SALAIRE").toString()));
            ui->tableWidgetemployer->setItem(row, 6, new QTableWidgetItem(query.value("ABSENCE").toString()));
            ui->tableWidgetemployer->setItem(row, 7, new QTableWidgetItem(query.value("POST").toString()));
            ui->tableWidgetemployer->setItem(row, 8, new QTableWidgetItem(query.value("DATE_NAISSANCE").toString()));
            ui->tableWidgetemployer->setItem(row, 9, new QTableWidgetItem(query.value("SEXE").toString()));
            row++;
        }
        qDebug() << "✅ Affichage réussi:" << row << "employés affichés";
    }
    else
    {
        qDebug() << "❌ Erreur d'affichage:" << query.lastError().text();
    }
}

bool Employee::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES WHERE ID = :id");
    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "❌ Erreur suppression:" << query.lastError().text();
        return false;
    }
    qDebug() << "✅ Suppression réussie ID:" << id;
    return true;
}

bool Employee::ajouter()
{
    QSqlQuery query;


    qDebug() << "=== TENTATIVE AJOUT EMPLOYÉ ===";
    qDebug() << "ID:" << id;
    qDebug() << "Nom:" << nom;
    qDebug() << "Prénom:" << prenom;
    qDebug() << "Téléphone:" << numtel;
    qDebug() << "Adresse:" << adresse;
    qDebug() << "Salaire:" << salaire;
    qDebug() << "Absence:" << absence;
    qDebug() << "Date Naissance:" << date_naissance;
    qDebug() << "Poste:" << poste;
    qDebug() << "Sexe:" << sexe;


    query.prepare("INSERT INTO EMPLOYES (ID, NOM, PRENOM, NUMTEL, ADRESSE, SALAIRE, ABSENCE, POST, DATE_NAISSANCE, SEXE) "
                  "VALUES (:id, :nom, :prenom, :numtel, :adresse, :salaire, :absence, :poste, TO_DATE(:date_naissance, 'DD/MM/YYYY'), :sexe)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":numtel", numtel);
    query.bindValue(":adresse", adresse);
    query.bindValue(":salaire", salaire);
    query.bindValue(":absence", absence);
    query.bindValue(":poste", poste);
    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":sexe", sexe);

    bool test = query.exec();

    if (test) {
        qDebug() << "✅ Ajout réussi pour l'employé:" << nom << prenom;
    } else {
        qDebug() << "❌ Erreur d'ajout de l'employé:" << query.lastError().text();
        qDebug() << "Erreur détaillée:" << query.lastError().databaseText();
    }

    return test;
}
bool Employee::modifier()
{
    QSqlQuery query;

    qDebug() << "=== TENTATIVE MODIFICATION EMPLOYÉ ===";
    qDebug() << "ID:" << id;
    qDebug() << "Nom:" << nom;
    qDebug() << "Prénom:" << prenom;
    qDebug() << "Téléphone:" << numtel;
    qDebug() << "Adresse:" << adresse;
    qDebug() << "Salaire:" << salaire;
    qDebug() << "Absence:" << absence;
    qDebug() << "Date Naissance:" << date_naissance;
    qDebug() << "Poste:" << poste;
    qDebug() << "Sexe:" << sexe;

    query.prepare("UPDATE EMPLOYES SET NOM=:nom, PRENOM=:prenom, NUMTEL=:numtel, ADRESSE=:adresse, "
                  "SALAIRE=:salaire, ABSENCE=:absence, POST=:poste, DATE_NAISSANCE=TO_DATE(:date_naissance, 'DD/MM/YYYY'), SEXE=:sexe "
                  "WHERE ID=:id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":numtel", numtel);
    query.bindValue(":adresse", adresse);
    query.bindValue(":salaire", salaire);
    query.bindValue(":absence", absence);
    query.bindValue(":poste", poste);
    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":sexe", sexe);

    bool test = query.exec();

    if (test) {
        qDebug() << "✅ Modification réussie pour l'employé:" << nom << prenom;
    } else {
        qDebug() << "❌ Erreur de modification:" << query.lastError().text();
        qDebug() << "Erreur détaillée:" << query.lastError().databaseText();
    }

    return test;
}
