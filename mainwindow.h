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
    QList<QList<QVector<double> > > pMatrices;
private:
    Ui::MainWindow *ui;

    double ** pPoints;
    int pPointsLength;
    QVector<double> plotter_x;
    QVector<double> plotter_y;
public slots:
    bool createMatrix(QString lines);
    void drawMatrices();
    void plotPoint(float x, float y);
    void drawPoint(double x, double y);
    void updateProgress(int c,int t);
    void clear();
private slots:
    void onCreateMatrixClicked();
    void onClearMatrices();
    void onDrawFractal();
signals:
    void drawPointSignal(double x,double y);
};

#endif // MAINWINDOW_H
