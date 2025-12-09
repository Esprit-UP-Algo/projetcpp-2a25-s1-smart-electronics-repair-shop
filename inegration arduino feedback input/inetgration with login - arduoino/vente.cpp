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
#include "contenir.h"
vente::vente()
{
    this->idvente = "";
    this->datedevente = "";

    QString tvaStr = 0;
    QString remiseStr = 0;
    QString montantStr = 0;

    // --- Contrôle : champ vide ---

    this->tauxtva = 0;

    this->montanttotal = 0;

    // --- Mode de paiement ---

    this->modedepaiment = "";


    // --- Debug facultatif ---
    qDebug() << "ID:" << idvente
             << "| TVA:" << tauxtva
             << "| Remise:" << remise
             << "| Montant:" << montanttotal
             << "| Paiement:" << modedepaiment;
}
vente::vente(Ui::MainWindow *ui)
{
    this->idvente = ui->lineEdit_45->text().trimmed();
    this->datedevente = ui->dateEdit_3->date().toString("yyyy-MM-dd")/*toString("dd-MM-yyyy")*/;

    QString tvaStr = ui->lineEdit_46->text().trimmed();
    QString remiseStr = ui->lineEdit_47->text().trimmed();
    QString montantStr = ui->lineEdit_49->text().trimmed();

    // --- Contrôle : champ vide ---
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

    // --- Mode de paiement ---
    if (ui->radioButton_5->isChecked())
        this->modedepaiment = "Espèce";
    else if (ui->radioButton_6->isChecked())
        this->modedepaiment = "Carte bancaire";
    else
        this->modedepaiment = "";

    // --- Debug facultatif ---
    qDebug() << "ID:" << idvente
             << "| TVA:" << tauxtva
             << "| Remise:" << remise
             << "| Montant:" << montanttotal
             << "| Paiement:" << modedepaiment;
}



// Ajouter sale
bool vente::ajouter()
{
    QString erreurs = "";

    // --- Vérifications des champs obligatoires ---
    if (idvente.trimmed().isEmpty())
        erreurs += "- L'ID de la vente est obligatoire.\n";

    if (modedepaiment.trimmed().isEmpty())
        erreurs += "- Le mode de paiement est obligatoire.\n";

    if (datedevente.trimmed().isEmpty())
        erreurs += "- La date de vente est obligatoire.\n";

    // --- Vérifications numériques (champ vide ou zéro) ---
    if (tauxtva <= 0)
        erreurs += "- Le taux de TVA doit être supérieur à 0.\n";

    if (tauxtva > 100)
        erreurs += "- Le taux de TVA ne peut pas dépasser 100.\n";

    if (remise < 0)
        erreurs += "- La remise ne peut pas être négative.\n";

    if (remise > 100)
        erreurs += "- La remise ne peut pas dépasser 100.\n";



    // --- Vérifier s’il y a des erreurs ---
    if (!erreurs.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreurs de saisie", erreurs);
        return false;
    }

    // --- Vérifier si l'ID existe déjà ---
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

    // --- Insertion dans la base ---
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




// Afficher sales
void vente::afficher(Ui::MainWindow *ui)
{
    QSqlQuery query;
    query.prepare("SELECT IDVENTE, TAUXTVA, REMISE, DATEDEVENTE, MONTANTTOTAL, MODEDEPAIMENT FROM VENTES");

    if (!query.exec()) {
        qDebug() << "Erreur affichage vente:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL", query.lastError().text());
        return;
    }

    ui->tableWidgetvente->setRowCount(0);
    int row = 0;

    while (query.next()) {

        ui->tableWidgetvente->insertRow(row);

        QString idVente = query.value("IDVENTE").toString();

        // ------------------ VENTES COLUMNS ------------------
        ui->tableWidgetvente->setItem(row, 0, new QTableWidgetItem(idVente));
        ui->tableWidgetvente->setItem(row, 1, new QTableWidgetItem(query.value("TAUXTVA").toString()));
        ui->tableWidgetvente->setItem(row, 2, new QTableWidgetItem(query.value("REMISE").toString()));
        ui->tableWidgetvente->setItem(row, 3, new QTableWidgetItem(query.value("DATEDEVENTE").toString()));
        ui->tableWidgetvente->setItem(row, 4, new QTableWidgetItem(query.value("MONTANTTOTAL").toString()));
        ui->tableWidgetvente->setItem(row, 5, new QTableWidgetItem(query.value("MODEDEPAIMENT").toString()));

        // ------------------ PRODUCTS FETCH ------------------
        QSqlQuery prodQuery;
        prodQuery.prepare("SELECT REFPRODUIT, QUANTITE FROM CONTENIR WHERE IDVENTE = :id");
        prodQuery.bindValue(":id", idVente);

        QString produitsText;

        if (prodQuery.exec()) {
            while (prodQuery.next()) {
                QString ref = prodQuery.value("REFPRODUIT").toString();
                int qte = prodQuery.value("QUANTITE").toInt();

                // ✓ NEW: each product on a new line for readability
                produitsText += QString("• %1  (x%2)\n").arg(ref).arg(qte);
            }

            if (produitsText.isEmpty())
                produitsText = "Aucun produit";
        }
        else {
            produitsText = "Erreur";
        }

        // ------------------ DISPLAY IN LAST COLUMN ------------------
        QTableWidgetItem *prodItem = new QTableWidgetItem(produitsText);
        prodItem->setTextAlignment(Qt::AlignLeft | Qt::AlignTop); // more readable
        ui->tableWidgetvente->setItem(row, 6, prodItem);

        row++;
    }

    qDebug() << "Ventes affichées (" << row << " lignes).";
    ui->tableWidgetvente->resizeColumnToContents(6);
    ui->tableWidgetvente->setWordWrap(true);
    ui->tableWidgetvente->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

}





bool vente::existe(QString idvente)
{
    QSqlQuery query;
    query.prepare("SELECT idvente FROM VENTES WHERE idvente = :idvente");
    query.bindValue(":idvente", idvente);

    if (query.exec() && query.next())
    {
        // Une vente avec cette idvente existe déjà
        return true;
    }
    else
    {
        // Aucune vente trouvé avec cette idvente
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

bool vente::modifier() {
    QString erreurs = "";

    // Champs obligatoires
    if (idvente.trimmed().isEmpty())
        erreurs += "- L'ID de la vente est obligatoire.\n";
    if (datedevente.trimmed().isEmpty())
        erreurs += "- La date de vente est obligatoire.\n";

    // Vérifications des champs numériques
    if (tauxtva < 0 || tauxtva > 100)
        erreurs += "- Le taux de TVA doit être entre 0 et 100.\n";
    if (remise < 0 || remise > 100)
        erreurs += "- La remise doit être entre 0 et 100.\n";

    if (modedepaiment.trimmed().isEmpty())
        erreurs += "- Le mode de paiement doit être sélectionné.\n";

    // Si erreurs → afficher message
    if (!erreurs.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreurs de saisie", erreurs);
        return false;
    }

    // Check database connection
    if (!checkAndRestoreConnection()) {
        QMessageBox::critical(nullptr, "Erreur de connexion",
                              "Impossible de se connecter à la base de données.");
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();
    db.transaction(); // Start transaction for both VENTES and CONTENIR updates

    // Vérifier si la vente existe
    QSqlQuery check;
    check.prepare("SELECT COUNT(*) FROM VENTES WHERE IDVENTE = :idvente");
    check.bindValue(":idvente", idvente);
    if (!check.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL", check.lastError().text());
        db.rollback();
        return false;
    }
    check.next();
    if (check.value(0).toInt() == 0) {
        QMessageBox::warning(nullptr, "Vente inexistante",
                             "Aucune vente trouvée avec cet ID !");
        db.rollback();
        return false;
    }

    // Récupérer les anciens produits de la vente pour ajuster les stocks
    QMap<QString, int> oldProducts;
    QSqlQuery selectOld;
    selectOld.prepare("SELECT REFPRODUIT, QUANTITE FROM CONTENIR WHERE IDVENTE = :idvente");
    selectOld.bindValue(":idvente", idvente);
    if (selectOld.exec()) {
        while (selectOld.next()) {
            QString ref = selectOld.value(0).toString();
            int qty = selectOld.value(1).toInt();
            oldProducts[ref] = qty;
        }
    }

    // Supprimer les anciennes entrées de CONTENIR
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM CONTENIR WHERE IDVENTE = :idvente");
    deleteQuery.bindValue(":idvente", idvente);
    if (!deleteQuery.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL",
                              "Erreur lors de la suppression des anciens produits: " +
                                  deleteQuery.lastError().text());
        db.rollback();
        return false;
    }

    // Restaurer les stocks des anciens produits
    for (auto it = oldProducts.begin(); it != oldProducts.end(); ++it) {
        QString ref = it.key();
        int qty = it.value();

        QSqlQuery restoreStock;
        restoreStock.prepare("UPDATE PRODUITS SET QUANTITE = QUANTITE + :qty "
                             "WHERE REFERENCE = :ref");
        restoreStock.bindValue(":qty", qty);
        restoreStock.bindValue(":ref", ref);
        if (!restoreStock.exec()) {
            QMessageBox::critical(nullptr, "Erreur SQL",
                                  "Erreur lors de la restauration du stock: " +
                                      restoreStock.lastError().text());
            db.rollback();
            return false;
        }
    }

    // UPDATE dans la table VENTES
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
        db.rollback();
        return false;
    }

    // Insérer les nouveaux produits dans CONTENIR (si disponibles)
    // Note: You need to have a way to get the new products list
    // This could be from staged ventes or from a separate parameter

    // Check if this vente is staged
    if (Contenir::hasStagedVente(idvente.toInt())) {
        StagedVente stagedVente = Contenir::getStagedVente(idvente.toInt());

        for (const auto &item : stagedVente.items) {
            QString refProduit = item.first;
            int quantite = item.second;

            // Vérifier le stock
            QSqlQuery checkStock;
            checkStock.prepare("SELECT QUANTITE FROM PRODUITS WHERE REFERENCE = :ref");
            checkStock.bindValue(":ref", refProduit);
            if (!checkStock.exec() || !checkStock.next()) {
                QMessageBox::critical(nullptr, "Erreur",
                                      "Produit non trouvé: " + refProduit);
                db.rollback();
                return false;
            }

            int stock = checkStock.value(0).toInt();
            if (quantite > stock) {
                QMessageBox::critical(nullptr, "Stock insuffisant",
                                      QString("Stock insuffisant pour %1\n"
                                              "Demandé: %2, Disponible: %3")
                                          .arg(refProduit).arg(quantite).arg(stock));
                db.rollback();
                return false;
            }

            // Insérer dans CONTENIR
            int nextId = getNextContenirId(); // You need to implement this
            QSqlQuery insertContenir;
            insertContenir.prepare("INSERT INTO CONTENIR (ID, IDVENTE, REFPRODUIT, QUANTITE) "
                                   "VALUES (:id, :idvente, :ref, :qty)");
            insertContenir.bindValue(":id", nextId);
            insertContenir.bindValue(":idvente", idvente);
            insertContenir.bindValue(":ref", refProduit);
            insertContenir.bindValue(":qty", quantite);

            if (!insertContenir.exec()) {
                QMessageBox::critical(nullptr, "Erreur SQL",
                                      "Erreur lors de l'insertion dans CONTENIR: " +
                                          insertContenir.lastError().text());
                db.rollback();
                return false;
            }

            // Mettre à jour le stock
            QSqlQuery updateStock;
            updateStock.prepare("UPDATE PRODUITS SET QUANTITE = QUANTITE - :qty "
                                "WHERE REFERENCE = :ref");
            updateStock.bindValue(":qty", quantite);
            updateStock.bindValue(":ref", refProduit);

            if (!updateStock.exec()) {
                QMessageBox::critical(nullptr, "Erreur SQL",
                                      "Erreur lors de la mise à jour du stock: " +
                                          updateStock.lastError().text());
                db.rollback();
                return false;
            }
        }

        // Remove from staged ventes after successful update
        Contenir::removeStagedVente(idvente.toInt());
    }

    // Commit transaction
    if (!db.commit()) {
        QMessageBox::critical(nullptr, "Erreur de transaction",
                              "Échec du commit de la transaction.");
        db.rollback();
        return false;
    }

    QMessageBox::information(nullptr, "Succès",
                             "La vente et les produits associés ont été modifiés avec succès !");
    return true;
}

// Helper function to get next ID for CONTENIR table
int vente::getNextContenirId() {
    QSqlQuery query;
    if (query.exec("SELECT COALESCE(MAX(ID), 0) + 1 FROM CONTENIR")) {
        if (query.next()) {
            return query.value(0).toInt();
        }
    }
    return 1; // Fallback
}
double vente::calculerMontantFinal(double montantSousTotal)
{
    // Calculate amount after discount
    double montantApresRemise = montantSousTotal;
    if (remise > 0) {
        montantApresRemise = montantSousTotal * (1 - remise / 100.0);
    }

    // Add TVA
    double montantAvecTVA = montantApresRemise * (1 + tauxtva / 100.0);

    return montantAvecTVA;
}

// Connection check function (similar to Contenir class)
bool vente::checkAndRestoreConnection() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        if (!db.open()) {
            return false;
        }
        return true;
    }

    QSqlQuery testQuery("SELECT 1 FROM DUAL");
    if (!testQuery.exec()) {
        db.close();
        if (!db.open()) {
            return false;
        }
    }
    return true;
}
bool vente::rechercherParId(QTableWidget *tableWidget, const QString &idvente)
{
    QSqlQuery query;

    // Recherche exacte
    query.prepare("SELECT * FROM VENTES WHERE IDVENTE = :idvente");
    query.bindValue(":idvente", idvente);

    if (!query.exec()) {
        qDebug() << "Erreur recherche :" << query.lastError().text();
        return false;
    }

    tableWidget->setRowCount(0);

    if (query.next()) {
        tableWidget->setRowCount(1);

        tableWidget->setItem(0, 0, new QTableWidgetItem(query.value("IDVENTE").toString()));
        tableWidget->setItem(0, 1, new QTableWidgetItem(query.value("TAUXTVA").toString()));
        tableWidget->setItem(0, 2, new QTableWidgetItem(query.value("REMISE").toString()));
        tableWidget->setItem(0, 3, new QTableWidgetItem(query.value("DATE").toString()));
        tableWidget->setItem(0, 4, new QTableWidgetItem(query.value("MONTANTTOTAL").toString()));
        tableWidget->setItem(0, 5, new QTableWidgetItem(query.value("MODEDEPAIMENT").toString()));

        qDebug() << "Vente trouvée :" << idvente;
        return true;
    }

    qDebug() << "Aucune vente trouvée avec l'ID :" << idvente;
    return false;
}








vente::~vente() {}
