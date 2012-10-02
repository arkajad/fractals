#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QStringList>
#include <QDebug>
#include <QGraphicsTextItem>
#include "regionmanager.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    FractalRegionManager * rm;
private:
    Ui::MainWindow *ui;
    QList<QList<QVector<double> > > pMatrices;
    double ** pPoints;
    int pPointsLength;
public slots:
    bool createMatrix(QString lines);
    void drawMatrices();

private slots:
    void onCreateMatrixClicked();
    void onClearMatrices();
    void onDrawFractal();
};

#endif // MAINWINDOW_H
