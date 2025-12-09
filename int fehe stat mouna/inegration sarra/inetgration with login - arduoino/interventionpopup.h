#ifndef INTERVENTIONPOPUP_H
#define INTERVENTIONPOPUP_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QHeaderView>

class InterventionPopup : public QDialog
{
    Q_OBJECT

public:
    explicit InterventionPopup(const QString &refProduit, QWidget *parent = nullptr);

private:
    QTableWidget *table;
    void loadTypePannes(const QString &refProduit);
};

#endif // INTERVENTIONPOPUP_H
