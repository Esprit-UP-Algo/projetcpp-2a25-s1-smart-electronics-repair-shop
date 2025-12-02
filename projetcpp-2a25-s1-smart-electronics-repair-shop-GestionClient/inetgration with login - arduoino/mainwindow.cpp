#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>

#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>

#include <QTextDocument>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QBuffer>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QPainter>
#include <cmath>
#include "smtp.h"
#include "client.h"
#include "vente.h"
#include "employes.h"
#include "produit.h"
#include "appareils.h"
#include "logindialog.h"
#include "contenir.h"

// Original constructor (for backward compatibility)
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    Etmp()
{
    // Add this code at the START of constructor:
    currentUser.id = 0;
    currentUser.nom = "Admin";
    currentUser.prenom = "System";
    currentUser.poste = "Administrateur";
    currentUser.email = "";

    // Your existing code continues here...
    ui->setupUi(this);
    //------------------------------------------------------------ARDUINO------------------------------------------------
    int ret=a.connect_arduino();
    switch(ret){
    case(0):qDebug()<<"arduino is available and connected to :"<<a.getarduino_port_name();
        break;
    case(1):qDebug()<<"arduino is available but not  connected to :"<<a.getarduino_port_name();break;
    case (-1):qDebug()<<"arduino is not available ";
    }
    QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));

    //-------------------------------------------------------------------------------------------------------------------
    regexCIN.setPattern("^[0-9]{8}$");
    regexNom.setPattern("^[A-Za-zÀ-ÿ\\s]+$");
    regexEmail.setPattern("^[\\w.-]+@[\\w.-]+\\.[A-Za-z]{2,6}$");
    regexPhone.setPattern("^[0-9]{8}$");

    // ... rest of your original initialization code
    appareils a(ui);
    a.afficher(ui);
    Produit p(ui);
    p.afficher(ui);
    vente v;
    v.afficher(ui);
    Employee e;
    e.afficher(ui);

    ui->tableWidgetclient->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetclient->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetclient->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetclient->verticalHeader()->setVisible(false);
    Client c;
    c.afficher(ui);

    ui->tableWidgetstock->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetstock->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetstock->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetstock->verticalHeader()->setVisible(false);

    ui->tableWidgetemployer->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetemployer->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetemployer->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetemployer->verticalHeader()->setVisible(false);

    ui->tableWidgetfour->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetfour->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetfour->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetfour->verticalHeader()->setVisible(false);

    ui->tableWidgetvente->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetvente->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetvente->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetvente->verticalHeader()->setVisible(false);

}

// New constructor with user info
MainWindow::MainWindow(const UserInfo &userInfo, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    Etmp(),
    currentUser(userInfo)
{
    ui->setupUi(this);

    // DEBUG: Check what we received
    qDebug() << "=== MAINWINDOW CONSTRUCTOR ===";
    qDebug() << "Received poste:" << currentUser.poste;

    // TEMPORARY FIX: Force the role if it's empty
    if (currentUser.poste.isEmpty() || currentUser.poste.trimmed().isEmpty()) {
        qDebug() << "Poste is empty, forcing to Administrateur";
        currentUser.poste = "Administrateur";
    }

    // Set window title
    setWindowTitle(QString("Smart Electronique - Connecté en tant que: %1 %2 (%3)")
                       .arg(currentUser.prenom)
                       .arg(currentUser.nom)
                       .arg(currentUser.poste));

    // Your existing initialization
    regexCIN.setPattern("^[0-9]{8}$");
    regexNom.setPattern("^[A-Za-zÀ-ÿ\\s]+$");
    regexEmail.setPattern("^[\\w.-]+@[\\w.-]+\\.[A-Za-z]{2,6}$");
    regexPhone.setPattern("^[0-9]{8}$");

    // Setup permissions
    setupPermissions();

    // Initialize modules
    setupPermissions();
    appareils a(ui);
    a.afficher(ui);
    Produit p(ui);
    p.afficher(ui);
    vente v;
    v.afficher(ui);
    Employee e;
    e.afficher(ui);

    // Client setup
    ui->tableWidgetclient->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetclient->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetclient->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetclient->verticalHeader()->setVisible(false);
    Client c;
    c.afficher(ui);

    // Stock setup
    ui->tableWidgetstock->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetstock->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetstock->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetstock->verticalHeader()->setVisible(false);

    // Employee setup
    ui->tableWidgetemployer->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetemployer->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetemployer->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetemployer->verticalHeader()->setVisible(false);

    // Supplier setup
    ui->tableWidgetfour->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetfour->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetfour->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetfour->verticalHeader()->setVisible(false);

    // Sales setup
    ui->tableWidgetvente->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetvente->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetvente->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetvente->verticalHeader()->setVisible(false);
}



// Rest of your existing MainWindow implementation remains the same...
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setupPermissions()
{
    // Clean the role string
    QString role = currentUser.poste.trimmed().toLower();

    qDebug() << "=== SETUP PERMISSIONS ===";
    qDebug() << "User:" << currentUser.prenom << currentUser.nom;
    qDebug() << "Role:" << currentUser.poste;
    qDebug() << "Cleaned role:" << role;

    // Reset all buttons first
    ui->employe->setEnabled(false);
    ui->client_2->setEnabled(false);
    ui->stock_2->setEnabled(false);
    ui->fournisseur_2->setEnabled(false);
    ui->ventes->setEnabled(false);

    // Admin has all permissions
    if (role == "administrateur" || role.contains("admin")) {
        ui->employe->setEnabled(true);
        ui->client_2->setEnabled(true);
        ui->stock_2->setEnabled(true);
        ui->fournisseur_2->setEnabled(true);
        ui->ventes->setEnabled(true);

        QMessageBox::information(this, "Connexion réussie",
                                 QString("Bienvenue %1 %2!\n\nRôle: %3\n\n✅ Tous les modules accessibles")
                                     .arg(currentUser.prenom)
                                     .arg(currentUser.nom)
                                     .arg(currentUser.poste));
    }
    // Responsable Clients - can only access Clients module
    else if (role.contains("client")) {
        ui->client_2->setEnabled(true);

        QMessageBox::information(this, "Connexion réussie",
                                 QString("Bienvenue %1 %2!\n\nRôle: %3\n\n✅ Module accessible: Clients")
                                     .arg(currentUser.prenom)
                                     .arg(currentUser.nom)
                                     .arg(currentUser.poste));
    }
    // Responsable Stock - can only access Stock module
    else if (role.contains("stock")) {
        ui->stock_2->setEnabled(true);

        QMessageBox::information(this, "Connexion réussie",
                                 QString("Bienvenue %1 %2!\n\nRôle: %3\n\n✅ Module accessible: Stock")
                                     .arg(currentUser.prenom)
                                     .arg(currentUser.nom)
                                     .arg(currentUser.poste));
    }
    // Responsable Fournisseurs - can only access Fournisseurs module
    else if (role.contains("fournisseur")) {
        ui->fournisseur_2->setEnabled(true);

        QMessageBox::information(this, "Connexion réussie",
                                 QString("Bienvenue %1 %2!\n\nRôle: %3\n\n✅ Module accessible: Fournisseurs")
                                     .arg(currentUser.prenom)
                                     .arg(currentUser.nom)
                                     .arg(currentUser.poste));
    }
    // Responsable Ventes - can only access Ventes module
    else if (role.contains("vente")) {
        ui->ventes->setEnabled(true);

        QMessageBox::information(this, "Connexion réussie",
                                 QString("Bienvenue %1 %2!\n\nRôle: %3\n\n✅ Module accessible: Ventes")
                                     .arg(currentUser.prenom)
                                     .arg(currentUser.nom)
                                     .arg(currentUser.poste));
    }
    // RH role - can access Employés module
    else if (role == "rh") {
        ui->employe->setEnabled(true);
        QMessageBox::information(this, "Connexion réussie",
                                 QString("Bienvenue %1 %2!\n\nRôle: %3\n\n✅ Module accessible: Employés")
                                     .arg(currentUser.prenom)
                                     .arg(currentUser.nom)
                                     .arg(currentUser.poste));
    }
    // Other roles can be added here
    else {
        QMessageBox::warning(this, "Accès limité",
                             QString("Bienvenue %1 %2!\n\nRôle: %3\n\n❌ Aucun module accessible avec ce rôle")
                                 .arg(currentUser.prenom)
                                 .arg(currentUser.nom)
                                 .arg(currentUser.poste));
    }

    // Debug: Show enabled modules
    qDebug() << "Enabled modules:";
    qDebug() << "  Employés:" << ui->employe->isEnabled();
    qDebug() << "  Clients:" << ui->client_2->isEnabled();
    qDebug() << "  Stock:" << ui->stock_2->isEnabled();
    qDebug() << "  Fournisseurs:" << ui->fournisseur_2->isEnabled();
    qDebug() << "  Ventes:" << ui->ventes->isEnabled();
}

bool MainWindow::hasPermission(const QString &module)
{
    QString role = currentUser.poste.trimmed().toLower();

    // Admin has all permissions
    if (role == "administrateur" || role.contains("admin")) {
        return true;
    }

    // Check specific module permissions
    if (module == "employe" && (role == "rh" || role.contains("employé"))) return true;
    if (module == "client" && role.contains("client")) return true;
    if (module == "stock" && role.contains("stock")) return true;
    if (module == "fournisseur" && role.contains("fournisseur")) return true;
    if (module == "vente" && role.contains("vente")) return true;

    return false;
}

void MainWindow::disableUnauthorizedButtons()
{
    // This is now handled in setupPermissions
}



// Modify navigation methods to check permissions
void MainWindow::on_stock_2_clicked()
{
    if (!hasPermission("stock")) {
        QMessageBox::warning(this, "Accès refusé", "Vous n'avez pas la permission d'accéder au module Stock.");
        return;
    }

    // Your original code
    ui->stackedWidgetstock->setCurrentWidget(0);
    ui->stackedWidget->setCurrentWidget(ui->stock);
    connect(ui->btnPage1stock, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetstock->setCurrentIndex(0);
    });
    connect(ui->btnPage2stock, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetstock->setCurrentIndex(1);
    });

    ui->lineEdit_stocksupp->setPlaceholderText("Supprimer par CIN");
    ui->lineEdit_strech->setPlaceholderText("  Recherche  par reference");
}

void MainWindow::on_employe_clicked()
{
    if (!hasPermission("employe")) {
        QMessageBox::warning(this, "Accès refusé", "Vous n'avez pas la permission d'accéder au module Employés.");
        return;
    }

    ui->stackedWidget->setCurrentWidget(ui->employer);
    ui->lineEdit_empsupp->setPlaceholderText("Supprimer par CIN");
    ui->lineEdit_emprech->setPlaceholderText("  Recherche  par reference");
}

void MainWindow::on_client_2_clicked()
{
    if (!hasPermission("client")) {
        QMessageBox::warning(this, "Accès refusé", "Vous n'avez pas la permission d'accéder au module Clients.");
        return;
    }

    ui->stackedWidget->setCurrentWidget(ui->client);
    ui->stackedWidgetclient->setCurrentIndex(0);
    connect(ui->btnPage1client, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetclient->setCurrentIndex(0);
    });
    connect(ui->btnPage2client, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetclient->setCurrentIndex(1);
    });

    ui->lineEdit_supprimer_client->setPlaceholderText("Supprimer par CIN");
    ui->lineEdit_Recherchecin_client->setPlaceholderText(" Recherche  Client");
}

void MainWindow::on_fournisseur_2_clicked()
{
    if (!hasPermission("fournisseur")) {
        QMessageBox::warning(this, "Accès refusé", "Vous n'avez pas la permission d'accéder au module Fournisseurs.");
        return;
    }

    ui->stackedWidget->setCurrentWidget(ui->fournisseur);
    ui->stackedWidgetfour->setCurrentIndex(0);
    connect(ui->btnpage1four, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetfour->setCurrentIndex(0);
    });
    connect(ui->btnpage2four, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetfour->setCurrentIndex(1);
    });
}

void MainWindow::on_ventes_clicked()
{
    if (!hasPermission("vente")) {
        QMessageBox::warning(this, "Accès refusé", "Vous n'avez pas la permission d'accéder au module Ventes.");
        return;
    }

    ui->stackedWidget->setCurrentWidget(ui->vente);
    ui->stackedWidgetvente->setCurrentIndex(1);
    connect(ui->btnpage1vente, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetvente->setCurrentIndex(1);
    });
    connect(ui->btnpage2vente, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetvente->setCurrentIndex(0);
    });

    ui->lineEdit_supprimer_vente->setPlaceholderText("Supprimer par Id Vente");
    ui->lineEdit_vente->setPlaceholderText("  Recherche  par Id Vente");
}




//client
void MainWindow::on_annulerajout_client_clicked()
{
    ui->lineEdit_IDClient_4->clear();
    ui->lineEdit_nom_4->clear();
    ui->lineEdit_Prenom_4->clear();
    ui->lineEdit_Adresse_4->clear();
    ui->lineEdit_Nt_4->clear();
    ui->datedenaissance_3->setSpecialValueText("");
    ui->datedenaissance_3->setDate(QDate::currentDate());
    ui->radioButton_Homme_4->setAutoExclusive(false);
    ui->radioButton_Femme_4->setAutoExclusive(false);
    ui->radioButton_Homme_4->setChecked(false);
    ui->radioButton_Femme_4->setChecked(false);
    ui->radioButton_Homme_4->setAutoExclusive(true);
    ui->radioButton_Femme_4->setAutoExclusive(true);
}

void MainWindow::on_pushButton_ValiderClient_clicked()
{
    Client c(ui);
    bool test = true;


    if (!regexCIN.match(c.getidclient()).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "CIN doit contenir exactement 8 chiffres.");
        test = false;
    }

    if (!regexNom.match(c.getnom()).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Nom doit contenir uniquement des lettres.");
        test = false;
    }

    if (!regexNom.match(c.getprenom()).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Prénom doit contenir uniquement des lettres.");
        test = false;
    }

    if (!regexEmail.match(c.getadresse()).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Adresse email invalide.");
        test = false;
    }

    if (!regexPhone.match(c.getnt()).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Numéro de téléphone doit contenir exactement 8 chiffres.");
        test = false;
    }

    if (test)
    {
        if (c.existe(c.getidclient())) {
            QMessageBox::critical(this, tr("Erreur"), tr("Le client existe !"));
        }
        else
        {
            bool ajoutReussi = c.ajouter(); // Check the return value
            if (ajoutReussi) {
            QMessageBox::information(this, "➕ Ajouté", "Client ajouté avec succès");
          /* Smtp mail ;

            mail.setUser("elyeskalai9@gmail.com");
            mail.setPassword("fmosngpfjgpkyuvy");

            mail.sendMail(
                "elyeskalai9@gmail.com",
                c.getadresse(),
                "Compte ajouté",
                "Bonjour " + c.getnom() + " " + c.getprenom() +
                    ",\nVotre compte de smart electronique repair shop a été créé.\n"
                    "CIN : " + c.getidclient() + "\n"
                                        "Numéro Téléphone : " + c.getnt() + "\n"
                                  "Anniversaire : " + c.getbirth() + "\n"
                                     "Adresse-Mail: " + c.getadresse()
                );*/
            MainWindow::on_annulerajout_client_clicked();
            }
            else QMessageBox::information(this, "➕ Ajouté", "Client n est pas ajouter ");


        }
    }

    c.afficher(ui);
}
void MainWindow::on_pushButton_modifierClient_clicked()
{
    Client c(ui);



    bool test=true;

    if(!regexCIN.match(c.getidclient()).hasMatch()) {
        QMessageBox::warning(nullptr, "Erreur", "CIN doit contenir exactement 8 chiffres.");
        test=false; // optional reset
    }

    if(!regexNom.match(c.getnom()).hasMatch()) {
        QMessageBox::warning(nullptr, "Erreur", "Nom doit contenir uniquement des lettres.");
        test=false;
    }

    if(!regexNom.match(c.getprenom()).hasMatch()) {
        QMessageBox::warning(nullptr, "Erreur", "Prénom doit contenir uniquement des lettres.");
        test=false;
    }

    if(!regexEmail.match(c.getadresse()).hasMatch()) {
        QMessageBox::warning(nullptr, "Erreur", "Adresse email invalide.");
        test=false;
    }

    if(!regexPhone.match(c.getnt()).hasMatch()) {
        QMessageBox::warning(nullptr, "Erreur", "Numéro de téléphone doit contenir exactement 8 chiffres.");
        test=false;
    }
    if (test){
        if (c.existe(c.getidclient()))   // only CIN check
        {
            c.modifier();
           /*Smtp mail ;

            mail.setUser("elyeskalai9@gmail.com");
            mail.setPassword("fmosngpfjgpkyuvy");

            mail.sendMail(
                "elyeskalai9@gmail.com",
                c.getadresse(),
                "Compte modifier",
                "Bonjour " + c.getnom()+"   " +c.getprenom()+ ",\nVotre compte de smart electronique repair shop a été modifier.\nCIN : " + c.getidclient()+ ",.\nNumero Télephone : " + c.getnt()+ ",.\nAnniversaire : " + c.getbirth()+ ",.\nAdresse-Mail: " + c.getadresse());

            QMessageBox::information(this, "✔️ Modifié", "Client modifié avec succès");*/
            MainWindow::on_annulerajout_client_clicked();
        }
        else
        {
            QMessageBox::critical(this,tr("Erreur"),tr("client pas trouvé") );
        }
    }
    c.afficher(ui);

}
void MainWindow::statsexe()
{
    int hommeCount = 0;
    int femmeCount = 0;
    int noneCount = 0;

    QSqlQuery query("SELECT SEXE, COUNT(*) FROM CLIENTS GROUP BY SEXE");
    while (query.next()) {
        QString sexe = query.value(0).toString().toLower();
        int count = query.value(1).toInt();

        if (sexe.contains("homme"))
            hommeCount = count;
        else if (sexe.contains("femme"))
            femmeCount = count;
        else
            noneCount = count;
    }

    int total = hommeCount + femmeCount + noneCount;
    if (total == 0) total = 1;

    // =========================
    // ANIMATION PROGRESS (0 → 100)
    // =========================
    double k = animationProgress / 100.0;

    if (animationProgress >= 100) {
        animTimer->stop();
    } else {
        animationProgress += 2; // animation speed
    }

    // =========================
    // DRAWING AREA
    // =========================
    int width = 500, height = 350;
    QPixmap pix(width, height);
    pix.fill(Qt::transparent);

    QPainter p(&pix);
    p.setRenderHint(QPainter::Antialiasing);

    QColor colorHomme(41, 102, 148);
    QColor colorFemme("#10b981");
    QColor colorNone(220, 20, 60);

    QRectF rect(30, 40, 250, 250);

    // =========================
    // ANGLES WITH ANIMATION
    // =========================
    int angleHomme = int((360.0 * hommeCount / total) * 16 * k);
    int angleFemme = int((360.0 * femmeCount / total) * 16 * k);
    int angleNone  = int((360.0 * noneCount  / total) * 16 * k);

    int startAngle = 0;

    // ===== Draw HOMME slice =====
    p.setBrush(colorHomme);
    p.drawPie(rect, startAngle, angleHomme);

    double percH = (double)hommeCount / total * 100.0;
    {
        double midDeg = (startAngle + angleHomme / 2.0) / 16.0;
        double rad = midDeg * M_PI / 180.0;
        double r = rect.width() * 0.33;
        QPointF pos(rect.center().x() + r * cos(rad),
                    rect.center().y() - r * sin(rad));
        p.setPen(Qt::white);
        if (k >= 1.0) p.drawText(pos, QString("%1%").arg(QString::number(percH, 'f', 1)));
    }
    startAngle += angleHomme;

    // ===== Draw FEMME slice =====
    p.setBrush(colorFemme);
    p.drawPie(rect, startAngle, angleFemme);

    double percF = (double)femmeCount / total * 100.0;
    {
        double midDeg = (startAngle + angleFemme / 2.0) / 16.0;
        double rad = midDeg * M_PI / 180.0;
        double r = rect.width() * 0.33;
        QPointF pos(rect.center().x() + r * cos(rad),
                    rect.center().y() - r * sin(rad));
        if (k >= 1.0) p.drawText(pos, QString("%1%").arg(QString::number(percF, 'f', 1)));
    }
    startAngle += angleFemme;

    // ===== Draw NONE slice =====
    p.setBrush(colorNone);
    p.drawPie(rect, startAngle, angleNone);

    double percN = (double)noneCount / total * 100.0;
    {
        double midDeg = (startAngle + angleNone / 2.0) / 16.0;
        double rad = midDeg * M_PI / 180.0;
        double r = rect.width() * 0.33;
        QPointF pos(rect.center().x() + r * cos(rad),
                    rect.center().y() - r * sin(rad));
        if (k >= 1.0) p.drawText(pos, QString("%1%").arg(QString::number(percN, 'f', 1)));
    }

    // ===== Legend =====
    int legendX = 310;
    int legendY = 100;
    int blockSize = 25;
    int spacing = 40;

    QFont font;
    font.setBold(true);
    font.setPointSize(14);
    p.setFont(font);
    p.setPen(Qt::white);

    p.setBrush(colorHomme);
    p.drawRect(legendX, legendY, blockSize, blockSize);
    p.drawText(legendX + blockSize + 10, legendY + 20, QString("Hommes: %1").arg(hommeCount));

    p.setBrush(colorFemme);
    p.drawRect(legendX, legendY + spacing, blockSize, blockSize);
    p.drawText(legendX + blockSize + 10, legendY + spacing + 20, QString("Femmes: %1").arg(femmeCount));

    p.setBrush(colorNone);
    p.drawRect(legendX, legendY + spacing * 2, blockSize, blockSize);
    p.drawText(legendX + blockSize + 10, legendY + spacing * 2 + 20, QString("Sans Sexe : %1").arg(noneCount));

    p.end();
    ui->labelclientsexe->setPixmap(pix);
}
void MainWindow::on_nettoyage_clicked(){
    Client c;
    // Pour voir les doublons sans supprimer
    c.afficherRapportDoublons();

    // Pour supprimer les doublons avec rapport détaillé
    c.nettoyerDoublonsAvecRapport();

    // Ou simplement supprimer
     c.supprimerDoublonsAmelioree();
    c.afficher(ui);
}
void MainWindow::statavis()
{
    int excellent = 0;
    int passable = 0;
    int mauvais = 0;

    // ===== Read AVIS from DB =====
    QSqlQuery q("SELECT AVIS, COUNT(*) FROM CLIENTS GROUP BY AVIS");
    while(q.next()){
        QString avis = q.value(0).toString().toLower();
        int c = q.value(1).toInt();
        if(avis.contains("excellent")) excellent = c;
        else if(avis.contains("passable")) passable = c;
        else if(avis.contains("mauvais")) mauvais = c;
    }

    int total = excellent + passable + mauvais;
    if(total==0) total = 1;

    // ===== Animation 0 -> 100% =====
    double k = avisAnim / 100.0;
    if(avisAnim >= 100) avisTimer->stop();
    else avisAnim += 2;

    // ===== Drawing area =====
    int width = 500, height = 350;
    QPixmap pix(width, height);
    pix.fill(Qt::transparent);

    QPainter p(&pix);
    p.setRenderHint(QPainter::Antialiasing);

    // ===== Colors =====
    QColor colorExcellent("#10b981");    // green
    QColor colorPassable(41,102,148);    // blue
    QColor colorMauvais(220,20,60);      // red

    // ===== Bar positions & size =====
    int barWidth = 80;
    int spacing = 40;
    int startX = 60;
    int baseY = 300;
    int maxBarHeight = 200;

    // Find max value for scaling
    int maxV = qMax(qMax(excellent, passable), mauvais);
    if(maxV == 0) maxV = 1;

    // ===== Draw bars =====
    auto drawBar = [&](int x, int value, QColor color, QString label){
        int h = int(maxBarHeight * value / maxV * k); // animated height
        QRectF rect(x, baseY - h, barWidth, h);

        // Draw bar
        p.setBrush(color);
        p.setPen(Qt::NoPen);
        p.drawRect(rect);

        // ===== Draw count inside bar =====
        p.setPen(Qt::white);   // ensure white
        p.setFont(QFont("Arial", 12, QFont::Bold));
        p.drawText(rect, Qt::AlignCenter, QString::number(value));

        // ===== Draw percentage on top (white) =====
        double perc = (double)value / total * 100.0;
        p.setPen(Qt::white);   // force white color
        p.setFont(QFont("Arial", 10, QFont::Bold));
        QRectF percRect(rect.left(), rect.top() - 20, rect.width(), 20);
        p.drawText(percRect, Qt::AlignCenter, QString("%1%").arg(QString::number(perc, 'f', 1)));

        // ===== Draw label below bar =====
        p.setPen(Qt::white);   // force white
        QRectF labelRect(rect.left(), baseY + 5, rect.width(), 20);
        p.drawText(labelRect, Qt::AlignCenter, label);
    };

    drawBar(startX, excellent, colorExcellent, "Excellent");
    drawBar(startX + barWidth + spacing, passable, colorPassable, "Passable");
    drawBar(startX + (barWidth + spacing) * 2, mauvais, colorMauvais, "Mauvais");

    p.end();
    ui->labelclientavis->setPixmap(pix);
}

void MainWindow::on_btnPage2client_clicked()
{
    animationProgress = 0;
    animTimer = new QTimer(this);
    connect(animTimer, &QTimer::timeout, this, &MainWindow::statsexe);
    animTimer->start(15);
    MainWindow::statsexe();

    avisAnim = 0;
    if (!avisTimer) avisTimer = new QTimer(this);
    connect(avisTimer, &QTimer::timeout, this, &MainWindow::statavis);
    avisTimer->start(20);
    MainWindow::statavis();
}

void MainWindow::on_pushButton_supprimer_client_clicked()
{
    QString id = ui->lineEdit_supprimer_client->text();

    Client c;
    Client c2  = c.getclientByCin(id);
    bool test = c.supprimer(id);
    if (test)
    {


       /* Smtp mail ;

        mail.setUser("elyeskalai9@gmail.com");
        mail.setPassword("fmosngpfjgpkyuvy");
        QMessageBox::information(this, "➕ supprime", "Client suprime avec succès");
        mail.sendMail(
            "elyeskalai9@gmail.com",
            c2.getadresse(),  // client email
            "Compte supprimé",
            "Bonjour " + c.getnom() +c.getprenom()+ ",\nVotre compte de smart electronique repair shop a été suprimée." );*/

    }
    else
    {
        QMessageBox::critical(this,tr("Erreur"),tr("La suppression a échoué. Vérifiez le CIN saisi.") );
    }
    c.afficher(ui);
    ui->lineEdit_supprimer_client->clear();
}

void MainWindow::on_pushButton_recherche_3_clicked()
{
    QString rech = ui->lineEdit_Recherchecin_client->text();
    Client c;

    if (!c.rech(rech, ui)) {
        QMessageBox::critical(this, tr("Erreur"), tr("Aucun client trouvé !"));
    }

}

void MainWindow::on_pushButton_filtrer_3_clicked()
{
    QString trier = ui->comboBox_3->currentText();

    if (trier == "      A-Z")
    {

        ui->tableWidgetclient->sortItems(1, Qt::AscendingOrder);
    }
    else if (trier == "      Age")
    {

        ui->tableWidgetclient->sortItems(6, Qt::AscendingOrder);
    }
    else if (trier == "      Sexe")
    {
        ui->tableWidgetclient->sortItems(5, Qt::DescendingOrder );
    }
    else
    {
        QMessageBox::warning(this, "Tri", "Choisissez un critère valide !");
    }
}

void MainWindow::on_tableWidgetclient_cellClicked(int row)
{
    ui->lineEdit_IDClient_4->setText(ui->tableWidgetclient->item(row, 0)->text());
    ui->lineEdit_nom_4->setText(ui->tableWidgetclient->item(row, 1)->text());
    ui->lineEdit_Prenom_4->setText(ui->tableWidgetclient->item(row, 2)->text());
    ui->lineEdit_Adresse_4->setText(ui->tableWidgetclient->item(row, 3)->text());
    ui->lineEdit_Nt_4->setText(ui->tableWidgetclient->item(row, 4)->text());
    ui->datedenaissance_3->setDate(QDate::fromString(ui->tableWidgetclient->item(row, 6)->text(), "yyyy-MM-dd"));
    QString sexe = ui->tableWidgetclient->item(row, 5)->text();

    if (sexe == "Homme") {
        ui->radioButton_Homme_4->setChecked(true);
        ui->radioButton_Femme_4->setChecked(false);
    }
    else if (sexe == "Femme") {
        ui->radioButton_Femme_4->setChecked(true);
        ui->radioButton_Homme_4->setChecked(false);
    }
    else {

        ui->radioButton_Homme_4->setAutoExclusive(false);
        ui->radioButton_Femme_4->setAutoExclusive(false);

        ui->radioButton_Homme_4->setChecked(false);
        ui->radioButton_Femme_4->setChecked(false);

        ui->radioButton_Homme_4->setAutoExclusive(true);
        ui->radioButton_Femme_4->setAutoExclusive(true);
    }
}

void MainWindow::on_pushButton_pdfclient_clicked()
{
    MainWindow::on_annulerajout_client_clicked();
    QTableWidgetItem *selectedItem = ui->tableWidgetclient->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "PDF Export", "Veuillez sélectionner un client !");
        return;
    }

    int row = selectedItem->row();

    // Get client info
    QString cin = ui->tableWidgetclient->item(row, 0)->text();
    QString nom = ui->tableWidgetclient->item(row, 1)->text();
    QString prenom = ui->tableWidgetclient->item(row, 2)->text();
    QString email = ui->tableWidgetclient->item(row, 3)->text();
    QString telephone = ui->tableWidgetclient->item(row, 4)->text();

    QString anniversaire = ui->tableWidgetclient->item(row, 6)->text().split("T").first(); // remove T00:00:00.000
    QString creation = ui->tableWidgetclient->item(row, 7)->text().split("T").first(); // remove T00:00:00.000


    // Calculate validity dates
    QDate currentDate = QDate::currentDate();
    QDate validUntilDate = currentDate.addDays(30);
    QString currentDateStr = currentDate.toString("dd/MM/yyyy");
    QString validUntilDateStr = validUntilDate.toString("dd/MM/yyyy");

    // Choose PDF file name
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Enregistrer l'attestation",
        nom + "_" + prenom + "_Attestation_Voyage.pdf",
        "PDF Files (*.pdf)"
        );
    if (fileName.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    // Build PDF content for TRAVEL & SECURITY purposes
    QString content;
    content += "<h1 style='text-align:center; margin-bottom:30px;'>ATTESTATION POUR VOYAGE</h1>";
    content += "<h2 style='text-align:center; margin-bottom:40px; color:#2c3e50;'>Certificat pour Sécurité Aéroportuaire & Douanes</h2>";

    content += "<div style='font-size:12pt; text-align:justify; line-height:1.6; margin:20px;'>";

    content += "<p style='text-indent:30px;'>"
               "À l'attention des <b>Autorités Aéroportuaires, des Services de Sécurité et des Douanes</b>,"
               "</p>";

    content += "<p style='text-indent:30px;'>"
               "Nous, <b>Smart Electronique</b>, centre professionnel de réparation électronique, "
               "certifions par la présente que :"
               "</p>";

    content += "<p style='text-align:center; font-weight:bold; margin:25px 0; padding:15px; background-color:#f8f9fa; border-left:4px solid #3498db;'>"
               "Monsieur/Madame " + nom.toUpper() + " " + prenom + "<br>"
                                                "Né(e) le : " + anniversaire + "<br>"
                                "Passeport/CIN N° : " + cin + "<br>"
                       "Nationalité : Tunisienne"
                       "</p>";

    content += "<p style='text-indent:30px;'>"
               "Est un client régulier de notre établissement depuis le <b>" + creation + "</b>. "
                            "Ce client nous a confié divers appareils électroniques pour réparation et entretien professionnel."
                            "</p>";

    content += "<h3 style='color:#e74c3c; margin-top:30px;'>OBJET DE L'ATTESTATION :</h3>";

    content += "<p style='text-indent:30px;'>"
               "La présente attestation a pour but d'expliquer la présence éventuelle d'appareils électroniques "
               "<b>réparés ou modifiés</b> dans les bagages de ce passager lors des contrôles de sécurité."
               "</p>";

    content += "<div style='margin-left:30px; margin-top:20px; padding:15px; background-color:#fff3cd; border-left:4px solid #ffc107;'>"
               "<h4 style='color:#856404;'>📱 Appareils Électroniques Concernés :</h4>"
               "<p>• Smartphones et tablettes réparés<br>"
               "• Ordinateurs portables avec composants remplacés<br>"
               "• Appareils électroniques avec soudures visibles<br>"
               "• Composants électroniques de rechange</p>"
               "</div>";

    content += "<p style='text-indent:30px; margin-top:20px;'>"
               "Tous les appareils réparés par nos soins ont subi des tests de fonctionnement et de sécurité. "
               "Les réparations ont été effectuées par des techniciens certifiés utilisant des pièces de qualité professionnelle."
               "</p>";

    content += "<h3 style='color:#27ae60; margin-top:30px;'>POUR INFORMATION DES AUTORITÉS :</h3>";

    content += "<p style='text-indent:30px;'>"
               "• Les appareils peuvent présenter des <b>marques de réparation</b> visibles<br>"
               "• Certains composants peuvent être <b>différents de l'origine</b><br>"
               "• Les soudures professionnelles peuvent être <b>visibles aux rayons X</b><br>"
               "• Tous les appareils sont <b>fonctionnels et sécuritaires</b>"
               "</p>";

    // Validity period section
    content += "<div style='margin:25px 0; padding:20px; background-color:#e8f4fd; border:2px solid #3498db; border-radius:8px;'>"
               "<h4 style='color:#2980b9; text-align:center; margin-bottom:15px;'>📅 PÉRIODE DE VALIDITÉ</h4>"
               "<p style='text-align:center; font-weight:bold; font-size:14pt;'>"
               "Cette attestation est valable du <span style='color:#e74c3c;'>" + currentDateStr + "</span><br>"
                                  "jusqu'au <span style='color:#e74c3c;'>" + validUntilDateStr + "</span><br>"
                                     "<span style='font-size:11pt; color:#7f8c8d;'>(Durée de 30 jours à compter de la date d'émission)</span>"
                                     "</p>"
                                     "</div>";

    content += "<p style='text-indent:30px; background-color:#d4edda; padding:15px; border-left:4px solid #28a745; margin-top:20px;'>"
               "📞 <b>Contact urgent pour vérification :</b><br>"
               "Téléphone : " + telephone + "<br>"
                             "Email : " + email + "<br>"
                         "Nous restons à disposition pour toute confirmation auprès des autorités compétentes."
                         "</p>";

    content += "<p style='text-indent:30px; margin-top:20px;'>"
               "Cette attestation vise à faciliter le passage des contrôles de sécurité et à éviter tout malentendu concernant "
               "les appareils électroniques réparés professionnellement."
               "</p>";

    content += "</div>";

    // Signature section
    content += "<div style='margin-top:80px; text-align:right;'>"
               "<p>Fait à <b>Ariana, Tunis</b>, le " + currentDateStr + "</p>"
                                  "<br><br>"
                                  "<div style='border-top:2px solid #2c3e50; width:350px; margin-left:auto; padding-top:15px;'>"
                                  "<p style='font-weight:bold;'>Le Responsable Technique<br>"
                                  "Smart Electronique<br>"
                                  "Centre Agréé de Réparation Électronique</p>"
                                  "</div>"
                                  "</div>";

    // Footer with contact info
    content += "<div style='margin-top:50px; padding:20px; background-color:#f8f9fa; text-align:center; font-size:10pt;'>"
               "<p><b>Smart Electronique</b> • 📞 +216 98 952 656 • 📧 contact@smartelectronique.com • 🌐 www.smartelectronique.com</p>"
               "</div>";

    QTextDocument doc;
    doc.setHtml(content);
    doc.print(&printer);

    QMessageBox::information(this, "PDF Export", "✅ L'attestation voyage a été générée avec succès !");
}


//employer
void MainWindow::on_annulerajout_4_clicked()
{
    ui->lineEdit_40->clear();
    ui->lineEdit_42->clear();
    ui->lineEdit_41->clear();
    ui->lineEdit_39->clear();
    ui->lineEdit_38->clear();
    ui->lineEdit_44->clear();
    ui->spinBox->setValue(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->lineEdit_43->clear();
    ui->radioButton_3->setAutoExclusive(false);
    ui->radioButton_4->setAutoExclusive(false);
    ui->radioButton_3->setChecked(false);
    ui->radioButton_4->setChecked(false);
    ui->radioButton_3->setAutoExclusive(true);
    ui->radioButton_4->setAutoExclusive(true);
}

void MainWindow::on_pushButton_4_clicked()
{
    // Validate required fields first
    if (ui->lineEdit_40->text().isEmpty() ||
        ui->lineEdit_42->text().isEmpty() ||
        ui->lineEdit_41->text().isEmpty() ||
        ui->lineEdit_39->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires (ID, Nom, Prénom, Téléphone)!");
        return;
    }

    // Validate ID is a number
    bool ok;
    int id = ui->lineEdit_40->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "L'ID doit être un nombre!");
        return;
    }

    Employee emp(ui);
    bool test = emp.ajouter();

    if (test) {
        QMessageBox::information(this, "Succès", "✅ Employé ajouté avec succès !");
        // Refresh the table
        emp.afficher(ui);
        // Clear the form
        on_annulerajout_4_clicked();
    } else {
        QMessageBox::critical(this, "Erreur", "❌ Impossible d'ajouter l'employé !\nVérifiez que l'ID n'existe pas déjà.");
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    int id = ui->lineEdit_empsupp->text().toInt();

    Employee emp;
    bool test = emp.supprimer(id);

    if (test)
    {
        QMessageBox::information(this, tr("Suppression réussie"), tr("L'employé a été supprimé avec succès."));
        emp.afficher(ui);
    }
    else
    {
        QMessageBox::critical(this, tr("Erreur"), tr("La suppression a échoué. Vérifiez l'ID saisi."));
    }
    ui->lineEdit_empsupp->clear();
}

void MainWindow::on_tableWidgetemployer_cellClicked(int row)
{
    QString id = ui->tableWidgetemployer->item(row, 0)->text();
    QString nom = ui->tableWidgetemployer->item(row, 1)->text();
    QString prenom = ui->tableWidgetemployer->item(row, 2)->text();
    QString numtel = ui->tableWidgetemployer->item(row, 3)->text();
    QString adresse = ui->tableWidgetemployer->item(row, 4)->text();
    QString salaire = ui->tableWidgetemployer->item(row, 5)->text();
    QString absence = ui->tableWidgetemployer->item(row, 6)->text();
    QString poste = ui->tableWidgetemployer->item(row, 7)->text();
    QString date_naissance = ui->tableWidgetemployer->item(row, 8)->text();
    QString sexe = ui->tableWidgetemployer->item(row, 9)->text();

    ui->lineEdit_40->setText(id);
    ui->lineEdit_42->setText(nom);
    ui->lineEdit_41->setText(prenom);
    ui->lineEdit_39->setText(numtel);
    ui->lineEdit_38->setText(adresse);
    ui->lineEdit_44->setText(salaire);
    ui->spinBox->setValue(absence.toInt());
    ui->lineEdit_43->setText(poste);

    // Try multiple date formats
    QDate date = QDate::fromString(date_naissance, "yyyy-MM-dd"); // Try database format first
    if (!date.isValid()) {
        date = QDate::fromString(date_naissance, "dd/MM/yyyy"); // Try display format
    }
    if (date.isValid()) {
        ui->dateEdit->setDate(date);
    } else {
        ui->dateEdit->setDate(QDate::currentDate()); // Default to current date if parsing fails
        qDebug() << "Failed to parse date:" << date_naissance;
    }

    ui->radioButton_3->setAutoExclusive(false);
    ui->radioButton_4->setAutoExclusive(false);

    if (sexe == "Homme" || sexe == "Male" || sexe.toLower().contains("homme")) {
        ui->radioButton_3->setChecked(true);
        ui->radioButton_4->setChecked(false);
    } else if (sexe == "Femme" || sexe == "Female" || sexe.toLower().contains("femme")) {
        ui->radioButton_3->setChecked(false);
        ui->radioButton_4->setChecked(true);
    } else {
        ui->radioButton_3->setChecked(false);
        ui->radioButton_4->setChecked(false);
    }

    ui->radioButton_3->setAutoExclusive(true);
    ui->radioButton_4->setAutoExclusive(true);
}

void MainWindow::on_pushButton_6_clicked()
{
    // Validate required fields
    if (ui->lineEdit_40->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un employé à modifier!");
        return;
    }

    // Create employee object from current UI data
    Employee emp(ui);
    bool test = emp.modifier();

    if (test) {
        QMessageBox::information(this, "Succès", "✅ Employé modifié avec succès !");
        // Refresh the table to show updated data
        emp.afficher(ui);
        // Clear the form
        on_annulerajout_4_clicked();
    } else {
        QMessageBox::critical(this, "Erreur", "❌ Impossible de modifier l'employé !");
    }
}
//vente
bool MainWindow::emailValide(const QString &email)
{
    QRegularExpression regex(
        "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$"
        );
    return regex.match(email).hasMatch();
}
QString MainWindow::generateVenteString(int row)
{
    QString data;
    int cols = ui->tableWidgetvente->columnCount();

    // Ajouter les en-têtes
    QStringList headers;
    for(int c = 0; c < cols; c++) {
        headers << ui->tableWidgetvente->horizontalHeaderItem(c)->text();
    }
    data = headers.join(" | ") + "\n";
    data += "----------------------------------------\n";

    // Ajouter les données de la ligne sélectionnée
    for(int c = 0; c < cols; c++){
        QTableWidgetItem *item = ui->tableWidgetvente->item(row, c);
        data += (item ? item->text() : "") + (c == cols-1 ? "" : " | ");
    }
    data += "\n";

    return data;
}

void MainWindow::genererQR(const QString &emailClient, const QString &subject, const QString &body)
{
    // 🔹 1 — CONTROLES DE SAISIE

    // Vérifier si une ligne est sélectionnée
    QList<QTableWidgetItem*> selectedItems = ui->tableWidgetvente->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une vente à envoyer !");
        return;
    }

    // Récupérer la ligne sélectionnée
    int selectedRow = selectedItems.first()->row();

    // Vérifier email vide
    if (emailClient.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir l'adresse email du client.");
        return;
    }

    // Vérifier format email
    if (!emailValide(emailClient)) {
        QMessageBox::warning(this, "Erreur", "Adresse email invalide !");
        return;
    }

    // Vérifier sujet vide
    if (subject.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un sujet.");
        return;
    }

    // Vérifier contenu (body) vide
    if (body.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le contenu du mail est vide.");
        return;
    }

    // 🔹 2 — Générer données de la vente sélectionnée
    QString venteData = generateVenteString(selectedRow);

    if(venteData.length() > 1500) {
        venteData = venteData.left(1500);
        QMessageBox::warning(this, "Attention",
                             "Les données ont été tronquées pour générer le QR code.");
    }

    // 🔹 3 — Générer URL du QR Code
    QString qrUrl = "https://api.qrserver.com/v1/create-qr-code/?size=300x300&data="
                    + QUrl::toPercentEncoding(venteData);

    // 🔹 4 — Construire tableau HTML pour une seule vente
    QString htmlTable = "<table border='1' cellspacing='0' cellpadding='5' "
                        "style='border-collapse: collapse; width: 100%;'>";

    htmlTable += "<tr style='background-color: #4CAF50; color: white;'>";

    int cols = ui->tableWidgetvente->columnCount();

    // En-têtes
    for(int c=0; c<cols; c++) {
        htmlTable += "<th style='padding: 12px; border: 1px solid #ddd; text-align: left;'>"
                     + ui->tableWidgetvente->horizontalHeaderItem(c)->text() + "</th>";
    }
    htmlTable += "</tr>";

    // Données de la ligne sélectionnée
    htmlTable += "<tr style='background-color: #f9f9f9;'>";
    for(int c=0; c<cols; c++){
        QTableWidgetItem *item = ui->tableWidgetvente->item(selectedRow, c);
        htmlTable += "<td style='padding: 10px; border: 1px solid #ddd;'>"
                     + (item ? item->text() : "") + "</td>";
    }
    htmlTable += "</tr>";
    htmlTable += "</table>";

    // Récupérer l'ID de la vente pour le sujet
    QString idVente = ui->tableWidgetvente->item(selectedRow, 0) ?
                          ui->tableWidgetvente->item(selectedRow, 0)->text() : "N/A";

    // 🔹 5 — Construire message HTML complet
    QString htmlMessage =
        "<div style='font-family: Arial; max-width: 800px;'>"

        "<h2 style='color: #2c3e50; text-align:center;'>📋 Facture de Vente #" + idVente + "</h2>"

                    "<p>Bonjour,<br>Voici les détails de votre achat :</p>"

        + htmlTable +

        "<h3 style='color:#1976d2; margin-top: 25px;'>📱 QR Code de votre facture</h3>"
        "<p>Scannez ce QR code pour voir les détails de votre facture :</p>"
        "<div style='text-align:center;'>"
        "<img src='" + qrUrl + "' width='250' height='250' "
                  "style='border:2px solid #1976d2; border-radius:10px;'/>"
                  "</div>"

                  "<div style='background-color: #f8f9fa; padding: 15px; margin-top: 20px; border-radius: 5px;'>"
                  "<h4 style='color: #2c3e50; margin-top: 0;'>📦 Informations de la vente</h4>"
                  "<p><strong>Référence:</strong> " + idVente + "</p>"
                    "<p><strong>Date:</strong> " + (ui->tableWidgetvente->item(selectedRow, 3) ? ui->tableWidgetvente->item(selectedRow, 3)->text() : "N/A") + "</p>"
                                                                                                                      "<p><strong>Montant total:</strong> " + (ui->tableWidgetvente->item(selectedRow, 4) ? ui->tableWidgetvente->item(selectedRow, 4)->text() : "N/A") + " DT</p>"
                                                                                                                      "</div>"

                                                                                                                      "<p style='color:#777; margin-top:20px;'>"
                                                                                                                      "Cordialement,<br><strong>Smart Electronique</strong></p>"
                                                                                                                      "</div>";

    // 🔹 6 — ENVOI DU MAIL
    try {
        Smtp smtp("elyeskalai9@gmail.com", "fmosngpfjgpkyuvy");
        smtp.sendMail2("elyeskalai9@gmail.com", emailClient, subject, htmlMessage);

        QMessageBox::information(this, "Succès",
                                 "Facture #" + idVente + " envoyée avec succès à : " + emailClient);
    }
    catch (...) {
        QMessageBox::critical(this, "Erreur", "Échec de l'envoi de l'email.");
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "Bouton cliqué !";

    QString emailClient = ui->lineEdit_email->text().trimmed();
    qDebug() << "Email saisi:" << emailClient;

    if(emailClient.isEmpty()){
        QMessageBox::warning(this, "Erreur", "Veuillez entrer l'email du client !");
        return;
    }

    // Vérifier qu'il y a des données dans le tableau
    if(ui->tableWidgetvente->rowCount() == 0) {
        QMessageBox::warning(this, "Erreur", "Le tableau de vente est vide !");
        return;
    }

    qDebug() << "Appel de genererQR...";
    QString mailSubject = "Facture de votre vente - QR Code inclus";
    QString mailBody = "Voici votre facture de vente avec QR code";

    genererQR(emailClient, mailSubject, mailBody);
    qDebug() << "genererQR appelé";
}
void MainWindow::on_modifier_vente_clicked()
{
    // Créer un objet vente à partir des champs UI
    vente v(ui);
    v.setidvente(ui->lineEdit_45->text());
    v.settauxtva(ui->lineEdit_46->text().toInt());
    v.setremise(ui->lineEdit_47->text().toInt());
    v.setdatedevente(ui->dateEdit_3->date().toString("dd-MM-yyyy"));
    v.setmontanttotal(ui->lineEdit_49->text().toInt());
    if (ui->radioButton_5->isChecked())
        v.setmodedepaiment("Espèce");
    else if (ui->radioButton_6->isChecked())
        v.setmodedepaiment("Carte bancaire");
    else {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un mode de paiement !");
        return;
    }

    // Appeler la méthode de modification
    if (v.modifier()) {
        QMessageBox::information(this, "Succès", "La vente a été modifiée avec succès !");
        v.afficher(ui); // si tu as une fonction pour rafraîchir un QTableView
    }
}
void MainWindow::on_pushButton_34_clicked()
{

    QString idvente = ui->lineEdit_vente->text();
    vente v(ui);

    if (idvente.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une idvente !");
        return;
    }

    bool success = v.rechercherParId(ui->tableWidgetvente, idvente);

    if (!success) {
        QMessageBox::information(this, "Résultat", "Aucune vente trouvé avec cette idvente.");
    }


}
void MainWindow::on_tableWidgetvente_cellClicked(int row)
{
    // Remplir les champs texte
    ui->lineEdit_45->setText(ui->tableWidgetvente->item(row, 0)->text());
    ui->lineEdit_46->setText(ui->tableWidgetvente->item(row, 1)->text());
    ui->lineEdit_47->setText(ui->tableWidgetvente->item(row, 2)->text());

    // Date
    QString dateStr = ui->tableWidgetvente->item(row, 3)->text();
    QDate date = QDate::fromString(dateStr, "dd-MM-yyyy");  // adapte le format si besoin
    if (date.isValid())
        ui->dateEdit_3->setDate(date);

    // Montant total
    ui->lineEdit_49->setText(ui->tableWidgetvente->item(row, 4)->text());

    // Mode de paiement
    QString mode = ui->tableWidgetvente->item(row, 5)->text();

    if (mode == "Espèce" || mode == "Espèces") {
        ui->radioButton_5->setChecked(true);   // bouton pour Espèce
        ui->radioButton_6->setChecked(false);
    }
    else if (mode == "Carte bancaire") {
        ui->radioButton_6->setChecked(true);   // bouton pour Carte bancaire
        ui->radioButton_5->setChecked(false);
    }
    else {
        // Si la valeur est inconnue, aucun bouton n'est coché
        ui->radioButton_5->setChecked(false);
        ui->radioButton_6->setChecked(false);
    }
}
void MainWindow::on_pushButton_35_clicked()
{
    QString choix = ui->comboBox_10->currentText();



    if (choix == "date") {
        ui->tableWidgetvente->sortItems(3, Qt::AscendingOrder);
        QMessageBox::information(this, "tri", "tri avec succ.");
    }
    else
    {QMessageBox::information(this, "tri", "no tri.");}

}

#include "contenir.h"
#include "vente.h"

void MainWindow::on_pushButton_33_clicked()
{
    // Get the sale ID from lineEdit_45
    QString saleIdText = ui->lineEdit_45->text().trimmed();

    if (saleIdText.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID vente !");
        return;
    }

    // Check if sale ID is valid
    bool ok;
    int saleId = saleIdText.toInt(&ok);
    if (!ok || saleId <= 0) {
        QMessageBox::warning(this, "Erreur", "ID vente invalide ! Doit être un nombre positif.");
        return;
    }

    // Check if there are staged products for this sale
    bool hasStagedProducts = Contenir::hasStagedVente(saleId);
    int productCount = 0;
    QString productList = "";

    if (hasStagedProducts) {
        // DEBUG: Show what's in the staged vente
        qDebug() << "=== Checking staged products for vente #" << saleId << " ===";

        StagedVente stagedVente = Contenir::getStagedVente(saleId);
        productCount = stagedVente.items.count();

        // Build product list for display
        for (int i = 0; i < stagedVente.items.count(); ++i) {
            QString ref = stagedVente.items[i].first;
            int qty = stagedVente.items[i].second;
            productList += QString("  • %1 x %2\n").arg(ref).arg(qty);
            qDebug() << "  Product:" << ref << "x" << qty;
        }
        qDebug() << "=== Total products:" << productCount << " ===";
    }

    // Create vente object
    vente v(ui);

    // Récupérer les données depuis l'interface utilisateur
    v.setidvente(ui->lineEdit_45->text());
    v.settauxtva(ui->lineEdit_46->text().toInt());
    v.setremise(ui->lineEdit_47->text().toInt());
    v.setdatedevente(ui->dateEdit_3->date().toString("dd-MM-yyyy"));
    v.setmontanttotal(ui->lineEdit_49->text().toInt());

    // Mode de paiement depuis les radio buttons
    if (ui->radioButton_5->isChecked())
        v.setmodedepaiment("Espèce");
    else if (ui->radioButton_6->isChecked())
        v.setmodedepaiment("Carte bancaire");
    else {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un mode de paiement !");
        return;
    }

    // Validate required fields
    if (v.getidvente().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "ID vente requis !");
        return;
    }

    if (v.getmontanttotal() <= 0) {
        QMessageBox::warning(this, "Erreur", "Montant total doit être > 0 !");
        return;
    }

    if (v.getmodedepaiment().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Mode de paiement requis !");
        return;
    }

    // Vérifier si la vente existe déjà
    if (v.existe(v.getidvente()))
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Cette vente existe déjà !"));
        return;  // Return here, don't proceed
    }

    // Build confirmation message
    QString confirmMessage = QString("Confirmer la création de la vente ?\n\n"
                                     "DÉTAILS DE LA VENTE:\n"
                                     "• ID Vente: %1\n"
                                     "• Date: %2\n"
                                     "• Montant total: %3 DT\n"
                                     "• TVA: %4%\n"
                                     "• Remise: %5%\n"
                                     "• Mode de paiement: %6\n")
                                 .arg(v.getidvente())
                                 .arg(v.getdatedevente())
                                 .arg(v.getmontanttotal())
                                 .arg(v.gettauxtva())
                                 .arg(v.getremise())
                                 .arg(v.getmodedepaiment());

    if (hasStagedProducts) {
        confirmMessage += QString("\n\nPRODUITS À AJOUTER (%1):\n%2")
                              .arg(productCount)
                              .arg(productList);
    } else {
        confirmMessage += "\n\n⚠️ ATTENTION: Aucun produit n'a été ajouté à cette vente.";
        confirmMessage += "\nLa vente sera créée sans produits dans le détail.";
    }

    QMessageBox::StandardButton confirm = QMessageBox::question(
        this,
        "Confirmation finale",
        confirmMessage,
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
        );

    if (confirm != QMessageBox::Yes) {
        qDebug() << "User cancelled vente creation for ID:" << saleId;
        return;  // User cancelled
    }

    // FIRST: Save the sale to VENTES table
    qDebug() << "Attempting to save vente #" << saleId << "to VENTES table...";

    if (!v.ajouter()) {
        QMessageBox::critical(this, tr("Erreur SQL"),
                              tr("Échec de l'ajout de la vente dans la table VENTES !"));
        return;
    }

    qDebug() << "Vente #" << saleId << "successfully saved to VENTES table";

    // SECOND: If there are staged products, commit them to CONTENIR table
    if (hasStagedProducts) {
        qDebug() << "Now attempting to commit " << productCount
                 << " products to CONTENIR table for vente #" << saleId;

        // Test database connection before committing
        QSqlDatabase db = QSqlDatabase::database();
        if (!db.isOpen()) {
            qDebug() << "Database not open! Attempting to reopen...";
            if (!db.open()) {
                QMessageBox::critical(this, "Erreur Base de données",
                                      "Impossible de se connecter à la base de données !");
                return;
            }
        }

        // Try to commit products
        bool commitSuccess = Contenir::commitVenteToDatabase(saleId);

        if (commitSuccess) {
            // Successfully saved products to CONTENIR
            Contenir::removeStagedVente(saleId);  // Clear from memory

            QMessageBox::information(this,
                                     "✅ Succès complet",
                                     QString("Vente créée avec succès !\n\n"
                                             "VENTE:\n"
                                             "• ID: %1\n"
                                             "• Montant: %2 DT\n"
                                             "• Paiement: %3\n\n"
                                             "PRODUITS:\n"
                                             "• %4 produit(s) ajouté(s) au détail")
                                         .arg(saleId)
                                         .arg(v.getmontanttotal())
                                         .arg(v.getmodedepaiment())
                                         .arg(productCount));

            qDebug() << "✅ Vente #" << saleId << "completely saved: VENTES + CONTENIR";

        } else {
            // Failed to save products - but sale was saved
            qDebug() << "❌ Failed to save products to CONTENIR table";

            // Ask user what to do
            QMessageBox::StandardButton choice = QMessageBox::question(
                this,
                "Produits non sauvegardés",
                QString("La vente #%1 a été créée MAIS les produits n'ont pas pu être ajoutés.\n\n"
                        "Que voulez-vous faire ?")
                    .arg(saleId),
                QMessageBox::Retry | QMessageBox::Ignore | QMessageBox::Cancel,
                QMessageBox::Retry
                );

            if (choice == QMessageBox::Retry) {
                // Keep products in memory for retry
                QMessageBox::information(this, "Réessayer plus tard",
                                         "Les produits restent en mémoire.\n"
                                         "Vous pouvez réessayer ultérieurement.");
            } else if (choice == QMessageBox::Ignore) {
                // Remove products from memory
                Contenir::removeStagedVente(saleId);
                QMessageBox::information(this, "Produits supprimés",
                                         "Les produits ont été supprimés de la mémoire.\n"
                                         "La vente existe sans produits dans le détail.");
            } else {
                // Cancel - rollback the vente? (You might want to delete the vente)
                // This is optional - depends on your requirements
            }
        }
    } else {
        // No products to save, just sale info
        QMessageBox::information(this,
                                 "✅ Vente créée",
                                 QString("Vente #%1 créée avec succès !\n\n"
                                         "Note: Aucun produit ajouté au détail.\n"
                                         "Vous pouvez ajouter des produits plus tard.")
                                     .arg(saleId));

        qDebug() << "✅ Vente #" << saleId << "saved without products";
    }

    // Clear the form (optional)
    ui->lineEdit_45->clear();
    ui->lineEdit_46->clear();
    ui->lineEdit_47->clear();
    ui->lineEdit_49->clear();
    ui->radioButton_5->setAutoExclusive(false);
    ui->radioButton_5->setChecked(false);
    ui->radioButton_6->setChecked(false);
    ui->radioButton_5->setAutoExclusive(true);

    // Actualiser le tableau des ventes
    v.afficher(ui);

    qDebug() << "=== on_pushButton_33_clicked() completed ===";
}
void MainWindow::on_pushButton_3_clicked()
{
    QString idvente = ui->lineEdit_supprimer_vente->text().trimmed();

    if (idvente.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir l'ID de la vente à supprimer !");
        return;
    }

    vente v(ui); // Crée un objet vente
    bool test = v.supprimer(idvente);

    if (test) {
        QMessageBox::information(this, "Succès", "Vente supprimée avec succès !");
        v.afficher(ui); // Actualiser le tableau
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression de la vente !");
    }
}

void MainWindow::on_annulerajout_vente_2_clicked()
{
    ui->lineEdit_45->clear();
    ui->lineEdit_46->clear();
    ui->lineEdit_47->clear();
    ui->lineEdit_49->clear();


    ui->dateEdit_3->setDate(QDate::currentDate());
    ui->radioButton_5->setAutoExclusive(false);
    ui->radioButton_6->setAutoExclusive(false);
    ui->radioButton_5->setChecked(false);
    ui->radioButton_6->setChecked(false);
    ui->radioButton_5->setAutoExclusive(true);
    ui->radioButton_6->setAutoExclusive(true);
}
//produit
//ajout
void MainWindow::on_pushButton_21_clicked()
{
    Produit p(ui);

    p.setreference(ui->lineEdit_reference->text());
    p.setnom(ui->lineEdit_nom->text());
    p.setcategorie(ui->lineEdit_categorie->text());
    p.setmarque(ui->comboBox->currentText());
    p.setprix(ui->lineEdit_prix->text().toDouble());
    p.setquantite(ui->lineEdit_quantite->text().toInt());
    p.setdateAchat(ui->dateEdit_2->text());
    p.setdateExpiration(ui->dateEdit_4->text());


    bool okPrix, okQuantite;
    double prix = ui->lineEdit_prix->text().toDouble(&okPrix);
    int quantite = ui->lineEdit_quantite->text().toInt(&okQuantite);

    if (!okPrix || !okQuantite) {
        QMessageBox::warning(this, tr("Erreur"),
                             tr("Veuillez entrer un prix et une quantité valides !"));
        return;
    }

    p.setprix(prix);
    p.setquantite(quantite);
    if (p.ajouter())
    {
        QMessageBox::information(this, tr("Ajouté"), tr("Produit ajouté avec succès !"));
        p.afficher(ui);
    }
    else
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de l'ajout du produit."));
    }
    MainWindow::on_annulerajout_6_clicked();
}




//annule
void MainWindow::on_annulerajout_6_clicked()
{
    ui->lineEdit_reference->clear();
    ui->lineEdit_nom->clear();
    ui->lineEdit_quantite->clear();
    ui->lineEdit_prix->clear();
    ui->lineEdit_categorie->clear();
    ui->comboBox_8->setCurrentText("MSI");

    // ui->lineEdit_20->clear();
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_4->setDate(QDate::currentDate());

}

//recherche
void MainWindow::on_pushButton_20_clicked()
{
    QString ref = ui->lineEdit_strech->text();
    Produit p;
    if (ref.isEmpty()) {
        p.afficher(ui);
        return;
    }
    if (!p.rechercherParReference(ui->tableWidgetstock, ref)) {
        QMessageBox::critical(this, tr("Erreur"), tr("Aucun produit trouvé !"));
    }

}

//modification
void MainWindow::on_pushButton_clicked()
{
    Produit p(ui);

    // récupérer
    p.setreference(ui->lineEdit_reference->text());
    p.setnom(ui->lineEdit_nom->text());
    p.setcategorie(ui->lineEdit_categorie->text());
    p.setmarque(ui->comboBox->currentText());
    p.setprix(ui->lineEdit_prix->text().toDouble());
    p.setquantite(ui->lineEdit_quantite->text().toInt());
    p.setdateAchat(ui->dateEdit_2->date().toString("yyyy-MM-dd"));
    p.setdateExpiration(ui->dateEdit_4->date().toString("yyyy-MM-dd"));


    if (!p.existe(p.getreference()))
    {
        QMessageBox::warning(this, tr("Erreur"),
                             tr("Le produit avec cette référence n'existe pas !"));
        return;
    }

    if (p.modifier())
    {
        QMessageBox::information(this, tr("Succès"),
                                 tr("Le produit a été modifié avec succès !"));
        p.afficher(ui);
    }
    else
    {
        QMessageBox::critical(this, tr("Erreur"),
                              tr("Échec de la modification du produit."));
    }
    MainWindow::on_annulerajout_6_clicked();
}
//tri
void MainWindow::on_pushButton_19_clicked()
{
    QString choix = ui->comboBox_8->currentText();
    Produit p(ui);
    bool success = false;

    if (  choix == "prix") {
        success =p.trierParPrix(ui->tableWidgetstock);
    }
    else if ( choix == "date d'achat") {
        success =p.trierParDateAchat(ui->tableWidgetstock);
    }
    else {
        QMessageBox::warning(this, "Erreur", "Veuillez choisir un critère de tri.");
        return;
    }

    if (success)
        QMessageBox::information(this, "Tri", "Les produits ont été triés avec succès !");
    else
        QMessageBox::warning(this, "Erreur", "Échec du tri !");
}
//supp
void MainWindow::on_pushButton_22_clicked()
{
    QString reference = ui->lineEdit_stocksupp->text();

    Produit p(ui);
    bool test = p.supprimer(reference);

    if (test) {
        QMessageBox::information(this, "Succès", "Produit supprimé avec succès !");
        p.afficher(ui);
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de la suppression du produit !");
    }
    ui->lineEdit_stocksupp->clear();
}
//from table to lineedit
void MainWindow::on_tableWidgetstock_cellClicked(int row)
{
    // Helper lambda to safely get cell text
    auto safeText = [this, row](int col) -> QString {
        QTableWidgetItem *item = ui->tableWidgetstock->item(row, col);
        return item ? item->text() : "";
    };

    ui->lineEdit_reference->setText(safeText(0));
    ui->lineEdit_nom->setText(safeText(1));
    ui->lineEdit_categorie->setText(safeText(2));

    // For marque (ComboBox)
    QString marque = safeText(3);
    int index = ui->comboBox->findText(marque);
    if (index != -1)
        ui->comboBox->setCurrentIndex(index);
    else
        ui->comboBox->setCurrentIndex(0); // optional fallback

    ui->lineEdit_prix->setText(safeText(4));
    ui->lineEdit_quantite->setText(safeText(5));

    // Dates
    QString dateAchatStr = safeText(6);
    QString dateExpStr = safeText(7);

    QDate dateAchat = QDate::fromString(dateAchatStr, "yyyy-MM-dd");
    QDate dateExpiration = QDate::fromString(dateExpStr, "yyyy-MM-dd");

    if (dateAchat.isValid())
        ui->dateEdit_2->setDate(dateAchat);
    if (dateExpiration.isValid())
        ui->dateEdit_4->setDate(dateExpiration);
}
//appareil
void MainWindow::on_pushButton_30_clicked(){
    appareils a(ui);
    a.ajouter();
    a.afficher(ui);
    MainWindow::annulerajout_5();

}
void MainWindow::on_pushButton_37_clicked(){
    appareils a(ui);

   a.existe(a.getreference());
    a.modifier();
    a.afficher(ui);
    MainWindow::annulerajout_5();

}
void MainWindow::on_pushButton_29_clicked(){
    QString ref=   ui->lineEdit_35->text();
    appareils a;
    a.supprimer(ref);
    a.afficher(ui);

}
void MainWindow::annulerajout_5()
{
    ui->lineEdit_28->clear();
    ui->lineEdit_29->clear();
    ui->dateEdit_5->setDate(QDate::currentDate());
    ui->dateEdit_6->setDate(QDate::currentDate());
    ui->lineEdit_32->clear();
}

void MainWindow::on_pushButton_25_clicked()
{
    QString choix = ui->comboBox_9->currentText();
    if (choix == "   A-Z") {
        ui->tableWidgetvente->sortItems(1, Qt::AscendingOrder);
        QMessageBox::information(this, "tri", "tri avec succ.");
    }
    else
    {QMessageBox::information(this, "tri", "no tri.");}

}
void MainWindow::on_pushButton_26_clicked()
{
    QString ref = ui->lineEdit_34->text();
    appareils p;
    if (ref.isEmpty()) {
        p.afficher(ui);
        return;
    }
    if (!p.rechercherParReference(ui->tableWidgetfour, ref)) {
        QMessageBox::critical(this, tr("Erreur"), tr("Aucun produit trouvé !"));
    }
}

// Employee Search Function
void MainWindow::on_pushButton_24_clicked()
{
    QString rech = ui->lineEdit_emprech->text().trimmed();
    Employee e;
    if (rech.isEmpty()) {
        e.afficher(ui);
        return;
    }


    if (!e.rech(rech, ui)) {
        QMessageBox::information(this, tr("Aucun résultat"),
                                 tr("Aucun employé trouvé pour : \"%1\"").arg(rech));
    }
}
// Employee Filter Function
void MainWindow::on_pushButton_31_clicked()
{
    QString trier = ui->comboBox_5->currentText();
    int column = -1;
    Qt::SortOrder order = Qt::AscendingOrder;

    if (trier == "age") {
        column = 8;
    } else if (trier == "salaire") {
        column = 5;
        order = Qt::DescendingOrder;
    } else {
        QMessageBox::warning(this, "Tri", "Choisissez un critère valide !");
        return;
    }

    if (column != -1) {
        ui->tableWidgetemployer->sortItems(column, order);
        QMessageBox::information(this, "Tri", "Employés triés avec succès !");
    }
}
// ADD these permission functions
/////////////////////stat vente
void MainWindow::on_btnpage2vente_clicked()
{
    ui->stackedWidgetvente->setCurrentIndex(2);

    // REQUÊTE PAR MOIS
    QSqlQuery query(
        "SELECT TO_CHAR(DATEDEVENTE, 'YYYY-MM') as MOIS, "
        "MIN(MONTANTTOTAL) as MIN_MONTANT, "
        "MAX(MONTANTTOTAL) as MAX_MONTANT, "
        "AVG(MONTANTTOTAL) as MOYENNE, "
        "SUM(MONTANTTOTAL) as TOTAL_MENSUEL, "
        "COUNT(*) as NB_VENTES "
        "FROM VENTES "
        "GROUP BY TO_CHAR(DATEDEVENTE, 'YYYY-MM') "
        "ORDER BY MOIS DESC"
        );

    QVector<QString> mois;
    QVector<double> minMontants;
    QVector<double> maxMontants;
    QVector<double> moyMontants;
    QVector<double> totaux;

    while (query.next()) {
        mois.append(query.value(0).toString());
        minMontants.append(query.value(1).toDouble());
        maxMontants.append(query.value(2).toDouble());
        moyMontants.append(query.value(3).toDouble());
        totaux.append(query.value(4).toDouble());
    }

    if (mois.isEmpty()) {
        QMessageBox::information(this, "Aucune donnée", "Aucune vente trouvée pour générer les statistiques.");
        return;
    }

    // CRÉATION DU GRAPHIQUE
    int width = ui->labelStatVentes->width();
    int height = ui->labelStatVentes->height();

    if (width == 0 || height == 0) {
        width = 700;
        height = 450;
    }

    QPixmap pix(width, height);

    // Fond dégradé élégant
    QPainter p(&pix);
    p.setRenderHint(QPainter::Antialiasing);
    QLinearGradient bgGradient(0, 0, 0, height);
    bgGradient.setColorAt(0, QColor(248, 250, 252));
    bgGradient.setColorAt(1, QColor(241, 245, 249));
    p.fillRect(0, 0, width, height, bgGradient);

    // Titre avec ombre
    p.setPen(QColor(30, 41, 59));
    p.setFont(QFont("Segoe UI", 18, QFont::Bold));
    p.drawText(QRect(0, 20, width, 30), Qt::AlignCenter, "📊 RAPPORT MENSUEL DES VENTES");

    // Sous-titre
    p.setFont(QFont("Segoe UI", 10));
    p.setPen(QColor(100, 116, 139));
    p.drawText(QRect(0, 52, width, 20), Qt::AlignCenter, "Analyse comparative des performances");

    // Légende moderne avec design carte
    int legendX = width - 180;
    int legendY = 90;

    // Fond de la légende avec ombre
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(255, 255, 255, 230));
    p.drawRoundedRect(legendX - 10, legendY - 10, 170, 130, 8, 8);

    // Ombre de la légende
    p.setBrush(QColor(0, 0, 0, 15));
    p.drawRoundedRect(legendX - 8, legendY - 8, 170, 130, 8, 8);

    // Redessiner la carte par-dessus l'ombre
    p.setBrush(QColor(255, 255, 255));
    p.drawRoundedRect(legendX - 10, legendY - 10, 170, 130, 8, 8);

    QString legendLabels[4] = {"Minimum", "Maximum", "Moyenne", "Total"};
    QColor colors[4] = {
        QColor(239, 68, 68),   // Rouge moderne
        QColor(59, 130, 246),  // Bleu moderne
        QColor(251, 146, 60),  // Orange moderne
        QColor(34, 197, 94)    // Vert moderne
    };

    p.setFont(QFont("Segoe UI", 9, QFont::DemiBold));
    for (int i = 0; i < 4; i++) {
        // Pastille colorée avec dégradé
        QLinearGradient dotGradient(legendX, legendY + i * 28, legendX + 18, legendY + i * 28 + 18);
        dotGradient.setColorAt(0, colors[i].lighter(110));
        dotGradient.setColorAt(1, colors[i]);
        p.setBrush(dotGradient);
        p.setPen(Qt::NoPen);
        p.drawRoundedRect(legendX, legendY + i * 28, 18, 18, 4, 4);

        p.setPen(QColor(51, 65, 85));
        p.drawText(legendX + 25, legendY + i * 28 + 13, legendLabels[i]);
    }

    // Dimensions du graphique
    int margin = 80;
    int topMargin = 140;
    int graphWidth = width - margin - 200;
    int graphHeight = height - topMargin - 80;
    int baseY = height - 70;

    // Échelle
    double maxValue = 0;
    for (double value : maxMontants) {
        if (value > maxValue) maxValue = value;
    }
    if (maxValue == 0) maxValue = 1;

    // Grille en arrière-plan
    p.setPen(QPen(QColor(226, 232, 240), 1, Qt::DashLine));
    for (int i = 0; i <= 5; i++) {
        int y = baseY - (graphHeight * i / 5);
        p.drawLine(margin, y, margin + graphWidth, y);
    }

    // Axes principaux
    p.setPen(QPen(QColor(148, 163, 184), 2));
    p.drawLine(margin, baseY - graphHeight, margin, baseY);
    p.drawLine(margin, baseY, margin + graphWidth, baseY);

    // Graduations axe Y avec style moderne
    p.setFont(QFont("Segoe UI", 8));
    p.setPen(QColor(100, 116, 139));
    for (int i = 0; i <= 5; i++) {
        double value = maxValue * i / 5;
        int y = baseY - (graphHeight * i / 5);
        p.drawText(QRect(10, y - 10, margin - 15, 20), Qt::AlignRight | Qt::AlignVCenter,
                   QString("%1 DT").arg(value, 0, 'f', 0));
    }

    // Barres groupées avec dégradés et ombres
    int barGroupWidth = graphWidth / mois.size();
    int barWidth = qMax(8, barGroupWidth / 5);
    int spacing = 2;

    for (int i = 0; i < mois.size(); i++) {
        int groupX = margin + (i * barGroupWidth) + (barGroupWidth - 4*barWidth - 3*spacing) / 2;

        // Dessiner chaque barre avec dégradé
        for (int j = 0; j < 4; j++) {
            double value;
            if (j == 0) value = minMontants[i];
            else if (j == 1) value = maxMontants[i];
            else if (j == 2) value = moyMontants[i];
            else value = totaux[i];

            int barHeight = (value / maxValue) * graphHeight;
            int barX = groupX + j * (barWidth + spacing);

            // Ombre de la barre
            p.setPen(Qt::NoPen);
            p.setBrush(QColor(0, 0, 0, 20));
            p.drawRoundedRect(barX + 2, baseY - barHeight + 2, barWidth, barHeight, 3, 3);

            // Barre avec dégradé
            QLinearGradient barGradient(barX, baseY - barHeight, barX + barWidth, baseY);
            barGradient.setColorAt(0, colors[j].lighter(115));
            barGradient.setColorAt(1, colors[j]);
            p.setBrush(barGradient);
            p.drawRoundedRect(barX, baseY - barHeight, barWidth, barHeight, 3, 3);

            // Valeur au-dessus de la barre si assez haute
            if (barHeight > 30) {
                p.setPen(Qt::white);
                p.setFont(QFont("Segoe UI", 7, QFont::Bold));
                QString valueText = QString("%1").arg(value, 0, 'f', 0);
                p.save();
                p.translate(barX + barWidth/2, baseY - barHeight + 15);
                p.rotate(-90);
                p.drawText(0, 0, valueText);
                p.restore();
            }
        }

        // Label du mois
        QString moisFormate = mois[i].right(2) + "/" + mois[i].left(4);
        p.setPen(QColor(71, 85, 105));
        p.setFont(QFont("Segoe UI", 8, QFont::DemiBold));
        p.drawText(QRect(groupX - 15, baseY + 8, barGroupWidth, 20),
                   Qt::AlignCenter, moisFormate);
    }

    // Résumé dans une carte élégante
    int summaryY = baseY + 35;
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(59, 130, 246, 15));
    p.drawRoundedRect(margin, summaryY, graphWidth, 30, 6, 6);

    p.setFont(QFont("Segoe UI", 9, QFont::DemiBold));
    p.setPen(QColor(30, 58, 138));
    p.drawText(QRect(margin, summaryY, graphWidth, 30), Qt::AlignCenter,
               QString("📈 Analyse sur %1 mois  •  Total général: %2 DT  •  Moyenne globale: %3 DT")
                   .arg(mois.size())
                   .arg(std::accumulate(totaux.begin(), totaux.end(), 0.0), 0, 'f', 0)
                   .arg(std::accumulate(moyMontants.begin(), moyMontants.end(), 0.0) / mois.size(), 0, 'f', 0));

    p.end();

    ui->labelStatVentes->setPixmap(pix);
    ui->labelStatVentes->setScaledContents(true);
}
void MainWindow::genererAttestationTravail(int idEmploye)
{
    Employee emp;
    Employee employe = emp.getEmployeeById(idEmploye);

    if (employe.getid() == 0) {
        QMessageBox::warning(this, "Erreur", "Employé non trouvé !");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Enregistrer l'attestation de travail",
        employe.getnom() + "_" + employe.getprenom() + "_Attestation_Travail.pdf",
        "PDF Files (*.pdf)"
        );

    if (fileName.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize::A4);

    // HTML très simple qui fonctionne
    QString content;
    content += "<html><body>";
    content += "<h1>ATTESTATION DE TRAVAIL</h1>";
    content += "<h2>SMART ELECTRONIQUE</h2>";
    content += "<hr>";

    QString currentDate = QDate::currentDate().toString("dd/MM/yyyy");
    content += "<p><strong>Ariana, le " + currentDate + "</strong></p>";
    content += "<p>Référence: ATT-" + QString::number(idEmploye) + "-" + QDate::currentDate().toString("yyyyMMdd") + "</p>";
    content += "<hr>";

    content += "<h3>OBJET : Attestation de travail</h3>";
    content += "<p>À qui de droit,</p>";
    content += "<p>Nous soussigné(e)s, <strong>Smart Electronique</strong>, société spécialisée dans la réparation électronique,</p>";
    content += "<p>certifions que <strong>Monsieur/Madame " + employe.getprenom().toUpper() + " " + employe.getnom().toUpper() + "</strong>,</p>";
    content += "<p>né(e) le <strong>" + employe.getdatenaissance() + "</strong>,</p>";
    content += "<p>demeurant au <strong>" + employe.getadresse() + "</strong>,</p>";
    content += "<p>est régulièrement employé(e) par notre société en qualité de :</p>";

    content += "<h2><center>" + employe.getposte().toUpper() + "</center></h2>";

    content += "<p>Cette attestation est délivrée à l'intéressé(e) pour faire valoir ce que de droit.</p>";
    content += "<p><em>L'intéressé(e) travaille actuellement dans notre établissement et y occupe les fonctions susmentionnées.</em></p>";

    // Signatures
    content += "<br><br><br><br>";
    content += "<table width='100%'>";
    content += "<tr>";
    content += "<td width='45%' align='center'>_________________________<br>Le Responsable des RH<br>Cachet et signature</td>";
    content += "<td width='10%'></td>";
    content += "<td width='45%' align='center'>_________________________<br>Le Directeur Général<br>Cachet et signature</td>";
    content += "</tr>";
    content += "</table>";

    content += "<br><br><br>";
    content += "<hr>";
    content += "<p align='center'><small>SMART ELECTRONIQUE - Centre de Réparation Électronique Agréé<br>";
    content += "Siège Social: Ariana, Tunisie - Tél: +216 98 952 656<br>";
    content += "Email: contact@smartelectronique.com - R.C. : XXXXXX - I.F. : XXXXXX</small></p>";

    content += "</body></html>";

    QTextDocument doc;
    doc.setHtml(content);
    doc.print(&printer);

    QMessageBox::information(this, "PDF Export", "✅ Attestation professionnelle générée avec succès !");
}

void MainWindow::on_pushButton_9_clicked()
{
    QList<QTableWidgetItem*> selectedItems = ui->tableWidgetemployer->selectedItems();

    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un employé dans le tableau !");
        return;
    }

    int row = selectedItems.first()->row();
    int idEmploye = ui->tableWidgetemployer->item(row, 0)->text().toInt();

    QString nom = ui->tableWidgetemployer->item(row, 1)->text();
    QString prenom = ui->tableWidgetemployer->item(row, 2)->text();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Générer l'attestation",
                                  QString("Voulez-vous générer une attestation de travail pour :\n%1 %2 ?")
                                      .arg(prenom).arg(nom),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        genererAttestationTravail(idEmploye);
    }
}
//stat emp
void MainWindow::statempage()
{
    // ==========================
    // CALCUL AGE GROUPS FROM DB
    // ==========================
    int age18_30 = 0;
    int age30_45 = 0;
    int age45plus = 0;

    QSqlQuery q("SELECT DATE_NAISSANCE FROM EMPLOYES");
    while (q.next()) {

        QDate birth = q.value(0).toDate();
        if (!birth.isValid()) continue;

        int age = birth.daysTo(QDate::currentDate()) / 365;

        if (age >= 18 && age <= 30) age18_30++;
        else if (age > 30 && age <= 45) age30_45++;
        else if (age > 45) age45plus++;
    }

    int total = age18_30 + age30_45 + age45plus;
    if (total == 0) total = 1;

    // ==========================
    // ANIMATION 0 → 100
    // ==========================
    double k = animationProgressemp / 100.0;

    if (animationProgressemp >= 100) {
        animTimeremp->stop();
    } else {
        animationProgressemp += 2;
    }

    // ==========================
    // DRAW AREA
    // ==========================
    int width = 500, height = 350;
    QPixmap pix(width, height);
    pix.fill(Qt::transparent);

    QPainter p(&pix);
    p.setRenderHint(QPainter::Antialiasing);

    QColor c18_30("#3b82f6");
    QColor c30_45("#10b981");
    QColor c45plus("#ef4444");

    QRectF rect(30, 40, 250, 250);

    // ==========================
    // CONVERT TO ANGLES WITH ANIMATION
    // ==========================
    int a18_30 = int((360.0 * age18_30 / total) * 16 * k);
    int a30_45 = int((360.0 * age30_45 / total) * 16 * k);
    int a45plus = int((360.0 * age45plus / total) * 16 * k);

    int start = 0;

    // ====================================================
    // DRAW SECTION + PERCENTAGE INSIDE THE CIRCLE (18–30)
    // ====================================================
    p.setBrush(c18_30);
    p.drawPie(rect, start, a18_30);

    double perc18_30 = (double)age18_30 / total * 100.0;
    if (k >= 1.0 && age18_30 > 0) {
        double midDeg = (start + a18_30 / 2.0) / 16.0;
        double rad = midDeg * M_PI / 180.0;
        double R = rect.width() * 0.33;

        QPointF pos(rect.center().x() + R * cos(rad),
                    rect.center().y() - R * sin(rad));

        p.setPen(Qt::white);
        p.drawText(pos, QString("%1%").arg(QString::number(perc18_30, 'f', 1)));
    }
    start += a18_30;

    // ====================================================
    // DRAW SECTION + PERCENTAGE (30–45)
    // ====================================================
    p.setBrush(c30_45);
    p.drawPie(rect, start, a30_45);

    double perc30_45 = (double)age30_45 / total * 100.0;
    if (k >= 1.0 && age30_45 > 0) {
        double midDeg = (start + a30_45 / 2.0) / 16.0;
        double rad = midDeg * M_PI / 180.0;
        double R = rect.width() * 0.33;

        QPointF pos(rect.center().x() + R * cos(rad),
                    rect.center().y() - R * sin(rad));

        p.setPen(Qt::white);
        p.drawText(pos, QString("%1%").arg(QString::number(perc30_45, 'f', 1)));
    }
    start += a30_45;

    // ====================================================
    // DRAW SECTION + PERCENTAGE (+45)
    // ====================================================
    p.setBrush(c45plus);
    p.drawPie(rect, start, a45plus);

    double perc45 = (double)age45plus / total * 100.0;
    if (k >= 1.0 && age45plus > 0) {
        double midDeg = (start + a45plus / 2.0) / 16.0;
        double rad = midDeg * M_PI / 180.0;
        double R = rect.width() * 0.33;

        QPointF pos(rect.center().x() + R * cos(rad),
                    rect.center().y() - R * sin(rad));

        p.setPen(Qt::white);
        p.drawText(pos, QString("%1%").arg(QString::number(perc45, 'f', 1)));
    }

    // ==========================
    // LEGEND
    // ==========================
    int X = 310;
    int Y = 100;
    int size = 25;
    int space = 40;

    QFont font;
    font.setBold(true);
    font.setPointSize(14);
    p.setFont(font);
    p.setPen(Qt::white);

    p.setBrush(c18_30);
    p.drawRect(X, Y, size, size);
    p.drawText(X + size + 10, Y + 20,
               QString("18–30 ans : %1").arg(age18_30));

    p.setBrush(c30_45);
    p.drawRect(X, Y + space, size, size);
    p.drawText(X + size + 10, Y + space + 20,
               QString("30–45 ans : %1").arg(age30_45));

    p.setBrush(c45plus);
    p.drawRect(X, Y + space * 2, size, size);
    p.drawText(X + size + 10, Y + space * 2 + 20,
               QString("+45 ans : %1").arg(age45plus));

    p.end();
    ui->empstat->setPixmap(pix);
}


void MainWindow::on_agestatemp_clicked()
{

    animationProgressemp = 0;
    animTimeremp = new QTimer(this);
    connect(animTimeremp, &QTimer::timeout, this, &MainWindow::statempage);
    animTimeremp->start(20);
    MainWindow::statempage();
}

// ADD CLOSE EVENT HANDLER
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Fermer l'application",
                                  "Voulez-vous vraiment fermer l'application?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    qDebug() << "Logout button clicked!";

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Déconnexion",
                                  "Êtes-vous sûr de vouloir vous déconnecter?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        qDebug() << "User confirmed logout";

        // Show logout confirmation


        // Close the main window - this will trigger the application to return to login
        this->close();
    }
}
void MainWindow::on_pushButton_7_clicked()
{
    // Get the sale ID from your line edit
    int idVente = ui->lineEdit_45->text().toInt(); // Replace with your actual line edit name

    // Validate the ID
    if (idVente <= 0) {
        QMessageBox::warning(this, "ID Vente Invalide", "Veuillez entrer un ID de vente valide.");
        return;
    }

    // Pass the sale ID to the constructor
    Contenir popup(idVente, this);
    popup.exec();
}


#include <QInputDialog>


void MainWindow::on_pushButton_10_clicked()
{
    // Get vente ID from user using input dialog
    bool ok;
    int venteId = QInputDialog::getInt(this,
                                       "Commit Vente to Database",
                                       "Enter Vente ID to commit:",
                                       1,    // Default value
                                       1,    // Minimum value
                                       1000, // Maximum value
                                       1,    // Step
                                       &ok);

    if (!ok) {
        // User cancelled
        qDebug() << "User cancelled vente commit";
        return;
    }

    qDebug() << "Attempting to commit vente #" << venteId << "to database";

    // Check if the vente exists in memory
    if (!Contenir::hasStagedVente(venteId)) {
        QMessageBox::information(this, "Vente Not Found",
                                 QString("Vente #%1 is not staged in memory.\n\n"
                                         "Please stage it first using the 'Contenir' dialog "
                                         "before committing to database.")
                                     .arg(venteId));
        return;
    }

    // Get vente details for confirmation
    StagedVente stagedVente = Contenir::getStagedVente(venteId);
    int itemCount = stagedVente.items.count();

    // Show confirmation dialog with details
    QMessageBox::StandardButton confirm = QMessageBox::question(
        this,
        "Commit to Database",
        QString("Are you sure you want to commit vente #%1 to the database?\n\n"
                "Details:\n"
                "• Vente ID: %1\n"
                "• Products: %2\n"
                "• Staged at: %3\n\n"
                "This action will:\n"
                "1. Save to CONTENIR table\n"
                "2. Update product stocks\n"
                "3. Remove from memory")
            .arg(venteId)
            .arg(itemCount)
            .arg(stagedVente.timestamp.toString("yyyy-MM-dd hh:mm:ss")),
        QMessageBox::Yes | QMessageBox::No
        );

    if (confirm != QMessageBox::Yes) {
        qDebug() << "User cancelled commit for vente #" << venteId;
        return;
    }

    // Try to commit to database and clear from memory
    if (Contenir::commitAndClearVente(venteId)) {
        QMessageBox::information(this,
                                 "Success",
                                 QString("Vente #%1 successfully saved to database!\n\n"
                                         "• %2 product(s) saved to CONTENIR table\n"
                                         "• Product stocks updated\n"
                                         "• Removed from memory")
                                     .arg(venteId)
                                     .arg(itemCount));

        qDebug() << "Vente #" << venteId << "commited to database and removed from memory";

    } else {
        QMessageBox::critical(this,
                              "Error",
                              QString("Error saving vente #%1 to database.\n\n"
                                      "Possible reasons:\n"
                                      "• Database connection issue\n"
                                      "• Insufficient stock\n"
                                      "• Database constraint violation\n\n"
                                      "The vente remains staged in memory.")
                                  .arg(venteId));
    }
}
