#include "region.h"

FractalRegion::FractalRegion()
{
    length = 0;
}
FractalRegion::~FractalRegion() {

}
void FractalRegion::append(double *point) {
    this->points.append(point);
    this->length++;
}
