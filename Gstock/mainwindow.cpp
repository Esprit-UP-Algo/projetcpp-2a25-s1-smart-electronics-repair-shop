#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QDir>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_supprimer->setPlaceholderText("Supprimer par Référence");\
    ui->lineEdit_recherche->setPlaceholderText("Supprimer par Référence");\
    connect(ui->btnPage1, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->btnPage2, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(1);
    });
    ui->image->setPixmap(QPixmap("C:/Users/Lenovo LOQ/Documents/Gstock/images/logo.png"));
    ui->image->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


