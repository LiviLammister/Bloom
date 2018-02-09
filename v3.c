#include "v3.h"

/***************************************************************************
 * set: sets x, y, and z values of V3                                      *
 ***************************************************************************/
void v3_set(V3 *pV3, float pX, float pY, float pZ) {
    pV3->x = pX;
    pV3->y = pY;
    pV3->z = pZ;
}

/***************************************************************************
 * copy: takes (the values from) valuesYouWant and puts them (in)          *
 *       whereYouWantThem.                                                 *
 ***************************************************************************/
void v3_copy(V3 *valuesYouWant, V3 *whereYouWantThem) {
    v3_set(whereYouWantThem, valuesYouWant->x, \
                             valuesYouWant->y, \
                             valuesYouWant->z);
}

/***************************************************************************
 * cross product: calculates the cross product of two vectors.             *
 ***************************************************************************/
void cross_product(V3 *crossProduct, V3 *point1, V3 *point2) {
    crossProduct->x = (point1->y * point2->z) - (point1->z * point2->y);
    crossProduct->y = (point1->z * point2->x) - (point1->x * point2->z);
    crossProduct->z = (point1->x * point2->y) - (point1->y * point2->x);
}

/***************************************************************************
 * invert: handy for flipping normals that are facing the wrong way        *
 ***************************************************************************/
void invert(V3 *vectorToInvert) {
    vectorToInvert->x *= -1.0;
    vectorToInvert->y *= -1.0;
    vectorToInvert->z *= -1.0;
}
