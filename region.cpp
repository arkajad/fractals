#include "region.h"
#include <stdlib.h>
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
void FractalRegion::cleanup() {

    this->points.clear();
}
