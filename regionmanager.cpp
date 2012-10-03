#include "regionmanager.h"
#include <math.h>
#include <QGraphicsTextItem>
#include <QFont>

FractalRegionManager::FractalRegionManager(QObject *parent) :
    QObject(parent)
{
}
FractalRegion * FractalRegionManager::getFractalRegionById(int id) {
    QHash<int, FractalRegion *>::const_iterator i = FractalRegions.find(id);
    if (i == FractalRegions.end()) {
        FractalRegion * r = new FractalRegion;
        r->id = id;
        FractalRegions.insert(id,r);

        count++;
        return r;
    } else {
        return i.value();
    }
}
void FractalRegionManager::init(double s,int pscale) {
    this->scale = pow(s,pscale);
    this->i_scale = round(1/this->scale);
    count = 0;
}

int FractalRegionManager::assignFractalRegion(double *vector) {
    qDebug() << "Assigning regions for: " << QString::number(vector[0]);
    qDebug() << "Scale is: " << QString::number(scale) << " i_scale is: " << QString::number(i_scale);
    int id = floor(vector[0]*i_scale) + floor(vector[1]*i_scale) * i_scale;
    qDebug() << "ID is: " << QString::number(id);
    FractalRegion * r = this->getFractalRegionById(id);
    r->append(vector);
    return r->id;
}
void FractalRegionManager::report() {
    qDebug() << "FractalRegion Manager Report: ";
    qDebug() << "FractalRegion manager has " << QString::number(this->count) << " FractalRegions";

    QList<int> keys = this->FractalRegions.keys();
    FractalRegion * r;
    float sum;
    foreach(int key,keys) {
        r = FractalRegions.value(key);
        qDebug() << "Legth: " << QString::number(r->length);
        // Here is where we do our calculations
        sum += pow(r->length,this->q);
        // here is where we cleanup after ourselves
        r->cleanup();
    }
    float y = log10(sum);
    float x = log10(this->scale);
    qDebug() << QString::number(y) << " = log10(" << QString::number(sum) << ") y";
    qDebug() << QString::number(x) << " = log10(" << QString::number(this->scale) << ") x";
    emit plotPoint(x,y);
    // And then we clean it up
    this->FractalRegions.clear();
}
void FractalRegionManager::drawRegions(QGraphicsScene *scene) {

    for (int i = 1; i < i_scale; i++ ) {
        int sx,ex,sy,ey;
        sx = 0;
        sy = i * scene->height() * scale;
        ex = scene->width();
        ey = i * scene->height() * scale;
        scene->addLine(sx,sy,ex,ey,QPen());



        sx = i * scene->width() * scale;
        sy = 0;
        ex = i * scene->width() * scale;
        ey = scene->height();
        scene->addLine(sx,sy,ex,ey,QPen());


    }
}
