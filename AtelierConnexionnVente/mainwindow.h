#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "produit.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_stock_2_clicked();

    void on_employe_clicked();

    void on_client_2_clicked();

    void on_fournisseur_2_clicked();

    void on_ventes_clicked();

    void on_pushButton_21_clicked();

    void on_annulerajout_6_clicked();

    void on_lineEdit_strech_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_22_clicked();
    void on_pushButton_33_clicked();
    void on_pushButton_37_clicked();
     void on_modifier_vente_clicked();
    void on_pushButton_34_clicked();
     void on_tableWidgetvente_cellClicked(int row, int column);
    void on_pushButton_35_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
