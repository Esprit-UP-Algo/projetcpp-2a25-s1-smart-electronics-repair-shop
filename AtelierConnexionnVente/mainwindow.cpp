#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produit.h"
#include "vente.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vente v;
    v.afficher(ui);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_stock_2_clicked()
{
    Produit p(ui);
    p.afficher(ui);

    ui->stackedWidget->setCurrentWidget(ui->stock);
    connect(ui->btnPage1stock, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetstock->setCurrentIndex(0);
    });

    connect(ui->btnPage2stock, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetstock->setCurrentIndex(1);
    });
     //no edit only copy case from table
    ui->tableWidgetstock->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetstock->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetstock->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetstock->verticalHeader()->setVisible(false);
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "Erreur", "La base de données n'est pas connectée !");
        return;
    }

    //supprimer
    ui->lineEdit_stocksupp->setPlaceholderText("Supprimer par references");
    //recherche
    ui->lineEdit_strech->setPlaceholderText("  Recherche  par reference");

}
void MainWindow::on_employe_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->employer);
     //no edit only copy case from table
    ui->tableWidgetemployer->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetemployer->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetemployer->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetemployer->verticalHeader()->setVisible(false);
    //supprimer
    ui->lineEdit_empsupp->setPlaceholderText("Supprimer par CIN");
    //recherche
    ui->lineEdit_emprech->setPlaceholderText("  Recherche  par reference");
}
void MainWindow::on_client_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->client);
    connect(ui->btnPage1client, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetclient->setCurrentIndex(0);
    });

    connect(ui->btnPage2client, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetclient->setCurrentIndex(1);
    });
    //no edit only copy case from table
    ui->tableWidgetclient->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetclient->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetclient->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetclient->verticalHeader()->setVisible(false);
    //supprimer
    ui->lineEdit_supprimer_client->setPlaceholderText("Supprimer par CIN");
    //recherche
    ui->lineEdit_Recherchecin_client->setPlaceholderText("  Recherche  par CIN");
}
void MainWindow::on_fournisseur_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->fournisseur);
    connect(ui->btnpage1four, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetfour->setCurrentIndex(0);
    });

    connect(ui->btnpage2four, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetfour->setCurrentIndex(1);
    });

}
void MainWindow::on_ventes_clicked()
{
    vente v(ui);

    ui->stackedWidget->setCurrentWidget(ui->vente);
    connect(ui->btnpage1vente, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetvente->setCurrentIndex(0);
    });

    connect(ui->btnpage2vente, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetvente->setCurrentIndex(1);
    });
    v.afficher(ui);
     //no edit only copy case from table
    ui->tableWidgetvente->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetvente->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidgetvente->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidgetvente->verticalHeader()->setVisible(false);
    //supprimer
    ui->lineEdit_supprimer_vente->setPlaceholderText("Supprimer par CIN");
    //recherche
    ui->lineEdit_vente->setPlaceholderText("  Recherche  par CIN");
}


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

    // Vérifier si le produit existe déjà
    if (p.existe(p.getreference()))
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Le produit existe déjà !"));
    }
    else
    {
        if (p.ajouter())
        {
            QMessageBox::information(this, tr("Ajouté"), tr("Produit ajouté avec succès !"));
            p.afficher(ui); // 👈 Actualise le tableau automatiquement
        }
        else
        {
            QMessageBox::critical(this, tr("Erreur"), tr("Échec de l'ajout du produit."));
        }
    }
}



void MainWindow::on_annulerajout_6_clicked()
{
    ui->lineEdit_reference->clear();
    ui->lineEdit_nom->clear();
    ui->lineEdit_quantite->clear();
    ui->lineEdit_prix->clear();
    ui->lineEdit_categorie->clear();
    ui->comboBox_8->setCurrentIndex(0);
    // ui->lineEdit_20->clear();
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_4->setDate(QDate::currentDate());

}





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
void MainWindow::on_pushButton_37_clicked()
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
void MainWindow::on_tableWidgetvente_cellClicked(int row, int column)
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
