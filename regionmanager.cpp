#include "regionmanager.h"
#include <math.h>
#include <QGraphicsTextItem>
#include <QFont>
#define N(x) QString::number(x)
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
    qDebug() << "rm->init called with " << QString::number(s) << "," << QString::number(pscale);
    this->scale = pow(s,pscale);
    this->i_scale = round(1/this->scale);
    qDebug() << "at start, i_scale == " << N(this->i_scale);
    count = 0;
}
void FractalRegionManager::redistribute(double s,int new_pscale) {
    qDebug() << "New pscale is: " << QString::number(new_pscale) ;
    QHash<int,FractalRegion *> new_fractal_regions;
    this->scale = pow(s,new_pscale);
    this->i_scale = round(1/this->scale);
    this->count = 0;
    QList<int> keys = this->FractalRegions.keys();
    FractalRegion * r;
    FractalRegion * new_region;
    foreach(int key,keys) {
        qDebug() << "Resizing region: " << QString::number(key);
        r = FractalRegions.value(key);
        qDebug() << "r->id: " << N(r->id) << " i_scale: " << N(this->i_scale);
        int new_id = floor( r->id / (2 * this->i_scale) ) * (this->i_scale / 2) + ( floor( (r->id % this->i_scale) / 2 ) );
        QHash<int, FractalRegion *>::const_iterator new_region_iterator = new_fractal_regions.find(new_id);
        if ( new_region_iterator == new_fractal_regions.end() ) {
            new_region = new FractalRegion;
            new_region->id = new_id;
            new_region->length = 0;
            new_region->length += r->length;
            new_fractal_regions.insert(new_id,new_region);
            count++;
        } else {
            new_region = new_region_iterator.value();
            new_region->length += r->length;
        }
        //r->cleanup();
    }
    FractalRegions.clear();
    keys = new_fractal_regions.keys();
     foreach(int key,keys) {
         FractalRegions.insert(key,new_fractal_regions.value(key));
     }

}

int FractalRegionManager::assignFractalRegion(double *vector) {

    int id = floor(vector[0]*i_scale) + floor(vector[1]*i_scale) * i_scale;
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
        // Here is where we do our calculations
        sum += pow(r->length,this->q);
        // here is where we cleanup after ourselves
        r->cleanup();
    }
    float y = log10(sum);
    float x = log10(this->scale);
    emit plotPoint(x,y);
    // And then we clean it up
    //this->FractalRegions.clear();
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
