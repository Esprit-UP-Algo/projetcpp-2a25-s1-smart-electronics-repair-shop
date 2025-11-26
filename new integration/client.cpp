#include "client.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
void Client::setsexe(Ui::MainWindow *ui)
{
    if (ui->radioButton_Homme_4->isChecked()) {
        sexe = "Homme";
    } else if (ui->radioButton_Femme_4->isChecked()) {
        sexe = "Femme";
    } else {
        sexe = "∅";
    }
}

Client::Client(Ui::MainWindow *ui)
{
    this->cin = ui->lineEdit_IDClient_4->text();
    this->nom = ui->lineEdit_nom_4->text();
    this->prenom = ui->lineEdit_Prenom_4->text();
    this->adresse = ui->lineEdit_Adresse_4->text();
    this->nt = ui->lineEdit_Nt_4->text();
    this->birth = ui->datedenaissance_3->text();
    this->setsexe(ui);
    this->creationdate = QDate::currentDate().toString("yyyy-MM-dd");


}

Client::~Client() {}
void Client::afficher(Ui::MainWindow *ui)
{

    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENTS");

    if (query.exec())
    {
        ui->tableWidgetclient->setRowCount(0); // clear table first
        int row = 0;

        while (query.next())
        {
            ui->tableWidgetclient->insertRow(row);
            ui->tableWidgetclient->setItem(row, 0, new QTableWidgetItem(query.value("CIN").toString()));
            ui->tableWidgetclient->setItem(row, 1, new QTableWidgetItem(query.value("NOM").toString()));
            ui->tableWidgetclient->setItem(row, 2, new QTableWidgetItem(query.value("PRENOM").toString()));
            ui->tableWidgetclient->setItem(row, 3, new QTableWidgetItem(query.value("ADRESSE").toString()));
            ui->tableWidgetclient->setItem(row, 4, new QTableWidgetItem(query.value("NT").toString()));
            ui->tableWidgetclient->setItem(row, 5, new QTableWidgetItem(query.value("SEXE").toString()));
            ui->tableWidgetclient->setItem(row, 6, new QTableWidgetItem(query.value("BIRTH").toString()));
            ui->tableWidgetclient->setItem(row, 7, new QTableWidgetItem(query.value("CREATIONDATE").toString()));

            row++;
        }
    }
}

bool Client::supprimer(QString id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENTS WHERE CIN = :id");
    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "Erreur suppression client:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Client::modifier()
{
    QSqlQuery query;

    query.prepare("UPDATE CLIENTS SET NOM=:nom, PRENOM=:prenom, ADRESSE=:adresse, NT=:nt, BIRTH=:birth, SEXE=:sexe "
                  "WHERE CIN=:cin");

    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":nt", nt);
    query.bindValue(":birth", birth);
    query.bindValue(":sexe", sexe);


    bool test = query.exec();

    if (test)
        qDebug() << "✅ Modification réussie pour le client:" << nom << prenom;
    else
        qDebug() << "❌ Erreur de modification:" << query.lastError().text();

    return test;
}

bool Client::existe(QString cin)
{
    QSqlQuery query;
    query.prepare("SELECT CIN FROM CLIENTS WHERE CIN = :cin");
    query.bindValue(":cin", cin);
    query.exec();

    return query.next();
}
Client Client::getclientByCin(QString cin)
{
    Client c;
    QSqlQuery query;
    query.prepare("SELECT CIN, NOM, PRENOM, ADRESSE, NT, BIRTH, CREATIONDATE "
                  "FROM CLIENTS WHERE CIN = :cin");
    query.bindValue(":cin", cin);

    if (query.exec() && query.next())
    {
        c.setidclient(query.value("CIN").toString());
        c.setnom(query.value("NOM").toString());
        c.setprenom(query.value("PRENOM").toString());
        c.setadresse(query.value("ADRESSE").toString());
        c.setnt(query.value("NT").toString());
        c.setbirth(query.value("BIRTH").toString());

        c.setcreationdate(query.value("CREATIONDATE").toString());
    }

    return c;
}


bool Client::rech(QString recherche, Ui::MainWindow *ui)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENTS WHERE NT LIKE :rech OR NOM LIKE :rech2 OR PRENOM LIKE :rech3");
    query.bindValue(":rech", "%" + recherche + "%");
    query.bindValue(":rech2", "%" + recherche + "%");
    query.bindValue(":rech3", "%" + recherche + "%");


    if (!query.exec()) {
        qDebug() << "❌ Search error:" << query.lastError().text();
        return false;
    }

    QTableWidget *table = ui->tableWidgetclient;  // your widget name here

    table->setRowCount(0); // clear old rows

    int row = 0;
    while (query.next())
    {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(query.value("CIN").toString()));
        table->setItem(row, 1, new QTableWidgetItem(query.value("NOM").toString()));
        table->setItem(row, 2, new QTableWidgetItem(query.value("PRENOM").toString()));
        table->setItem(row, 3, new QTableWidgetItem(query.value("ADRESSE").toString()));
        table->setItem(row, 4, new QTableWidgetItem(query.value("NT").toString()));
        table->setItem(row, 5, new QTableWidgetItem(query.value("SEXE").toString()));
        table->setItem(row, 6, new QTableWidgetItem(query.value("BIRTH").toString()));
        table->setItem(row, 7, new QTableWidgetItem(query.value("CREATIONDATE").toString()));
        row++;
    }

    return row > 0;
}




bool Client::ajouter()
{
    QSqlQuery query;
    bool test;
    query.prepare("INSERT INTO CLIENTS (CIN, NOM, PRENOM, ADRESSE, NT, BIRTH, SEXE, CREATIONDATE) "
                  "VALUES (:cin, :nom, :prenom, :adresse, :nt, :birth, :sexe, :creationdate)");
    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":nt", nt);
    query.bindValue(":birth", birth);
    query.bindValue(":sexe", sexe);
    query.bindValue(":creationdate", creationdate);
     test = query.exec();

    if (test) {
        qDebug() << "✅ Ajout réussi pour le client:" << nom << prenom;
    } else {
        qDebug() << "❌ Erreur d'ajout du client:" << query.lastError().text();
    }

    return test;
}

