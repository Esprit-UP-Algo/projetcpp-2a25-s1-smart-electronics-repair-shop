#include "appareils.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>

appareils::appareils(Ui::MainWindow *ui) {
    this->reference=ui->lineEdit_28->text();
    this->marque=ui->lineEdit_29->text();
    this->datedachat=ui->dateEdit_5->text();
    this->dernierdateentretien=ui->dateEdit_6->text();
    this->etatappareil=ui->lineEdit_32->text();
}

bool appareils::existe(QString ref)
{
    QSqlQuery query;
    query.prepare("SELECT REFERENCE FROM APPAREILS WHERE REFERENCE = :ref");
    query.bindValue(":ref", ref);

    if (!query.exec()) {
        qDebug() << "❌ Erreur lors de la vérification d'existence:" << query.lastError().text();
        return false;
    }

    return query.next(); // Returns true if reference exists
}

bool appareils::ajouter()
{
    // ============================
    // 1) VALIDATION DES CHAMPS
    // ============================

    QRegularExpression lettersOnly("^[A-Za-z]+$");

    // Référence : exactement 8 caractères
    if (reference.trimmed().isEmpty()) {
        qDebug() << "❌ Erreur: la référence ne peut pas être vide.";
        QMessageBox::warning(nullptr, "Erreur", "La référence ne peut pas être vide.");
        return false;
    }

    if (reference.length() != 8) {
        qDebug() << "❌ Erreur: la référence doit contenir exactement 8 caractères.";
        QMessageBox::warning(nullptr, "Erreur", "La référence doit contenir exactement 8 caractères.");
        return false;
    }

    // ✅ CHECK IF REFERENCE ALREADY EXISTS
    if (existe(reference)) {
        qDebug() << "❌ Erreur: cette référence existe déjà dans la base de données.";
        QMessageBox::warning(nullptr, "Erreur", "Cette référence existe déjà. Veuillez utiliser une référence unique.");
        return false;
    }

    // Marque : uniquement lettres + longueur 7
    if (marque.trimmed().isEmpty()) {
        qDebug() << "❌ Erreur: la marque ne peut pas être vide.";
        QMessageBox::warning(nullptr, "Erreur", "La marque ne peut pas être vide.");
        return false;
    }

    if (!lettersOnly.match(marque).hasMatch() || marque.length() != 7) {
        qDebug() << "❌ Erreur: la marque doit contenir exactement 7 lettres.";
        QMessageBox::warning(nullptr, "Erreur", "La marque doit contenir exactement 7 lettres (uniquement des lettres).");
        return false;
    }

    // État appareil : uniquement lettres
    if (etatappareil.trimmed().isEmpty()) {
        qDebug() << "❌ Erreur: l'état de l'appareil ne peut pas être vide.";
        QMessageBox::warning(nullptr, "Erreur", "L'état de l'appareil ne peut pas être vide.");
        return false;
    }

    if (!lettersOnly.match(etatappareil).hasMatch()) {
        qDebug() << "❌ Erreur: l'état de l'appareil doit contenir uniquement des lettres.";
        QMessageBox::warning(nullptr, "Erreur", "L'état de l'appareil doit contenir uniquement des lettres.");
        return false;
    }

    // ============================
    // 2) CONVERSION DES DATES
    // ============================

    // Try multiple date formats
    QDate dAchat = QDate::fromString(datedachat, "dd/MM/yyyy");
    if (!dAchat.isValid()) {
        dAchat = QDate::fromString(datedachat, "yyyy-MM-dd");
    }
    if (!dAchat.isValid()) {
        dAchat = QDate::fromString(datedachat, "M/d/yyyy");
    }

    QDate dEnt = QDate::fromString(dernierdateentretien, "dd/MM/yyyy");
    if (!dEnt.isValid()) {
        dEnt = QDate::fromString(dernierdateentretien, "yyyy-MM-dd");
    }
    if (!dEnt.isValid()) {
        dEnt = QDate::fromString(dernierdateentretien, "M/d/yyyy");
    }

    if (!dAchat.isValid() || !dEnt.isValid()) {
        qDebug() << "❌ Erreur: date invalide. "
                 << "Reçues: achat=" << datedachat << " entretien=" << dernierdateentretien;
        QMessageBox::warning(nullptr, "Erreur", "Format de date invalide. Veuillez vérifier les dates.");
        return false;
    }

    // Validate that purchase date is before maintenance date
    if (dAchat > dEnt) {
        qDebug() << "❌ Erreur: la date d'achat ne peut pas être après la date d'entretien.";
        QMessageBox::warning(nullptr, "Erreur", "La date d'achat ne peut pas être après la date d'entretien.");
        return false;
    }

    QVariant vAchat = dAchat;
    QVariant vEnt = dEnt;

    // ============================
    // 3) REQUETE SQL (POUR ORACLE)
    // ============================

    QSqlQuery query;
    // ⭐ FIXED: Use DATEDACHAT instead of DATEACHAT
    query.prepare(
        "INSERT INTO APPAREILS "
        "(REFERENCE, MARQUE, DATEDACHAT, DERNIEREN, ETATAPPAREIL) "
        "VALUES (:reference, :marque, :dateAchat, :dateEntretien, :etat)"
        );

    query.bindValue(":reference", reference);
    query.bindValue(":marque", marque);
    query.bindValue(":dateAchat", vAchat);
    query.bindValue(":dateEntretien", vEnt);
    query.bindValue(":etat", etatappareil);

    // ============================
    // 4) EXECUTION
    // ============================

    if (!query.exec()) {
        qDebug() << "❌ Erreur SQL:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL", "Impossible d'ajouter l'appareil: " + query.lastError().text());
        return false;
    }

    qDebug() << "✅ Ajout réussi pour l'appareil:" << reference;
    QMessageBox::information(nullptr, "Succès", "Appareil ajouté avec succès!");
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
            // ⭐ FIXED: Use DATEDACHAT instead of DATEACHAT
            ui->tableWidgetfour->setItem(row, 2, new QTableWidgetItem(query.value("DATEDACHAT").toString()));
            ui->tableWidgetfour->setItem(row, 3, new QTableWidgetItem(query.value("DERNIEREN").toString()));
            ui->tableWidgetfour->setItem(row, 4, new QTableWidgetItem(query.value("ETATAPPAREIL").toString()));

            row++;
        }
    }
    else
    {
        qDebug() << "❌ Erreur lors de l'affichage:" << query.lastError().text();
    }
}

bool appareils::supprimer(QString id)
{
    if (id.trimmed().isEmpty()) {
        qDebug() << "❌ Erreur: référence vide pour la suppression.";
        QMessageBox::warning(nullptr, "Erreur", "Veuillez sélectionner un appareil à supprimer.");
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM APPAREILS WHERE REFERENCE = :id");
    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << "❌ Erreur suppression appareil:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur", "Impossible de supprimer l'appareil: " + query.lastError().text());
        return false;
    }

    if (query.numRowsAffected() == 0) {
        qDebug() << "⚠️ Aucun appareil trouvé avec cette référence.";
        QMessageBox::warning(nullptr, "Avertissement", "Aucun appareil trouvé avec cette référence.");
        return false;
    }

    qDebug() << "✅ Suppression réussie pour l'appareil:" << id;
    QMessageBox::information(nullptr, "Succès", "Appareil supprimé avec succès!");
    return true;
}

bool appareils::modifier()
{
    // ============================
    // 1) VALIDATION DES CHAMPS
    // ============================

    QRegularExpression lettersOnly("^[A-Za-z]+$");

    // Vérifier la référence
    if (reference.trimmed().isEmpty()) {
        qDebug() << "❌ Erreur: la référence ne peut pas être vide.";
        QMessageBox::warning(nullptr, "Erreur", "La référence ne peut pas être vide.");
        return false;
    }

    if (reference.length() != 8) {
        qDebug() << "❌ Erreur: la référence doit contenir exactement 8 caractères.";
        QMessageBox::warning(nullptr, "Erreur", "La référence doit contenir exactement 8 caractères.");
        return false;
    }

    // Vérifier la marque
    if (marque.trimmed().isEmpty()) {
        qDebug() << "❌ Erreur: la marque ne peut pas être vide.";
        QMessageBox::warning(nullptr, "Erreur", "La marque ne peut pas être vide.");
        return false;
    }

    if (!lettersOnly.match(marque).hasMatch() || marque.length() != 7) {
        qDebug() << "❌ Erreur: la marque doit contenir exactement 7 lettres.";
        QMessageBox::warning(nullptr, "Erreur", "La marque doit contenir exactement 7 lettres (uniquement des lettres).");
        return false;
    }

    // Vérifier l'état de l'appareil
    if (etatappareil.trimmed().isEmpty()) {
        qDebug() << "❌ Erreur: l'état de l'appareil ne peut pas être vide.";
        QMessageBox::warning(nullptr, "Erreur", "L'état de l'appareil ne peut pas être vide.");
        return false;
    }

    if (!lettersOnly.match(etatappareil).hasMatch()) {
        qDebug() << "❌ Erreur: l'état de l'appareil doit contenir uniquement des lettres.";
        QMessageBox::warning(nullptr, "Erreur", "L'état de l'appareil doit contenir uniquement des lettres.");
        return false;
    }

    // ============================
    // 2) CONVERSION DES DATES
    // ============================

    // Try multiple date formats
    QDate dAchat = QDate::fromString(datedachat, "dd/MM/yyyy");
    if (!dAchat.isValid()) {
        dAchat = QDate::fromString(datedachat, "yyyy-MM-dd");
    }
    if (!dAchat.isValid()) {
        dAchat = QDate::fromString(datedachat, "M/d/yyyy");
    }

    QDate dEnt = QDate::fromString(dernierdateentretien, "dd/MM/yyyy");
    if (!dEnt.isValid()) {
        dEnt = QDate::fromString(dernierdateentretien, "yyyy-MM-dd");
    }
    if (!dEnt.isValid()) {
        dEnt = QDate::fromString(dernierdateentretien, "M/d/yyyy");
    }

    if (!dAchat.isValid() || !dEnt.isValid()) {
        qDebug() << "❌ Erreur: date invalide. "
                 << "Reçues: achat=" << datedachat << " entretien=" << dernierdateentretien;
        QMessageBox::warning(nullptr, "Erreur", "Format de date invalide. Veuillez vérifier les dates.");
        return false;
    }

    // Validate that purchase date is before maintenance date
    if (dAchat > dEnt) {
        qDebug() << "❌ Erreur: la date d'achat ne peut pas être après la date d'entretien.";
        QMessageBox::warning(nullptr, "Erreur", "La date d'achat ne peut pas être après la date d'entretien.");
        return false;
    }

    QVariant vAchat = dAchat;
    QVariant vEnt = dEnt;

    // ============================
    // 3) EXECUTION DE LA REQUETE SQL
    // ============================

    QSqlQuery query;
    // ⭐ FIXED: Use DATEDACHAT and proper date binding
    query.prepare("UPDATE APPAREILS SET MARQUE=:marque, DATEDACHAT=:datedachat, "
                  "DERNIEREN=:dernierdateentretien, ETATAPPAREIL=:etatappareil "
                  "WHERE REFERENCE=:reference");

    query.bindValue(":reference", reference);
    query.bindValue(":marque", marque);
    query.bindValue(":datedachat", vAchat);              // ⭐ Use QVariant(QDate)
    query.bindValue(":dernierdateentretien", vEnt);      // ⭐ Use QVariant(QDate)
    query.bindValue(":etatappareil", etatappareil);

    if (!query.exec()) {
        qDebug() << "❌ Erreur de modification:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL", "Impossible de modifier l'appareil: " + query.lastError().text());
        return false;
    }

    if (query.numRowsAffected() == 0) {
        qDebug() << "⚠️ Aucun appareil trouvé avec cette référence.";
        QMessageBox::warning(nullptr, "Avertissement", "Aucun appareil trouvé avec cette référence.");
        return false;
    }

    qDebug() << "✅ Modification réussie pour l'appareil:" << reference;
    QMessageBox::information(nullptr, "Succès", "Appareil modifié avec succès!");
    return true;
}

bool appareils::rechercherParReference(QTableWidget *tableWidget, const QString &reference)
{
    if (tableWidget == nullptr) {
        qDebug() << "❌ Erreur: tableWidget est null.";
        return false;
    }

    QSqlQuery query;

    // First try exact match, then partial match
    QString searchRef = reference.trimmed().toUpper();
    
    // Try exact match first
    query.prepare("SELECT * FROM APPAREILS WHERE UPPER(REFERENCE) = :reference");
    query.bindValue(":reference", searchRef);

    if (!query.exec()) {
        qDebug() << "❌ Erreur recherche exacte:" << query.lastError().text();
        // Fall through to partial match
    }

    int row = 0;
    tableWidget->setRowCount(0); // clear table

    // If exact match found, use it
    if (query.next()) {
        do {
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("REFERENCE").toString()));
            tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("MARQUE").toString()));
            tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("DATEDACHAT").toString()));
            tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("DERNIEREN").toString()));
            tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("ETATAPPAREIL").toString()));
            row++;
        } while (query.next());
    } else {
        // Try partial match (LIKE)
        query.prepare("SELECT * FROM APPAREILS WHERE UPPER(REFERENCE) LIKE :reference");
        query.bindValue(":reference", "%" + searchRef + "%");

        if (!query.exec()) {
            qDebug() << "❌ Erreur recherche partielle:" << query.lastError().text();
            QMessageBox::critical(nullptr, "Erreur", "Erreur lors de la recherche: " + query.lastError().text());
            return false;
        }

        while (query.next()) {
            tableWidget->insertRow(row);
            tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("REFERENCE").toString()));
            tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("MARQUE").toString()));
            tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("DATEDACHAT").toString()));
            tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("DERNIEREN").toString()));
            tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("ETATAPPAREIL").toString()));
            row++;
        }
    }

    qDebug() << "🔍 Search completed. Found" << row << "result(s) for reference:" << reference;

    if (row == 0) {
        qDebug() << "⚠️ No results found";
        // Don't show message box here, let the caller handle it
    }

    return row > 0;
}

bool appareils::changerEtat(const QString &reference, const QString &nouvelEtat)
{
    if (reference.trimmed().isEmpty()) {
        qDebug() << "❌ Erreur: référence vide pour le changement d'état.";
        return false;
    }

    if (nouvelEtat.trimmed().isEmpty()) {
        qDebug() << "❌ Erreur: nouvel état vide.";
        return false;
    }

    // Validate that the reference exists
    if (!existe(reference)) {
        qDebug() << "❌ Erreur: référence non trouvée:" << reference;
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE APPAREILS SET ETATAPPAREIL = :etat WHERE REFERENCE = :reference");
    query.bindValue(":etat", nouvelEtat);
    query.bindValue(":reference", reference);

    if (!query.exec()) {
        qDebug() << "❌ Erreur changement d'état:" << query.lastError().text();
        return false;
    }

    if (query.numRowsAffected() == 0) {
        qDebug() << "⚠️ Aucun appareil trouvé avec cette référence.";
        return false;
    }

    qDebug() << "✅ État changé avec succès pour l'appareil:" << reference << "->" << nouvelEtat;
    return true;
}
