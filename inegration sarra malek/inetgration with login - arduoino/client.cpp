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
    this->creationdate = QDate::currentDate().toString("yyyy-MM-dd")/*toString("dd-MM-yyyy")*/;


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


    bool test = query.exec();

    if (test) {
        qDebug() << "✅ Ajout réussi pour le client:" << nom << prenom;
    } else {
        qDebug() << "❌ Erreur d'ajout du client:" << query.lastError().text();
        qDebug() << "Query:" << query.lastQuery();
        qDebug() << "Values - CIN:" << cin << "Nom:" << nom << "Prenom:" << prenom;
    }

    return test;
}

/**
 * @brief Version améliorée pour supprimer tous les doublons
 * @return int Nombre de doublons supprimés
 */
int Client::supprimerDoublonsAmelioree()
{
    QSqlQuery query;
    int doublonsSupprimes = 0;

    // Démarrer une transaction
    QSqlDatabase::database().transaction();

    try {
        // Méthode 1: Vérifier d'abord les doublons
        query.prepare("SELECT NOM, PRENOM, NT, ADRESSE, COUNT(*) as count, MIN(CIN) as CIN_GARDE "
                      "FROM CLIENTS "
                      "GROUP BY NOM, PRENOM, NT, ADRESSE "
                      "HAVING COUNT(*) > 1");

        if (query.exec()) {
            while (query.next()) {
                QString nom = query.value("NOM").toString();
                QString prenom = query.value("PRENOM").toString();
                QString nt = query.value("NT").toString();
                QString adresse = query.value("ADRESSE").toString();
                QString cinAGarder = query.value("CIN_GARDE").toString();
                int count = query.value("count").toInt();

                qDebug() << "🔍 Doublon trouvé:" << nom << prenom << "| Count:" << count << "| Garder CIN:" << cinAGarder;

                // Supprimer tous les doublons sauf celui qu'on garde
                QSqlQuery deleteQuery;
                deleteQuery.prepare("DELETE FROM CLIENTS "
                                    "WHERE NOM = :nom AND PRENOM = :prenom AND NT = :nt AND ADRESSE = :adresse "
                                    "AND CIN != :cin_garde");
                deleteQuery.bindValue(":nom", nom);
                deleteQuery.bindValue(":prenom", prenom);
                deleteQuery.bindValue(":nt", nt);
                deleteQuery.bindValue(":adresse", adresse);
                deleteQuery.bindValue(":cin_garde", cinAGarder);

                if (deleteQuery.exec()) {
                    doublonsSupprimes += deleteQuery.numRowsAffected();
                    qDebug() << "✅ Supprimé" << deleteQuery.numRowsAffected() << "doublon(s) pour" << nom << prenom;
                }
            }
        }

        // Valider la transaction
        QSqlDatabase::database().commit();
        qDebug() << "🎉 Nettoyage terminé. Doublons supprimés:" << doublonsSupprimes;

    } catch (...) {
        // Annuler en cas d'erreur
        QSqlDatabase::database().rollback();
        qDebug() << "❌ Erreur lors du nettoyage - Transaction annulée";
        return 0;
    }

    return doublonsSupprimes;
}

/**
 * @brief Affiche un rapport détaillé des doublons sans les supprimer
 */
void Client::afficherRapportDoublons()
{
    QSqlQuery query;

    query.prepare("SELECT NOM, PRENOM, NT, ADRESSE, COUNT(*) as count, "
                  "GROUP_CONCAT(CIN) as cins "
                  "FROM CLIENTS "
                  "GROUP BY NOM, PRENOM, NT, ADRESSE "
                  "HAVING COUNT(*) > 1 "
                  "ORDER BY count DESC");

    if (query.exec()) {
        qDebug() << "📊 RAPPORT DES DOUBLONS:";
        qDebug() << "========================";

        int totalGroupes = 0;
        int totalDoublons = 0;

        while (query.next()) {
            QString nom = query.value("NOM").toString();
            QString prenom = query.value("PRENOM").toString();
            QString nt = query.value("NT").toString();
            QString adresse = query.value("ADRESSE").toString();
            int count = query.value("count").toInt();
            QString cins = query.value("cins").toString();

            qDebug() << "👥 Groupe" << ++totalGroupes << ":";
            qDebug() << "   Nom/Prénom:" << nom << prenom;
            qDebug() << "   Téléphone:" << nt;
            qDebug() << "   Adresse:" << adresse;
            qDebug() << "   Nombre de doublons:" << count;
            qDebug() << "   CINs:" << cins;
            qDebug() << "   ---";

            totalDoublons += (count - 1);
        }

        qDebug() << "📈 TOTAL:";
        qDebug() << "   Groupes de doublons:" << totalGroupes;
        qDebug() << "   Doublons à supprimer:" << totalDoublons;

    } else {
        qDebug() << "❌ Erreur rapport doublons:" << query.lastError().text();
    }
}

/**
 * @brief Version ultra-simple pour supprimer tous les doublons
 * @return int Nombre de doublons supprimés
 */
int Client::supprimerDoublonsSimple()
{
    QSqlQuery query;

    // Compter avant
    query.prepare("SELECT COUNT(*) as total FROM CLIENTS");
    query.exec();
    query.next();
    int totalAvant = query.value("total").toInt();

    // Supprimer les doublons en gardant le plus petit CIN
    query.prepare("DELETE FROM CLIENTS "
                  "WHERE CIN NOT IN ("
                  "   SELECT MIN(CIN) "
                  "   FROM CLIENTS "
                  "   GROUP BY NOM, PRENOM, NT, ADRESSE"
                  ")");

    if (query.exec()) {
        int supprimes = query.numRowsAffected();

        // Compter après
        query.prepare("SELECT COUNT(*) as total FROM CLIENTS");
        query.exec();
        query.next();
        int totalApres = query.value("total").toInt();

        qDebug() << "✅ Doublons supprimés :" << supprimes;
        qDebug() << "📊 Avant:" << totalAvant << "| Après:" << totalApres;

        return supprimes;
    } else {
        qDebug() << "❌ Erreur suppression doublons :" << query.lastError().text();
        return 0;
    }
}

/**
 * @brief Supprime les doublons et affiche un rapport détaillé
 */
void Client::nettoyerDoublonsAvecRapport()
{
    qDebug() << "🧹 Début du nettoyage des doublons...";

    // D'abord afficher le rapport
    afficherRapportDoublons();

    // Ensuite supprimer
    int doublonsSupprimes = supprimerDoublonsAmelioree();

    qDebug() << "💾 Nettoyage terminé :" << doublonsSupprimes << "doublons supprimés";
}
