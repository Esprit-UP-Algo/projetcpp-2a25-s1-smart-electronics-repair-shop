#include "appareils.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
appareils::appareils(Ui::MainWindow *ui) {
    this->reference=ui->lineEdit_28->text();
    this->marque=ui->lineEdit_29->text();
    this->datedachat=ui->dateEdit_5->text();
    this->dernierdateentretien=ui->dateEdit_6->text();
    this->etatappareil=ui->lineEdit_32->text();
}
bool appareils::existe(QString cin)
{
    QSqlQuery query;
    query.prepare("SELECT CIN FROM APPAREILS WHERE REFERENCE = :cin");
    query.bindValue(":cin", cin);
    query.exec();

    return query.next();
}
bool appareils::ajouter()
{
    // === Validation des champs ===
    QRegularExpression lettersOnly("^[A-Za-z]+$"); // Only letters

    // Vérifier la référence
    if (reference.length()!=8)  {
        qDebug() << "❌ Erreur: la référence doit contenir exactement 8 caractères.";
        return false;
    }

    // Vérifier la marque
    if (!lettersOnly.match(marque).hasMatch() || marque.length() != 7) {
        qDebug() << "❌ Erreur: la marque doit contenir exactement 7 lettres.";
        return false;
    }

    // Vérifier l'état de l'appareil
    if (!lettersOnly.match(etatappareil).hasMatch()) {
        qDebug() << "❌ Erreur: l'état de l'appareil doit contenir uniquement des lettres.";
        return false;
    }

    // === Requête SQL ===
    QSqlQuery query;
    query.prepare("INSERT INTO APPAREILS (REFERENCE, MARQUE, DATEDACHAT, DERNIEREN, ETATAPPAREIL) "
                  "VALUES (:reference, :marque, :datedachat, :dernierdateentretien, :etatappareil)");

    query.bindValue(":reference", reference);
    query.bindValue(":marque", marque);
    query.bindValue(":datedachat", datedachat);
    query.bindValue(":dernierdateentretien", dernierdateentretien);
    query.bindValue(":etatappareil", etatappareil);

    bool test = query.exec();

    if (test) {
        qDebug() << "✅ Ajout réussi pour l'appareil:" << reference;
    } else {
        qDebug() << "❌ Erreur d'ajout de l'appareil:" << query.lastError().text();
    }

    return test;
}

void appareils::afficher(Ui::MainWindow *ui)
{

    QSqlQuery query;
    query.prepare("SELECT * FROM APPAREILS");

    if (query.exec())
    {
        ui->tableWidgetfour->setRowCount(0); // clear table first
        int row = 0;

        while (query.next())
        {
            ui->tableWidgetfour->insertRow(row);
            ui->tableWidgetfour->setItem(row, 0, new QTableWidgetItem(query.value("REFERENCE").toString()));
            ui->tableWidgetfour->setItem(row, 1, new QTableWidgetItem(query.value("MARQUE").toString()));
            ui->tableWidgetfour->setItem(row, 2, new QTableWidgetItem(query.value("DATEDACHAT").toString()));
            ui->tableWidgetfour->setItem(row, 3, new QTableWidgetItem(query.value("DERNIEREN").toString()));
            ui->tableWidgetfour->setItem(row, 4, new QTableWidgetItem(query.value("ETATAPPAREIL").toString()));

            row++;
        }
    }
}

bool appareils::supprimer(QString id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM APPAREILS WHERE REFERENCE = :id");
    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "Erreur suppression appareil:" << query.lastError().text();
        return false;
    }
    return true;
}

bool appareils::modifier()
{
    // === Validation des champs ===
    QRegularExpression lettersOnly("^[A-Za-z]+$"); // Seulement lettres A-Z ou a-z

    // Vérifier la référence
    if (reference.length() != 8) {
        qDebug() << "❌ Erreur: la référence doit contenir exactement 8 caractères.";
        return false;
    }

    // Vérifier la marque
    if (!lettersOnly.match(marque).hasMatch() || marque.length() != 7) {
        qDebug() << "❌ Erreur: la marque doit contenir exactement 7 lettres.";
        return false;
    }

    // Vérifier l'état de l'appareil
    if (!lettersOnly.match(etatappareil).hasMatch()) {
        qDebug() << "❌ Erreur: l'état de l'appareil doit contenir uniquement des lettres.";
        return false;
    }

    // === Exécution de la requête SQL ===
    QSqlQuery query;
    query.prepare("UPDATE APPAREILS SET MARQUE=:marque, DATEDACHAT=:datedachat, DERNIEREN=:dernierdateentretien, ETATAPPAREIL=:etatappareil "
                  "WHERE REFERENCE=:reference");

    query.bindValue(":reference", reference);
    query.bindValue(":marque", marque);
    query.bindValue(":datedachat", datedachat);
    query.bindValue(":dernierdateentretien", dernierdateentretien);
    query.bindValue(":etatappareil", etatappareil);

    bool test = query.exec();

    if (test) {
        qDebug() << "✅ Modification réussie pour l'appareil:" << reference;
    } else {
        qDebug() << "❌ Erreur de modification:" << query.lastError().text();
    }

    return test;
}
bool appareils::rechercherParReference(QTableWidget *tableWidget, const QString &reference)
{
    QSqlQuery query;

    // Put the matching reference first
    query.prepare("SELECT * FROM APPAREILS WHERE REFERENCE LIKE :reference ");
    query.bindValue(":reference", reference);

    if (!query.exec()) {
        qDebug() << "Erreur recherche :" << query.lastError().text();
        return false;
    }
    QTableWidget *table=tableWidget;
    table->setRowCount(0); // clear table
    int row = 0;

    while (query.next()) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(query.value("REFERENCE").toString()));
        table->setItem(row, 1, new QTableWidgetItem(query.value("MARQUE").toString()));
        table->setItem(row, 2, new QTableWidgetItem(query.value("DATEDACHAT").toString()));
        table->setItem(row, 3, new QTableWidgetItem(query.value("DERNIEREN").toString()));
        table->setItem(row, 4, new QTableWidgetItem(query.value("ETATAPPAREIL").toString()));
        row++;
    }

    return row > 0;
}
// === NOUVELLES MÉTHODES POUR LA GESTION DES INTERVENTIONS ===

bool appareils::ajouterIntervention(const Intervention& intervention)
{
    QSqlQuery query;
    query.prepare("INSERT INTO INTERVENTIONS (REFERENCE_APPAREIL, DATE_INTERVENTION, TYPE_PANNE, DESCRIPTION, GRAVITE, STATUT, COUT_ESTIME, TECHNICIEN, DUREE_INTERVENTION) "
                  "VALUES (:reference, :date, :type, :description, :gravite, :statut, :cout, :technicien, :duree)");

    query.bindValue(":reference", intervention.referenceAppareil);
    query.bindValue(":date", intervention.dateIntervention);
    query.bindValue(":type", intervention.typePanne);
    query.bindValue(":description", intervention.description);
    query.bindValue(":gravite", intervention.gravite);
    query.bindValue(":statut", intervention.statut);
    query.bindValue(":cout", intervention.coutEstime);
    query.bindValue(":technicien", intervention.technicien);
    query.bindValue(":duree", intervention.dureeIntervention);

    if (!query.exec()) {
        qDebug() << "❌ Erreur ajout intervention:" << query.lastError().text();
        return false;
    }

    qDebug() << "✅ Intervention ajoutée pour:" << intervention.referenceAppareil;
    return true;
}

QList<Intervention> appareils::getInterventionsParAppareil(const QString& referenceAppareil)
{
    QList<Intervention> interventions;
    QSqlQuery query;

    query.prepare("SELECT ID_INTERVENTION, REFERENCE_APPAREIL, DATE_INTERVENTION, TYPE_PANNE, DESCRIPTION, GRAVITE, STATUT, COUT_ESTIME, TECHNICIEN, DUREE_INTERVENTION "
                  "FROM INTERVENTIONS WHERE REFERENCE_APPAREIL = :reference ORDER BY DATE_INTERVENTION DESC");
    query.bindValue(":reference", referenceAppareil);

    if (query.exec()) {
        while (query.next()) {
            Intervention intervention;
            intervention.id = query.value("ID_INTERVENTION").toInt();
            intervention.referenceAppareil = query.value("REFERENCE_APPAREIL").toString();
            intervention.dateIntervention = query.value("DATE_INTERVENTION").toDate();
            intervention.typePanne = query.value("TYPE_PANNE").toString();
            intervention.description = query.value("DESCRIPTION").toString();
            intervention.gravite = query.value("GRAVITE").toString();
            intervention.statut = query.value("STATUT").toString();
            intervention.coutEstime = query.value("COUT_ESTIME").toDouble();
            intervention.technicien = query.value("TECHNICIEN").toString();
            intervention.dureeIntervention = query.value("DUREE_INTERVENTION").toInt();

            interventions.append(intervention);
        }
        qDebug() << "✅" << interventions.size() << "interventions récupérées pour" << referenceAppareil;
    } else {
        qDebug() << "❌ Erreur récupération interventions:" << query.lastError().text();
    }

    return interventions;
}

QList<QString> appareils::getTypesPanneFrequents(const QString& reference)
{
    QList<QString> types;
    QSqlQuery query;

    query.prepare("SELECT TYPE_PANNE, COUNT(*) as NB "
                  "FROM INTERVENTIONS WHERE REFERENCE_APPAREIL = :reference "
                  "GROUP BY TYPE_PANNE ORDER BY NB DESC");
    query.bindValue(":reference", reference);

    if (query.exec()) {
        while (query.next()) {
            types.append(query.value("TYPE_PANNE").toString());
        }
    }

    return types;
}

QMap<QString, int> appareils::getStatistiquesTypesPanne()
{
    QMap<QString, int> stats;
    QSqlQuery query;

    query.prepare("SELECT TYPE_PANNE, COUNT(*) as NB FROM INTERVENTIONS GROUP BY TYPE_PANNE ORDER BY NB DESC");

    if (query.exec()) {
        while (query.next()) {
            stats[query.value("TYPE_PANNE").toString()] = query.value("NB").toInt();
        }
    }

    return stats;
}

bool appareils::supprimerIntervention(int idIntervention)
{
    QSqlQuery query;
    query.prepare("DELETE FROM INTERVENTIONS WHERE ID_INTERVENTION = :id");
    query.bindValue(":id", idIntervention);

    if (query.exec()) {
        qDebug() << "✅ Intervention supprimée, ID:" << idIntervention;
        return true;
    } else {
        qDebug() << "❌ Erreur suppression intervention:" << query.lastError().text();
        return false;
    }
}

QStringList appareils::getTypesPannePredefinis()
{
    return QStringList{
        "Écran cassé",
        "Batterie défectueuse",
        "Problème de charge",
        "Logiciel corrompu",
        "Connecteur USB",
        "Haut-parleur",
        "Microphone",
        "Boutons physiques",
        "Surchauffe",
        "Eau/liquide",
        "Carte mère",
        "Connectivité Wi-Fi",
        "Bluetooth",
        "Caméra",
        "Capteur empreinte",
        "Vibrateur",
        "Carte SIM",
        "Mémoire pleine",
        "Système d'exploitation"
    };
}
