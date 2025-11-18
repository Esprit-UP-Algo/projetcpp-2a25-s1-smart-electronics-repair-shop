#include "vente.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
vente::vente()
{
    this->idvente = "";
    this->datedevente = "";

    QString tvaStr = 0;
    QString remiseStr = 0;
    QString montantStr = 0;


    this->tauxtva = 0;

    this->montanttotal = 0;



    this->modedepaiment = "";



    qDebug() << "ID:" << idvente
             << "| TVA:" << tauxtva
             << "| Remise:" << remise
             << "| Montant:" << montanttotal
             << "| Paiement:" << modedepaiment;
}
vente::vente(Ui::MainWindow *ui)
{
    this->idvente = ui->lineEdit_45->text().trimmed();
    this->datedevente = ui->dateEdit_3->date().toString("dd-MM-yyyy");

    QString tvaStr = ui->lineEdit_46->text().trimmed();
    QString remiseStr = ui->lineEdit_47->text().trimmed();
    QString montantStr = ui->lineEdit_49->text().trimmed();


    if (tvaStr.isEmpty())
        this->tauxtva = -1;
    else
        this->tauxtva = tvaStr.toInt();

    if (remiseStr.isEmpty())
        this->remise = -1;
    else
        this->remise = remiseStr.toInt();

    if (montantStr.isEmpty())
        this->montanttotal = -1;
    else
        this->montanttotal = montantStr.toInt();


    if (ui->radioButton_5->isChecked())
        this->modedepaiment = "Espèce";
    else if (ui->radioButton_6->isChecked())
        this->modedepaiment = "Carte bancaire";
    else
        this->modedepaiment = "";


    qDebug() << "ID:" << idvente
             << "| TVA:" << tauxtva
             << "| Remise:" << remise
             << "| Montant:" << montanttotal
             << "| Paiement:" << modedepaiment;
}



bool vente::ajouter()
{
    QString erreurs = "";


    if (idvente.trimmed().isEmpty())
        erreurs += "- L'ID de la vente est obligatoire.\n";

    if (modedepaiment.trimmed().isEmpty())
        erreurs += "- Le mode de paiement est obligatoire.\n";

    if (datedevente.trimmed().isEmpty())
        erreurs += "- La date de vente est obligatoire.\n";


    if (tauxtva <= 0)
        erreurs += "- Le taux de TVA doit être supérieur à 0.\n";

    if (tauxtva > 100)
        erreurs += "- Le taux de TVA ne peut pas dépasser 100.\n";

    if (remise < 0)
        erreurs += "- La remise ne peut pas être négative.\n";

    if (remise > 100)
        erreurs += "- La remise ne peut pas dépasser 100.\n";

    if (montanttotal <= 0)
        erreurs += "- Le montant total doit être supérieur à 0.\n";


    if (!erreurs.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreurs de saisie", erreurs);
        return false;
    }


    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM VENTES WHERE IDVENTE = :idvente");
    checkQuery.bindValue(":idvente", idvente);

    if (!checkQuery.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL", checkQuery.lastError().text());
        return false;
    }

    checkQuery.next();
    if (checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(nullptr, "Doublon détecté", "Une vente avec cet ID existe déjà !");
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO VENTES (IDVENTE, TAUXTVA, REMISE, DATEDEVENTE, MONTANTTOTAL, MODEDEPAIMENT) "
                  "VALUES (:idvente, :tauxtva, :remise, TO_DATE(:datedevente,'DD-MM-YYYY'), :montanttotal, :modedepaiment)");

    query.bindValue(":idvente", idvente);
    query.bindValue(":tauxtva", tauxtva);
    query.bindValue(":remise", remise);
    query.bindValue(":datedevente", datedevente);
    query.bindValue(":montanttotal", montanttotal);
    query.bindValue(":modedepaiment", modedepaiment);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
        return false;
    }

    QMessageBox::information(nullptr, "Succès ✅", "La vente a été ajoutée avec succès !");
    return true;
}





void vente::afficher(Ui::MainWindow *ui)
{
    QSqlQuery query;
    query.prepare("SELECT IDVENTE, TAUXTVA, REMISE, DATEDEVENTE, MONTANTTOTAL, MODEDEPAIMENT FROM VENTES");

    if (query.exec()) {
        ui->tableWidgetvente->setRowCount(0);
        int row = 0;
        while (query.next()) {
            ui->tableWidgetvente->insertRow(row);
            ui->tableWidgetvente->setItem(row, 0, new QTableWidgetItem(query.value("IDVENTE").toString()));
            ui->tableWidgetvente->setItem(row, 1, new QTableWidgetItem(query.value("TAUXTVA").toString()));
            ui->tableWidgetvente->setItem(row, 2, new QTableWidgetItem(query.value("REMISE").toString()));
            ui->tableWidgetvente->setItem(row, 3, new QTableWidgetItem(query.value("DATEDEVENTE").toString()));
            ui->tableWidgetvente->setItem(row, 4, new QTableWidgetItem(query.value("MONTANTTOTAL").toString()));
            ui->tableWidgetvente->setItem(row, 5, new QTableWidgetItem(query.value("MODEDEPAIMENT").toString()));
            row++;
        }
        qDebug() << "Ventes affichées (" << row << " lignes).";
    } else {
        qDebug() << "Erreur affichage vente:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
    }
}



bool vente::existe(QString idvente)
{
    QSqlQuery query;
    query.prepare("SELECT idvente FROM VENTES WHERE idvente = :idvente");
    query.bindValue(":idvente", idvente);

    if (query.exec() && query.next())
    {

        return true;
    }
    else
    {
        return false;
    }
}


bool vente::supprimer(QString idvente)
{
    QSqlQuery query;
    query.prepare("DELETE FROM VENTES WHERE IDVENTE = :idvente");
    query.bindValue(":idvente", idvente);

    if (!query.exec())
    {
        qDebug() << "Erreur lors de la suppression du vente :" << query.lastError().text();
        return false;
    }
    return true;
}

bool vente::modifier()
{
    QString erreurs = "";


    if (idvente.trimmed().isEmpty())
        erreurs += "- L'ID de la vente est obligatoire.\n";
    if (datedevente.trimmed().isEmpty())
        erreurs += "- La date de vente est obligatoire.\n";

    if (tauxtva < 0 || tauxtva > 100)
        erreurs += "- Le taux de TVA doit être entre 0 et 100.\n";
    if (remise < 0 || remise > 100)
        erreurs += "- La remise doit être entre 0 et 100.\n";
    if (montanttotal <= 0)
        erreurs += "- Le montant total doit être supérieur à 0.\n";
    if (modedepaiment.trimmed().isEmpty())
        erreurs += "- Le mode de paiement doit être sélectionné.\n";

    if (!erreurs.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreurs de saisie", erreurs);
        return false;
    }

    QSqlQuery check;
    check.prepare("SELECT COUNT(*) FROM VENTES WHERE IDVENTE = :idvente");
    check.bindValue(":idvente", idvente);
    if (!check.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL", check.lastError().text());
        return false;
    }
    check.next();
    if (check.value(0).toInt() == 0) {
        QMessageBox::warning(nullptr, "Vente inexistante", "Aucune vente trouvée avec cet ID !");
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE VENTES SET "
                  "TAUXTVA = :tauxtva, "
                  "REMISE = :remise, "
                  "DATEDEVENTE = TO_DATE(:datedevente,'DD-MM-YYYY'), "
                  "MONTANTTOTAL = :montanttotal, "
                  "MODEDEPAIMENT = :modedepaiment "
                  "WHERE IDVENTE = :idvente");

    query.bindValue(":tauxtva", tauxtva);
    query.bindValue(":remise", remise);
    query.bindValue(":datedevente", datedevente);
    query.bindValue(":montanttotal", montanttotal);
    query.bindValue(":modedepaiment", modedepaiment);
    query.bindValue(":idvente", idvente);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
        return false;
    }

    QMessageBox::information(nullptr, "Succès", "La vente a été modifiée avec succès !");
    return true;
}
bool vente::rechercherParId(QTableWidget *tableWidget, const QString &idvente)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM VENTES WHERE IDVENTE = :idvente");
    query.bindValue(":idvente", idvente);

    if (!query.exec()) {
        qDebug() << "Erreur recherche :" << query.lastError().text();
        return false;
    }

    tableWidget->setRowCount(0);
    int row = 0;

    while (query.next()) {
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("IDVENTE").toString()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("TAUXTVA").toString()));
        tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("REMISE").toString()));
        tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("DATE").toString()));
        tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("MONTANTTOTAL").toString()));
        tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("MODEDEPAIMENT").toString()));
        row++;
    }

    if (row == 0) {
        qDebug() << "Aucune vente trouvée avec cet ID.";
        return false;
    } else {
        qDebug() << "Vente trouvée et affichée.";
        return true;
    }
}








vente::~vente() {}
