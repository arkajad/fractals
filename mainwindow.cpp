#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math_functions.h"
#include "math.h"
#include "fractalworker.h"
#include <QThread>
#include <QFileDialog>
#include <QScriptEngine>
#include <QScriptValue>
#include <QMessageBox>
#define N(x) QString::number(x)
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->rm = new FractalRegionManager;
    this->connect(this->rm,SIGNAL(plotPoint(float,float)),SLOT(plotPoint(float,float)));
    connect(this,SIGNAL(drawPointSignal(double,double)),this,SLOT(drawPoint(double,double)));
    ui->Plotter->addGraph();
    ui->Plotter->yAxis->setRange(0,-14);
    ui->Plotter->xAxis->setRange(-12,0);
    QPen pen(Qt::black, 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen2(Qt::black, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    ui->Plotter->graph(0)->setPen(pen); // line color blue for first graph
    ui->Plotter->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 5)));
    ui->Plotter->addGraph();
    ui->Plotter->graph(1)->setPen(pen2); // line color blue for first graph
    ui->Plotter->graph(1)->setBrush(QBrush(QColor(0, 0, 255, 5)));


    ui->Plotter->xAxis2->setVisible(true);
    ui->Plotter->xAxis2->setTickLabels(false);
    ui->Plotter->yAxis2->setVisible(true);
    ui->Plotter->yAxis2->setTickLabels(false);

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
    QGraphicsScene * scene = new QGraphicsScene;
    scene->setSceneRect(0,0,ui->graphicsView->width(),ui->graphicsView->height() );
    QFont font;
    font.setPixelSize(12);
    font.setBold(false);
    font.setFamily("Calibri");

    QString text = "Matrices: \n";
    for (int i = 0; i < pMatrices.length(); i++) {
        text += "{\n";
        QList<QVector<double> > matrix = pMatrices.at(i);
        for (int j = 0; j < matrix.length(); j++) {
            QVector<double> v = matrix.at(j);
            text += "    [ ";
            for (int x = 0; x < v.size(); x++ ) {
                text += "    " + QString::number(v.at(x)) + " ";
            }
            text += "    ]\n";
        }
        text += "}\n\n";
    }
    QGraphicsTextItem * item = new QGraphicsTextItem;
    //item->setFont(font);
    item->setPlainText(text);
    item->setPos(10,10);
    item->setTextWidth(400);
    scene->addItem(item);
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
    scene->setSceneRect(0,0,ui->graphicsView->width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scene()->clear();
    QThread* thread = new QThread;
    FractalWorker * worker = new FractalWorker;
    worker->alpha = this->alpha;
    worker->smatrices = this->smatrices;
    worker->num_points = num_points;
    worker->q = ui->lineEdit_3->text().toFloat();
    worker->pMatrices = this->pMatrices;
    worker->pscale = ui->lineEdit_2->text().toInt();
    worker->scale = 0.5;
    worker->skip = ui->toSkip->text().toInt();
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
    QStringList points;
    for (int i = plotter_x.size() - 1; i > -1; i--) {
                points.append(N(plotter_x.at(i)) + "," + N(plotter_y.at(i)));
    }
    ui->plottedPoints->setPlainText(points.join(":\n"));
}
void MainWindow::plotPoint2(float x, float y) {
    plotter_x2.append(x);
    plotter_y2.append(y);;
    ui->Plotter->graph(1)->setData(plotter_x2,plotter_y2);
    ui->Plotter->replot();
}
void MainWindow::drawPoint(double x, double y) {
    double rad = 1;
    QGraphicsScene * scene = ui->graphicsView->scene();
    scene->addEllipse(x * (scene->width()-10), (1.0 - y) * (scene->height()-10), rad*2.0, rad*2.0,
                      QPen(), QBrush(Qt::SolidPattern));

}
void MainWindow::updateProgress(int c, int t) {
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(t);
    ui->progressBar->setValue(c);
}
void MainWindow::clear() {
    plotter_x.clear();
    plotter_y.clear();
    plotter_x2.clear();
    plotter_y2.clear();
    ui->Plotter->removeItem(0);
    ui->Plotter->graph(0)->setData(plotter_x,plotter_y);
    ui->Plotter->graph(1)->setData(plotter_x2,plotter_y2);
    ui->Plotter->replot();
    ui->graphicsView->scene()->clear();
    ui->plottedPoints->setPlainText("");
    ui->progressBar->setValue(0);

}

void MainWindow::onLinearRegression() {
    QTextCursor c = ui->plottedPoints->textCursor();
    QString text = c.selectedText();
    QStringList lines = text.split(":",QString::SkipEmptyParts);
    double ** list = (double **)malloc(sizeof(double *) * lines.length());
    int i = 0;
    double sum_x,sum_y;
    double smallest_x = 0.0;
    double largest_x = 0.0;

    sum_x = 0.0;
    sum_y = 0.0;
    foreach (QString line, lines) {
        QStringList parts = line.split(",");
        double * coords = new double[2];
        coords[0] = parts.at(0).toDouble();
        coords[1] = parts.at(1).toDouble();
        list[i] = coords;
        i++;

        sum_x += coords[0];
        sum_y += coords[1];
        if (smallest_x == 0.0) {
            smallest_x = coords[0];
        } else {
            if ( coords[0] < smallest_x) {
                smallest_x = coords[0];
            }
        }

        if (largest_x == 0.0) {
            largest_x = coords[0];
        } else {
            if ( coords[0] > largest_x) {
                largest_x = coords[0];
            }
        }
    }

    double sx_dvd = sum_x / lines.length();
    double sy_dvd = sum_y / lines.length();

    double * tmp_x = new double[lines.length()];
    double * tmp_y = new double[lines.length()];

    for (i = 0; i < lines.length();i++) {
        tmp_x[i] = list[i][0] - sx_dvd;
        tmp_y[i] = list[i][1] - sy_dvd;
    }

    double sx = 0;
    double sy = 0;
    double sxy = 0;
    for (i = 0; i < lines.length();i++) {
        sx += tmp_x[i] * tmp_x[i];
        sy += tmp_y[i] * tmp_y[i];
        sxy += tmp_x[i] * tmp_y[i];
    }

    double b = sxy / sx;
    double a = sy_dvd - b * sx_dvd;
    qDebug() << "b is: " << QString::number(b);

    QCPItemText *textLabel = new QCPItemText(ui->Plotter);
    ui->Plotter->removeItem(0);
    ui->Plotter->addItem(textLabel);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
    textLabel->setText("SLOPE = " + QString::number(b));
    textLabel->setFont(QFont(font().family(), 16)); // make font a bit larger
    textLabel->setPen(QPen(Qt::black));

    plotter_x2.clear();
    plotter_y2.clear();

    plotter_x2.append(smallest_x);
    plotter_y2.append(a + b * smallest_x);
    plotter_x2.append(largest_x);
    plotter_y2.append(a + b * largest_x);
    ui->Plotter->graph(1)->setData(plotter_x2,plotter_y2);
    ui->Plotter->replot();
    qDebug() << "Done";

}
void MainWindow::onUseScriptClicked() {
    qDebug() << "Clicked";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Files (*.*)"));
    qDebug() << "File is: " << fileName;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {

        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString script = in.readAll();
    file.close();
    qDebug() << "Script is: " << script;

    QScriptEngine interpreter;
    QScriptValue objectValue = interpreter.newQObject(this);
    interpreter.globalObject().setProperty("MainWindow", objectValue);
    interpreter.evaluate(script);
    if ( interpreter.hasUncaughtException() ) {
        qDebug() << interpreter.uncaughtException().toString();
        QMessageBox::critical(this,"There was an error", interpreter.uncaughtException().toString() + " at line: " + N(interpreter.uncaughtExceptionLineNumber()));
    }
}
