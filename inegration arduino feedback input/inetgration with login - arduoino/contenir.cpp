#include "contenir.h"
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QApplication>
#include <QRandomGenerator>
#include <QCloseEvent>
#include <QDateTime>

// Initialize static member
QMap<int, StagedVente> Contenir::stagedVentes;

bool checkAndRestoreConnection() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open, attempting to reopen...";
        if (!db.open()) {
            qDebug() << "Failed to reopen database:" << db.lastError().text();
            return false;
        }
        return true;
    }

    QSqlQuery testQuery("SELECT 1 FROM DUAL");
    if (!testQuery.exec()) {
        qDebug() << "Connection test failed, reopening...";
        db.close();
        if (!db.open()) {
            qDebug() << "Failed to reopen database after test:" << db.lastError().text();
            return false;
        }
    }
    return true;
}

Contenir::Contenir(int idVente, QWidget *parent)
    : QDialog(parent), currentIdVente(idVente)
{
    setWindowTitle("Ajouter des produits - Vente #" + QString::number(idVente));
    resize(500, 400);

    int retryCount = 0;
    while (retryCount < 3) {
        loadProduits();
        if (!produitsList.isEmpty()) break;
        retryCount++;
        if (retryCount < 3) {
            QMessageBox::StandardButton retry = QMessageBox::question(
                this, "Retry Connection",
                "Failed to load products. Would you like to retry?",
                QMessageBox::Yes | QMessageBox::No
                );
            if (retry == QMessageBox::No) break;
        }
    }

    if (produitsList.isEmpty()) {
        useDemoData();
        QMessageBox::information(this, "Demo Mode",
                                 "Running in demo mode with sample data.");
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    listWidget = new QListWidget(this);
    mainLayout->addWidget(listWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    btnAdd = new QPushButton("+");
    btnAdd->setAutoDefault(false);  // Prevent closing dialog
    btnAdd->setDefault(false);      // Prevent closing dialog

    btnRemove = new QPushButton("-");
    btnRemove->setAutoDefault(false);
    btnRemove->setDefault(false);

    btnRefresh = new QPushButton("Refresh");
    btnRefresh->setAutoDefault(false);
    btnRefresh->setDefault(false);

    btnValider = new QPushButton("Valider la Vente");
    btnValider->setAutoDefault(false);
    btnValider->setDefault(false);

    btnClose = new QPushButton("Close");
    btnClose->setAutoDefault(false);
    btnClose->setDefault(false);

    buttonsLayout->addWidget(btnAdd);
    buttonsLayout->addWidget(btnRemove);
    buttonsLayout->addWidget(btnRefresh);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(btnValider);
    buttonsLayout->addWidget(btnClose);

    mainLayout->addLayout(buttonsLayout);

    connect(btnAdd, &QPushButton::clicked, this, &Contenir::addRow);
    connect(btnRemove, &QPushButton::clicked, this, &Contenir::removeSelectedRow);
    connect(btnRefresh, &QPushButton::clicked, this, &Contenir::loadProduits);
    connect(btnValider, &QPushButton::clicked, this, &Contenir::validerVente);
    connect(btnClose, &QPushButton::clicked, this, &QDialog::close);

    loadExistingVente(idVente);

    if (listWidget->count() == 0)
        addRow();

}

// ==================== VENTE STAGING ====================


// In Contenir.cpp, modify the validerVente() function:
bool Contenir::validerVente()
{
    if (hasInvalidReferences()) {
        checkAllReferences();
        return false;
    }

    QList<QPair<QString, int>> items = getItems();
    if (items.isEmpty()) {
        QMessageBox::information(this, "Aucun produit",
                                 "Veuillez ajouter au moins un produit valide.");
        return false;
    }

    // Calculate total amount based on product prices
    double montantTotal = 0.0;
    QStringList details;

    for (const auto &item : items) {
        QString refProduit = item.first;
        int quantite = item.second;

        // Get product price from database
        double prixUnitaire = getProductPrice(refProduit);
        double sousTotal = prixUnitaire * quantite;
        montantTotal += sousTotal;

        details << QString("%1 x %2 = %3 DT")
                       .arg(refProduit)
                       .arg(quantite)
                       .arg(sousTotal, 0, 'f', 3);
    }

    // Apply TVA and discount (you might want to get these from vente class)
    // For now, just show the subtotal

    QMessageBox::StandardButton confirm = QMessageBox::question(
        this, "Staging Vente",
        QString("Êtes-vous sûr de vouloir stage cette vente #%1 ?\n\n"
                "Produits (%2):\n%3\n\n"
                "Montant total: %4 DT")
            .arg(currentIdVente)
            .arg(items.count())
            .arg(details.join("\n"))
            .arg(montantTotal, 0, 'f', 3),
        QMessageBox::Yes | QMessageBox::No
        );

    if (confirm != QMessageBox::Yes) {
        return false;
    }

    // Check if this vente is already staged
    if (hasStagedVente(currentIdVente)) {
        QMessageBox::StandardButton overwrite = QMessageBox::question(
            this, "Vente Already Staged",
            QString("Vente #%1 est déjà staged.\nVoulez-vous l'écraser?")
                .arg(currentIdVente),
            QMessageBox::Yes | QMessageBox::No
            );

        if (overwrite != QMessageBox::Yes) {
            return false;
        }
    }

    // Create staged vente
    StagedVente stagedVente;
    stagedVente.idVente = currentIdVente;
    stagedVente.timestamp = QDateTime::currentDateTime();
    stagedVente.montantTotal = montantTotal; // Store the calculated total

    // Convert QList to QVector
    for (const auto &item : items) {
        stagedVente.items.append(item);
    }

    // Save to memory
    stagedVentes[currentIdVente] = stagedVente;

    qDebug() << "Vente #" << currentIdVente << "staged with"
             << stagedVente.items.count() << "items, total:" << montantTotal << "DT";

    // Emit signal with calculated total
    emit montantTotalCalcule(montantTotal);
    emit venteStaged(currentIdVente);

    QMessageBox::information(this, "Vente Staged",
                             QString("Vente #%1 a été staged en mémoire.\n"
                                     "%2 produit(s) - Total: %3 DT")
                                 .arg(currentIdVente)
                                 .arg(stagedVente.items.count())
                                 .arg(montantTotal, 0, 'f', 3));

    accept();
    return true;
}

// Add this helper function to get product price
double Contenir::getProductPrice(const QString &reference)
{
    if (!checkAndRestoreConnection()) {
        return 0.0;
    }

    QSqlQuery query;
    query.prepare("SELECT PRIX FROM PRODUITS WHERE REFERENCE = :reference");
    query.bindValue(":reference", reference);

    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }

    return 0.0;
}

QList<QPair<QString, int>> Contenir::getItems() const
{
    QList<QPair<QString, int>> items;

    for (int i = 0; i < listWidget->count(); ++i) {
        QListWidgetItem *item = listWidget->item(i);
        QWidget *rowWidget = listWidget->itemWidget(item);
        if (!rowWidget) continue;

        QComboBox *comboRef = rowWidget->findChild<QComboBox*>();
        QSpinBox *spinQuantite = rowWidget->findChild<QSpinBox*>();

        if (!comboRef || !spinQuantite) continue;

        QString refProduit = comboRef->currentText().trimmed();
        int quantite = spinQuantite->value();

        if (!refProduit.isEmpty() && refProduit != "RefProduit") {
            items.append(qMakePair(refProduit, quantite));
        }
    }

    return items;
}

// ==================== STAGED VENTES MANAGEMENT ====================
bool Contenir::commitVenteToDatabase(int idVente)
{
    if (!stagedVentes.contains(idVente)) {
        qDebug() << "No staged vente found with ID:" << idVente;
        return false;
    }

    StagedVente stagedVente = stagedVentes.value(idVente);

    if (!checkAndRestoreConnection()) {
        QMessageBox::critical(nullptr, "Database Error",
                              "Cannot establish database connection.");
        return false;
    }

    qDebug() << "Starting to commit vente #" << idVente
             << "with" << stagedVente.items.count() << "items";

    QSqlDatabase::database().transaction();

    bool allSuccess = true;
    QString errorMessage;
    int itemCount = 0;
    double montantTotal = 0.0;  // Variable to accumulate total

    for (const auto &item : stagedVente.items) {
        QString refProduit = item.first;
        int quantite = item.second;

        qDebug() << "Processing:" << refProduit << "x" << quantite;

        // Check if product exists in PRODUITS table and get its price
        QSqlQuery checkProdQuery;
        checkProdQuery.prepare("SELECT COUNT(*), PRIX, QUANTITE FROM PRODUITS WHERE REFERENCE = :reference");
        checkProdQuery.bindValue(":reference", refProduit);

        if (!checkProdQuery.exec()) {
            errorMessage = "Database error checking product: " + checkProdQuery.lastError().text();
            qDebug() << errorMessage;
            allSuccess = false;
            break;
        }

        if (!checkProdQuery.next()) {
            errorMessage = QString("Product '%1' does not exist in PRODUITS table").arg(refProduit);
            qDebug() << errorMessage;
            allSuccess = false;
            break;
        }

        int exists = checkProdQuery.value(0).toInt();
        double prixUnitaire = checkProdQuery.value(1).toDouble();
        int stock = checkProdQuery.value(2).toInt();

        if (exists == 0) {
            errorMessage = QString("Product '%1' does not exist in PRODUITS table").arg(refProduit);
            qDebug() << errorMessage;
            allSuccess = false;
            break;
        }

        // Calculate subtotal for this product
        double sousTotal = prixUnitaire * quantite;
        montantTotal += sousTotal;

        qDebug() << "Product price:" << prixUnitaire << ", Subtotal:" << sousTotal << ", Running total:" << montantTotal;

        // Check stock
        if (quantite > stock) {
            errorMessage = QString("Insufficient stock for %1. Requested: %2, Available: %3")
            .arg(refProduit).arg(quantite).arg(stock);
            qDebug() << errorMessage;
            allSuccess = false;
            break;
        }

        // Get next ID for CONTENIR table
        int nextId = getNextId();
        if (nextId == -1) {
            errorMessage = "Failed to generate unique ID for CONTENIR table";
            qDebug() << errorMessage;
            allSuccess = false;
            break;
        }

        qDebug() << "Generated ID for CONTENIR:" << nextId;

        // Insert into CONTENIR table (without price)
        QSqlQuery query;
        query.prepare("INSERT INTO CONTENIR (ID, IDVENTE, REFPRODUIT, QUANTITE) "
                      "VALUES (:id, :idVente, :refProduit, :quantite)");

        query.bindValue(":id", nextId);
        query.bindValue(":idVente", idVente);
        query.bindValue(":refProduit", refProduit);
        query.bindValue(":quantite", quantite);

        if (!query.exec()) {
            errorMessage = QString("Error inserting into CONTENIR for %1 (ID=%2): %3")
            .arg(refProduit).arg(nextId).arg(query.lastError().text());
            qDebug() << errorMessage;
            allSuccess = false;
            break;
        }

        // Update stock in PRODUITS table
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE PRODUITS SET QUANTITE = QUANTITE - :quantite "
                            "WHERE REFERENCE = :reference");
        updateQuery.bindValue(":quantite", quantite);
        updateQuery.bindValue(":reference", refProduit);

        if (!updateQuery.exec()) {
            errorMessage = QString("Error updating stock for %1: %2")
            .arg(refProduit).arg(updateQuery.lastError().text());
            qDebug() << errorMessage;
            allSuccess = false;
            break;
        }

        itemCount++;
        qDebug() << "Successfully processed" << refProduit;
    }

    if (allSuccess) {
        // Get TVA rate and discount from VENTES table
        double tauxTVA = 0.0;
        double remise = 0.0;
        double montantFinal = montantTotal;

        QSqlQuery getVenteInfo;
        getVenteInfo.prepare("SELECT TAUXTVA, REMISE FROM VENTES WHERE IDVENTE = :idVente");
        getVenteInfo.bindValue(":idVente", idVente);

        if (getVenteInfo.exec() && getVenteInfo.next()) {
            tauxTVA = getVenteInfo.value(0).toDouble();
            remise = getVenteInfo.value(1).toDouble();

            // Calculate final amount with discount and TVA
            if (remise > 0) {
                montantFinal = montantTotal * (1 - remise / 100.0);
            }
            if (tauxTVA > 0) {
                montantFinal = montantFinal * (1 + tauxTVA / 100.0);
            }

            qDebug() << "Applying discount:" << remise << "% and TVA:" << tauxTVA << "%";
            qDebug() << "Original total:" << montantTotal << ", Final amount:" << montantFinal;
        } else {
            qDebug() << "Could not get TVA/remise info, using base total";
        }

        // Update the total amount in VENTES table
        QSqlQuery updateVenteQuery;
        updateVenteQuery.prepare("UPDATE VENTES SET MONTANTTOTAL = :montantTotal WHERE IDVENTE = :idVente");
        updateVenteQuery.bindValue(":montantTotal", montantFinal);
        updateVenteQuery.bindValue(":idVente", idVente);

        if (!updateVenteQuery.exec()) {
            errorMessage = "Error updating total in VENTES table: " + updateVenteQuery.lastError().text();
            qDebug() << errorMessage;
            QSqlDatabase::database().rollback();
            return false;
        }

        QSqlDatabase::database().commit();
        qDebug() << "✅ Successfully committed vente #" << idVente
                 << "with" << itemCount << "items to CONTENIR table";
        qDebug() << "💰 Total amount calculated:" << montantFinal << "DT";

        // Update the staged vente with final calculated amount
        stagedVente.montantTotal = montantFinal;
        stagedVentes[idVente] = stagedVente;

        return true;
    } else {
        QSqlDatabase::database().rollback();
        qDebug() << "❌ Failed to commit vente #" << idVente
                 << "- rolled back. Error:" << errorMessage;

        if (!errorMessage.isEmpty()) {
            QMessageBox::critical(nullptr, "Commit Error",
                                  QString("Failed to commit products to database:\n\n%1")
                                      .arg(errorMessage));
        }
        return false;
    }
}
int Contenir::getNextId()
{
    if (!checkAndRestoreConnection()) {
        QMessageBox::critical(nullptr, "Database Error",
                              "Cannot establish database connection.");
        return -1;
    }

    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database();

    // Use a more robust approach for getting next ID
    QString databaseType = db.driverName();

    if (databaseType.contains("QSQLITE", Qt::CaseInsensitive)) {
        // SQLite specific
        if (!query.exec("SELECT MAX(ID) FROM CONTENIR")) {
            qDebug() << "Error getting max ID:" << query.lastError().text();
            return -1;
        }

        if (query.next()) {
            int maxId = query.value(0).toInt();
            return (maxId > 0) ? maxId + 1 : 1;
        }
        return 1;
    }
    else if (databaseType.contains("QMYSQL", Qt::CaseInsensitive)) {
        // MySQL specific with proper transaction
        db.transaction();

        if (!query.exec("SELECT COALESCE(MAX(ID), 0) FROM CONTENIR")) {
            qDebug() << "Error getting max ID:" << query.lastError().text();
            db.rollback();
            return -1;
        }

        int nextId = 1;
        if (query.next()) {
            nextId = query.value(0).toInt() + 1;
        }

        db.commit();
        return nextId;
    }
    else {
        // Generic approach
        if (!query.exec("SELECT COALESCE(MAX(ID), 0) FROM CONTENIR")) {
            qDebug() << "Error getting max ID:" << query.lastError().text();
            return -1;
        }

        if (query.next()) {
            int maxId = query.value(0).toInt();
            return (maxId > 0) ? maxId + 1 : 1;
        }
        return 1;
    }
}
bool Contenir::commitAndClearVente(int idVente)
{
    if (commitVenteToDatabase(idVente)) {
        removeStagedVente(idVente);
        return true;
    }
    return false;
}

bool Contenir::commitAllVentesToDatabase()
{
    bool allSuccess = true;
    QList<int> venteIds = stagedVentes.keys();

    for (int idVente : venteIds) {
        if (!commitVenteToDatabase(idVente)) {
            allSuccess = false;
        } else {
            removeStagedVente(idVente);
        }
    }

    return allSuccess;
}

bool Contenir::removeStagedVente(int idVente)
{
    if (stagedVentes.remove(idVente) > 0) {
        qDebug() << "Removed staged vente #" << idVente << "from memory";
        return true;
    }
    return false;
}

StagedVente Contenir::getStagedVente(int idVente)
{
    return stagedVentes.value(idVente);
}

QVector<StagedVente> Contenir::getAllStagedVentes()
{
    QVector<StagedVente> allVentes;

    for (const StagedVente &vente : stagedVentes) {
        allVentes.append(vente);
    }

    return allVentes;
}

QList<int> Contenir::getAllStagedVenteIds()
{
    return stagedVentes.keys();
}

int Contenir::getStagedVenteCount()
{
    return stagedVentes.count();
}

bool Contenir::hasStagedVente(int idVente)
{
    return stagedVentes.contains(idVente);
}

void Contenir::clearAllStagedVentes()
{
    stagedVentes.clear();
    qDebug() << "Cleared all staged ventes from memory";
}

// ==================== EXISTING METHODS ====================

void Contenir::useDemoData()
{
    produitsList = {
        "REF001", "REF002", "REF003", "REF004", "REF005",
        "REF006", "REF007", "REF008", "REF009", "REF010"
    };

    stockQuantities.clear();
    for (int i = 0; i < produitsList.size(); ++i) {
        stockQuantities[produitsList[i]] = QRandomGenerator::global()->bounded(1, 100);
    }

    qDebug() << "Using demo data with" << produitsList.size() << "products";
}

void Contenir::loadProduits()
{
    produitsList.clear();
    stockQuantities.clear();

    if (!checkAndRestoreConnection()) {
        QMessageBox::critical(this, "Database Error",
                              "Cannot establish database connection.\n"
                              "Please check your connection and try again.");
        useDemoData();
        return;
    }

    QSqlQuery q;

    if (!q.prepare("SELECT REFERENCE, QUANTITE FROM PRODUITS")) {
        QMessageBox::warning(this, "SQL Preparation Error",
                             "Failed to prepare query:\n" + q.lastError().text());
        useDemoData();
        return;
    }

    if (!q.exec()) {
        QSqlError error = q.lastError();
        qDebug() << "SQL Error:" << error.text();
        qDebug() << "Database Error:" << error.databaseText();
        qDebug() << "Driver Error:" << error.driverText();

        QMessageBox::warning(this, "Database Warning",
                             "Cannot load products from database:\n" + error.text() +
                                 "\nUsing demo data for testing.");
        useDemoData();
        return;
    }

    int loadedCount = 0;
    while (q.next()) {
        QString reference = q.value(0).toString().trimmed();
        int quantite = q.value(1).toInt();

        if (!reference.isEmpty()) {
            produitsList << reference;
            stockQuantities[reference] = quantite;
            loadedCount++;
        }
    }

    if (loadedCount == 0) {
        QMessageBox::information(this, "No Data",
                                 "No products found in database.\nUsing demo data.");
        useDemoData();
    } else {
        qDebug() << "Successfully loaded" << loadedCount << "products from database";
    }
}

int Contenir::getStockQuantity(const QString &reference) const
{
    if (!referenceExists(reference)) {
        return 0;
    }

    if (stockQuantities.contains(reference)) {
        return stockQuantities.value(reference);
    }

    if (checkAndRestoreConnection()) {
        QSqlQuery q;
        if (q.prepare("SELECT QUANTITE FROM PRODUITS WHERE REFERENCE = ?")) {
            q.addBindValue(reference);
            if (q.exec() && q.next()) {
                int freshQuantity = q.value(0).toInt();
                const_cast<QMap<QString, int>&>(stockQuantities)[reference] = freshQuantity;
                return freshQuantity;
            }
        }
    }

    return 0;
}

bool Contenir::referenceExists(const QString &reference) const
{
    return stockQuantities.contains(reference);
}

void Contenir::updateQuantiteMax(const QString &reference, QSpinBox *spinBox)
{
    if (reference.isEmpty() || !referenceExists(reference)) {
        spinBox->setMaximum(9999);
        spinBox->setToolTip("Select a valid product reference first");
        spinBox->setStyleSheet("QSpinBox { background-color: #FFF3CD; }");
        return;
    }

    int stock = getStockQuantity(reference);
    spinBox->setMaximum(stock);
    spinBox->setToolTip(QString("Available stock: %1").arg(stock));

    if (spinBox->value() > stock) {
        spinBox->blockSignals(true);
        spinBox->setValue(qMin(spinBox->value(), stock));
        spinBox->blockSignals(false);
    }

    if (stock == 0) {
        spinBox->setStyleSheet("QSpinBox { background-color: #F8D7DA; color: #721C24; }");
    } else if (stock < 10) {
        spinBox->setStyleSheet("QSpinBox { background-color: #FFF3CD; color: #856404; }");
    } else {
        spinBox->setStyleSheet("");
    }
}

void Contenir::addRow()
{
    // Main container widget for the row
    QWidget *rowWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(rowWidget);
    layout->setContentsMargins(5, 0, 5, 0);
    layout->setSpacing(10);

    // ───────────────────────────────────────────────
    // 1) COMBOBOX – Product Reference (editable + search)
    // ───────────────────────────────────────────────
    QComboBox *comboRef = new QComboBox(this);
    comboRef->setEditable(true);
    comboRef->lineEdit()->setPlaceholderText("Référence...");
    comboRef->addItems(produitsList);  // Your vector/list of references

    // Live search / autocomplete
    connect(comboRef->lineEdit(), &QLineEdit::textEdited, this, [=](const QString &text) {
        comboRef->clear();

        for (const QString &ref : produitsList) {
            if (ref.contains(text, Qt::CaseInsensitive)) {
                comboRef->addItem(ref);
            }
        }

        // Allow manual entry
        if (comboRef->count() == 0)
            comboRef->addItem(text);
    });

    layout->addWidget(comboRef, 2);

    // ───────────────────────────────────────────────
    // 2) SPINBOX – Quantity
    // ───────────────────────────────────────────────
    QSpinBox *spinQuantite = new QSpinBox(this);
    spinQuantite->setMinimum(1);
    spinQuantite->setMaximum(9999);
    spinQuantite->setValue(1);

    layout->addWidget(spinQuantite, 1);

    // Update quantity max when reference changes
    connect(comboRef, &QComboBox::currentTextChanged, this, [=]() {
        QString ref = comboRef->currentText().trimmed();
        updateQuantiteMax(ref, spinQuantite);
    });

    // Keep quantity within the updated limit
    connect(spinQuantite, qOverload<int>(&QSpinBox::valueChanged), this, [=](int) {
        QString ref = comboRef->currentText().trimmed();
        updateQuantiteMax(ref, spinQuantite);
    });

    // ───────────────────────────────────────────────
    // 3) ADD THE ROW TO QListWidget
    // ───────────────────────────────────────────────
    QListWidgetItem *item = new QListWidgetItem(listWidget);
    item->setSizeHint(QSize(0, 40));
    listWidget->addItem(item);
    listWidget->setItemWidget(item, rowWidget);
}

void Contenir::removeRowByButton()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QWidget *rowWidget = button->property("rowWidget").value<QWidget*>();
    if (!rowWidget) return;

    for (int i = 0; i < listWidget->count(); ++i) {
        QListWidgetItem *item = listWidget->item(i);
        if (listWidget->itemWidget(item) == rowWidget) {
            QMessageBox::StandardButton confirm = QMessageBox::question(
                this, "Confirm Removal",
                "Are you sure you want to remove this row?",
                QMessageBox::Yes | QMessageBox::No
                );

            if (confirm == QMessageBox::Yes) {
                delete listWidget->takeItem(i);
            }
            break;
        }
    }
}

void Contenir::validateQuantite(int newValue)
{
    QWidget *currentRow = listWidget->itemWidget(listWidget->currentItem());
    if (!currentRow) return;

    QComboBox *comboRef = currentRow->findChild<QComboBox*>();
    if (!comboRef) return;

    QString reference = comboRef->currentText().trimmed();

    if (reference.isEmpty() || reference == "RefProduit") {
        return;
    }

    if (!referenceExists(reference)) {
        return;
    }

    int stock = getStockQuantity(reference);

    if (newValue > stock) {
        QSpinBox *spinQuantite = currentRow->findChild<QSpinBox*>();
        if (spinQuantite) {
            spinQuantite->blockSignals(true);
            spinQuantite->setValue(qMin(spinQuantite->value(), stock));
            spinQuantite->blockSignals(false);
        }

        QMessageBox::warning(this, "Insufficient Stock",
                             QString("Cannot exceed available stock!\n"
                                     "Reference: %1\n"
                                     "Requested: %2\n"
                                     "Available: %3")
                                 .arg(reference)
                                 .arg(newValue)
                                 .arg(stock));
    }
}

void Contenir::removeSelectedRow()
{
    int row = listWidget->currentRow();
    if (row == -1) {
        QMessageBox::information(this, "No Selection", "Please select a row to remove.");
        return;
    }

    QMessageBox::StandardButton confirm = QMessageBox::question(
        this, "Confirm Removal",
        "Are you sure you want to remove this row?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (confirm == QMessageBox::Yes) {
        delete listWidget->takeItem(row);
    }
}

bool Contenir::hasInvalidReferences() const
{
    for (int i = 0; i < listWidget->count(); ++i) {
        QListWidgetItem *item = listWidget->item(i);
        QWidget *rowWidget = listWidget->itemWidget(item);
        if (!rowWidget) continue;

        QComboBox *comboRef = rowWidget->findChild<QComboBox*>();
        if (!comboRef) continue;

        QString reference = comboRef->currentText().trimmed();

        if (!reference.isEmpty() &&
            reference != "RefProduit" &&
            !referenceExists(reference)) {
            return true;
        }
    }
    return false;
}

void Contenir::checkAllReferences()
{
    QStringList invalidReferences;

    for (int i = 0; i < listWidget->count(); ++i) {
        QListWidgetItem *item = listWidget->item(i);
        QWidget *rowWidget = listWidget->itemWidget(item);
        if (!rowWidget) continue;

        QComboBox *comboRef = rowWidget->findChild<QComboBox*>();
        if (!comboRef) continue;

        QString reference = comboRef->currentText().trimmed();

        if (!reference.isEmpty() &&
            reference != "RefProduit" &&
            !referenceExists(reference)) {
            invalidReferences << reference;
        }
    }

    if (!invalidReferences.isEmpty()) {
        QMessageBox::warning(this, "Invalid References",
                             QString("The following references do not exist:\n%1\n\n"
                                     "Please select valid references from the list.")
                                 .arg(invalidReferences.join("\n")));
    }
}

void Contenir::closeEvent(QCloseEvent *event)
{
    if (hasInvalidReferences()) {
        checkAllReferences();
    }
    event->accept();
}

void Contenir::loadExistingVente(int idVente)
{
    if (!checkAndRestoreConnection())
        return;

    QSqlQuery q;
    q.prepare("SELECT REFPRODUIT, QUANTITE FROM CONTENIR WHERE IDVENTE = :id");
    q.bindValue(":id", idVente);

    if (!q.exec()) {
        qDebug() << "Error loading existing vente:" << q.lastError().text();
        return;
    }

    bool hasData = false;

    while (q.next()) {
        hasData = true;
        QString ref = q.value(0).toString();
        int qty = q.value(1).toInt();

        addRowWithValues(ref, qty);  // we will create this helper
    }

    if (hasData) {
        qDebug() << "Loaded existing vente #" << idVente << " from SQL.";
    }
}
void Contenir::addRowWithValues(const QString &reference, int quantite)
{
    // Same as addRow() but fills values
    QWidget *rowWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(rowWidget);
    layout->setContentsMargins(5, 0, 5, 0);
    layout->setSpacing(10);

    QComboBox *comboRef = new QComboBox(this);
    comboRef->setEditable(true);
    comboRef->addItems(produitsList);
    comboRef->setCurrentText(reference);
    layout->addWidget(comboRef, 2);

    QSpinBox *spinQuantite = new QSpinBox(this);
    spinQuantite->setMinimum(1);
    spinQuantite->setMaximum(9999);
    spinQuantite->setValue(quantite);
    layout->addWidget(spinQuantite, 1);

    QListWidgetItem *item = new QListWidgetItem(listWidget);
    item->setSizeHint(QSize(0, 40));
    listWidget->addItem(item);
    listWidget->setItemWidget(item, rowWidget);

    updateQuantiteMax(reference, spinQuantite);
}


Contenir::~Contenir()
{
}
