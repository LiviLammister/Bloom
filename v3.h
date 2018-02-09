/***************************************************************************
 * v3: struct representing a vertex or a vector and associated functions.  *
 ***************************************************************************/
#ifndef V3_H
#define V3_H

#define SIZE_OF_TRI 48

typedef struct V3 {
    float x,
          y,
          z;
} V3;

void v3_set(V3 *pV3, float pX, float pY, float pZ);

void v3_copy(V3 *valuesYouWant, V3 *whereYouWantThem);

void cross_product(V3 *crossProduct, V3 *point1, V3 *point2);

void invert(V3 *vectorToInvert);

#endif
