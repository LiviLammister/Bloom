/***************************************************************************
 * Tri: Triangular face of an STL defined by three verticies and a normal. *
 ***************************************************************************/
#ifndef TRI_H
#define TRI_H

#include <stdint.h>

#include "v3.h"

#define SIZE_OF_TRI 48

typedef struct Tri {
    V3 norm,
       a,
       b,
       c;
} Tri;

void tri_set(Tri *pTri, V3 *pA, V3 *pB, V3 *pC, V3 *pNorm);
void tri_copy(Tri *valuesYouWant, Tri *whereYouWantThem);

void generate_normal(Tri *pTri);
void generate_shadow(Tri *original, Tri *shadow);

#endif
