#ifndef CONTENIR_H
#define CONTENIR_H

#include <QDialog>
#include <QString>
#include <QList>
#include <QMap>
#include <QPair>
#include <QVector>
#include <QLabel>
#include <QDateTime> // Add this for QDateTime
#include <QVector>    // Add this for QVector
#include <QString>    // Add this for QString

class QListWidget;
class QPushButton;
class QSpinBox;
class QComboBox;


struct StagedVente {
    int idVente;
    QDateTime timestamp;
    double montantTotal;  // Add this field
    QVector<QPair<QString, int>> items;
};

class Contenir : public QDialog
{
    Q_OBJECT

public:
    explicit Contenir(int idVente, QWidget *parent = nullptr);
    ~Contenir();

    // CRUD Operations
    QList<QPair<QString, int>> getItems() const;
    bool validerVente();

    // Static methods for staged ventes management
    static bool commitVenteToDatabase(int idVente);
    static bool commitAndClearVente(int idVente);
    static bool commitAllVentesToDatabase();
    static bool removeStagedVente(int idVente);
    static StagedVente getStagedVente(int idVente);
    static QVector<StagedVente> getAllStagedVentes();
    static QList<int> getAllStagedVenteIds();
    static int getStagedVenteCount();
    static bool hasStagedVente(int idVente);
    static void clearAllStagedVentes();

    // Helper methods
    void loadProduits();
    bool referenceExists(const QString &reference) const;
    int getStockQuantity(const QString &reference) const;
    void updateQuantiteMax(const QString &reference, QSpinBox *spinBox);
    void loadExistingProducts(int idVente);

    void afficherProduits(int idVente);
    QString formatProduitsText(int idVente) const;
    static int getNextId();
    double getProductPrice(const QString &reference);


signals:
    void venteStaged(int idVente);  // Signal emitted when vente is staged

    void montantTotalCalcule(double montant); // Add this signal

private slots:
    void addRow();
    void removeSelectedRow();
    void removeRowByButton();
    void validateQuantite(int newValue);
    void checkAllReferences();
    void loadExistingVente(int idVente);
    void addRowWithValues(const QString &reference, int quantite);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    // Helper methods
    void useDemoData();
    bool hasInvalidReferences() const;


    // Static memory storage for staged ventes
    static QMap<int, StagedVente> stagedVentes;

    // UI Components
    QListWidget *listWidget = nullptr;
    QPushButton *btnAdd = nullptr;
    QPushButton *btnRemove = nullptr;
    QPushButton *btnRefresh = nullptr;
    QPushButton *btnValider = nullptr;
    QPushButton *btnClose = nullptr;
    QLabel *summaryLabel;

    // Data
    int currentIdVente;
    QStringList produitsList;
    QMap<QString, int> stockQuantities;
};

#endif // CONTENIR_H
