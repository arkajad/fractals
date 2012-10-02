#ifndef FractalRegion_H
#define FractalRegion_H
#include <QList>
class FractalRegion
{
public:
    FractalRegion();
    ~FractalRegion();
    QList<double *> points;
    int length;
    int id;
    void append(double * point);
};

#endif // FractalRegion_H
