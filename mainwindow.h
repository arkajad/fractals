#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QStringList>
#include <QDebug>
#include <QGraphicsTextItem>
#include "regionmanager.h"
#include <QVector>
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
    QVector<double> plotter_x;
    QVector<double> plotter_y;
public slots:
    bool createMatrix(QString lines);
    void drawMatrices();
    void plotPoint(float x, float y);
private slots:
    void onCreateMatrixClicked();
    void onClearMatrices();
    void onDrawFractal();
};

#endif // MAINWINDOW_H
