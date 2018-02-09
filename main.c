#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v3.h"
#include "tri.h"
#include "quad.h"
#include "sphere.h"
#include "moremath.h"

#define SIZE_OF_ATTRIB  2  // size of attribute byte count
#define SIZE_OF_FACE   50  // size of face in an STL
#define SIZE_OF_HEADER 80  // size of binary STL header

int main(void) {

    // Basic parameters //-----------------------------------------------------
    // TODO: Make these values user generated

    double offset = 1;
    double radius = 100;

    /*************************************************************************
     * Generate points (phyllotatic)                                         *
     *                                                                       *
     * Create phyllotactic spiral of points                                  *
     *************************************************************************/

    int numPoints;
    numPoints = (int)(radius/offset);

    double startingDist;
    startingDist = 10 * offset;

    V3* points;
    points = malloc(sizeof(V3) * numPoints);
    v3_set(&points[0], startingDist, 0, radius);
    
    double currAngle;
    currAngle = 0;

    double currRadius;
    currRadius = startingDist;
    
    int i;
    for (i=1; i<numPoints; i++) {
        currAngle -= GOLDEN_ANGLE;
        currRadius = currRadius + offset;
        points[i].x = currRadius*cosd(currAngle);
        points[i].y = currRadius*sind(currAngle);
        points[i].z = radius;
    }
    
    /*************************************************************************
     * Find closest point                                                    *
     *                                                                       *
     * TODO: Return to this in a later version to calculate correct          *
     *       parastichies for any given radius and offset.                   *
     *************************************************************************/
    /*
    double shortestDist; // shortest distance to first point
    shortestDist = sqrt(pow(points[0].x - points[1].x, 2) + \
                        pow(points[0].y - points[1].y, 2));

    double currDist;
    currDist = shortestDist;

    int closestPoint = 1;

    for (i=2; i<numPoints; i++) {
        currDist = sqrt(pow(points[i-1].x-points[i].y, 2) + \
                        pow(points[i-1].y-points[i].y, 2));
        if (currDist<shortestDist) {
            currDist = shortestDist;
            closestPoint = i;
        }
    }

    printf("%d\n", closestPoint);
    */

    /*************************************************************************
     * Projection                                                            *
     *                                                                       *
     * Projects points onto a hemisphere                                     *
     *************************************************************************/

    V3 origin;
    v3_set(&origin, 0.0, 0.0, 0.0);
    
    Sphere* surface;
    surface = malloc(sizeof(Sphere));
    surface->center = origin;
    surface->radius = 2;

    // General equation for a sphere: x^2+y^2+z^2 = r^2
    //   Therefore the new Z value is z = sqrt(r^2-x^2-y^2) 

    for (i=0; i<numPoints; i++) {
        points[i].z = sqrt(pow(surface->radius, 2)-\
                           pow(points[i].x, 2)-\
                           pow(points[i].y, 2));
    }

    /*************************************************************************
     * Generate Quads                                                        *
     *                                                                       *
     * Generates quads based on a (5,8) parastichy                           *
     * TODO: Change parastichy to best fit user input                        *
     *************************************************************************/

    int numQuads;
    numQuads = numPoints - 21;

    Quad* lattice;
    lattice = malloc(numQuads * sizeof(Quad));

    for (i=0; i<numQuads; i++) {
        lattice[i].a = points[i];
        lattice[i].b = points[i + 13];
        lattice[i].c = points[i + 21];
        lattice[i].d = points[i + 8];
    }
    
    /*************************************************************************
     * Spike                                                                 *
     *                                                                       *
     * Generates spikey surface                                              *
     *************************************************************************/

    V3* spikes;
    spikes = malloc(numQuads * sizeof(V3));

    V3 midpoint;

    double extOffset = 1.1;
    
    for (i=0; i<numQuads; i++) {

        // find midpoint of quad
        midpoint.x = ((lattice[i].a.x-lattice[i].c.x)/2)+lattice[i].c.x;
        midpoint.y = ((lattice[i].a.y-lattice[i].c.y)/2)+lattice[i].c.y;
        midpoint.z = ((lattice[i].a.z-lattice[i].c.z)/2)+lattice[i].c.z;
        
        printf("Midpoint %d: (%f, %f, %f)\n", \
               i, midpoint.x, midpoint.y, midpoint.z);

        // extend midpoint from center of sphere by offset
        midpoint.x *= extOffset;
        midpoint.y *= extOffset;
        midpoint.z *= extOffset;
        
        spikes[i] = midpoint;
        printf("Spike %d: (%f, %f, %f)\n\n", \
               i, spikes[i].x, spikes[i].y, spikes[i].z);
           
    }
    
    /*************************************************************************
     * Stitch                                                                *
     *                                                                       *
     * Stitches edges of extrusion to surface of sphere                      *
     *************************************************************************/

    int sizeOfExport;
    sizeOfExport = 4*numQuads;
    
    Tri* final;
    final = malloc(sizeOfExport*sizeof(Tri));

    for (i=0; i<numQuads; i++) {

        final[i*4].a = spikes[i];
        final[i*4].b = lattice[i].a;
        final[i*4].c = lattice[i].b;

        final[(i*4)+1].a = spikes[i];
        final[(i*4)+1].b = lattice[i].b;
        final[(i*4)+1].c = lattice[i].c;

        final[(i*4)+2].a = spikes[i];
        final[(i*4)+2].b = lattice[i].c;
        final[(i*4)+2].c = lattice[i].d;

        final[(i*4)+3].a = spikes[i];
        final[(i*4)+3].b = lattice[i].d;
        final[(i*4)+3].c = lattice[i].a;
    }

    /*************************************************************************
     * Triangulate                                                           *
     *                                                                       *
     * Not needed yet, but could be useful later                             *
     *************************************************************************/
    /*
    int sizeOfExport;
    sizeOfExport = finalSize * 2;

    Tri* triangulation;
    triangulation = malloc(sizeOfExport * sizeof(Tri));

    for (i=0; i<numQuads; i++) {
        triangulate(&final[i], \
                    &triangulation[2*i], \
                    &triangulation[(2*i) + 1]);
    }
    */
    /*************************************************************************
     * Import STL                                                            *
     *                                                                       *
     * This is in here simply to test the STL output                         *
     *************************************************************************/
    /*
    FILE *fp;
    fp = fopen("Massive_Ball.stl", "rb");

    Tri* stl = malloc(0);
    Tri curr;

    unsigned int numFaces;
    int index;

    // Read through file and rewind
    printf("Read through file and rewind\n");
    fseek(fp, 84, SEEK_SET);
    fseek(fp, SIZE_OF_FACE , SEEK_END);
    rewind(fp);

    // Move past 80 byte header and get number of faces
    printf("Move past 80 byte header and get number of faces\n");
    fseek(fp, SIZE_OF_HEADER, SEEK_SET);
    fread(&numFaces, sizeof(unsigned int), 1, fp);

    // Resize array to fit correct number of triangles
    printf("Resize array to fit correct number of triangles\n");
    stl = realloc(stl, numFaces * SIZE_OF_TRI);

    // Import faces
    printf("Import faces\n");
    for (index = 0; index < numFaces; index++) {
        fread(&curr, SIZE_OF_FACE, 1, fp);
        stl[index] = curr;
    }
    
    fclose(fp);
    */

    /*************************************************************************
     * Export STL                                                            *
     *************************************************************************/
    
    FILE *newfp;
    newfp = fopen("newSTL.stl","wb");
    
    const char *header;
    header = malloc(SIZE_OF_HEADER);
    const char *attribute;
    attribute = malloc(SIZE_OF_ATTRIB);

    // Write header
    fwrite(header, SIZE_OF_HEADER, 1, newfp);

    // Write number of faces
    unsigned int numFaces;
    numFaces = (unsigned int)sizeOfExport;
    fwrite(&numFaces, sizeof(unsigned int), 1, newfp);

    // Write faces
    for (i=0; i<sizeOfExport; i++) {
        // Write normal and vertices
        fwrite(&final[i], SIZE_OF_TRI, 1, newfp);
        // Write attribute byte count
        fwrite(attribute, SIZE_OF_ATTRIB, 1, newfp);
    }
    
    fclose(newfp);
    
    return 0;

}
