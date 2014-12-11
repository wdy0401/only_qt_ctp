/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_8;
    QPushButton *pushButton_10;
    QPushButton *pushButton_7;
    QPushButton *pushButton_9;
    QPushButton *pushButton_11;
    QTextEdit *textEdit;
    QTextBrowser *textBrowser;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QTextBrowser *textBrowser_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QFontComboBox *fontComboBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QComboBox *comboBox_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QFontComboBox *fontComboBox_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_7;
    QFontComboBox *fontComboBox_3;
    QHBoxLayout *horizontalLayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(998, 597);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_2->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        gridLayout_2->addWidget(pushButton_8, 0, 1, 1, 1);

        pushButton_10 = new QPushButton(centralWidget);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));

        gridLayout_2->addWidget(pushButton_10, 0, 2, 1, 1);

        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        gridLayout_2->addWidget(pushButton_7, 1, 0, 1, 1);

        pushButton_9 = new QPushButton(centralWidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        gridLayout_2->addWidget(pushButton_9, 1, 1, 1, 1);

        pushButton_11 = new QPushButton(centralWidget);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));

        gridLayout_2->addWidget(pushButton_11, 1, 2, 1, 1);


        horizontalLayout_2->addLayout(gridLayout_2);


        verticalLayout->addLayout(horizontalLayout_2);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setMinimumSize(QSize(0, 30));
        textEdit->setMaximumSize(QSize(16777215, 30));

        verticalLayout->addWidget(textEdit);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);


        horizontalLayout_4->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        textBrowser_2 = new QTextBrowser(centralWidget);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setMinimumSize(QSize(300, 0));
        textBrowser_2->setMaximumSize(QSize(500, 16777215));

        verticalLayout_2->addWidget(textBrowser_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 0, 0, 1, 1);

        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 1, 0, 1, 1);

        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        gridLayout->addWidget(pushButton_6, 1, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        horizontalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_5->addWidget(label_3);

        fontComboBox = new QFontComboBox(centralWidget);
        fontComboBox->setObjectName(QStringLiteral("fontComboBox"));
        fontComboBox->setMinimumSize(QSize(100, 0));
        fontComboBox->setMaximumSize(QSize(100, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(9);
        fontComboBox->setFont(font);
        fontComboBox->setContextMenuPolicy(Qt::DefaultContextMenu);
        fontComboBox->setIconSize(QSize(0, 0));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(9);
        font1.setKerning(false);
        font1.setStyleStrategy(QFont::NoAntialias);
        fontComboBox->setCurrentFont(font1);

        horizontalLayout_5->addWidget(fontComboBox);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_6->addWidget(label_4);

        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(100, 0));
        comboBox->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_6->addWidget(comboBox);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_7->addWidget(label_5);

        comboBox_2 = new QComboBox(centralWidget);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setMinimumSize(QSize(100, 0));
        comboBox_2->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_7->addWidget(comboBox_2);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_8->addWidget(label_6);

        fontComboBox_2 = new QFontComboBox(centralWidget);
        fontComboBox_2->setObjectName(QStringLiteral("fontComboBox_2"));
        fontComboBox_2->setMinimumSize(QSize(100, 0));
        fontComboBox_2->setMaximumSize(QSize(100, 16777215));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        fontComboBox_2->setCurrentFont(font2);

        horizontalLayout_8->addWidget(fontComboBox_2);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_9->addWidget(label_7);

        fontComboBox_3 = new QFontComboBox(centralWidget);
        fontComboBox_3->setObjectName(QStringLiteral("fontComboBox_3"));
        fontComboBox_3->setMinimumSize(QSize(100, 0));
        fontComboBox_3->setMaximumSize(QSize(100, 16777215));
        fontComboBox_3->setCurrentFont(font2);

        horizontalLayout_9->addWidget(fontComboBox_3);


        verticalLayout_4->addLayout(horizontalLayout_9);


        horizontalLayout_4->addLayout(verticalLayout_4);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));

        verticalLayout_3->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 998, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CTP_QUOTE_DISPLAY", 0));
        label->setText(QApplication::translate("MainWindow", "Quote info", 0));
        pushButton->setText(QApplication::translate("MainWindow", "start quote", 0));
        pushButton_8->setText(QApplication::translate("MainWindow", "add symbol", 0));
        pushButton_10->setText(QApplication::translate("MainWindow", "show symbol", 0));
        pushButton_7->setText(QApplication::translate("MainWindow", "stop quote", 0));
        pushButton_9->setText(QApplication::translate("MainWindow", "delete symbol", 0));
        pushButton_11->setText(QApplication::translate("MainWindow", "deleta all symbol", 0));
        label_2->setText(QApplication::translate("MainWindow", "Trade info", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "start trade", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "delete all order", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "insert order", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "show order", 0));
        pushButton_6->setText(QApplication::translate("MainWindow", "load order", 0));
        label_3->setText(QApplication::translate("MainWindow", "\345\220\210\347\272\246", 0));
        label_4->setText(QApplication::translate("MainWindow", "\344\271\260\345\215\226", 0));
        label_5->setText(QApplication::translate("MainWindow", "\345\274\200\345\271\263", 0));
        label_6->setText(QApplication::translate("MainWindow", "\344\273\267\346\240\274", 0));
        label_7->setText(QApplication::translate("MainWindow", "\346\211\213\346\225\260", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
