#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"
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

    void on_annulerajout_client_clicked();

    void on_pushButton_ValiderClient_clicked();

    void on_pushButton_supprimer_client_clicked();
    void on_tableWidgetclient_cellClicked(int row);

    void on_pushButton_modifierClient_clicked();

    void on_pushButton_recherche_3_clicked();

    void on_pushButton_filtrer_3_clicked();

    void on_pushButton_pdfclient_clicked();
    void on_annulerajout_4_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_8_clicked();
    void on_tableWidgetemployer_cellClicked(int row);
    void on_pushButton_6_clicked();
    void on_modifier_vente_clicked();
    void on_pushButton_34_clicked();
    void on_tableWidgetvente_cellClicked(int row);
    void on_pushButton_35_clicked();
    void on_pushButton_33_clicked();
    void on_pushButton_3_clicked();

void on_pushButton_28_clicked();
    void on_annulerajout_vente_2_clicked();
    void on_tableWidgetstock_cellClicked(int row);
    void on_pushButton_22_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_clicked();
    void on_pushButton_20_clicked();
    void on_annulerajout_6_clicked();
    void on_pushButton_21_clicked();
                                      void on_pushButton_30_clicked();
                                      void on_pushButton_37_clicked();
                                      void on_pushButton_29_clicked();
                                      void annulerajout_5();
                                      void on_pushButton_25_clicked();
                                      void on_pushButton_26_clicked();
                                      void on_btnpage2four_clicked();


private:
    Ui::MainWindow *ui;
    QRegularExpression regexCIN;
    QRegularExpression regexNom;
    QRegularExpression regexEmail;
    QRegularExpression regexPhone;
    Client Etmp;
};

#endif // MAINWINDOW_H
