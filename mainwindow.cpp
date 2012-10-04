#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math_functions.h"
#include "math.h"
#include "fractalworker.h"
#include <QThread>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->rm = new FractalRegionManager;
    this->connect(this->rm,SIGNAL(plotPoint(float,float)),SLOT(plotPoint(float,float)));
    connect(this,SIGNAL(drawPointSignal(double,double)),this,SLOT(drawPoint(double,double)));
    ui->Plotter->addGraph();
    ui->Plotter->yAxis->setRange(0,9);
    ui->Plotter->xAxis->setRange(-5,0);
    ui->Plotter->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->Plotter->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->progressBar->setValue(0);
    QString t1 = "0.5,0,0\n0,0.5,0\n0,0,1";
    QString t2 = "0.5,0,0.5\n0,0.5,0\n0,0,1";
    QString t3 = "0.5,0,0.25\n0,0.5,0.5\n0,0,1";
    createMatrix(t1);
    createMatrix(t2);
    createMatrix(t3);
    drawMatrices();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onCreateMatrixClicked() {

    QString text = ui->plainTextEdit->toPlainText();
    qDebug() << "onCreateMatrixClicked was called";
    createMatrix(text);
    drawMatrices();
}

bool MainWindow::createMatrix(QString text) {
    qDebug() << "create matirix called with " << text;
    QStringList lines = text.split("\n");
    QList<QVector<double> > matrix;
    for (int i = 0; i < lines.length();i++) {
        QStringList parts = lines.at(i).split(",");
        QVector<double> members;
        for (int j = 0; j < parts.length(); j++) {
            members.append(parts.at(j).toDouble());
        }
        qDebug() << "Appending line: " << parts;
        matrix.append(members);
    }
    this->pMatrices.append(matrix);
}
void MainWindow::drawMatrices() {
    qreal ypos = 0;
    QGraphicsScene * scene = new QGraphicsScene;
    scene->setSceneRect(0,0,ui->graphicsView->width() - 5,ui->graphicsView->height() - 5);
    QFont font;
    font.setPixelSize(23);
    font.setBold(false);
    font.setFamily("Calibri");
    QGraphicsTextItem * item = new QGraphicsTextItem;
    item->setFont(font);
    item->setPlainText("Matrices:\n");
    item->setPos(0,ypos);
    item->setTextWidth(200);
    scene->addItem(item);
    QString text;
    for (int i = 0; i < pMatrices.length(); i++) {
        text += "{\n";
        QList<QVector<double> > matrix = pMatrices.at(i);
        for (int j = 0; j < matrix.length(); j++) {
            QVector<double> v = matrix.at(j);
            text += "    [ ";
            for (int x = 0; x < v.size(); x++ ) {
                text += "    " + QString::number(v.at(x)) + " ";
                ypos += 10;
            }
            text += "    ]\n";
            ypos += 10;
        }
        text += "}\n\n";

        QGraphicsTextItem * item = new QGraphicsTextItem;
        //item->setFont(font);
        item->setPlainText(text);
        item->setPos(0,ypos);
        item->setTextWidth(400);
        scene->addItem(item);
        ypos += 20;
        text = "";
    }
    //qDebug() << "setting scene";
    ui->graphicsView->setScene(scene);
}
void MainWindow::onClearMatrices() {
    pMatrices.clear();
    drawMatrices();
}
void MainWindow::onDrawFractal() {
    int num_points = ui->lineEdit->text().toInt();
    //this->rm->init(0.5, ui->lineEdit_2->text().toInt());
    //this->rm->q = ui->lineEdit_3->text().toFloat();

    QFont font;
    font.setPixelSize(11);
    font.setBold(false);
    font.setFamily("Calibri");
    QGraphicsScene * scene = new QGraphicsScene;
    scene->setSceneRect(0,0,ui->graphicsView->width() - 5,ui->graphicsView->height() - 5);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scene()->clear();
    QThread* thread = new QThread;
    FractalWorker * worker = new FractalWorker;
    worker->num_points = num_points;
    worker->q = ui->lineEdit_3->text().toFloat();
    worker->pMatrices = this->pMatrices;
    worker->pscale = ui->lineEdit_2->text().toInt();
    worker->scale = 0.5;
    connect(worker,SIGNAL(drawPointSignal(double,double)),this,SLOT(drawPoint(double,double)));
    connect(worker,SIGNAL(plotPointSignal(float,float)),this,SLOT(plotPoint(float,float)));
    connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    connect(worker,SIGNAL(updateProgressSignal(int,int)),this,SLOT(updateProgress(int,int)));

    thread->start();
    qDebug() << "Returning from worker";
    return;
    int i;
    double vector[3];

    //qDebug() << "Created vectors";

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

    }
    //this->rm->drawRegions(scene);

    this->rm->report();
    delete worker;

}
void MainWindow::plotPoint(float x, float y) {
    plotter_x.append(x);
    plotter_y.append(y);;
    ui->Plotter->graph(0)->setData(plotter_x,plotter_y);
    ui->Plotter->replot();
}
void MainWindow::drawPoint(double x, double y) {
    double rad = 1;
    QGraphicsScene * scene = ui->graphicsView->scene();
    scene->addEllipse(x * scene->width(), (1.0 - y) * scene->height(), rad*2.0, rad*2.0,
                      QPen(), QBrush(Qt::SolidPattern));

}
void MainWindow::updateProgress(int c, int t) {
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(t);
    ui->progressBar->setValue(c);
}
