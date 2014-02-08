#ifndef FRACTALWORKER_H
#define FRACTALWORKER_H

#include <QObject>
#include "regionmanager.h"
#include "region.h"
#include "math_functions.h"
class FractalWorker : public QObject
{
    Q_OBJECT
public:
    explicit FractalWorker(QObject *parent = 0);
    int num_points;
    double scale;
    int pscale;
    double q;
    double ** points;
    int skip;
    FractalRegionManager * rm;
    QList<QList<QVector<double> > > pMatrices;
    QList<QList<double> > smatrices;
    double alpha;
    double the_d;
signals:
    void plotPointSignal(float x, float y);
    void drawPointSignal(double x, double y);
    void finished();
    void error(QString err);
    void updateProgressSignal(int c,int t);
public slots:
    void process();
    void plotPointSlot(float x, float y);
    void drawPointSlot(double x, double y);
    void updateProgressSlot(int c,int t);
};

#endif // FRACTALWORKER_H
