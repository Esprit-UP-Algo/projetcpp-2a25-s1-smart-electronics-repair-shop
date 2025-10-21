#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_stock_2_clicked();

    void on_employe_clicked();

    void on_client_2_clicked();

    void on_fournisseur_2_clicked();

    void on_ventes_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
