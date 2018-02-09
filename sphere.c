#include <math.h>

#include "sphere.h"
#include "v3.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * project onto: projects point onto the surface of a sphere                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void project_onto(V3 *point, Sphere *surface, V3 *projection) {
    // get distance from point to center of sphere (always at origin)
    double originalDist;
    originalDist = fabs(sqrt(pow(point->x, 2) + \
                             pow(point->y, 2) + \
                             pow(point->z, 2)));
    
    // scale length of vector so it is equal to the radius of the circle
    double scalar = surface->radius / originalDist;
    projection->x = scalar * point->x;
    projection->y = scalar * point->y;
    projection->z = scalar * point->z;
}

