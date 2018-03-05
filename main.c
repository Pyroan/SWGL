#include "swgl.h"
#include <stdio.h>

void example() {
/*
	myVertex v1 = {0.0, 0.0, 0.0, 1.0};
	myVertex v2 = {10.0, 5.0, 0.0, 1.0};
	
	myVertex v3 = {10.0, 5.0, -3.0, 1.0};
	myVertex v4 = {12.0, 8.0, -4.0, 1.0};
	myVertex v5 = {6.0, 12.0, -5.0, 1.0};

	myVertex *vector1 = {v3, v4, v5};

	myColor c1 = {1.0, 0.0, 0.0};
	myColor c2 = {5.0, 0.0, 0.5};

	setView(10, 50, 60, 100);

	// Default OpenGL case
	setVRC(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);

	setProjection(PARALLEL, 0.0, 0.0, 1.0, 30.0, 30.0, 0.0, 10.0);

	myTranslate(2.0, 1.0, -4.0);
	myScale(2.0, 3.0, 1.0);
	drawLine(c1, v1, v2);
	
	matInit(curMatrix);
	myRotate(10.0, 1.0, 1.0, -1.0);
	drawPolyv(c2, vector1, 3);
*/
}

int main() {
	myMat mat = {{0, 1, 0, 1},
		     {1, 0, 1, 0},
		     {0, 1, 0, 1},
		     {1, 0, 1, 0}};
	multMatrix4x4(mat, mat);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%lf ", mat[i][j]); 		
		}
		printf("\n");	
	}
	return 0;
}
