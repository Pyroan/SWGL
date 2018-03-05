#include "swgl.h"

/*************************************
 *          SWGL - A 3D API          *
 *   They said it couldn't be done.  *
 *************************************/

/***********************
 * Auxiliary Functions *
 ***********************/

/**
 * multiplies 4x4 matrices mat1 times mat2,
 * storing the result in mat 1. This works like OpenGL's glMultMtarix,
 * with the order mat1 X mat2
 */
void multMatrix4x4(myMat mat1, myMat mat2) {
}

/**
 * Multiplies 4x4 matrix mat times point vertex, returningthe result as
 * a new myVertex array.
 */
myVertex* transformVertex(myMat mat, myVertex vertex) {
}

/**
 * Performs the same operations as transformVertex, except it alters of the vertex
 * argument itself.
 */
void resetVertex(myMat mat, myVertex vertex) {
}

/**
 * Initializes 4x4 mat to the identity matrix.
 */
void initMat(myMat mat) {
}


/**************
 * Transforms *
 **************/

/**
 * Multiplies curMatrix times the corresponding
 * translation matrix and sets curMatrix to the product.
 */
void myTranslate(double dx, double dy, double dz) {
}

/**
 * Multiplies curMatrix times the corresponding scale
 * matrix and sets curMatrix to the product.
 */
void myScale(double sx, double sy, double sz) {
}

/**
 * Rotates θ degrees about the vector from the origin to (x, y, z)
 * a la OpenGL's glRotate(). myRotate multiplies curMatrix times the
 * corresponding rotation matrix and sets it to the product.
 * This is to be implemented using quaternions.
 */
void myRotate(double theta, double x, double y, double z) {
}


/**************
 * Primitives *
 **************/

/**
 * Draws a line from (x1, y1, z1) to (x2, y2, z2).
 */
void drawLine(myColor c, myVertex v1, myVertex v2) {
}

/**
 * Draws a polygon with numVertices vertices. vector is a 1D array
 * that holds the vertices as v1, v2, ..., vn. There must be at least
 * numVertices vertices in vector.
 */
void drawPolyv(myColor c, myVertex *vector, int numVertices) {
}



