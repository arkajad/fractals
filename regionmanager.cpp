#include "regionmanager.h"
#include <math.h>
#include <QGraphicsTextItem>
#include <QFont>
#include <QPainter>
#include <QImage>
#include <QBrush>
#include <QPen>
#include <QColor>
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
//        qDebug() << "Resizing region: " << QString::number(key);
        r = FractalRegions.value(key);
//        qDebug() << "r->id: " << N(r->id) << " i_scale: " << N(this->i_scale);
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
    float sum=0.0;
    if (this->q != 1) {
        foreach(int key,keys) {
            r = FractalRegions.value(key);
            // Here is where we do our calculations
            sum += pow(r->length,this->q);
        }

        float y = (log(sum)-(this->q)*log(num_points))/(this->q-1);
        float x = log(this->scale);
        emit plotPoint(x,y);
    } else {

        foreach(int key,keys) {
            r = FractalRegions.value(key);
            // Here is where we do our calculations
            sum += (r->length)*(log(r->length)-log(num_points));
         }
        sum=sum/num_points;
        float y = sum;
        float x = log(this->scale);
        emit plotPoint(x,y);
    }
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
void FractalRegionManager::drawImage() {
    QImage image(this->i_scale+1,this->i_scale+1,QImage::Format_RGB32);
//    qDebug() << "image width is: " << QString::number(i_scale) << " FractalRegionManager";
//    image.fill(Qt::white);
    image.fill(Qt::black);
    QPainter paint;
    paint.begin(&image);
    QList<int> keys = this->FractalRegions.keys();
    FractalRegion * r;
    int max_c = 0;
    foreach(int key,keys) {
        r = FractalRegions.value(key);
        if (r->length > max_c)
            max_c = log(log(r->length) + 1)+1;
//            max_c = r->length;
    }
    foreach(int key,keys) {
        r = FractalRegions.value(key);
        int y = this->i_scale - floor(r->id / this->i_scale);
        int x = (r->id % this->i_scale);
        double to_color = log(log((float)r->length)+1)+1;
         int hue = round(( (255 * (float)r->length) / (float)max_c));
//        int hue = round(( (255 * to_color) / (float)max_c));
        QPen b;
        QColor c;

        c.setHsv(hue,255,255);
        b.setColor(c);
        b.setWidth(1);
        paint.setPen(b);
        paint.drawPoint(x,y);
        image.scanLine(x)[y];
    }
    paint.end();
    image.save("./image.png");
}
