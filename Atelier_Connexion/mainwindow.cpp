#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_stock_2_clicked()
{
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
    //supprimer
    ui->lineEdit_stocksupp->setPlaceholderText("Supprimer par CIN");
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
    ui->stackedWidget->setCurrentWidget(ui->vente);
    connect(ui->btnpage1vente, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetvente->setCurrentIndex(0);
    });

    connect(ui->btnpage2vente, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetvente->setCurrentIndex(1);
    });
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

