/*****************************************************************************
 * quad.h: struct representing a quadrilateral and its related functions.    *
 *****************************************************************************/
#ifndef QUAD_H
#define QUAD_H

#include "tri.h"
#include "v3.h"

typedef struct Quad {
    V3 a,
       b,
       c,
       d;
} Quad;

void triangulate(Quad* quad, Tri* tri1, Tri* tri2);

#endif 
