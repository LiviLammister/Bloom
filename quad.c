#include "quad.h"
#include "tri.h"
#include "v3.h"

/*****************************************************************************
 * triangulate: splits Quad into two Tris                                    *
 *****************************************************************************/
void triangulate(Quad* quad, Tri* tri1, Tri* tri2) {
    // first triangle
    v3_copy(&quad->a, &tri1->a);
    v3_copy(&quad->b, &tri1->b);
    v3_copy(&quad->c, &tri1->c);
    generate_normal(tri1);
    // second triangle
    v3_copy(&quad->c, &tri2->a);
    v3_copy(&quad->d, &tri2->b);
    v3_copy(&quad->a, &tri2->c);
    generate_normal(tri2);
}
