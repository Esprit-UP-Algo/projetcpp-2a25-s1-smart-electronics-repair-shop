#include "smartmarket.h"
#include "./ui_smartmarket.h"

SmartMarket::SmartMarket(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SmartMarket)
{
    ui->setupUi(this);
    connect(ui->btnPage1, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetclient->setCurrentIndex(0);
    });

    connect(ui->btnPage2, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetclient->setCurrentIndex(1);
    });
    connect(ui->btnPage11, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetstock->setCurrentIndex(0);
    });

    connect(ui->btnPage22, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetstock->setCurrentIndex(1);
    });
    connect(ui->btnpage1, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetvente->setCurrentIndex(1);
    });

    connect(ui->btnpage2, &QPushButton::clicked, this, [=](){
        ui->stackedWidgetvente->setCurrentIndex(0);
    });
}

SmartMarket::~SmartMarket()
{
    delete ui;
}

void SmartMarket::on_btnstock_clicked()
{
    ui->travaille->setCurrentIndex(0);
    ui->stackedWidgetstock->setCurrentIndex(0);
}



void SmartMarket::on_btnclient_clicked()
{
     ui->travaille->setCurrentIndex(1);
    ui->stackedWidgetclient->setCurrentIndex(0);
}


void SmartMarket::on_btnvente_clicked()
{
     ui->travaille->setCurrentIndex(3);
    ui->stackedWidgetvente->setCurrentIndex(1);
}



void SmartMarket::on_btnemployer_clicked()
{
    ui->travaille->setCurrentIndex(2);
}

