#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math_functions.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
        ypos += 10;
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
        ypos += 10;
        QGraphicsTextItem * item = new QGraphicsTextItem;
        //item->setFont(font);
        item->setPlainText(text);
        item->setPos(0,ypos);
        item->setTextWidth(400);
        scene->addItem(item);
        ypos += 5;
        text = "";
    }
    qDebug() << "setting scene";
    ui->graphicsView->setScene(scene);
}
void MainWindow::onClearMatrices() {
    pMatrices.clear();
    drawMatrices();
}
void MainWindow::onDrawFractal() {
    int num_points = ui->lineEdit->text().toInt();
    pPoints = (double **)malloc(sizeof(double**) * num_points);
    pPointsLength = num_points;
    int i;
    double vector[3];
    double rad = 1;
    qDebug() << "Created vectors";
    QGraphicsScene * scene = new QGraphicsScene;
    scene->setSceneRect(0,0,ui->graphicsView->width() - 5,ui->graphicsView->height() - 5);
    for (i = 0; i < 2; i++) {
        vector[i] = (double) rand()/RAND_MAX;
    }
    qDebug() << "Initialized vectors";
    vector[2] = 1.0;
    qDebug() << "After initialization: x: " << QString::number(vector[0]) << " y: " << QString::number(vector[1]);
    qDebug() << "Finale set to 1";
    for (i = 0; i < num_points; i++) {
        int m = randInt(1,pMatrices.length());
        //qDebug() << "m is " << QString::number(m);
        QList<QVector<double> > matrix = pMatrices.at(m-1);
        //qDebug() << "Extracted matrix";
        matrix_x_vector(matrix,&vector[0]);
        qDebug() << "Adding point: x: " << QString::number(vector[0]) << " y: " << QString::number(vector[1]);
        scene->addEllipse((1.0 - vector[0]) * scene->width(), (1.0 - vector[1]) * scene->height(), rad*2.0, rad*2.0,
                          QPen(), QBrush(Qt::SolidPattern));
        pPoints[i] = (double *)malloc(sizeof(double) * 2);
        pPoints[i][0] = vector[0];
        pPoints[i][1] = vector[1];
    }
    ui->graphicsView->setScene(scene);
    for (i = 0; i < num_points; i++) {
         qDebug() << "Stored point is: " << QString::number(pPoints[i][0]);
    }
}
