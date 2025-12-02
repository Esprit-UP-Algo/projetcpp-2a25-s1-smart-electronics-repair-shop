#ifndef CONTENIR_H
#define CONTENIR_H

#include <QDialog>
#include <QString>
#include <QList>
#include <QMap>
#include <QPair>
#include <QVector>
#include <QDateTime>

class QListWidget;
class QPushButton;
class QSpinBox;
class QComboBox;

// Structure to store staged vente data
struct StagedVente {
    int idVente;
    QVector<QPair<QString, int>> items;  // List of (refProduit, quantite)
    QDateTime timestamp;
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
    void addRowWithValues(const QString &reference, int quantite);
    void afficherProduits(int idVente);
    QString formatProduitsText(int idVente) const;
signals:
    void venteStaged(int idVente);  // Signal emitted when vente is staged

private slots:
    void addRow();
    void removeSelectedRow();
    void removeRowByButton();
    void validateQuantite(int newValue);
    void checkAllReferences();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    // Helper methods
    void useDemoData();
    bool hasInvalidReferences() const;
    static int getNextId();

    // Static memory storage for staged ventes
    static QMap<int, StagedVente> stagedVentes;

    // UI Components
    QListWidget *listWidget = nullptr;
    QPushButton *btnAdd = nullptr;
    QPushButton *btnRemove = nullptr;
    QPushButton *btnRefresh = nullptr;
    QPushButton *btnValider = nullptr;
    QPushButton *btnClose = nullptr;

    // Data
    int currentIdVente;
    QStringList produitsList;
    QMap<QString, int> stockQuantities;
};

#endif // CONTENIR_H
