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
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page_2;
    QPushButton *pushButton_2;
    QWidget *page_1;
    QGroupBox *groupBox_2;
    QLabel *label_9;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_11;
    QLineEdit *lineEdit_13;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QDateEdit *dateEdit_3;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QLineEdit *leditrech;
    QPushButton *pushButton_8;
    QDateEdit *dateEdit_4;
    QTableWidget *tableWidget_2;
    QPushButton *pushButton_10;
    QLineEdit *lineEdit_supprimer;
    QPushButton *pushButton;
    QLabel *label;
    QPushButton *pushButton_3;
    QWidget *widget;
    QPushButton *btnpage1;
    QPushButton *btnpage2;
    QLabel *label_2;
    QGroupBox *groupBox;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_9;
    QPushButton *pushButton_11;
    QPushButton *pushButton_13;
    QPushButton *pushButton_12;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1318, 681);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color:rgb(209, 209, 209)"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(250, 50, 1031, 591));
        stackedWidget->setStyleSheet(QString::fromUtf8("QStackedWidget {\n"
"  border: 2px solid black;\n"
"  border-radius: 4px;\n"
"  padding: 4px;\n"
"}"));
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        pushButton_2 = new QPushButton(page_2);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(770, 500, 151, 51));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        stackedWidget->addWidget(page_2);
        page_1 = new QWidget();
        page_1->setObjectName("page_1");
        groupBox_2 = new QGroupBox(page_1);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(0, 40, 291, 491));
        groupBox_2->setStyleSheet(QString::fromUtf8("\n"
"QGroupBox {\n"
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
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 60, 63, 31));
        label_9->setStyleSheet(QString::fromUtf8("background-color:rgb(41, 102, 148);\n"
"color: rgb(255, 255, 255)"));
        lineEdit_8 = new QLineEdit(groupBox_2);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(140, 60, 131, 26));
        lineEdit_8->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    width: 150px;\n"
"    height: 150px;\n"
"    border: 3px solid rgb(245,245,245);\n"
"    border-radius: 6px;\n"
"    padding: 6px 12px;\n"
"    color: rgb(0,0,0);\n"
"    background-color: rgb(245,245,245); \n"
"}"));
        lineEdit_9 = new QLineEdit(groupBox_2);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(140, 110, 131, 26));
        lineEdit_9->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    width: 150px;\n"
"    height: 150px;\n"
"    border: 3px solid rgb(245,245,245);\n"
"    border-radius: 6px;\n"
"    padding: 6px 12px;\n"
"    color: rgb(0,0,0);\n"
"    background-color: rgb(245,245,245); \n"
"}"));
        lineEdit_10 = new QLineEdit(groupBox_2);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(140, 160, 131, 26));
        lineEdit_10->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    width: 150px;\n"
"    height: 150px;\n"
"    border: 3px solid rgb(245,245,245);\n"
"    border-radius: 6px;\n"
"    padding: 6px 12px;\n"
"    color: rgb(0,0,0);\n"
"    background-color: rgb(245,245,245); \n"
"}"));
        lineEdit_11 = new QLineEdit(groupBox_2);
        lineEdit_11->setObjectName("lineEdit_11");
        lineEdit_11->setGeometry(QRect(140, 260, 131, 26));
        lineEdit_11->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    width: 150px;\n"
"    height: 150px;\n"
"    border: 3px solid rgb(245,245,245);\n"
"    border-radius: 6px;\n"
"    padding: 6px 12px;\n"
"    color: rgb(0,0,0);\n"
"    background-color: rgb(245,245,245); \n"
"}"));
        lineEdit_13 = new QLineEdit(groupBox_2);
        lineEdit_13->setObjectName("lineEdit_13");
        lineEdit_13->setGeometry(QRect(140, 320, 131, 26));
        lineEdit_13->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    width: 150px;\n"
"    height: 150px;\n"
"    border: 3px solid rgb(245,245,245);\n"
"    border-radius: 6px;\n"
"    padding: 6px 12px;\n"
"    color: rgb(0,0,0);\n"
"    background-color: rgb(245,245,245); \n"
"}"));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 110, 121, 20));
        label_10->setStyleSheet(QString::fromUtf8("background-color:rgb(41, 102, 148);\n"
"color: rgb(255, 255, 255)"));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 160, 63, 20));
        label_11->setStyleSheet(QString::fromUtf8("background-color:rgb(41, 102, 148);\n"
"color: rgb(255, 255, 255)"));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 210, 63, 20));
        label_12->setStyleSheet(QString::fromUtf8("background-color:rgb(41, 102, 148);\n"
"color: rgb(255, 255, 255)"));
        dateEdit_3 = new QDateEdit(groupBox_2);
        dateEdit_3->setObjectName("dateEdit_3");
        dateEdit_3->setGeometry(QRect(140, 200, 131, 31));
        dateEdit_3->setStyleSheet(QString::fromUtf8("QDateEdit {\n"
"    border: 3px solid rgb(245,245,245);\n"
"    border-radius: 6px;\n"
"    padding: 6px 12px;\n"
"    color: rgb(0,0,0);\n"
"    background-color: rgb(245,245,245); \n"
"}"));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 260, 81, 20));
        label_13->setStyleSheet(QString::fromUtf8("background-color:rgb(41, 102, 148);\n"
"color: rgb(255, 255, 255)"));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 320, 111, 20));
        label_14->setStyleSheet(QString::fromUtf8("background-color:rgb(41, 102, 148);\n"
"color: rgb(255, 255, 255)"));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 320, 111, 20));
        label_15->setStyleSheet(QString::fromUtf8("background-color:rgb(41, 102, 148);\n"
"color: rgb(255, 255, 255)"));
        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(10, 380, 141, 20));
        label_16->setStyleSheet(QString::fromUtf8("background-color:rgb(41, 102, 148);\n"
"color: rgb(255, 255, 255)"));
        radioButton_3 = new QRadioButton(groupBox_2);
        radioButton_3->setObjectName("radioButton_3");
        radioButton_3->setGeometry(QRect(160, 380, 110, 31));
        radioButton_3->setStyleSheet(QString::fromUtf8("QRadioButton {\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    padding-left: 8px;\n"
"background-color: rgb(41, 102, 148);\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"    border: 2px solid #3b82f6;\n"
"    border-radius: 6px;      /* rounded corners */\n"
"    background-color: white;  /* unchecked background */\n"
"}\n"
"\n"
"QRadioButton::indicator:checked {\n"
"    background-color: #FFD700;  /* blue fill when checked */\n"
"}"));
        radioButton_4 = new QRadioButton(groupBox_2);
        radioButton_4->setObjectName("radioButton_4");
        radioButton_4->setGeometry(QRect(160, 410, 161, 24));
        radioButton_4->setStyleSheet(QString::fromUtf8("QRadioButton {\n"
"    color: white;\n"
"    font-size: 14px;\n"
"    padding-left: 8px;\n"
"background-color: rgb(41, 102, 148);\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"    border: 2px solid #3b82f6;\n"
"    border-radius: 6px;      /* rounded corners */\n"
"    background-color: white;  /* unchecked background */\n"
"}\n"
"\n"
"QRadioButton::indicator:checked {\n"
"    background-color: #FFD700;  /* blue fill when checked */\n"
"}"));
        pushButton_6 = new QPushButton(groupBox_2);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(20, 440, 101, 41));
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_7 = new QPushButton(page_1);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(310, 90, 121, 29));
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        leditrech = new QLineEdit(page_1);
        leditrech->setObjectName("leditrech");
        leditrech->setGeometry(QRect(440, 90, 131, 31));
        leditrech->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    width: 150px;\n"
"    height: 150px;\n"
"    border: 3px solid rgb(245,245,245);\n"
"    border-radius: 6px;\n"
"    padding: 6px 12px;\n"
"    color: rgb(0,0,0);\n"
"    background-color: rgb(245,245,245); \n"
"}"));
        pushButton_8 = new QPushButton(page_1);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(600, 90, 121, 29));
        pushButton_8->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"}\n"
""));
        dateEdit_4 = new QDateEdit(page_1);
        dateEdit_4->setObjectName("dateEdit_4");
        dateEdit_4->setGeometry(QRect(720, 90, 131, 31));
        dateEdit_4->setStyleSheet(QString::fromUtf8("QDateEdit {\n"
"    border: 3px solid rgb(245,245,245);\n"
"    border-radius: 6px;\n"
"    padding: 6px 12px;\n"
"    color: rgb(0,0,0);\n"
"    background-color: rgb(245,245,245); \n"
"}"));
        tableWidget_2 = new QTableWidget(page_1);
        if (tableWidget_2->columnCount() < 7)
            tableWidget_2->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(300, 180, 711, 291));
        tableWidget_2->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
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
"}"));
        pushButton_10 = new QPushButton(page_1);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(670, 500, 221, 31));
        pushButton_10->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        lineEdit_supprimer = new QLineEdit(page_1);
        lineEdit_supprimer->setObjectName("lineEdit_supprimer");
        lineEdit_supprimer->setGeometry(QRect(400, 490, 151, 41));
        lineEdit_supprimer->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    width: 150px;\n"
"    height: 150px;\n"
"    border: 3px solid rgb(245,245,245);\n"
"    border-radius: 6px;\n"
"    padding: 6px 12px;\n"
"    color: rgb(0,0,0);\n"
"    background-color: rgb(245,245,245); \n"
"}"));
        pushButton = new QPushButton(page_1);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(570, 500, 51, 29));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
"}\n"
""));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete));
        pushButton->setIcon(icon);
        label = new QLabel(page_1);
        label->setObjectName("label");
        label->setGeometry(QRect(590, 160, 141, 21));
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    border: 2px solid black;           /* bordure noire, 2px */\n"
"    border-radius: 8px;\n"
"    background-color: rgb(41, 102, 148); /* m\303\252me couleur de fond */\n"
"    color: white;                       /* texte blanc */\n"
"    font-weight: bold;                  /* texte un peu gras */\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;    /* titre centr\303\251 */\n"
"    padding: 2px 10px;\n"
"}"));
        pushButton_3 = new QPushButton(page_1);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(930, 500, 51, 31));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #10b981;   /* normal state */\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 20px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
""));
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::GoDown));
        pushButton_3->setIcon(icon1);
        widget = new QWidget(page_1);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(860, 50, 120, 80));
        widget->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-image: url(\"C:/Users/mouna/Downloads/logo.png\");\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"    background-attachment: fixed;\n"
"}\n"
""));
        stackedWidget->addWidget(page_1);
        btnpage1 = new QPushButton(centralwidget);
        btnpage1->setObjectName("btnpage1");
        btnpage1->setGeometry(QRect(260, 10, 101, 41));
        btnpage1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid black;           /* bordure noire, 2px */\n"
"    border-radius: 8px;\n"
"    background-color: rgb(41, 102, 148); /* m\303\252me couleur de fond */\n"
"    color: white;                       /* texte blanc */\n"
"    font-weight: bold;                  /* texte un peu gras */\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;    /* titre centr\303\251 */\n"
"    padding: 2px 10px;\n"
"}"));
        btnpage2 = new QPushButton(centralwidget);
        btnpage2->setObjectName("btnpage2");
        btnpage2->setGeometry(QRect(360, 10, 111, 41));
        btnpage2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid black;           /* bordure noire, 2px */\n"
"    border-radius: 8px;\n"
"    background-color: rgb(41, 102, 148); /* m\303\252me couleur de fond */\n"
"    color: white;                       /* texte blanc */\n"
"    font-weight: bold;                  /* texte un peu gras */\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;    /* titre centr\303\251 */\n"
"    padding: 2px 10px;\n"
"}"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(970, -10, 251, 71));
        label_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    border: 2px solid black;           /* bordure noire, 2px */\n"
"    border-radius: 8px;\n"
"    background-color: rgb(41, 102, 148); /* m\303\252me couleur de fond */\n"
"    color: white;                       /* texte blanc */\n"
"    font-weight: bold;                  /* texte un peu gras */\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;    /* titre centr\303\251 */\n"
"    padding: 2px 10px;\n"
"}"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 30, 251, 581));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(20, 68, 211, 51));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(20, 230, 211, 51));
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_9 = new QPushButton(groupBox);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(20, 150, 211, 51));
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
        pushButton_11 = new QPushButton(groupBox);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(20, 390, 211, 51));
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
        pushButton_13 = new QPushButton(groupBox);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(20, 310, 211, 51));
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
        pushButton_12 = new QPushButton(groupBox);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(20, 480, 211, 51));
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
        MainWindow->setCentralWidget(centralwidget);
        label_2->raise();
        stackedWidget->raise();
        btnpage1->raise();
        btnpage2->raise();
        groupBox->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1318, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "stat", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Ajouter vente /Modifier vente", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "ID: ", nullptr));
        lineEdit_8->setText(QString());
        lineEdit_9->setText(QString());
        lineEdit_10->setText(QString());
        lineEdit_11->setText(QString());
        lineEdit_13->setText(QString());
        label_10->setText(QCoreApplication::translate("MainWindow", "taux TVA :", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251 :", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Date :", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "ID vendeur :", nullptr));
        label_14->setText(QString());
        label_15->setText(QCoreApplication::translate("MainWindow", "Montant total :", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Mode de paiement :", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "Esp\303\250ces", nullptr));
        radioButton_4->setText(QCoreApplication::translate("MainWindow", "Carte bancaire", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "valider", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "rechercher :", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "trier par :", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "n\302\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom du produit:", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Date:", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "ID vendeur:", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "CIN de Client:", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_2->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Montant total:", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_2->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", " Mode de paiement :", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Exportation format Excel", nullptr));
        lineEdit_supprimer->setText(QString());
        pushButton->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "liste des ventes", nullptr));
        pushButton_3->setText(QString());
        btnpage1->setText(QCoreApplication::translate("MainWindow", "vente", nullptr));
        btnpage2->setText(QCoreApplication::translate("MainWindow", "statistique", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "           Gestion des ventes", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Tableau de Bord", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Gestion des interventions", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "geston des Clients", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Gestion de stock", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Gestion des ventes", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "Gestion des Fournisseur", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "Gestion des employ\303\251e", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
