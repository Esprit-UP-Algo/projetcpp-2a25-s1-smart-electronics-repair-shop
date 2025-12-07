#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_supprimer->setPlaceholderText("Supprimer par ID");
    ui->leditrech->setPlaceholderText("rechercher par ID ");
    connect(ui->btnpage1, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->btnpage2, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //no edit only copy case from table
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableWidget_2->verticalHeader()->setVisible(false);
    //taille mta first column
    ui->tableWidget_2->setColumnWidth(0, 35);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    for (int i = 1; i < ui->tableWidget_2->columnCount(); ++i) {
        ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

