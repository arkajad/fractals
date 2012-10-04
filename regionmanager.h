#ifndef FractalRegionMANAGER_H
#define FractalRegionMANAGER_H
#include <QObject>
#include <QHash>
#include <QDebug>
#include <QGraphicsScene>
#include "region.h"
class FractalRegionManager: public QObject
{
    Q_OBJECT
public:
    explicit FractalRegionManager(QObject *parent = 0);
    QHash<int,FractalRegion *> FractalRegions;
    FractalRegion * getFractalRegionById(int id);
    int assignFractalRegion(double * vector);
    double scale;
    int i_scale;
    int count;
    void init(double scale, int pscale);
    void report();
    int s_width;
    int s_height;
    float q;
    void drawRegions(QGraphicsScene * scene);
    void redistribute(double s,int new_pscale);
signals:
    void plotPoint(float x, float y);
public slots:
};

#endif // FractalRegionMANAGER_H
