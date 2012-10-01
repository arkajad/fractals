#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H
#include <QVector>
#include <QList>

static void matrix_x_vector(QList<QVector<double> > &matrix,double * vector) {
    vector[0] = (matrix.at(0).at(0) * vector[0]) +
                (matrix.at(0).at(1) * vector[1]) +
                (matrix.at(0).at(2) * vector[2]);
    vector[1] = (matrix.at(1).at(0) * vector[0]) +
                (matrix.at(1).at(1) * vector[1]) +
                (matrix.at(1).at(2) * vector[2]);
    vector[2] = 1;
}
static int randInt(int low, int high)
{
// Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}
#endif // MATH_FUNCTIONS_H
