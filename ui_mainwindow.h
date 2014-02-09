/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Feb 9 13:28:05 2014
**      by: Qt User Interface Compiler version 4.8.2
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
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
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
    QPushButton *restartButton;
    QLabel *label_3;
    QLineEdit *toSkip;
    QTabWidget *tabWidget;
    QWidget *Fractaltab;
    QGraphicsView *graphicsView;
    QWidget *PlotTab;
    QCustomPlot *Plotter;
    QPlainTextEdit *plottedPoints;
    QPushButton *linearRegressionButton;
    QPushButton *savePlotPDF;
    QWidget *imageTab;
    QGraphicsView *imageTabGraphic;
    QProgressBar *progressBar;
    QLabel *StatusLabel;
    QPushButton *useScriptButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 794);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(20, 600, 391, 61));
        CreateMatrix = new QPushButton(centralWidget);
        CreateMatrix->setObjectName(QString::fromUtf8("CreateMatrix"));
        CreateMatrix->setGeometry(QRect(20, 560, 131, 27));
        clearMatrices = new QPushButton(centralWidget);
        clearMatrices->setObjectName(QString::fromUtf8("clearMatrices"));
        clearMatrices->setGeometry(QRect(160, 560, 111, 27));
        fractalGroupBox = new QGroupBox(centralWidget);
        fractalGroupBox->setObjectName(QString::fromUtf8("fractalGroupBox"));
        fractalGroupBox->setGeometry(QRect(430, 570, 581, 141));
        numPointsLabel = new QLabel(fractalGroupBox);
        numPointsLabel->setObjectName(QString::fromUtf8("numPointsLabel"));
        numPointsLabel->setGeometry(QRect(10, 20, 67, 17));
        lineEdit = new QLineEdit(fractalGroupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(80, 20, 111, 27));
        drawFractal = new QPushButton(fractalGroupBox);
        drawFractal->setObjectName(QString::fromUtf8("drawFractal"));
        drawFractal->setGeometry(QRect(220, 30, 97, 61));
        lineEdit_2 = new QLineEdit(fractalGroupBox);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(90, 50, 113, 25));
        label = new QLabel(fractalGroupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 50, 71, 16));
        lineEdit_3 = new QLineEdit(fractalGroupBox);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(90, 80, 113, 25));
        label_2 = new QLabel(fractalGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 80, 58, 15));
        label_2->setAlignment(Qt::AlignCenter);
        restartButton = new QPushButton(fractalGroupBox);
        restartButton->setObjectName(QString::fromUtf8("restartButton"));
        restartButton->setGeometry(QRect(320, 30, 94, 61));
        label_3 = new QLabel(fractalGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 110, 58, 15));
        toSkip = new QLineEdit(fractalGroupBox);
        toSkip->setObjectName(QString::fromUtf8("toSkip"));
        toSkip->setGeometry(QRect(90, 110, 113, 25));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 1021, 551));
        Fractaltab = new QWidget();
        Fractaltab->setObjectName(QString::fromUtf8("Fractaltab"));
        graphicsView = new QGraphicsView(Fractaltab);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(0, 10, 1011, 471));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        tabWidget->addTab(Fractaltab, QString());
        PlotTab = new QWidget();
        PlotTab->setObjectName(QString::fromUtf8("PlotTab"));
        Plotter = new QCustomPlot(PlotTab);
        Plotter->setObjectName(QString::fromUtf8("Plotter"));
        Plotter->setGeometry(QRect(0, 10, 691, 501));
        plottedPoints = new QPlainTextEdit(PlotTab);
        plottedPoints->setObjectName(QString::fromUtf8("plottedPoints"));
        plottedPoints->setGeometry(QRect(700, 10, 311, 471));
        linearRegressionButton = new QPushButton(PlotTab);
        linearRegressionButton->setObjectName(QString::fromUtf8("linearRegressionButton"));
        linearRegressionButton->setGeometry(QRect(866, 480, 141, 27));
        savePlotPDF = new QPushButton(PlotTab);
        savePlotPDF->setObjectName(QString::fromUtf8("savePlotPDF"));
        savePlotPDF->setGeometry(QRect(700, 480, 95, 27));
        tabWidget->addTab(PlotTab, QString());
        imageTab = new QWidget();
        imageTab->setObjectName(QString::fromUtf8("imageTab"));
        imageTabGraphic = new QGraphicsView(imageTab);
        imageTabGraphic->setObjectName(QString::fromUtf8("imageTabGraphic"));
        imageTabGraphic->setGeometry(QRect(10, 10, 1001, 511));
        tabWidget->addTab(imageTab, QString());
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(30, 680, 371, 23));
        progressBar->setValue(24);
        StatusLabel = new QLabel(centralWidget);
        StatusLabel->setObjectName(QString::fromUtf8("StatusLabel"));
        StatusLabel->setGeometry(QRect(40, 660, 55, 14));
        useScriptButton = new QPushButton(centralWidget);
        useScriptButton->setObjectName(QString::fromUtf8("useScriptButton"));
        useScriptButton->setGeometry(QRect(290, 560, 85, 27));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 29));
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
        QObject::connect(restartButton, SIGNAL(clicked()), MainWindow, SLOT(clear()));
        QObject::connect(linearRegressionButton, SIGNAL(clicked()), MainWindow, SLOT(onLinearRegression()));
        QObject::connect(useScriptButton, SIGNAL(clicked()), MainWindow, SLOT(onUseScriptClicked()));
        QObject::connect(savePlotPDF, SIGNAL(clicked()), MainWindow, SLOT(onSavePlottedPDF()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        CreateMatrix->setText(QApplication::translate("MainWindow", "Create Matrix", 0, QApplication::UnicodeUTF8));
        clearMatrices->setText(QApplication::translate("MainWindow", "Clear Matrices", 0, QApplication::UnicodeUTF8));
        fractalGroupBox->setTitle(QApplication::translate("MainWindow", "Controls", 0, QApplication::UnicodeUTF8));
        numPointsLabel->setText(QApplication::translate("MainWindow", "Points:", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("MainWindow", "100000", 0, QApplication::UnicodeUTF8));
        drawFractal->setText(QApplication::translate("MainWindow", "Draw", 0, QApplication::UnicodeUTF8));
        lineEdit_2->setText(QApplication::translate("MainWindow", "8", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Scale pow:", 0, QApplication::UnicodeUTF8));
        lineEdit_3->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "q:", 0, QApplication::UnicodeUTF8));
        restartButton->setText(QApplication::translate("MainWindow", "Restart", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Skip", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(Fractaltab), QApplication::translate("MainWindow", "Fractal Tab", 0, QApplication::UnicodeUTF8));
        linearRegressionButton->setText(QApplication::translate("MainWindow", "Linear Regression", 0, QApplication::UnicodeUTF8));
        savePlotPDF->setText(QApplication::translate("MainWindow", "Save PDF", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(PlotTab), QApplication::translate("MainWindow", "Plot Tab", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(imageTab), QApplication::translate("MainWindow", "Image Tab", 0, QApplication::UnicodeUTF8));
        StatusLabel->setText(QApplication::translate("MainWindow", "Status", 0, QApplication::UnicodeUTF8));
        useScriptButton->setText(QApplication::translate("MainWindow", "Script", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
