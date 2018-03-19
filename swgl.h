#ifndef SWGL_H_
#define SWGL_H_

// Data types
typedef double myVertex[4];
typedef double myColor[3];
typedef double myMat[4][4];

// Global Vars
myMat curMatrix;

// Auxiliary functions
void multMatrix4x4(myMat mat1, myMat mat2);
myVertex* transformVertex(myMat mat, myVertex vertex);
void resetVertex(myMat mat, myVertex vertex);
void initMat (myMat mat);

// Transforms
void myTranslate(double dx, double dy, double dz);
void myScale(double sx, double sy, double sz);
void myRotate(double theta, double x, double y, double z);

// Primitives
void drawLine(myColor c, myVertex v1, myVertex v2);
void drawPolyv(myColor c, myVertex *vector, int numVertices);

#endif // SWGL_H_
