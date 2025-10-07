#ifndef SMARTMARKET_H
#define SMARTMARKET_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class SmartMarket;
}
QT_END_NAMESPACE

class SmartMarket : public QMainWindow
{
    Q_OBJECT

public:
    SmartMarket(QWidget *parent = nullptr);
    ~SmartMarket();

private slots:
    void on_btnstock_clicked();

    void on_btnclient_clicked();

    void on_btnvente_clicked();

    void on_btnemployer_clicked();

private:
    Ui::SmartMarket *ui;
};
#endif // SMARTMARKET_H
