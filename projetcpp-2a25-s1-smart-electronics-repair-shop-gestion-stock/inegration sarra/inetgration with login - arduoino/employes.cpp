#include "employes.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QMap>
#include <QDebug>

Employee::Employee()
    : id(0), nom(""), prenom(""), absence(0), numtel(0), sexe(""),
    adresse(""), poste(""), date_naissance(""), salaire(0), pwd(""), card_uid("")
{
}

Employee::Employee(Ui::MainWindow *ui)
{
    id = ui->lineEdit_40->text().toInt();
    nom = ui->lineEdit_42->text();
    prenom = ui->lineEdit_41->text();
    numtel = ui->lineEdit_39->text().toInt();
    adresse = ui->lineEdit_38->text();
    salaire = ui->lineEdit_44->text().toDouble();
    absence = ui->spinBox->value();
    poste = ui->lineEdit_43->text();
    date_naissance = ui->dateEdit->date().toString("yyyy-MM-dd");
    pwd = ui->lineEdit->text();
    // You can add a field for card_uid in your UI if needed

    if (ui->radioButton_3->isChecked())
        sexe = "Homme";
    else if (ui->radioButton_4->isChecked())
        sexe = "Femme";
    else
        sexe = "Homme";
}

Employee::~Employee()
{
}

void Employee::setsexe(Ui::MainWindow *ui)
{
    if (ui->radioButton_3->isChecked())
        sexe = "Homme";
    else if (ui->radioButton_4->isChecked())
        sexe = "Femme";
    else
        sexe = "";
}

bool Employee::modifier()
{
    QSqlQuery query;

    // Update query with CARD_UID
    query.prepare("UPDATE EMPLOYES SET NOM=:nom, PRENOM=:prenom, ABSENCE=:absence, "
                  "NUMTEL=:numtel, SEXE=:sexe, ADRESSE=:adresse, POST=:post, "
                  "DATE_NAISSANCE=TO_DATE(:date_naissance, 'YYYY-MM-DD'), SALAIRE=:salaire, "
                  "PWD=:pwd, CARD_UID=:card_uid WHERE ID=:id");  // ADDED CARD_UID

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":absence", absence);
    query.bindValue(":numtel", numtel);
    query.bindValue(":sexe", sexe);
    query.bindValue(":adresse", adresse);
    query.bindValue(":post", poste);
    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":salaire", salaire);
    query.bindValue(":pwd", pwd);
    query.bindValue(":card_uid", card_uid);  // ADDED

    if (!query.exec()) {
        qDebug() << "Modifier error:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Error", "Cannot modify employee:\n" + query.lastError().text());
        return false;
    }

    return true;
}

bool Employee::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES WHERE ID = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool Employee::ajouter()
{
    QSqlQuery query;

    // Insert query with CARD_UID
    query.prepare("INSERT INTO EMPLOYES (ID, NOM, PRENOM, ABSENCE, NUMTEL, SEXE, ADRESSE, POST, "
                  "DATE_NAISSANCE, SALAIRE, PWD, CARD_UID) "  // ADDED CARD_UID
                  "VALUES (:id, :nom, :prenom, :absence, :numtel, :sexe, :adresse, :post, "
                  "TO_DATE(:date_naissance, 'YYYY-MM-DD'), :salaire, :pwd, :card_uid)");  // ADDED CARD_UID

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":absence", absence);
    query.bindValue(":numtel", numtel);
    query.bindValue(":sexe", sexe);
    query.bindValue(":adresse", adresse);
    query.bindValue(":post", poste);
    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":salaire", salaire);
    query.bindValue(":pwd", pwd);
    query.bindValue(":card_uid", card_uid);  // ADDED

    if (!query.exec()) {
        qDebug() << "Ajouter error:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Error", "Cannot add employee:\n" + query.lastError().text());
        return false;
    }

    return true;
}

void Employee::afficher(Ui::MainWindow *ui)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYES");

    if (query.exec()) {
        ui->tableWidgetemployer->setRowCount(0);

        int row = 0;
        while (query.next()) {
            ui->tableWidgetemployer->insertRow(row);
            ui->tableWidgetemployer->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // ID
            ui->tableWidgetemployer->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // NOM
            ui->tableWidgetemployer->setItem(row, 2, new QTableWidgetItem(query.value(3).toString())); // PRENOM
            ui->tableWidgetemployer->setItem(row, 3, new QTableWidgetItem(query.value(2).toString())); // NUMTEL
            ui->tableWidgetemployer->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // ADRESSE
            ui->tableWidgetemployer->setItem(row, 5, new QTableWidgetItem(query.value(5).toString())); // SALAIRE
            ui->tableWidgetemployer->setItem(row, 6, new QTableWidgetItem(query.value(6).toString())); // ABSENCE
            ui->tableWidgetemployer->setItem(row, 7, new QTableWidgetItem(query.value(7).toString())); // POST
            ui->tableWidgetemployer->setItem(row, 8, new QTableWidgetItem(query.value(8).toString())); // DATE_NAISSANCE
            ui->tableWidgetemployer->setItem(row, 9, new QTableWidgetItem(query.value(9).toString())); // SEXE
            // Add card_uid column if you want to display it
            // ui->tableWidgetemployer->setItem(row, 10, new QTableWidgetItem(query.value(11).toString())); // CARD_UID
            row++;
        }
    }
}

bool Employee::rech(QString recherche, Ui::MainWindow *ui)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYES WHERE ID = ? OR NOM LIKE ? OR PRENOM LIKE ? OR CARD_UID LIKE ?");  // ADDED CARD_UID
    query.addBindValue(recherche.toInt());
    query.addBindValue("%" + recherche + "%");
    query.addBindValue("%" + recherche + "%");
    query.addBindValue("%" + recherche + "%");  // ADDED

    if (query.exec()) {
        ui->tableWidgetemployer->setRowCount(0);

        int row = 0;
        bool found = false;
        while (query.next()) {
            found = true;
            ui->tableWidgetemployer->insertRow(row);
            ui->tableWidgetemployer->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidgetemployer->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidgetemployer->setItem(row, 2, new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidgetemployer->setItem(row, 3, new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidgetemployer->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidgetemployer->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidgetemployer->setItem(row, 6, new QTableWidgetItem(query.value(6).toString()));
            ui->tableWidgetemployer->setItem(row, 7, new QTableWidgetItem(query.value(7).toString()));
            ui->tableWidgetemployer->setItem(row, 8, new QTableWidgetItem(query.value(8).toString()));
            ui->tableWidgetemployer->setItem(row, 9, new QTableWidgetItem(query.value(9).toString()));
            row++;
        }
        return found;
    }
    return false;
}

Employee Employee::getEmployeeById(int id)
{
    Employee emp;
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYES WHERE ID = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        emp.setid(query.value(0).toInt());
        emp.setnom(query.value(1).toString());
        emp.setprenom(query.value(3).toString());
        emp.setnumtel(query.value(2).toInt());
        emp.setadresse(query.value(4).toString());
        emp.setsalaire(query.value(5).toDouble());
        emp.setabsence(query.value(6).toInt());
        emp.setposte(query.value(7).toString());
        emp.setdatenaissance(query.value(8).toString());
        emp.setsexe(query.value(9).toString());
        emp.setpwd(query.value(10).toString());
        emp.setcard_uid(query.value(11).toString());  // ADDED
    }

    return emp;
}
