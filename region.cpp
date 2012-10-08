#include "region.h"
#include <stdlib.h>
FractalRegion::FractalRegion()
{
    length = 0;
}
FractalRegion::~FractalRegion() {

}
void FractalRegion::append(double *point) {
    this->length++;
}
void FractalRegion::cleanup() {

}
