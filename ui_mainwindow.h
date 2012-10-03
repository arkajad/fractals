/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Oct 2 23:21:03 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QPlainTextEdit *plainTextEdit;
    QPushButton *CreateMatrix;
    QPushButton *clearMatrices;
    QGroupBox *fractalGroupBox;
    QLabel *numPointsLabel;
    QLineEdit *lineEdit;
    QPushButton *drawFractal;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLineEdit *lineEdit_3;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 750);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 20, 1024, 531));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(20, 600, 391, 78));
        CreateMatrix = new QPushButton(centralWidget);
        CreateMatrix->setObjectName(QString::fromUtf8("CreateMatrix"));
        CreateMatrix->setGeometry(QRect(20, 560, 131, 27));
        clearMatrices = new QPushButton(centralWidget);
        clearMatrices->setObjectName(QString::fromUtf8("clearMatrices"));
        clearMatrices->setGeometry(QRect(160, 560, 111, 27));
        fractalGroupBox = new QGroupBox(centralWidget);
        fractalGroupBox->setObjectName(QString::fromUtf8("fractalGroupBox"));
        fractalGroupBox->setGeometry(QRect(430, 570, 421, 111));
        numPointsLabel = new QLabel(fractalGroupBox);
        numPointsLabel->setObjectName(QString::fromUtf8("numPointsLabel"));
        numPointsLabel->setGeometry(QRect(10, 30, 67, 17));
        lineEdit = new QLineEdit(fractalGroupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(90, 30, 111, 27));
        drawFractal = new QPushButton(fractalGroupBox);
        drawFractal->setObjectName(QString::fromUtf8("drawFractal"));
        drawFractal->setGeometry(QRect(260, 30, 97, 91));
        lineEdit_2 = new QLineEdit(fractalGroupBox);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(90, 60, 113, 25));
        label = new QLabel(fractalGroupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 60, 71, 16));
        lineEdit_3 = new QLineEdit(fractalGroupBox);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(90, 90, 113, 25));
        label_2 = new QLabel(fractalGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 90, 58, 15));
        label_2->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(CreateMatrix, SIGNAL(clicked()), MainWindow, SLOT(onCreateMatrixClicked()));
        QObject::connect(clearMatrices, SIGNAL(clicked()), MainWindow, SLOT(onClearMatrices()));
        QObject::connect(drawFractal, SIGNAL(clicked()), MainWindow, SLOT(onDrawFractal()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        CreateMatrix->setText(QApplication::translate("MainWindow", "Create Matrix", 0, QApplication::UnicodeUTF8));
        clearMatrices->setText(QApplication::translate("MainWindow", "Clear Matrices", 0, QApplication::UnicodeUTF8));
        fractalGroupBox->setTitle(QApplication::translate("MainWindow", "Fractals", 0, QApplication::UnicodeUTF8));
        numPointsLabel->setText(QApplication::translate("MainWindow", "Points:", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("MainWindow", "100", 0, QApplication::UnicodeUTF8));
        drawFractal->setText(QApplication::translate("MainWindow", "Draw", 0, QApplication::UnicodeUTF8));
        lineEdit_2->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Scale pow:", 0, QApplication::UnicodeUTF8));
        lineEdit_3->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "q:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
