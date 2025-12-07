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
    // ============================
    // 1) VALIDATION DES CHAMPS
    // ============================

    QRegularExpression lettersOnly("^[A-Za-z]+$");

    // Référence : exactement 8 caractères
    if (reference.length() != 8) {
        qDebug() << "❌ Erreur: la référence doit contenir exactement 8 caractères.";
        return false;
    }

    // Marque : uniquement lettres + longueur 7
    if (!lettersOnly.match(marque).hasMatch() || marque.length() != 7) {
        qDebug() << "❌ Erreur: la marque doit contenir exactement 7 lettres.";
        return false;
    }

    // État appareil : uniquement lettres
    if (!lettersOnly.match(etatappareil).hasMatch()) {
        qDebug() << "❌ Erreur: l'état de l'appareil doit contenir uniquement des lettres.";
        return false;
    }

    // ============================
    // 2) CONVERSION DES DATES
    // ============================

    // 👉 Ici je suppose date en QString "dd/MM/yyyy"
    QDate dAchat = QDate::fromString(datedachat, "dd/MM/yyyy");
    QDate dEnt = QDate::fromString(dernierdateentretien, "dd/MM/yyyy");

    if (!dAchat.isValid() || !dEnt.isValid()) {
        qDebug() << "❌ Erreur: date invalide (format attendu dd/MM/yyyy). "
                 << "Reçues: achat=" << datedachat << " entretien=" << dernierdateentretien;
        return false;
    }

    // Oracle reçoit le type DATE via QVariant (pas besoin de TO_DATE)
    QVariant vAchat = dAchat;
    QVariant vEnt = dEnt;

    // ============================
    // 3) REQUETE SQL (POUR ORACLE)
    // ============================

    QSqlQuery query;
    query.prepare(
        "INSERT INTO APPAREILS "
        "(REFERENCE, MARQUE, DATEACHAT, DERNIEREN, ETATAPPAREIL) "
        "VALUES (:reference, :marque, :dateAchat, :dateEntretien, :etat)"
        );

    query.bindValue(":reference", reference);
    query.bindValue(":marque", marque);
    query.bindValue(":dateAchat", vAchat);               // ⭐ Oracle accepte QVariant(QDate)
    query.bindValue(":dateEntretien", vEnt);             // ⭐ Pas besoin de TO_DATE()
    query.bindValue(":etat", etatappareil);

    // ============================
    // 4) EXECUTION
    // ============================

    if (!query.exec()) {
        qDebug() << "❌ Erreur SQL:" << query.lastError().text();
        return false;
    }

    qDebug() << "✅ Ajout réussi pour l'appareil:" << reference;
    return true;
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
            ui->tableWidgetfour->setItem(row, 2, new QTableWidgetItem(query.value("DATEACHAT").toString()));
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
    query.prepare("UPDATE APPAREILS SET MARQUE=:marque, DATEACHAT=:datedachat, DERNIEREN=:dernierdateentretien, ETATAPPAREIL=:etatappareil "
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
        table->setItem(row, 2, new QTableWidgetItem(query.value("DATEACHAT").toString()));
        table->setItem(row, 3, new QTableWidgetItem(query.value("DERNIEREN").toString()));
        table->setItem(row, 4, new QTableWidgetItem(query.value("ETATAPPAREIL").toString()));
        row++;
    }

    return row > 0;
}
