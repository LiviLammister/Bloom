#include <stdlib.h>

#include "tri.h"
#include "v3.h"

/***************************************************************************
 * set: sets verticies and normal of the tri .                             *
 ***************************************************************************/
void tri_set(Tri *pTri, V3 *pA, V3 *pB, V3 *pC, V3 *pNorm) {
    v3_copy(pA, &pTri->a);
    v3_copy(pB, &pTri->b);
    v3_copy(pC, &pTri->c);
    v3_copy(pNorm, &pTri->norm);
}

/***************************************************************************
 * copy: takes valuesYouWant and puts them whereYouWantThem.               *
 ***************************************************************************/
void tri_copy(Tri *valuesYouWant, Tri *whereYouWantThem) {
    tri_set(whereYouWantThem, &valuesYouWant->a, \
                               &valuesYouWant->b, \
                               &valuesYouWant->c, \
                               &valuesYouWant->norm);
}

/***************************************************************************
 * calculate normal: calculates normal vector of Tri by averaging the      *
 *                   normals of it's vertices.                             *
 ***************************************************************************/
void generate_normal(Tri *pTri) {
    V3 *aNormal,
       *bNormal,
       *cNormal;

    aNormal = (V3 *) malloc(1);
    bNormal = (V3 *) malloc(1);
    cNormal = (V3 *) malloc(1);

    cross_product(aNormal, &pTri->b, &pTri->c);
    cross_product(bNormal, &pTri->c, &pTri->a);
    cross_product(cNormal, &pTri->a, &pTri->b);
    
    v3_set(&pTri->norm, (aNormal->x + bNormal->x + cNormal->x) / 3.0, \
                        (aNormal->y + bNormal->y + cNormal->y) / 3.0, \
                        (aNormal->z + bNormal->z + cNormal->z) / 3.0);

    free(aNormal);
    free(bNormal);
    free(cNormal);
}

/***************************************************************************
 * project z: projects triangle onto z axis                                *
 ***************************************************************************/
void tri_project_z(Tri *original, Tri *shadow) {
    tri_copy(original, shadow);
    shadow->a.z = 0.0;
    shadow->b.z = 0.0;
    shadow->c.z = 0.0;
}
