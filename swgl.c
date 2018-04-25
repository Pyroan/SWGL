#include "swgl.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


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
 * Rotates Î¸ degrees about the vector from the origin to (x, y, z)
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






// still WIP
/**************
 * Projection *
 **************/
 
 
//Matrices for projection
double projMatrix[3][3];
double viewMatrix[3][3];
myMat VRP;
typedef int OutCode;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

int xmin = 0;
int xmax = 0;
int ymin = 0;
int ymax = 0;
OutCode ComputeOutCode(double x, double y)
{
	OutCode code;

	code = INSIDE;          // initialised as being inside of [[clip window]]
	if (x < xmin)           // to the left of clip window
		code |= LEFT;
	else if (x > xmax)      // to the right of clip window
		code |= RIGHT;
	if (y < ymin)           // below the clip window
		code |= BOTTOM;
	else if (y > ymax)      // above the clip window
		code |= TOP;

	return code;
}

void convertToCanonical(){
 
}


// Cohen–Sutherland clipping algorithm clips a line from
// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with 
// diagonal from (xmin, ymin) to (xmax, ymax).
void CohenSutherlandLineClipAndDraw(double x0, double y0, double x1, double y1)
{
	// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
	OutCode outcode0 = ComputeOutCode(x0, y0);
	OutCode outcode1 = ComputeOutCode(x1, y1);
	int accept = 0;
  double x;
  double y;
  OutCode outcodeOut;
	while (accept==0) {
		if (!(outcode0 | outcode1)) {
			// bitwise OR is 0: both points inside window; trivially accept and exit loop
			accept = 1;
			break;
		} else if (outcode0 & outcode1) {
			// bitwise AND is not 0: both points share an outside zone (LEFT, RIGHT, TOP,
			// or BOTTOM), so both must be outside window; exit loop (accept is false)
			break;
		} else {
			// failed both tests, so calculate the line segment to clip
			// from an outside point to an intersection with clip edge
		

			// At least one endpoint is outside the clip rectangle; pick it.
			  outcodeOut = outcode0 ? outcode0 : outcode1;

				x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
				y = ymax;
			} 
      if (outcodeOut & BOTTOM) { // point is below the clip window
				x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
				y = ymin;
			} else if (outcodeOut & RIGHT) {  // point is to the right of clip window
				y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				x = xmax;
			} else if (outcodeOut & LEFT) {   // point is to the left of clip window
				y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}

			// move outside point to intersection point to clip
			if (outcodeOut == outcode0) {
				x0 = x;
				y0 = y;
				outcode0 = ComputeOutCode(x0, y0);
			} else {
				x1 = x;
				y1 = y;
				outcode1 = ComputeOutCode(x1, y1);
			}
		}
	
	if (accept == 1) {
		// Draw
	}
}

/*
*  general idea found
*  https://www.3dgep.com/understanding-the-view-matrix/

*/
void setVRC (double vrpx, double vrpy, double vrpz, double vpnx, double vpny, double vpnz, double upx, double upy, double upz){
/* 
  https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluLookAt.xml
  myMat M;
  double vecF[] = {(vpnx - vrpx), (vpny - vrpy ), (vpnz - vrpz)};
  double vecUP[] = {upx,upy,upz};
  // Normalize 
  double f = sqrt((vecF[0]*vecF[0])+(vecF[1]*vecF[1])+(vecF[2]*vecF[2]));
  double up = sqrt((vecUP[0]*vecUP[0])+(vecUP[1]*vecUP[1])+(vecUP[2]*vecUP[2]));

  // let s = f × UP ? , and u = s s × f . M is then constructed as follows: 
  // M = s ? 0 s ? 1 s ? 2 0 u ? 0 u ? 1 u ? 2 0 - f ? 0 - f ? 1 - f ? 2 0 0 0 0 1
  double s = f * up;
  double u = (s*s)*f;
*/
	viewMatrix[0][0] = vpnx;
	viewMatrix[0][1] = upx;
	viewMatrix[0][2] = vrpx;
 	viewMatrix[0][3] = 0;
	viewMatrix[1][0] = vpny;
	viewMatrix[1][1] = upy;
	viewMatrix[1][2] = vrpy;
 	viewMatrix[1][3] = 0;
	viewMatrix[2][0] = vpnz;
	viewMatrix[2][1] = upz;
	viewMatrix[2][2] = vrpz;
 	viewMatrix[2][3] = 0;
 	viewMatrix[3][0] = 0;
	viewMatrix[3][1] = 0;
	viewMatrix[3][2] = 0;
 	viewMatrix[3][3] = 1;


}

/* specifies projections. Type is PARALLEL or PERSPECTIVE; PRP specifies
 * the COP (DOP = CW - P RP). The view volume is symmetric about the x and y axes: It extends from
 * -width/2 = x = width/2, and from -height/2 = y = height/2.
*/
void setProjection (int type, double prpx, double prpy, double prpz, double width, double height, double front, double back) {


 // DOP = CW - PRP;
}
void setView(int xMin, int yMin, int xMax, int yMax){

}
//will use CohenSutherlandLineClipAndDraw
int clipLine(myVertex v1, myVertex v2, double xMin, double xMax, double yMin, double yMax) {
  
  
}
//will use CohenSutherlandLineClipAndDraw
int clipPolygon(myVertex *vector, double xMin, double xMax, double yMin, double yMax){

}
