#include "produit.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QMessageBox>
Produit::Produit(Ui::MainWindow *ui)
{
    this->reference = ui->lineEdit_reference->text();
    this->nom = ui->lineEdit_nom->text();
    this->categorie = ui->lineEdit_categorie->text();
    this->marque = ui->comboBox->currentText();
    this->prix = ui->lineEdit_prix->text().toDouble();
    this->quantite = ui->lineEdit_quantite->text().toInt();
    this->dateAchat = ui->dateEdit_2->date().toString("dd-MM-yyyy");
    this->dateExpiration = ui->dateEdit_4->date().toString("dd-MM-yyyy");
}
bool Produit::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO PRODUITS (REFERENCE, NOM, CATEGORIE, MARQUE, PRIX, QUANTITE, DATEACHAT, DATEEXPIRATION) "
                  "VALUES (:reference, :nom, :categorie, :marque, :prix, :quantite, "
                  "TO_DATE(:dateAchat, 'DD-MM-YYYY'), TO_DATE(:dateExpiration, 'DD-MM-YYYY'))");


    query.bindValue(":reference", reference);
    query.bindValue(":nom", nom);
    query.bindValue(":categorie", categorie);
    query.bindValue(":marque", marque);
    query.bindValue(":prix", prix);
    query.bindValue(":quantite", quantite);


    query.bindValue(":dateAchat", dateAchat);
    query.bindValue(":dateExpiration", dateExpiration);

    if (!query.exec())
    {
        qDebug() << "Erreur lors de l'ajout du produit :" << query.lastError().text();
        return false;
    }
    else
        qDebug() << "succes l'ajout du produit :" ;
    return true;
}
bool Produit::existe(QString reference)
{
    QSqlQuery query;
    query.prepare("SELECT reference FROM PRODUITS WHERE reference = :reference");
    query.bindValue(":reference", reference);

    if (query.exec() && query.next())
    {
        // Un produit avec cette référence existe déjà
        return true;
    }
    else
    {
        // Aucun produit trouvé avec cette référence
        return false;
    }
}

void Produit::afficher(Ui::MainWindow *ui)
{
    QSqlQuery query;
    query.prepare("SELECT REFERENCE, NOM, CATEGORIE, MARQUE, PRIX, QUANTITE, DATEACHAT, DATEEXPIRATION FROM PRODUITS");

    if (query.exec()) {
        ui->tableWidgetstock->setRowCount(0); // clear old data
        int row = 0;

        while (query.next()) {
            ui->tableWidgetstock->insertRow(row);
            ui->tableWidgetstock->setItem(row, 0, new QTableWidgetItem(query.value("reference").toString()));
            ui->tableWidgetstock->setItem(row, 1, new QTableWidgetItem(query.value("nom").toString()));
            ui->tableWidgetstock->setItem(row, 2, new QTableWidgetItem(query.value("categorie").toString()));
            ui->tableWidgetstock->setItem(row, 3, new QTableWidgetItem(query.value("marque").toString()));
            ui->tableWidgetstock->setItem(row, 4, new QTableWidgetItem(query.value("prix").toString()));
            ui->tableWidgetstock->setItem(row, 5, new QTableWidgetItem(query.value("quantite").toString()));
            ui->tableWidgetstock->setItem(row, 6, new QTableWidgetItem(query.value("dateAchat").toString()));
            ui->tableWidgetstock->setItem(row, 7, new QTableWidgetItem(query.value("dateExpiration").toString()));
            row++;
        }

        qDebug() << "Produits affichés dans le tableau (" << row << " lignes ).";
    } else {
        qDebug() << " Erreur affichage produits:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
    }
}

bool Produit::supprimer(QString reference)
{
    QSqlQuery query;
    query.prepare("DELETE FROM PRODUITS WHERE REFERENCE = :reference");
    query.bindValue(":reference", reference);

    if (!query.exec())
    {
        qDebug() << "Erreur lors de la suppression du produit :" << query.lastError().text();
        return false;
    }
    return true;
}





Produit::~Produit() {}
