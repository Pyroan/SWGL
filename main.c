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

void printMat(myMat mat) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d ", (int)mat[i][j]);
		}
		printf("\n");
	}
}

int main() {
	myMat mat1 = {{1, 2, 3, 4},
				{4, 1, 2, 3},
				{3, 4, 1, 2},
				{2, 3, 4, 1}};
	myMat mat2 = {{1, 4, 3, 2},
				{2, 1, 4, 3},
				{3, 2, 1, 4},
				{4, 3, 2, 1}};
	multMatrix4x4(mat1, mat2);
	
	printf("Matrix Multiplication Test\n");
	printMat(mat1);
	printf("\n");
	
	printf("Identity Matrix Init Test\n");
	myMat mat;
	initMat(mat);
	printMat(mat);
	printf("\n");
	return 0;
}
