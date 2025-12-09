#include "employes.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QMap>
Employee::Employee()
    : id(0), nom(""), prenom(""), absence(0), numtel(0), sexe(""),
    adresse(""), poste(""), date_naissance(""), salaire(0), pwd("")
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
    date_naissance = ui->dateEdit->date()./*toString("dd/MM/yyyy")*/toString("yyyy-MM-dd");

    pwd =ui->lineEdit->text();

    if (ui->radioButton_3->isChecked())
        sexe = "Homme";
    else if (ui->radioButton_4->isChecked())
        sexe = "Femme";
    else
        sexe = "Homme"; // Default value instead of "%"
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

    qDebug() << "=== MODIFIER EMPLOYEE ===";
    qDebug() << "ID:" << id;
    qDebug() << "Nom:" << nom;
    qDebug() << "Prenom:" << prenom;
    qDebug() << "NumTel:" << numtel;
    qDebug() << "Adresse:" << adresse;
    qDebug() << "Salaire:" << salaire;
    qDebug() << "Absence:" << absence;
    qDebug() << "Poste:" << poste;
    qDebug() << "Date Naissance:" << date_naissance;
    qDebug() << "Sexe:" << sexe;
    qDebug() << "pwd:" << pwd;


    // FIXED: Use TO_DATE for Oracle date conversion
    query.prepare("UPDATE EMPLOYES SET NOM=:nom, PRENOM=:prenom, ABSENCE=:absence, "
                  "NUMTEL=:numtel, SEXE=:sexe, ADRESSE=:adresse, POST=:post, "
                  "DATE_NAISSANCE=TO_DATE(:date_naissance, 'YYYY-MM-DD'), SALAIRE=:salaire, PWD=:pwd WHERE ID=:id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":absence", absence);
    query.bindValue(":numtel", numtel);
    query.bindValue(":sexe", sexe);
    query.bindValue(":adresse", adresse);
    query.bindValue(":post", poste);
    query.bindValue(":date_naissance", date_naissance); // This should be in 'YYYY-MM-DD' format
    query.bindValue(":salaire", salaire);
    query.bindValue(":pwd", pwd);

    if (!query.exec()) {
        qDebug() << "Modifier error:" << query.lastError().text();
        qDebug() << "Error details:" << query.lastError().databaseText();

        // Show detailed error message to user
        QMessageBox::critical(nullptr, "Erreur de modification",
                              "Impossible de modifier l'employé:\n" + query.lastError().text());
        return false;
    }

    qDebug() << "Employee modified successfully!";
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

    qDebug() << "=== AJOUTER EMPLOYEE ===";
    qDebug() << "ID:" << id;
    qDebug() << "Nom:" << nom;
    qDebug() << "Prenom:" << prenom;
    qDebug() << "NumTel:" << numtel;
    qDebug() << "Adresse:" << adresse;
    qDebug() << "Salaire:" << salaire;
    qDebug() << "Absence:" << absence;
    qDebug() << "Poste:" << poste;
    qDebug() << "Date Naissance:" << date_naissance;
    qDebug() << "Sexe:" << sexe;
    qDebug() << "Password:" << pwd;

    // FIXED: Use TO_DATE for Oracle date conversion
    query.prepare("INSERT INTO EMPLOYES (ID, NOM, PRENOM, ABSENCE, NUMTEL, SEXE, ADRESSE, POST, DATE_NAISSANCE, SALAIRE, PWD) "
                  "VALUES (:id, :nom, :prenom, :absence, :numtel, :sexe, :adresse, :post, TO_DATE(:date_naissance, 'YYYY-MM-DD'), :salaire, :pwd)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":absence", absence);
    query.bindValue(":numtel", numtel);
    query.bindValue(":sexe", sexe);
    query.bindValue(":adresse", adresse);
    query.bindValue(":post", poste);
    query.bindValue(":date_naissance", date_naissance); // This should be in 'YYYY-MM-DD' format
    query.bindValue(":salaire", salaire);
    query.bindValue(":pwd", pwd);

    if (!query.exec()) {
        qDebug() << "Ajouter error:" << query.lastError().text();
        qDebug() << "Error details:" << query.lastError().databaseText();
        qDebug() << "Last query:" << query.lastQuery();

        // Show detailed error message to user
        QMessageBox::critical(nullptr, "Erreur d'ajout",
                              "Impossible d'ajouter l'employé:\n" + query.lastError().text());
        return false;
    }

    qDebug() << "Employee added successfully!";
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
            ui->tableWidgetemployer->setItem(row, 2, new QTableWidgetItem(query.value(3).toString())); // PRENOM (index 3)
            ui->tableWidgetemployer->setItem(row, 3, new QTableWidgetItem(query.value(2).toString())); // NUMTEL (index 2)
            ui->tableWidgetemployer->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // ADRESSE (index 4)
            ui->tableWidgetemployer->setItem(row, 5, new QTableWidgetItem(query.value(5).toString())); // SALAIRE (index 5)
            ui->tableWidgetemployer->setItem(row, 6, new QTableWidgetItem(query.value(6).toString())); // ABSENCE (index 6)
            ui->tableWidgetemployer->setItem(row, 7, new QTableWidgetItem(query.value(7).toString())); // POST (index 7)
            ui->tableWidgetemployer->setItem(row, 8, new QTableWidgetItem(query.value(8).toString())); // DATE_NAISSANCE (index 8)
            ui->tableWidgetemployer->setItem(row, 9, new QTableWidgetItem(query.value(9).toString())); // SEXE (index 9)
            row++;
        }
    }
}

bool Employee::rech(QString recherche, Ui::MainWindow *ui)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYES WHERE ID = ? OR NOM LIKE ? OR PRENOM LIKE ?");
    query.addBindValue(recherche.toInt());
    query.addBindValue("%" + recherche + "%");
    query.addBindValue("%" + recherche + "%");

    if (query.exec()) {
        ui->tableWidgetemployer->setRowCount(0);

        int row = 0;
        bool found = false;
        while (query.next()) {
            found = true;
            ui->tableWidgetemployer->insertRow(row);
            ui->tableWidgetemployer->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidgetemployer->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidgetemployer->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidgetemployer->setItem(row, 3, new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidgetemployer->setItem(row, 4, new QTableWidgetItem(query.value(6).toString()));
            ui->tableWidgetemployer->setItem(row, 5, new QTableWidgetItem(query.value(9).toString()));
            ui->tableWidgetemployer->setItem(row, 6, new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidgetemployer->setItem(row, 7, new QTableWidgetItem(query.value(7).toString()));
            ui->tableWidgetemployer->setItem(row, 8, new QTableWidgetItem(query.value(8).toString()));
            ui->tableWidgetemployer->setItem(row, 9, new QTableWidgetItem(query.value(5).toString()));
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
        emp.setid(query.value(0).toInt());           // ID
        emp.setnom(query.value(1).toString());       // NOM
        emp.setprenom(query.value(3).toString());    // PRENOM (index 3)
        emp.setnumtel(query.value(2).toInt());       // NUMTEL (index 2)
        emp.setadresse(query.value(4).toString());   // ADRESSE (index 4)
        emp.setsalaire(query.value(5).toDouble());   // SALAIRE (index 5)
        emp.setabsence(query.value(6).toInt());      // ABSENCE (index 6)
        emp.setposte(query.value(7).toString());     // POST (index 7)
        emp.setdatenaissance(query.value(8).toString()); // DATE_NAISSANCE (index 8)
        emp.setsexe(query.value(9).toString());      // SEXE (index 9)
        emp.setpwd(query.value(10).toString());      // PWD (index 10)
    }

    return emp;
}
// Add these methods to employes.cpp

