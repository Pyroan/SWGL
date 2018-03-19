#include "swgl.h"
#include <math.h>

/*************************************
 *          SWGL - A 3D API          *
 *   They said it couldn't be done.  *
 *************************************/

/***********************
 * Auxiliary Functions *
 ***********************/

/**
 * multiplies 4x4 matrices mat1 times mat2,
 * storing the result in mat 1. This works like OpenGL's glMultMatrix,
 * with the order mat1  X mat2
 */
void multMatrix4x4(myMat mat1, myMat mat2) {
	myMat newMat;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			double sum = 0;
			// sum(mat1[i][0:4] * mat2[0:4][j])
			for (int k = 0; k < 4; k++) {
				sum += (mat1[i][k] * mat2[k][j]);
			}
			newMat[i][j] = sum;
		}
	}
	// copy newMat over to mat1
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mat1[i][j] = newMat[i][j];
		}
	}
}

/**
 * Multiplies 4x4 matrix mat times point vertex, returning the result as
 * a new myVertex array.
 */
myVertex* transformVertex(myMat mat, myVertex vertex) {
/*	myVertex newv;
	for (int i = 0; i < 4; i++) {
		double sum = 0;
		for (int j = 0; j < 4; j++) {
			sum += mat[i][j] * vertex[j];
		}
		newv[i] = sum;
	}
	return newv;
*/ }

/**
 * Performs the same operations as transformVertex, except it alters the vertex
 * argument itself. Not preferred. Probably unnecessary. But it's way easier tho.
 */
void resetVertex(myMat mat, myVertex vertex) {
	myVertex v;
	for (int i = 0; i < 4; i++) {
		double sum = 0;
		for (int j = 0; j < 4; j++) {
			sum += mat[i][j] * vertex[j];
		}
		v[i] = sum;
	}
	for (int i = 0; i < 4; i++)
		vertex[i] = v[i];
}

/**
 * Initializes 4x4 mat to the identity matrix.
 */
void initMat(myMat mat) {
	// Basically pretending it's a 1d matrix with a 1 at every 5th index.
	for (int i = 0; i < 16; i++) {
		if (i % 5 == 0) {
			mat[i/4][i%4] = 1;
		} else {
			mat[i/4][i%4] = 0;
		}
	}
}


/**************
 * Transforms *
 **************/

/**
 * Multiplies curMatrix times the corresponding
 * translation matrix and sets curMatrix to the product.
 */
void myTranslate(double dx, double dy, double dz) {
	// Construct the translation matrix
	myMat mat;
	initMat(mat);
	mat[0][3] = dx;
	mat[1][3] = dy;
	mat[2][3] = dz;
	// Multiply curMatrix by it (and store it in curMatrix).
	multMatrix4x4(curMatrix, mat);
}

/**
 * Multiplies curMatrix times the corresponding scale
 * matrix and sets curMatrix to the product.
 */
void myScale(double sx, double sy, double sz) {
	// Construct scale matrix
	myMat mat;
	initMat(mat);
	mat[0][0] = sx;
	mat[1][1] = sy;
	mat[2][2] = sz;
	// Multiply curMatrix by it (and store it in curMatrix).
	multMatrix4x4(curMatrix, mat);
}

/**
 * Rotates θ degrees about the vector from the origin to (x, y, z)
 * a la OpenGL's glRotate(). myRotate multiplies curMatrix times the
 * corresponding rotation matrix and sets it to the product.
 * This is to be implemented using quaternions.
 */
void myRotate(double theta, double x, double y, double z) {
	// Normalize [x, y, z]
	double magnitude = sqrt((x*x)+(y*y)+(z*z));
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
	// Construct the quaternion rotation matrix (for there is but one).'
	// I can't think of a non-brute force way to do this so prepare for obtuse code.
	// Actual problem: The Quaternion matrix is 3x3.
	myMat rot;
	initMat(rot);
	double ct = cos(theta * (M_PI / 180.0)); // Cosine of theta
	double st = sin(theta * (M_PI / 180.0)); // Sine of theta
	rot[0][0] = (x*x) * (1 - ct) + ct;
	rot[0][1] = (x*y) * (1 - ct) - (z * st);
	rot[0][2] = (x*z) * (1 - ct) + (y * st);
	rot[1][0] = (y*x) * (1 - ct) + (z * st);
	rot[1][1] = (y*y) * (1 - ct) + ct;
	rot[1][2] = (y*z) * (1 - ct) - (x * st);
	rot[2][0] = (z*x) * (1 - ct) - (y * st);
	rot[2][1] = (z*y) * (1 - ct) + (x * st);
	rot[2][2] = (z*z) * (1 - ct) + ct;
	
	multMatrix4x4(curMatrix, rot);
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



