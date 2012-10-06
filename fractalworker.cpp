#include "fractalworker.h"
#include <QFont>

FractalWorker::FractalWorker(QObject *parent) :
    QObject(parent)
{
}
void FractalWorker::process() {
    int i;
    double vector[3];
    //qDebug() << "Created vectors";
    this->rm = new FractalRegionManager;
    this->connect(this->rm,SIGNAL(plotPoint(float,float)),SLOT(plotPointSlot(float,float)));
    this->rm->init(this->scale,this->pscale);
    this->rm->q = this->q;
    this->rm->num_points = this->num_points;

    for (i = 0; i < 2; i++) {
        vector[i] = (double) rand()/RAND_MAX;
    }
    //qDebug() << "Initialized vectors";
    vector[2] = 1.0;
    //qDebug() << "After initialization: x: " << QString::number(vector[0]) << " y: " << QString::number(vector[1]);
    //qDebug() << "Finale set to 1";
    for (i = 0; i < num_points; i++) {
        int m = randInt(1,pMatrices.length());
        //qDebug() << "m is " << QString::number(m);
        QList<QVector<double> > matrix = pMatrices.at(m-1);
        //qDebug() << "Extracted matrix";
        matrix_x_vector(matrix,&vector[0]);
        //qDebug() << "Adding point: x: " << QString::number(vector[0]) << " y: " << QString::number(vector[1]);
        emit drawPointSignal(vector[0],vector[1]);

        int id = this->rm->assignFractalRegion(vector);
        if (randInt(1,100) < 25) {
            emit updateProgressSignal(i,num_points);
        }

    }
    //this->rm->drawRegions(scene);

    this->rm->report();
    emit updateProgressSignal(100,100);

    // Now let's loop through and resize

    int start;
    int prog = 0;
    int total = this->pscale;
    for (start = this->pscale - 1; start > 0; start--) {
        this->rm->redistribute(0.5,start);
        this->rm->report();
        prog++;
        emit updateProgressSignal(prog,total);
    }
    emit updateProgressSignal(total,total);
}
void FractalWorker::plotPointSlot(float x, float y) {
    qDebug() << "Emitting plotPointSignal" << QString::number(x) << "," << QString::number(y);
    emit plotPointSignal(x,y);
}
void FractalWorker::drawPointSlot(double x, double y) {
    emit drawPointSignal(x,y);
}
void FractalWorker::updateProgressSlot(int c, int t) {
    emit updateProgressSignal(c,t);
}
