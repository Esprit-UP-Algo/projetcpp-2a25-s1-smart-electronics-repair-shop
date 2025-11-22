#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>
#include "smtp.h"
#include <QFileDialog>
#include <QMessageBox>
#include "client.h"
#include "vente.h"
#include "employes.h"
#include "produit.h"
#include "appareils.h"
#include <QPixmap>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QBuffer>
#include <QByteArray>
#include <QFile>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),

    Etmp()
{

    ui->setupUi(this);
    ui->lineEdit_email->setPlaceholderText("Ecrire gmail du client");
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);

    regexCIN.setPattern("^[0-9]{8}$");
    regexNom.setPattern("^[A-Za-zÀ-ÿ\\s]+$");
    regexEmail.setPattern("^[\\w.-]+@[\\w.-]+\\.[A-Za-z]{2,6}$");
    regexPhone.setPattern("^[0-9]{8}$");
    //appareil
    appareils a(ui);
    a.afficher(ui);
    //produit
    Produit p(ui);
    p.afficher(ui);
    //vente
    vente v;
    v.afficher(ui);
    //employe
    Employee e;
    e.afficher(ui);
    //client
    ui->tableWidgetclient->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetclient->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetclient->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetclient->verticalHeader()->setVisible(false);
    Client c;
    c.afficher(ui);
    //stock
    ui->tableWidgetstock->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetstock->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetstock->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetstock->verticalHeader()->setVisible(false);
    //emp
    ui->tableWidgetemployer->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetemployer->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetemployer->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetemployer->verticalHeader()->setVisible(false);
    //fournisseur
    ui->tableWidgetfour->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetfour->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetfour->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetfour->verticalHeader()->setVisible(false);
    //ventes
    ui->tableWidgetvente->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetvente->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetvente->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetvente->verticalHeader()->setVisible(false);
}
MainWindow::~MainWindow()
{
    delete ui;

}
void MainWindow::on_stock_2_clicked()
{
    ui->stackedWidgetstock->setCurrentWidget(0);
    ui->stackedWidget->setCurrentWidget(ui->stock);
    connect(ui->btnPage1stock, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetstock->setCurrentIndex(0);
    });

    connect(ui->btnPage2stock, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetstock->setCurrentIndex(1);
    });


    //supprimer
    ui->lineEdit_stocksupp->setPlaceholderText("Supprimer par CIN");
    //recherche
    ui->lineEdit_strech->setPlaceholderText("  Recherche  par reference");
}
void MainWindow::on_employe_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->employer);

    //supprimer
    ui->lineEdit_empsupp->setPlaceholderText("Supprimer par CIN");
    //recherche
    ui->lineEdit_emprech->setPlaceholderText("  Recherche  par reference");
}
void MainWindow::on_client_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->client);
    ui->stackedWidgetclient->setCurrentIndex(0);
    connect(ui->btnPage1client, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetclient->setCurrentIndex(0);
    });

    connect(ui->btnPage2client, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetclient->setCurrentIndex(1);
    });

    //supprimer
    ui->lineEdit_supprimer_client->setPlaceholderText("Supprimer par CIN");
    //recherche
    ui->lineEdit_Recherchecin_client->setPlaceholderText(" Recherche  Client");
}
void MainWindow::on_fournisseur_2_clicked()
{
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
    ui->stackedWidget->setCurrentWidget(ui->vente);
     ui->stackedWidgetvente->setCurrentIndex(1);
    connect(ui->btnpage1vente, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetvente->setCurrentIndex(1);
    });

    connect(ui->btnpage2vente, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetvente->setCurrentIndex(0);
    });
    //supprimer
    ui->lineEdit_supprimer_vente->setPlaceholderText("Supprimer par Id Vente");
    //recherche
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
            c.ajouter();
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

            on_annulerajout_client_clicked();
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
*/
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
            noneCount = count; // handles ∅ or empty
    }

    int total = hommeCount + femmeCount + noneCount;
    if (total == 0) total = 1; // avoid division by zero

    int width = 500, height = 350;
    QPixmap pix(width, height);
    pix.fill(Qt::transparent);

    QPainter p(&pix);
    p.setRenderHint(QPainter::Antialiasing);

    // Define colors
    QColor colorHomme(41, 102, 148);
    QColor colorFemme("#10b981");
    QColor colorNone(220, 20, 60);

    // Pie area
    QRectF rect(30, 40, 250, 250);

    // Angles (Qt uses 1/16th of a degree)
    int angleHomme = int((360.0 * hommeCount / total) * 16);
    int angleFemme = int((360.0 * femmeCount / total) * 16);
    int angleNone  = int((360.0 * noneCount  / total) * 16);

    // Draw slices
    int startAngle = 0;

    p.setBrush(colorHomme);
    p.drawPie(rect, startAngle, angleHomme);
    startAngle += angleHomme;

    p.setBrush(colorFemme);
    p.drawPie(rect, startAngle, angleFemme);
    startAngle += angleFemme;

    p.setBrush(colorNone);
    p.drawPie(rect, startAngle, angleNone);

    // ===== Draw Legend =====
    int legendX = 310;
    int legendY = 100;
    int blockSize = 25;
    int spacing = 40;

    QFont font;
    font.setBold(true);
    font.setPointSize(14);
    p.setFont(font);
    p.setPen(Qt::white);

    // Homme block + label
    p.setBrush(colorHomme);
    p.drawRect(legendX, legendY, blockSize, blockSize);
    p.drawText(legendX + blockSize + 10, legendY + 20, QString("Hommes: %1").arg(hommeCount));

    // Femme block + label
    p.setBrush(colorFemme);
    p.drawRect(legendX, legendY + spacing, blockSize, blockSize);
    p.drawText(legendX + blockSize + 10, legendY + spacing + 20, QString("Femmes: %1").arg(femmeCount));

    // None block + label
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


       /* Smtp mail ;

        mail.setUser("elyeskalai9@gmail.com");
        mail.setPassword("fmosngpfjgpkyuvy");
        QMessageBox::information(this, "➕ supprime", "Client suprime avec succès");
        mail.sendMail(
            "elyeskalai9@gmail.com",
            c2.getadresse(),  // client email
            "Compte supprimé",
            "Bonjour " + c.getnom() +c.getprenom()+ ",\nVotre compte de smart electronique repair shop a été suprimée." );
*/
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
    Employee emp(ui);
    bool test = emp.ajouter();
    if (test) {
        QMessageBox::information(this, "Succès", "✅ Employé ajouté avec succès !");
        int row = ui->tableWidgetemployer->rowCount();
        ui->tableWidgetemployer->insertRow(row);
        ui->tableWidgetemployer->setItem(row, 0, new QTableWidgetItem(QString::number(emp.getid())));
        ui->tableWidgetemployer->setItem(row, 1, new QTableWidgetItem(emp.getnom()));
        ui->tableWidgetemployer->setItem(row, 2, new QTableWidgetItem(emp.getprenom()));
        ui->tableWidgetemployer->setItem(row, 3, new QTableWidgetItem(QString::number(emp.getnumtel())));
        ui->tableWidgetemployer->setItem(row, 4, new QTableWidgetItem(emp.getadresse()));
        ui->tableWidgetemployer->setItem(row, 5, new QTableWidgetItem(QString::number(emp.getsalaire())));
        ui->tableWidgetemployer->setItem(row, 6, new QTableWidgetItem(QString::number(emp.getabsence())));
        ui->tableWidgetemployer->setItem(row, 7, new QTableWidgetItem(emp.getdatenaissance()));
        ui->tableWidgetemployer->setItem(row, 8, new QTableWidgetItem(emp.getposte()));
        ui->tableWidgetemployer->setItem(row, 9, new QTableWidgetItem(emp.getsexe()));
    } else {
        QMessageBox::critical(this, "Erreur", "❌ Impossible d'ajouter l'employé !");
    }
    MainWindow::on_annulerajout_4_clicked();
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
    ui->lineEdit_email->setPlaceholderText("Ecrire gmail du client");
}
QString MainWindow::generateVenteString()
{
    QString data;
    int rows = ui->tableWidgetvente->rowCount();
    int cols = ui->tableWidgetvente->columnCount();

    // Ajouter les en-têtes
    QStringList headers;
    for(int c = 0; c < cols; c++) {
        headers << ui->tableWidgetvente->horizontalHeaderItem(c)->text();
    }
    data = headers.join(" | ") + "\n";
    data += "----------------------------------------\n";

    // Ajouter les données
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            QTableWidgetItem *item = ui->tableWidgetvente->item(r, c);
            data += (item ? item->text() : "") + (c == cols-1 ? "" : " | ");
        }
        data += "\n";
    }
    return data;
}

void MainWindow::genererQR(const QString &emailClient, const QString &subject, const QString &body)
{
    // 1️⃣ Générer les données de vente formatées pour le QR code
    QString venteData = generateVenteString();

    // 2️⃣ Limiter si trop long (API QR limite ~2000 chars)
    if(venteData.length() > 1500) {
        venteData = venteData.left(1500);
        QMessageBox::warning(this, "Attention", "Les données ont été tronquées pour le QR code.");
    }

    // 3️⃣ Construire l'URL du QR code avec les données formatées
    QString qrUrl = "https://api.qrserver.com/v1/create-qr-code/?size=300x300&data="
                    + QUrl::toPercentEncoding(venteData);

    // 4️⃣ Générer le tableau HTML pour l'email
    QString htmlTable = "<table border='1' cellspacing='0' cellpadding='5' style='border-collapse: collapse; width: 100%;'>";
    htmlTable += "<tr style='background-color: #4CAF50; color: white;'>";

    int cols = ui->tableWidgetvente->columnCount();
    int rows = ui->tableWidgetvente->rowCount();

    for(int c=0; c<cols; c++) {
        htmlTable += "<th style='padding: 12px; border: 1px solid #ddd; text-align: left;'>"
                     + ui->tableWidgetvente->horizontalHeaderItem(c)->text() + "</th>";
    }
    htmlTable += "</tr>";

    for(int r=0; r<rows; r++){
        // Alterner les couleurs des lignes pour meilleure lisibilité
        QString rowColor = (r % 2 == 0) ? "background-color: #f9f9f9;" : "background-color: white;";
        htmlTable += "<tr style='" + rowColor + "'>";
        for(int c=0; c<cols; c++){
            QTableWidgetItem *item = ui->tableWidgetvente->item(r,c);
            htmlTable += "<td style='padding: 10px; border: 1px solid #ddd;'>"
                         + (item ? item->text() : "") + "</td>";
        }
        htmlTable += "</tr>";
    }
    htmlTable += "</table>";

    // 5️⃣ Construire le message HTML avec instructions claires
    QString htmlMessage =
        "<div style='font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto;'>"
        "<div style='background-color: #f8f9fa; padding: 20px; border-radius: 10px;'>"
        "<h2 style='color: #2c3e50; text-align: center; margin-bottom: 20px;'>📋 Votre Facture de Vente</h2>"
        "<p style='color: #555; font-size: 16px;'>Bonjour,</p>"
        "<p style='color: #555; font-size: 16px;'>Voici le détail de votre achat :</p>"
        "</div>"

        "<div style='margin: 20px 0;'>"
        + htmlTable +
        "</div>"

        "<div style='background-color: #e8f4fd; padding: 20px; border-radius: 10px; margin: 20px 0;'>"
        "<h3 style='color: #1976d2;'>📱 QR Code de votre facture</h3>"
        "<p style='color: #555;'>Scannez ce QR code avec votre smartphone pour accéder aux détails de votre vente :</p>"
        "<div style='text-align: center; padding: 15px; background-color: white; border-radius: 10px; display: inline-block;'>"
        "<img src='" + qrUrl + "' width='250' height='250' alt='QR Code de la vente' style='border: 2px solid #1976d2; border-radius: 10px;'/>"
                  "</div>"
                  "<p style='color: #666; font-size: 14px; margin-top: 10px;'><strong>Instructions :</strong> Ouvrez l'appareil photo de votre smartphone et pointez-la vers le QR code, ou utilisez une application de scan QR.</p>"
                  "</div>"

                  "<div style='background-color: #f8f9fa; padding: 15px; border-radius: 5px; margin-top: 20px;'>"
                  "<p style='color: #777; font-size: 14px;'>Cordialement,<br/><strong>Votre application de vente</strong></p>"
                  "</div>"
                  "</div>";

    // 6️⃣ Envoyer le mail avec la NOUVELLE classe Smtp
    try {
        // REMPLACEZ "votre_app_password" par le mot de passe d'application Gmail
        Smtp smtp("elyeskalai9@gmail.com", "fmosngpfjgpkyuvy");
        smtp.sendMail("elyeskalai9@gmail.com", emailClient, subject, htmlMessage);

        QMessageBox::information(this, "Succès",
                                 "✅ Email avec QR code envoyé avec succès à : " + emailClient + "\n\n"
                                                                                                 "Le client pourra scanner le QR code pour voir le tableau des ventes.");
    }
    catch (...) {
        QMessageBox::critical(this, "Erreur d'envoi",
                              "Échec de l'envoi de l'email. Vérifiez :\n\n"
                              "1. Votre connexion Internet\n"
                              "2. Le mot de passe d'application Gmail\n"
                              "3. Que l'email du client est valide\n"
                              "4. Que la vérification à 2 facteurs est activée sur Gmail");
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

    bool test=a.existe(a.getreference());
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

