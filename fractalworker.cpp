#include "fractalworker.h"
#include <QFont>
#include <math.h>
FractalWorker::FractalWorker(QObject *parent) :
    QObject(parent)
{
    skip = 0;
}
void FractalWorker::process() {
    int i,j,k,m;
    double vector[3];
    //create also working vector that will be in (-1,1)x(-1,1)
    double w_vector[3];
    //qDebug() << "Created vectors";
    this->rm = new FractalRegionManager;
    this->connect(this->rm,SIGNAL(plotPoint(float,float)),SLOT(plotPointSlot(float,float)));
    this->rm->init(this->scale,this->pscale);
    this->rm->q = this->q;
    this->rm->num_points = this->num_points;

//    for (i = 0; i < 2; i++) {
//        vector[i] = (double) rand()/RAND_MAX;
//    }
    //qDebug() << "Initialized vectors";
    w_vector[0] = 0.784851; w_vector[1] = 0.536636; w_vector[2] = 0.30989;
    //qDebug() << "After initialization: x: " << QString::number(vector[0]) << " y: " << QString::number(vector[1]);
    //qDebug() << "Finale set to 1";
// ark's quantum changes
//    double vertices[][3] = {{-1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,-1.0},{0.0,0.0,1.0},{0.0,-1.0,0.0},
//                          {1.0,0.0,0.0}};
    double sq3 = 1/sqrt(3);
    double sq6 = 1/sqrt(6);
    //double vertices[][3] = {{-1,-sq3,-sq6},{1,-sq3,-sq6},{0,2*sq3,-sq6},{0,0,3*sq6}};

    double vertices[this->smatrices.length()][3];
    for ( int _i = 0; _i < this->smatrices.length(); _i++ ) {
        vertices[_i][0] = this->smatrices.at(_i).at(0);
        vertices[_i][1] = this->smatrices.at(_i).at(1);
        vertices[_i][2] = this->smatrices.at(_i).at(2);
    }
    int lv = this->smatrices.length();
    double new_vector[lv][3];
//    double a = 0.58;
    double a = this->alpha;
    double a1 = 1 - a*a;
    double a2 = 2*a;
    double * p = new double[lv];
    double * norm = new double[lv];
    double sum;
//  Initializing vertices
    for (i=0; i < lv; i++){
        for (j = 0; j < 3; j++) {
            vertices[i][j] = a*vertices[i][j];
        }
    }
    for (i = 0; i < num_points; i++) {
        if (i < this->skip && this->skip > 0) {
            continue;
        };
// create array of potentially transformed unnormalized vectors
        for(j = 0;j < lv; j++){
            for (k = 0; k < 3; k++){
             new_vector[j][k] = a1*w_vector[k]+2*(1 + vertices[j][0]*w_vector[0] + vertices[j][1]*w_vector[1] +
                                                vertices[j][2]*w_vector[2])*vertices[j][k];
//             qDebug() << "j = " << QString::number(j) << "k = " << QString::number(k) <<
//                         "nv[j,k] = " << QString::number(new_vector[j][k]);

            }
        }
// Calculate the norm of each new vector
        for (j = 0; j < lv; j++){
            norm[j] = sqrt(new_vector[j][0]*new_vector[j][0] + new_vector[j][1]*new_vector[j][1] +
                         new_vector[j][2]*new_vector[j][2]);
        }
// Calculate probabilities
        sum = 0;
        for (j = 0; j < lv; j++){sum += norm[j];
//            qDebug() << "j = " << QString::number(j) << "norm[j] " << QString::number(norm[j]);
        }
//        qDebug() << "sum = " << QString::number(sum);
        for(j = 0; j < lv; j++){
            p[j] = norm[j]/sum;
//            qDebug() << "p = " << QString::number(p[j]);
        }
// select one of the transformed vectors
        float random = (float)rand()/(float)RAND_MAX;
//        qDebug() << "in loop, random = " << QString::number(random);
        float p_tmp = 0;
        m = 0;
        for (j = 0; j < lv; j++) {
            m = j;
            p_tmp += p[j];
//        qDebug() << "j = " << QString::number(j);
            if (random < p_tmp) {
                break;
            }
        }
//        qDebug() << "m = " << QString::number(m);
// Define the new vector as the selected normalized vector:
        for (k = 0; k < 3; k++){
            w_vector[k] = new_vector[m][k]/norm[m];
// Vector to plot needs to be translated to (0,1)x(0,1):
            vector[k] = 0.5 * (1.0 + w_vector[k]);
//            qDebug() << "new vector x: " << QString::number(vector[0]);
//            qDebug() << "new vector y: " << QString::number(vector[1]);
        }

//        qDebug() << "Adding point: x: " << QString::number(vector[0]) << " y: " << QString::number(vector[1]);
        emit drawPointSignal(vector[0],vector[1]);

        if ( fabs(vector[0]) > this->the_d && fabs(vector[1]) > this->the_d) {
            int id = this->rm->assignFractalRegion(vector);
        }


        if (randInt(1,100) < 25) {
            emit updateProgressSignal(i,num_points);
        }

    }
    //this->rm->drawRegions(scene);
    this->rm->drawImage();
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
