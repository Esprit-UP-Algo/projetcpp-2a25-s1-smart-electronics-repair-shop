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
    QLabel *label_2;
    QLabel *label;
    QStackedWidget *stackedWidget_2;
    QWidget *page_3;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_7;
    QTableWidget *tableWidget;
    QComboBox *comboBox;
    QLabel *label_4;
    QPushButton *pushButton_9;
    QLineEdit *lineEdit_8;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QLineEdit *lineEdit_9;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_13;
    QLabel *label_12;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QWidget *widget;
    QLabel *label_14;
    QLineEdit *lineEdit_10;
    QLabel *label_15;
    QLineEdit *lineEdit_11;
    QWidget *page_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QLabel *label_3;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1331, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color:rgb(209,209,209);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 20, 331, 521));
        label_2->setStyleSheet(QString::fromUtf8("QLabel{\n"
" border: 2px solid black;   /* blue border */\n"
"    border-radius: 8px;\n"
" font-weight: bold;\n"
"    font-size: 14px;\n"
"background-color: rgb(41, 102, 148);}"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 0, 131, 31));
        label->setStyleSheet(QString::fromUtf8("QLabel{\n"
" border: 2px solid black;   /* blue border */\n"
"    border-radius: 8px;\n"
" font-weight: bold;\n"
"    font-size: 14px;\n"
"background-color: rgb(41, 102, 148);}"));
        stackedWidget_2 = new QStackedWidget(centralwidget);
        stackedWidget_2->setObjectName("stackedWidget_2");
        stackedWidget_2->setGeometry(QRect(350, 60, 971, 481));
        stackedWidget_2->setStyleSheet(QString::fromUtf8("QStackedWidget {\n"
"  border: 2px solid black;\n"
"  border-radius: 4px;\n"
"  padding: 4px;\n"
"}"));
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        label_5 = new QLabel(page_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 20, 331, 451));
        label_5->setStyleSheet(QString::fromUtf8("QLabel{\n"
" border: 2px solid black;   /* blue border */\n"
"    border-radius: 8px;\n"
" font-weight: bold;\n"
"    font-size: 14px;\n"
"background-color: rgb(41, 102, 148);}"));
        label_6 = new QLabel(page_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(40, 0, 191, 31));
        label_6->setStyleSheet(QString::fromUtf8("QLabel{\n"
" border: 2px solid black;   /* blue border */\n"
"    border-radius: 8px;\n"
" font-weight: bold;\n"
"    font-size: 14px;\n"
"background-color: rgb(41, 102, 148);}"));
        lineEdit = new QLineEdit(page_3);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(150, 50, 171, 31));
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
"}\n"
""));
        lineEdit_2 = new QLineEdit(page_3);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(150, 90, 171, 31));
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
        lineEdit_3 = new QLineEdit(page_3);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(150, 130, 171, 31));
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
"}\n"
""));
        lineEdit_4 = new QLineEdit(page_3);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(150, 170, 171, 31));
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
"}\n"
""));
        lineEdit_5 = new QLineEdit(page_3);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(150, 210, 171, 31));
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
"}\n"
""));
        lineEdit_7 = new QLineEdit(page_3);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setGeometry(QRect(150, 250, 171, 31));
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
"}\n"
""));
        tableWidget = new QTableWidget(page_3);
        if (tableWidget->columnCount() < 11)
            tableWidget->setColumnCount(11);
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
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(345, 110, 591, 301));
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
"}"));
        comboBox = new QComboBox(page_3);
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(780, 10, 81, 41));
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
        label_4 = new QLabel(page_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(580, 70, 161, 41));
        label_4->setStyleSheet(QString::fromUtf8("QLabel{\n"
" border: 2px solid black;   /* blue border */\n"
"    border-radius: 8px;\n"
" font-weight: bold;\n"
"    font-size: 14px;\n"
"background-color: rgb(41, 102, 148);}"));
        pushButton_9 = new QPushButton(page_3);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(660, 10, 111, 41));
        pushButton_9->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        lineEdit_8 = new QLineEdit(page_3);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setGeometry(QRect(480, 10, 171, 41));
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
"}\n"
""));
        pushButton_10 = new QPushButton(page_3);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(350, 10, 121, 41));
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
        pushButton_11 = new QPushButton(page_3);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(640, 420, 181, 41));
        pushButton_11->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_12 = new QPushButton(page_3);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(860, 420, 61, 41));
        pushButton_12->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::GoDown));
        pushButton_12->setIcon(icon);
        lineEdit_9 = new QLineEdit(page_3);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(360, 420, 171, 41));
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
"}\n"
""));
        pushButton_13 = new QPushButton(page_3);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(540, 420, 41, 41));
        pushButton_13->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete));
        pushButton_13->setIcon(icon1);
        pushButton_14 = new QPushButton(page_3);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(50, 430, 201, 31));
        pushButton_14->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        label_7 = new QLabel(page_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 60, 63, 20));
        label_7->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        label_8 = new QLabel(page_3);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 90, 63, 20));
        label_8->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        label_9 = new QLabel(page_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 130, 121, 20));
        label_9->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        label_10 = new QLabel(page_3);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 210, 101, 20));
        label_10->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        label_11 = new QLabel(page_3);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(10, 170, 111, 20));
        label_11->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        label_13 = new QLabel(page_3);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 250, 121, 20));
        label_13->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        label_12 = new QLabel(page_3);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(20, 370, 63, 20));
        label_12->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        radioButton = new QRadioButton(page_3);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(140, 370, 111, 25));
        radioButton->setStyleSheet(QString::fromUtf8("QRadioButton {\n"
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
        radioButton_2 = new QRadioButton(page_3);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(140, 400, 111, 25));
        radioButton_2->setStyleSheet(QString::fromUtf8("QRadioButton {\n"
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
        widget = new QWidget(page_3);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(869, 10, 81, 81));
        widget->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-image: url(\"C:/Users/USER/Downloads/image7.png\");\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}\n"
""));
        label_14 = new QLabel(page_3);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 300, 63, 20));
        label_14->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_10 = new QLineEdit(page_3);
        lineEdit_10->setObjectName("lineEdit_10");
        lineEdit_10->setGeometry(QRect(150, 290, 171, 31));
        lineEdit_10->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        label_15 = new QLabel(page_3);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 330, 131, 20));
        label_15->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 102, 148);"));
        lineEdit_11 = new QLineEdit(page_3);
        lineEdit_11->setObjectName("lineEdit_11");
        lineEdit_11->setGeometry(QRect(150, 330, 171, 31));
        lineEdit_11->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
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
        stackedWidget_2->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        stackedWidget_2->addWidget(page_4);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(30, 60, 281, 51));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(30, 220, 281, 51));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(30, 140, 281, 51));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(30, 390, 281, 51));
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
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(30, 310, 281, 51));
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
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(30, 470, 281, 51));
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(960, 10, 361, 51));
        label_3->setStyleSheet(QString::fromUtf8("QLabel{\n"
" border: 2px solid black;   /* blue border */\n"
"    border-radius: 8px;\n"
" font-weight: bold;\n"
"    font-size: 34px;\n"
"background-color: rgb(41, 102, 148);}\n"
""));
        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(350, 20, 141, 41));
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(490, 20, 121, 41));
        pushButton_8->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        MainWindow->setCentralWidget(centralwidget);
        stackedWidget_2->raise();
        label_2->raise();
        label->raise();
        pushButton->raise();
        pushButton_2->raise();
        pushButton_3->raise();
        pushButton_4->raise();
        pushButton_5->raise();
        pushButton_6->raise();
        label_3->raise();
        pushButton_7->raise();
        pushButton_8->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1331, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Tableau De Bord", nullptr));
        label_5->setText(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "Ajout/Modif Fournisseur", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "CIN", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Contrat", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Commande", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Numero", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "commande", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Type de produit", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Facture", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "livraison-R\303\251ception", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Sexe", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "   A-Z", nullptr));

        label_4->setText(QCoreApplication::translate("MainWindow", "Liste Des Fournisseurs", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Trier", nullptr));
        lineEdit_8->setText(QCoreApplication::translate("MainWindow", "Rechercher parCIN", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Rechercher:", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Exporter format Exel", nullptr));
        pushButton_12->setText(QString());
        lineEdit_9->setText(QCoreApplication::translate("MainWindow", "Supprimer par CIN", nullptr));
        pushButton_13->setText(QString());
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "Valider le Fournisseur", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "NOM", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "CIN Fournisseur", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Commande", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Contrat", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Type de Produit", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Sexe", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "Homme", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Femme", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Facture", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Livraison/R\303\251ception", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Gestion Des Interventions", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Gestion Des Employ\303\251es", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Gestion De Stock", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Gestion Des Fournisseurs", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Gestion Des Clients", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Gestion Des Ventes", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Gestion Fournisseur", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Fournisseurs", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Stastique", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
