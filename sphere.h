/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Sphere defined by center point and radius                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef SPHERE_H
#define SPHERE_H

#include "v3.h"

typedef struct Sphere {
    V3 center;
    double radius;
} Sphere;

void project_onto(V3 *point, Sphere *surface, V3 *projection);

#endif
