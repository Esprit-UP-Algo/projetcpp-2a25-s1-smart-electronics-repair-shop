#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "arduino.h"
#include "client.h"
#include "contenir.h"
#include <QMainWindow>
#include "vente.h"
#include "logindialog.h"
class QNetworkAccessManager;

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(const UserInfo &userInfo, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // ... (all your existing slots remain the same)
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
    void on_btnPage2client_clicked();
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
    void on_pushButton_24_clicked();
    void on_pushButton_31_clicked();
    void on_pushButton_2_clicked();
    void on_nettoyage_clicked();
    void on_pushButton_9_clicked();
    void genererAttestationTravail(int idEmploye);
    void on_agestatemp_clicked();
    void on_pushButtonLogout_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_10_clicked();
    void on_btnPage2stock_clicked();
    void calculerStatsParMarque();
    void on_btnpage2vente_clicked();
    void on_pushButton_expor_clicked();


    void on_pushButton_pdfStatStock_2_clicked();
    void animateFinancialLabel(QLabel* label, double value, const QString& marque);
    void on_pushButton_sms_clicked();
    void sendSMSTwilio(const QString &to, const QString &message);

protected :
    void closeEvent(QCloseEvent *event) override;
private:

    Ui::MainWindow *ui;
    QRegularExpression regexCIN;
    QRegularExpression regexNom;
    QRegularExpression regexEmail;
    QRegularExpression regexPhone;
    Client Etmp;
    UserInfo currentUser;
    void setupPermissions();
    bool hasPermission(const QString &module);
    void disableUnauthorizedButtons();
    void statsexe();
    void statavis();
    QByteArray data;
    Arduino a;
    bool emailValide(const QString &email);
    QString generateVenteString(int row);
    void genererQR(const QString &emailClient, const QString &subject, const QString &body);
    QString genererHTMLFacture(const vente &v);
    int animationProgress = 0;
    QTimer *animTimer;
    int avisAnim = 0;
    QTimer *avisTimer = nullptr;
    void statempage();
    int animationProgressemp = 0;
    QTimer *animTimeremp;
    QNetworkAccessManager *networkManager;




};
#endif // MAINWINDOW_H
