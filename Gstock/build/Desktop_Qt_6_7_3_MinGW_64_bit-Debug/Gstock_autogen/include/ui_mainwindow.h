/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QComboBox *comboBox;
    QPushButton *pushButton_5;
    QLineEdit *lineEdit_recherche;
    QPushButton *pushButton_2;
    QTableWidget *tableWidget;
    QLineEdit *lineEdit_supprimer;
    QGroupBox *groupBox_2;
    QLabel *label_10;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLabel *label_8;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_9;
    QLineEdit *lineEdit_9;
    QPushButton *pushButton;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLabel *image;
    QLabel *label;
    QPushButton *pushButton_4;
    QLabel *label_13;
    QPushButton *pushButton_3;
    QWidget *page_2;
    QGroupBox *groupBox;
    QTextEdit *textEdit;
    QPushButton *btnPage2;
    QGroupBox *groupBox_3;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *btnPage1;
    QLabel *label_11;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1421, 706);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 209, 209);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(310, 90, 1041, 541));
        stackedWidget->setStyleSheet(QString::fromUtf8("/* ---- Style du QStackedWidget ---- */\n"
"QStackedWidget {\n"
"    background-color: rgb(209, 209, 209); /* couleur gris clair */\n"
"    border: 2px solid black;\n"
"    border-radius: 8px;\n"
"}\n"
"\n"
"/* ---- Style des deux pages ---- */\n"
"QWidget#page_1 {\n"
"    background-color: rgb(209, 209, 209); /* m\303\252me gris clair */\n"
"    color: black;\n"
"    font-size: 18px;\n"
"}\n"
"\n"
"QWidget#page_2 {\n"
"    background-color: rgb(209, 209, 209); /* m\303\252me gris clair */\n"
"    color: black;\n"
"    font-size: 18px;\n"
"}\n"
"\n"
"/* ---- Style des boutons ---- */\n"
"QPushButton {\n"
"    border: 2px solid black;\n"
"    border-radius: 8px;\n"
"    font-weight: bold;\n"
"    font-size: 18px;\n"
"    background-color: rgb(41, 102, 148); /* bleu normal */\n"
"    color: white;\n"
"    padding: 8px 16px;\n"
"}\n"
"\n"
"/* Quand la souris passe dessus */\n"
"QPushButton:hover {\n"
"    background-color: rgb(61, 122, 168); /* bleu plus clair */\n"
"}\n"
"\n"
"/* Quand on clique dessus */\n"
"QP"
                        "ushButton:pressed {\n"
"    background-color: rgb(81, 142, 188); /* encore plus clair */\n"
"}\n"
"\n"
"/* Bouton actif (ex. page 1 active) */\n"
"QPushButton[active=\"true\"] {\n"
"    background-color: #10b981; /* vert */\n"
"    color: white;\n"
"}"));
        page = new QWidget();
        page->setObjectName("page");
        comboBox = new QComboBox(page);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(770, 30, 101, 41));
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: rgb(255, 255, 255);   /* white background */\n"
"    color: #1f2937;                         /* selected text color */\n"
"    border: 2px solid #3b82f6;              /* blue border */\n"
"    border-radius: 8px;\n"
"    font-size: 14px;\n"
"    padding: 4px 8px;\n"
"}\n"
"\n"
"/* Dropdown list styling */\n"
"QComboBox QAbstractItemView {\n"
"    background-color: rgb(255, 255, 255);\n"
"    color: #1f2937;\n"
"    selection-background-color: #3b82f6;\n"
"    selection-color: white;\n"
"}\n"
"\n"
"/* Make the arrow black */\n"
"QComboBox::down-arrow {\n"
"    width: 12px;\n"
"    height: 12px;\n"
"    image: none; \n"
"                      /* remove default image */\n"
"	background-color: rgb(0, 170, 255);\n"
"    border-left: 6px solid transparent;\n"
"    border-right: 6px solid transparent;\n"
"    border-top: 6px solid black;       /* black arrow */\n"
"}"));
        pushButton_5 = new QPushButton(page);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(650, 30, 111, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #10b981;   /* normal state */\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #059669;   /* darker on hover */\n"
"}"));
        lineEdit_recherche = new QLineEdit(page);
        lineEdit_recherche->setObjectName("lineEdit_recherche");
        lineEdit_recherche->setGeometry(QRect(430, 30, 161, 41));
        lineEdit_recherche->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    /* dark background */\n"
"	background-color: rgb(255, 255, 255);\n"
"    color: #1f2937;              /* typed text color */\n"
"    border: 2px solid #3b82f6;   /* blue border */\n"
"    border-radius: 8px;\n"
"\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: white;                /* placeholder text color */\n"
"}"));
        pushButton_2 = new QPushButton(page);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(300, 30, 121, 41));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #10b981;   /* normal state */\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #059669;   /* darker on hover */\n"
"}"));
        tableWidget = new QTableWidget(page);
        if (tableWidget->columnCount() < 9)
            tableWidget->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(300, 130, 711, 341));
        tableWidget->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: rgb(41, 102, 148);   /* blue background */\n"
"    border: 2px solid black;\n"
"    border-radius: 8px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"    gridline-color: black;                 /* cell grid lines */\n"
"    color: white;                          \n"
"    selection-background-color: #10b981;\n"
"    selection-color: white;\n"
"    outline: 0;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    border: 1px solid black;               /* give each cell a border */\n"
"    padding: 4px;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: rgb(41, 102, 148);\n"
"    color: white;\n"
"    border: 1px solid black;              /* column header border */\n"
"    padding: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"Elyes\n"
"combo box\n"
"Elyes\n"
"QComboBox {\n"
"    background-color: rgb(255, 255, 255);   /* white background */\n"
"    color: #1f2937;                         /* selected text color */\n"
"    border: 2px solid #3b82f6;              /* "
                        "blue border */\n"
"    border-radius: 8px;\n"
"    font-size: 14px;\n"
"    padding: 4px 8px;\n"
"}\n"
"\n"
"/* Dropdown list styling */\n"
"QComboBox QAbstractItemView {\n"
"    background-color: rgb(255, 255, 255);\n"
"    color: #1f2937;\n"
"    selection-background-color: #3b82f6;\n"
"    selection-color: white;\n"
"}\n"
"\n"
"/* Make the arrow black */\n"
"QComboBox::down-arrow {\n"
"    width: 12px;\n"
"    height: 12px;\n"
"    image: none; \n"
"                      /* remove default image */\n"
"	background-color: rgb(0, 170, 255);\n"
"    border-left: 6px solid transparent;\n"
"    border-right: 6px solid transparent;\n"
"    border-top: 6px solid black;       /* black arrow */\n"
"}"));
        lineEdit_supprimer = new QLineEdit(page);
        lineEdit_supprimer->setObjectName("lineEdit_supprimer");
        lineEdit_supprimer->setGeometry(QRect(320, 490, 161, 41));
        lineEdit_supprimer->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    /* dark background */\n"
"	background-color: rgb(255, 255, 255);\n"
"    color: #1f2937;              /* typed text color */\n"
"    border: 2px solid #3b82f6;   /* blue border */\n"
"    border-radius: 8px;\n"
"\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: white;                /* placeholder text color */\n"
"}"));
        groupBox_2 = new QGroupBox(page);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(20, 60, 271, 461));
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: rgb(41, 102, 148);   /* blue background */\n"
"    border: 2px solid black;               /* black border, 2px wide */\n"
"    border-radius: 8px;                    /* rounded corners */\n"
"    margin-top: 20px;                      /* space for the title */\n"
"    color: white;                          /* title text color */\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
" border: 2px solid black;               /* black border, 2px wide */\n"
"    border-radius: 8px;     \n"
"background-color: rgb(41, 102, 148);\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;       /* title centered */\n"
"    padding: 2px 10px;\n"
"}"));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 250, 91, 20));
        label_10->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_5 = new QLineEdit(groupBox_2);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(140, 210, 113, 28));
        lineEdit_5->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    /* dark background */\n"
"	background-color: rgb(255, 255, 255);\n"
"    color: #1f2937;              /* typed text color */\n"
"    border: 2px solid #3b82f6;   /* blue border */\n"
"    border-radius: 8px;\n"
"\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: white;                /* placeholder text color */\n"
"}"));
        lineEdit_6 = new QLineEdit(groupBox_2);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(140, 290, 113, 28));
        lineEdit_6->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    /* dark background */\n"
"	background-color: rgb(255, 255, 255);\n"
"    color: #1f2937;              /* typed text color */\n"
"    border: 2px solid #3b82f6;   /* blue border */\n"
"    border-radius: 8px;\n"
"\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: white;                /* placeholder text color */\n"
"}"));
        lineEdit_7 = new QLineEdit(groupBox_2);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(140, 330, 113, 28));
        lineEdit_7->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    /* dark background */\n"
"	background-color: rgb(255, 255, 255);\n"
"    color: #1f2937;              /* typed text color */\n"
"    border: 2px solid #3b82f6;   /* blue border */\n"
"    border-radius: 8px;\n"
"\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: white;                /* placeholder text color */\n"
"}"));
        lineEdit_8 = new QLineEdit(groupBox_2);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(140, 370, 113, 28));
        lineEdit_8->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    /* dark background */\n"
"	background-color: rgb(255, 255, 255);\n"
"    color: #1f2937;              /* typed text color */\n"
"    border: 2px solid #3b82f6;   /* blue border */\n"
"    border-radius: 8px;\n"
"\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: white;                /* placeholder text color */\n"
"}"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 330, 111, 41));
        label_8->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 210, 63, 20));
        label_6->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 290, 111, 20));
        label_7->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 370, 121, 20));
        label_9->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_9 = new QLineEdit(groupBox_2);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(140, 250, 113, 28));
        lineEdit_9->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    /* dark background */\n"
"	background-color: rgb(255, 255, 255);\n"
"    color: #1f2937;              /* typed text color */\n"
"    border: 2px solid #3b82f6;   /* blue border */\n"
"    border-radius: 8px;\n"
"\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: white;                /* placeholder text color */\n"
"}"));
        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(69, 418, 91, 31));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #10b981;   /* normal state */\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #059669;   /* darker on hover */\n"
"}"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 50, 81, 20));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 80, 63, 20));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 120, 71, 20));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 160, 63, 20));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(140, 50, 113, 28));
        lineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    /* dark background */\n"
"	background-color: rgb(255, 255, 255);\n"
"    color: #1f2937;              /* typed text color */\n"
"    border: 2px solid #3b82f6;   /* blue border */\n"
"    border-radius: 8px;\n"
"\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: white;                /* placeholder text color */\n"
"}"));
        lineEdit_2 = new QLineEdit(groupBox_2);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(140, 90, 113, 28));
        lineEdit_2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    /* dark background */\n"
"	background-color: rgb(255, 255, 255);\n"
"    color: #1f2937;              /* typed text color */\n"
"    border: 2px solid #3b82f6;   /* blue border */\n"
"    border-radius: 8px;\n"
"\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: white;                /* placeholder text color */\n"
"}\n"
""));
        lineEdit_3 = new QLineEdit(groupBox_2);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(140, 130, 113, 28));
        lineEdit_3->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    /* dark background */\n"
"	background-color: rgb(255, 255, 255);\n"
"    color: #1f2937;              /* typed text color */\n"
"    border: 2px solid #3b82f6;   /* blue border */\n"
"    border-radius: 8px;\n"
"\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: white;                /* placeholder text color */\n"
"}"));
        lineEdit_4 = new QLineEdit(groupBox_2);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(140, 170, 113, 28));
        lineEdit_4->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    /* dark background */\n"
"	background-color: rgb(255, 255, 255);\n"
"    color: #1f2937;              /* typed text color */\n"
"    border: 2px solid #3b82f6;   /* blue border */\n"
"    border-radius: 8px;\n"
"\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: white;                /* placeholder text color */\n"
"}"));
        image = new QLabel(page);
        image->setObjectName("image");
        image->setGeometry(QRect(900, 20, 91, 81));
        image->setPixmap(QPixmap(QString::fromUtf8("images/logo.png")));
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(600, 100, 141, 41));
        label->setStyleSheet(QString::fromUtf8("QLabel{\n"
" border: 2px solid black;   /* blue border */\n"
"    border-radius: 8px;\n"
" font-weight: bold;\n"
"    font-size: 14px;\n"
"background-color: rgb(41, 102, 148);}"));
        pushButton_4 = new QPushButton(page);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(510, 490, 51, 41));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"\n"
"	background-color: rgb(220, 20, 60);\n"
"	\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"      /* darker on hover */\n"
"	background-color: rgb(140, 0, 0);\n"
"}"));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete));
        pushButton_4->setIcon(icon);
        label_13 = new QLabel(page);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(730, 480, 211, 41));
        label_13->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: #10b981;   /* normal state */\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}"));
        pushButton_3 = new QPushButton(page);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(960, 480, 41, 41));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #10b981;   /* normal state */\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #059669;   /* darker on hover */\n"
"}"));
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::GoDown));
        pushButton_3->setIcon(icon1);
        stackedWidget->addWidget(page);
        label->raise();
        comboBox->raise();
        pushButton_5->raise();
        pushButton_2->raise();
        lineEdit_supprimer->raise();
        lineEdit_recherche->raise();
        groupBox_2->raise();
        tableWidget->raise();
        image->raise();
        pushButton_4->raise();
        label_13->raise();
        pushButton_3->raise();
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        groupBox = new QGroupBox(page_2);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(440, 120, 251, 221));
        textEdit = new QTextEdit(groupBox);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(30, 60, 181, 121));
        stackedWidget->addWidget(page_2);
        btnPage2 = new QPushButton(centralwidget);
        btnPage2->setObjectName("btnPage2");
        btnPage2->setGeometry(QRect(420, 40, 131, 51));
        btnPage2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid black;\n"
"    border-radius: 8px;\n"
"    font-weight: bold;\n"
"    font-size: 18px;              /* texte plus grand */\n"
"    background-color: rgb(41, 102, 148); /* bleu normal */\n"
"    color: white;\n"
"    padding: 8px 16px;\n"
"}\n"
"\n"
"/* Quand la souris passe dessus */\n"
"QPushButton:hover {\n"
"    background-color: rgb(61, 122, 168); /* bleu plus clair */\n"
"}\n"
"\n"
"/* Quand on clique dessus */\n"
"QPushButton:pressed {\n"
"    background-color: rgb(81, 142, 188); /* encore plus clair */\n"
"}\n"
"\n"
"/* Bouton actif (par ex. quand on est sur la page 1) */\n"
"QPushButton[active=\"true\"] {\n"
"    background-color: #10b981;  /* vert quand actif */\n"
"    color: white;\n"
"}"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(10, 80, 301, 481));
        groupBox_3->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: rgb(41, 102, 148);   /* blue background */\n"
"    border: 2px solid black;               /* black border, 2px wide */\n"
"    border-radius: 8px;                    /* rounded corners */\n"
"    margin-top: 20px;                      /* space for the title */\n"
"    color: white;                          /* title text color */\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
" border: 2px solid black;               /* black border, 2px wide */\n"
"    border-radius: 8px;     \n"
"background-color: rgb(41, 102, 148);\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;       /* title centered */\n"
"    padding: 2px 10px;\n"
"}"));
        pushButton_8 = new QPushButton(groupBox_3);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(30, 70, 221, 51));
        pushButton_8->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"      background-color: rgb(209, 209, 209);\n"
"    /* normal state */\n"
"    color: rgb(41, 102, 148);\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"      /* darker on hover */\n"
"	background-color: rgb(97, 97, 97);\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        pushButton_9 = new QPushButton(groupBox_3);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(30, 260, 221, 51));
        pushButton_9->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"      background-color: rgb(209, 209, 209);\n"
"    /* normal state */\n"
"    color: rgb(41, 102, 148);\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"      /* darker on hover */\n"
"	background-color: rgb(97, 97, 97);\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        pushButton_10 = new QPushButton(groupBox_3);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(30, 330, 221, 51));
        pushButton_10->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"      background-color: rgb(209, 209, 209);\n"
"    /* normal state */\n"
"    color: rgb(41, 102, 148);\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"      /* darker on hover */\n"
"	background-color: rgb(97, 97, 97);\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        pushButton_11 = new QPushButton(groupBox_3);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(30, 190, 221, 51));
        pushButton_11->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"      background-color: rgb(209, 209, 209);\n"
"    /* normal state */\n"
"    color: rgb(41, 102, 148);\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"      /* darker on hover */\n"
"	background-color: rgb(97, 97, 97);\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        pushButton_12 = new QPushButton(groupBox_3);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(30, 130, 221, 51));
        pushButton_12->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"      background-color: rgb(209, 209, 209);\n"
"    /* normal state */\n"
"    color: rgb(41, 102, 148);\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"      /* darker on hover */\n"
"	background-color: rgb(97, 97, 97);\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        pushButton_13 = new QPushButton(groupBox_3);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(30, 400, 221, 61));
        pushButton_13->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"      background-color: rgb(209, 209, 209);\n"
"    /* normal state */\n"
"    color: rgb(41, 102, 148);\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"      /* darker on hover */\n"
"	background-color: rgb(97, 97, 97);\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        btnPage1 = new QPushButton(centralwidget);
        btnPage1->setObjectName("btnPage1");
        btnPage1->setGeometry(QRect(310, 40, 111, 51));
        btnPage1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid black;\n"
"    border-radius: 8px;\n"
"    font-weight: bold;\n"
"    font-size: 18px;              /* texte plus grand */\n"
"    background-color: rgb(41, 102, 148); /* bleu normal */\n"
"    color: white;\n"
"    padding: 8px 16px;\n"
"}\n"
"\n"
"/* Quand la souris passe dessus */\n"
"QPushButton:hover {\n"
"    background-color: rgb(61, 122, 168); /* bleu plus clair */\n"
"}\n"
"\n"
"/* Quand on clique dessus */\n"
"QPushButton:pressed {\n"
"    background-color: rgb(81, 142, 188); /* encore plus clair */\n"
"}\n"
"\n"
"/* Bouton actif (par ex. quand on est sur la page 1) */\n"
"QPushButton[active=\"true\"] {\n"
"    background-color: #10b981;  /* vert quand actif */\n"
"    color: white;\n"
"}"));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(1030, 30, 321, 61));
        label_11->setStyleSheet(QString::fromUtf8("QLabel{\n"
" border: 2px solid black;   /* blue border */\n"
"    border-radius: 8px;\n"
" font-weight: bold;\n"
"    font-size: 34px;\n"
"background-color: rgb(41, 102, 148);}"));
        MainWindow->setCentralWidget(centralwidget);
        btnPage1->raise();
        btnPage2->raise();
        label_11->raise();
        stackedWidget->raise();
        groupBox_3->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1421, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Cat\303\251gorie", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "prix", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "date d'achat", nullptr));

        pushButton_5->setText(QCoreApplication::translate("MainWindow", "trier", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Rechercher ", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "R\303\251f\303\251rence", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Categorie", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Marque", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Prix", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "ID Fournisseur", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Date d'\303\251xpiration ", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Ajouter /modifier un produit", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Date d\342\200\231achat\n"
"", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Prix", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "ID Fournisseur", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Date d\342\200\231expiration", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Valider", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "R\303\251f\303\251rence", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Cat\303\251gorie", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Marque", nullptr));
        lineEdit->setText(QString());
        image->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "  Liste des Stocks", nullptr));
        pushButton_4->setText(QString());
        label_13->setText(QCoreApplication::translate("MainWindow", "Exporter Format Excel", nullptr));
        pushButton_3->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        btnPage2->setText(QCoreApplication::translate("MainWindow", "Statistique", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Tableau de Bord", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", " Gestion Clients", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "\342\200\215Gestion employee", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "\360\237\224\247Gestion interventions", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "\360\237\223\210Gestion des ventes", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "\360\237\223\246Gestion de stock", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "\360\237\223\246Gestion fournisseurs", nullptr));
        btnPage1->setText(QCoreApplication::translate("MainWindow", "Stock", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", " Gestion de stock", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
