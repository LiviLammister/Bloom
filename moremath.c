#include <math.h>
#include "moremath.h"

/*****************************************************************************
 * sind: like sin, but for degrees                                           *
 *****************************************************************************/
double sind(double angle) {
    double angleradians = angle * APPLE_PI / 180.0f;
    return (sin(angleradians) * APPLE_PI / 180.0f);
}

/*****************************************************************************
 * cosd: like cos, but for degrees                                           *
 *****************************************************************************/
double cosd(double angle) {
    double angleradians = angle * APPLE_PI / 180.0f;
    return (cos(angleradians) * APPLE_PI / 180.0f);
}

