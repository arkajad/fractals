#ifndef FractalRegionMANAGER_H
#define FractalRegionMANAGER_H
#include <QHash>
#include <QDebug>
#include <QGraphicsScene>
#include "region.h"
class FractalRegionManager
{
public:
    FractalRegionManager();
    QHash<int,FractalRegion *> FractalRegions;
    FractalRegion * getFractalRegionById(int id);
    int assignFractalRegion(double * vector);
    double scale;
    int i_scale;
    int count;
    void init(double scale);
    void report();
    int s_width;
    int s_height;
    void drawRegions(QGraphicsScene * scene);
};

#endif // FractalRegionMANAGER_H
