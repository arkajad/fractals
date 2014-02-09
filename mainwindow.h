#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QStringList>
#include <QDebug>
#include <QGraphicsTextItem>
#include "regionmanager.h"
#include <QVector>
#include <QScriptValue>
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
    Q_PROPERTY(QList<QList<double> > smatrices READ get_smatrices WRITE set_smatrices SCRIPTABLE true)
    double alpha;
    double the_d;
    QList<QList<double> > smatrices;
private:
    Ui::MainWindow *ui;

    double ** pPoints;
    int pPointsLength;
    QVector<double> plotter_x;
    QVector<double> plotter_y;
    QVector<double> plotter_x2;
    QVector<double> plotter_y2;


public slots:
    bool createMatrix(QString lines);
    void drawMatrices();
    void plotPoint(float x, float y);
    void plotPoint2(float x, float y);
    void drawPoint(double x, double y);
    void updateProgress(int c,int t);
    void onLinearRegression();
    QList<QList<double> > get_smatrices() { return this->smatrices; }
    void set_smatrices(QList<QList<double> >sm) { qDebug() << "Received: " << sm; this->smatrices = sm; }
    void setMatrices(QScriptValue v) {
        this->smatrices.clear();
        qDebug() << "Received QSV: " << v.toQObject();
         QList<QVariant> l1 = v.toVariant().toList();
         for ( int i = 0; i < l1.length(); i++ ) {
             QVariant val = l1.at(i);
             QList<QVariant> l2 = val.toList();
             QList<double> l3;
             for( int j = 0; j < l2.length(); j++ ) {
                 l3.append(l2.at(j).toDouble());
             }
             this->smatrices.append(l3);
         }
         qDebug() << this->smatrices;
    }
    void setAlpha(double a) { this->alpha = a; }
    void setD(double d) { this->the_d = d; }
    void clear();
private slots:
    void onCreateMatrixClicked();
    void onClearMatrices();
    void onDrawFractal();
    void onUseScriptClicked();
    void onSavePlottedPDF();
signals:
    void drawPointSignal(double x,double y);
};

#endif // MAINWINDOW_H
