#include "interventionpopup.h"

InterventionPopup::InterventionPopup(const QString &refProduit, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Historique des pannes");
    resize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Pannes du produit : " + refProduit);
    title->setStyleSheet("font-size: 14px; font-weight: bold; margin-bottom: 10px;");
    layout->addWidget(title);

    table = new QTableWidget(this);
    table->setColumnCount(1);
    table->setHorizontalHeaderLabels({"Type de Panne"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    layout->addWidget(table);

    loadTypePannes(refProduit);
}

void InterventionPopup::loadTypePannes(const QString &refProduit)
{
    table->setRowCount(0);

    QSqlQuery query;
    // Use REFAPP instead of REFPRODUIT
    query.prepare("SELECT TYPEPANNE FROM INTERVENTION WHERE REFAPP = :ref");
    query.bindValue(":ref", refProduit);

    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next()) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(query.value("TYPEPANNE").toString()));
        row++;
    }

    if (row == 0)
        qDebug() << "Aucune panne trouvée pour" << refProduit;
}
