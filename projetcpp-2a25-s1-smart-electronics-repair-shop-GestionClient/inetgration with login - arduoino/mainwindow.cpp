#include "mainwindow.h"
#include "ui_mainwindow.h"

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

#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "smtp.h"
#include "client.h"
#include "vente.h"
#include "employes.h"
#include "produit.h"
#include "appareils.h"
#include "logindialog.h"

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
            Smtp mail ;

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
                );
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
            Smtp mail ;

            mail.setUser("elyeskalai9@gmail.com");
            mail.setPassword("fmosngpfjgpkyuvy");

            mail.sendMail(
                "elyeskalai9@gmail.com",
                c.getadresse(),
                "Compte modifier",
                "Bonjour " + c.getnom()+"   " +c.getprenom()+ ",\nVotre compte de smart electronique repair shop a été modifier.\nCIN : " + c.getidclient()+ ",.\nNumero Télephone : " + c.getnt()+ ",.\nAnniversaire : " + c.getbirth()+ ",.\nAdresse-Mail: " + c.getadresse());

            QMessageBox::information(this, "✔️ Modifié", "Client modifié avec succès");
            MainWindow::on_annulerajout_client_clicked();
        }
        else
        {
            QMessageBox::critical(this,tr("Erreur"),tr("client pas trouvé") );
        }
    }
    c.afficher(ui);

}
void MainWindow::on_btnPage2client_clicked()
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

    int width = 500, height = 350;
    QPixmap pix(width, height);
    pix.fill(Qt::transparent);

    QPainter p(&pix);
    p.setRenderHint(QPainter::Antialiasing);

    QColor colorHomme(41, 102, 148);
    QColor colorFemme("#10b981");
    QColor colorNone(220, 20, 60);

    QRectF rect(30, 40, 250, 250);

    int angleHomme = int((360.0 * hommeCount / total) * 16);
    int angleFemme = int((360.0 * femmeCount / total) * 16);
    int angleNone  = int((360.0 * noneCount  / total) * 16);

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
        p.drawText(pos, QString("%1%").arg(QString::number(percH, 'f', 1)));
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
        p.drawText(pos, QString("%1%").arg(QString::number(percF, 'f', 1)));
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
        p.drawText(pos, QString("%1%").arg(QString::number(percN, 'f', 1)));
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

void MainWindow::on_pushButton_supprimer_client_clicked()
{
    QString id = ui->lineEdit_supprimer_client->text();

    Client c;
    Client c2  = c.getclientByCin(id);
    bool test = c.supprimer(id);
    if (test)
    {


        Smtp mail ;

        mail.setUser("elyeskalai9@gmail.com");
        mail.setPassword("fmosngpfjgpkyuvy");
        QMessageBox::information(this, "➕ supprime", "Client suprime avec succès");
        mail.sendMail(
            "elyeskalai9@gmail.com",
            c2.getadresse(),  // client email
            "Compte supprimé",
            "Bonjour " + c.getnom() +c.getprenom()+ ",\nVotre compte de smart electronique repair shop a été suprimée." );

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
    QString clients = QFileDialog::getSaveFileName(
        this,
        "Save PDF",
        "Liste_Clients.pdf",
        "PDF Files (*.pdf)"
        );

    if (clients.isEmpty()) return;

    // Create PDF Printer
    QPrinter printer(QPrinter::PrinterMode::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(clients);

    // Build the PDF content
    QString content;
    content += "<h2 style='text-align:center;'>Liste des Clients</h2>";
    content += "<br><table border='1' cellspacing='0' cellpadding='5'>";

    // Table header row
    content += "<tr>";
    for (int col = 0; col < ui->tableWidgetclient->columnCount(); col++) {
        content += "<th>" + ui->tableWidgetclient->horizontalHeaderItem(col)->text() + "</th>";
    }
    content += "</tr>";

    // Table data rows
    for (int row = 0; row < ui->tableWidgetclient->rowCount(); row++) {
        content += "<tr>";
        for (int col = 0; col < ui->tableWidgetclient->columnCount(); col++) {
            QTableWidgetItem *item = ui->tableWidgetclient->item(row, col);
            content += "<td>" + (item ? item->text() : "") + "</td>";
        }
        content += "</tr>";
    }
    content += "</table>";

    // Create a text document
    QTextDocument doc;
    doc.setHtml(content);

    // Print to PDF
    doc.print(&printer);

    QMessageBox::information(this, "PDF Export", "✅ Le fichier PDF a été généré avec succès !");
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
        ui->lineEdit_41->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires!");
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
        QMessageBox::critical(this, "Erreur", "❌ Impossible d'ajouter l'employé !");
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

    QDate date = QDate::fromString(date_naissance, "dd/MM/yyyy");
    if (date.isValid()) {
        ui->dateEdit->setDate(date);
    }

    ui->radioButton_3->setAutoExclusive(false);
    ui->radioButton_4->setAutoExclusive(false);

    if (sexe == "Homme" || sexe == "Male") {
        ui->radioButton_3->setChecked(true);
        ui->radioButton_4->setChecked(false);
    } else if (sexe == "Femme" || sexe == "Female") {
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
    // Create employee object from current UI data
    Employee emp(ui);
    bool test = emp.modifier();

    if (test) {
        QMessageBox::information(this, "Succès", "✅ Employé modifié avec succès !");
        // Refresh the table to show updated data
        emp.afficher(ui);
        // Clear the form
        MainWindow::on_annulerajout_4_clicked();
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
void MainWindow::on_pushButton_33_clicked()
{
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

    // Vérifier si la vente existe déjà
    if (v.existe(v.getidvente()))
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Cette vente existe déjà !"));
    }
    else
    {
        // Ajouter la vente
        if (v.ajouter())
        {
            QMessageBox::information(this, tr("Succès"), tr("Vente ajoutée avec succès !"));
            v.afficher(ui); // Actualiser le tableau
        }
        else
        {
            QMessageBox::critical(this, tr("Erreur SQL"), tr("Échec de l'ajout de la vente !"));
        }
    }
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

    // REQUÊTE : total des ventes par mois
    QSqlQuery query(
        "SELECT TO_CHAR(DATEDEVENTE, 'YYYY-MM') as MOIS, "
        "SUM(MONTANTTOTAL) as TOTAL_MENSUEL "
        "FROM VENTES "
        "GROUP BY TO_CHAR(DATEDEVENTE, 'YYYY-MM') "
        "ORDER BY MOIS ASC"      // ordre chronologique
        );

    QVector<QString> mois;
    QVector<double> totaux;

    while (query.next()) {
        mois.append(query.value(0).toString());
        totaux.append(query.value(1).toDouble());
    }

    if (mois.isEmpty()) {
        QMessageBox::information(this, "Aucune donnée", "Aucune vente trouvée.");
        return;
    }

    // Dimensions du graphique
    int width = ui->labelStatVentes->width();
    int height = ui->labelStatVentes->height();

    if (width == 0 || height == 0) {
        width = 700; height = 450;
    }

    QPixmap pix(width, height);
    QPainter p(&pix);
    p.setRenderHint(QPainter::Antialiasing);

    // Fond dégradé
    QLinearGradient bg(0, 0, 0, height);
    bg.setColorAt(0, QColor(248, 250, 252));
    bg.setColorAt(1, QColor(241, 245, 249));
    p.fillRect(0, 0, width, height, bg);

    // Titre
    p.setPen(QColor(30, 41, 59));
    p.setFont(QFont("Segoe UI", 17, QFont::Bold));
    p.drawText(QRect(0, 20, width, 40), Qt::AlignCenter, "📈 Évolution des Ventes Mensuelles");

    // Marges
    int marginLeft = 70;
    int marginBottom = 60;
    int marginTop = 110;
    int marginRight = 30;

    int graphWidth = width - marginLeft - marginRight;
    int graphHeight = height - marginBottom - marginTop;

    int baseY = height - marginBottom;

    // Trouver la valeur max
    double maxValue = 0;
    for (double v : totaux)
        if (v > maxValue) maxValue = v;
    if (maxValue == 0) maxValue = 1;

    // Grille horizontale
    p.setPen(QPen(QColor(226, 232, 240), 1, Qt::DashLine));
    for (int i = 0; i <= 5; i++) {
        int y = baseY - (graphHeight * i / 5);
        p.drawLine(marginLeft, y, marginLeft + graphWidth, y);

        // Labels Y
        p.setPen(QColor(100, 116, 139));
        p.setFont(QFont("Segoe UI", 8));
        p.drawText(10, y - 5, QString("%1 DT").arg(maxValue * i / 5, 0, 'f', 0));
        p.setPen(QPen(QColor(226, 232, 240), 1, Qt::DashLine));
    }

    // AXES
    p.setPen(QPen(QColor(148, 163, 184), 2));
    p.drawLine(marginLeft, baseY - graphHeight, marginLeft, baseY);
    p.drawLine(marginLeft, baseY, marginLeft + graphWidth, baseY);

    // COURBE
    QPainterPath path;
    QPainterPath fillPath;
    QColor lineColor(59, 130, 246);

    bool firstPoint = true;

    for (int i = 0; i < mois.size(); ++i) {
        double value = totaux[i];

        int x = marginLeft + (i * graphWidth / (mois.size() - 1));
        int y = baseY - ((value / maxValue) * graphHeight);

        if (firstPoint) {
            path.moveTo(x, y);
            fillPath.moveTo(x, baseY);
            fillPath.lineTo(x, y);
            firstPoint = false;
        } else {
            path.lineTo(x, y);
            fillPath.lineTo(x, y);
        }
    }
    // fermer le dégradé
    fillPath.lineTo(marginLeft + graphWidth, baseY);
    fillPath.closeSubpath();

    // Dégradé sous la courbe
    QLinearGradient grad(0, marginTop, 0, baseY);
    grad.setColorAt(0, QColor(59, 130, 246, 90));
    grad.setColorAt(1, QColor(59, 130, 246, 10));
    p.fillPath(fillPath, grad);

    // Tracé de la courbe
    p.setPen(QPen(lineColor, 3));
    p.drawPath(path);

    // Points + valeurs
    for (int i = 0; i < mois.size(); ++i) {
        double value = totaux[i];

        int x = marginLeft + (i * graphWidth / (mois.size() - 1));
        int y = baseY - ((value / maxValue) * graphHeight);

        // Point
        p.setBrush(Qt::white);
        p.setPen(QPen(lineColor, 2));
        p.drawEllipse(QPoint(x, y), 5, 5);

        // Valeur au-dessus
        p.setPen(QColor(15, 23, 42));
        p.setFont(QFont("Segoe UI", 8, QFont::Bold));
        p.drawText(x - 25, y - 15, QString("%1 DT").arg(value, 0, 'f', 0));

        // Mois
        QString m = mois[i].right(2) + "/" + mois[i].left(4);
        p.setPen(QColor(71, 85, 105));
        p.setFont(QFont("Segoe UI", 9));
        p.drawText(x - 30, baseY + 20, 60, 20, Qt::AlignCenter, m);
    }

    // Fin
    p.end();
    ui->labelStatVentes->setPixmap(pix);
    ui->labelStatVentes->setScaledContents(true);
}


//////////exportation
QString MainWindow::genererHTMLFacture(const vente &v)
{
    QString html;
    html = R"(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            padding: 40px 20px;
            display: flex;
            justify-content: center;
            align-items: center;
        }

        .invoice-container {
            background: white;
            border-radius: 20px;
            box-shadow: 0 20px 40px rgba(0,0,0,0.1);
            padding: 40px;
            max-width: 800px;
            width: 100%;
            margin: 0 auto;
            position: relative;
            overflow: hidden;
        }

        .invoice-container::before {
            content: '';
            position: absolute;
            top: 0;
            left: 0;
            right: 0;
            height: 8px;
            background: linear-gradient(90deg, #4CAF50, #45a049);
        }

        .header {
            text-align: center;
            margin-bottom: 40px;
            padding-bottom: 20px;
            border-bottom: 2px solid #f0f0f0;
        }

        .header h1 {
            font-size: 36px;
            color: #2c3e50;
            margin-bottom: 10px;
            font-weight: 700;
        }

        .header .subtitle {
            font-size: 18px;
            color: #7f8c8d;
            font-weight: 300;
        }

        .invoice-table {
            width: 100%;
            margin: 30px 0;
            border-collapse: collapse;
            border-radius: 15px;
            overflow: hidden;
            box-shadow: 0 5px 15px rgba(0,0,0,0.08);
        }

        .invoice-table th {
            background: linear-gradient(135deg, #4CAF50, #45a049);
            color: white;
            padding: 18px 20px;
            text-align: left;
            font-weight: 600;
            font-size: 16px;
            text-transform: uppercase;
            letter-spacing: 0.5px;
        }

        .invoice-table td {
            padding: 16px 20px;
            border-bottom: 1px solid #ecf0f1;
            font-size: 15px;
            color: #2c3e50;
        }

        .invoice-table tr:nth-child(even) {
            background-color: #f8f9fa;
        }

        .invoice-table tr:hover {
            background-color: #e8f5e8;
            transition: background-color 0.3s ease;
        }

        .total-section {
            text-align: center;
            margin: 40px 0 30px 0;
            padding: 25px;
            background: linear-gradient(135deg, #f8f9fa, #e9ecef);
            border-radius: 15px;
            border: 2px dashed #4CAF50;
        }

        .total-amount {
            font-size: 32px;
            font-weight: 800;
            color: #2c3e50;
            margin: 10px 0;
        }

        .total-label {
            font-size: 18px;
            color: #7f8c8d;
            text-transform: uppercase;
            letter-spacing: 1px;
        }

        .footer {
            text-align: center;
            margin-top: 40px;
            padding-top: 25px;
            border-top: 1px solid #ecf0f1;
            color: #95a5a6;
            font-size: 14px;
            line-height: 1.6;
        }

        .contact-info {
            display: flex;
            justify-content: center;
            gap: 30px;
            margin-top: 15px;
            flex-wrap: wrap;
        }

        .contact-item {
            display: flex;
            align-items: center;
            gap: 8px;
        }

        .badge {
            background: #4CAF50;
            color: white;
            padding: 4px 12px;
            border-radius: 20px;
            font-size: 12px;
            font-weight: 600;
        }

        .highlight {
            background: linear-gradient(120deg, #a8e6cf 0%, #dcedc1 100%);
            padding: 2px 6px;
            border-radius: 4px;
            font-weight: 600;
        }
    </style>
</head>
<body>
    <div class="invoice-container">
        <div class="header">
            <h1>🎉 Facture de Vente</h1>
            <div class="subtitle">Reçu officiel • Transaction validée</div>
        </div>

        <table class="invoice-table">
            <tr>
                <th>Description</th>
                <th>Détails</th>
            </tr>
            <tr>
                <td><strong>ID Vente</strong></td>
                <td><span class="highlight">)" + v.getidvente() + R"(</span></td>
            </tr>
            <tr>
                <td><strong>Date de Vente</strong></td>
                <td>📅 )" + v.getdatedevente() + R"(</td>
            </tr>
            <tr>
                <td><strong>Mode de Paiement</strong></td>
                <td>💳 )" + v.getmodedepaiment() + R"(</td>
            </tr>
            <tr>
                <td><strong>Taux TVA</strong></td>
                <td>🏷️ )" + QString::number(v.gettauxtva()) + R"( %</td>
            </tr>
            <tr>
                <td><strong>Remise Appliquée</strong></td>
                <td>🎁 )" + QString::number(v.getremise()) + R"( %</td>
            </tr>
        </table>

        <div class="total-section">
            <div class="total-label">Montant Total TTC</div>
            <div class="total-amount">)" + QString::number(v.getmontanttotal()) + R"( DT</div>
            <div style="margin-top: 10px;">
                <span class="badge">PAYMENT CONFIRMED</span>
            </div>
        </div>

        <div class="footer">
            <div>Merci pour votre confiance ! Votre satisfaction est notre priorité.</div>
            <div class="contact-info">
                <div class="contact-item">📧 contact@entreprise.tn</div>
                <div class="contact-item">📞 +216 00 000 000</div>
                <div class="contact-item">🌐 www.entreprise.tn</div>
            </div>
        </div>
    </div>
</body>
</html>
)";

    return html;
}



// -------------------------------------------------------
// Exportation PDF quand on clique sur le bouton
// -------------------------------------------------------
void MainWindow::on_pushButton_expor_clicked()
{
    // Vérifier la sélection
    int row = ui->tableWidgetvente->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une vente !");
        return;
    }

    // ------------------------
    // Récupération sécurisée
    // ------------------------

    QString idvente;
    QString date;
    int tva = 0;
    int remise = 0;
    double total = 0;
    QString mode;

    auto getText = [&](int col) -> QString {
        QTableWidgetItem *item = ui->tableWidgetvente->item(row, col);
        if (item)
            return item->text();
        return "";
    };

    idvente = getText(0);
    date    = getText(1);
    tva     = getText(2).toInt();
    remise  = getText(3).toInt();
    total   = getText(4).toDouble();
    mode    = getText(5);

    // ------------------------
    // DEBUG AUTO
    // ------------------------
    QString dbg =
        "ID Vente : " + idvente + "\n" +
        "Date : "     + date    + "\n" +
        "TVA : "      + QString::number(tva) + "\n" +
        "Remise : "   + QString::number(remise) + "\n" +
        "Montant : "  + QString::number(total) + "\n" +
        "Mode : "     + mode;

    QMessageBox::information(this, "DEBUG", dbg);

    // ------------------------
    // Remplir objet vente
    // ------------------------
    vente v;
    v.setidvente(idvente);
    v.setdatedevente(date);
    v.settauxtva(tva);
    v.setremise(remise);
    v.setmontanttotal(total);
    v.setmodedepaiment(mode);

    // ------------------------
    // Choisir le fichier PDF
    // ------------------------
    QString filename = QFileDialog::getSaveFileName(
        this,
        "Enregistrer la facture",
        "Facture_Vente.pdf",
        "PDF (*.pdf)");

    if (filename.isEmpty())
        return;

    // ------------------------
    // Génération du PDF
    // ------------------------
    QPdfWriter pdf(filename);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(300);

    QPainter painter(&pdf);

    if (!painter.isActive()) {
        QMessageBox::warning(this, "Erreur", "Impossible de créer le PDF !");
        return;
    }

    QString html = genererHTMLFacture(v);  // <<< NE PAS TOUCHER

    QTextDocument doc;
    doc.setHtml(html);
    doc.setPageSize(QSizeF(pdf.width(), pdf.height()));
    doc.drawContents(&painter);

    QMessageBox::information(this, "Succès", "Facture exportée avec succès !");
}
