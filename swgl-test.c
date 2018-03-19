#include "swgl.h"
#include <stdio.h>

void printMat(myMat mat) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%.2lf ", mat[i][j]);
		}
		printf("\n");
	}
}

void testMatrixMultiplication() {
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
}

void testIdentityMatrixInit() {
	printf("Identity Matrix Init Test\n");
	myMat mat;
	initMat(mat);
	printMat(mat);
	printf("\n");
}

void testMyTranslate() {
	printf("Translate Matrix Test\n");
	initMat(curMatrix);
	myTranslate(2, 3, 4);
	printMat(curMatrix);
	printf("\n");
}

void testMyScale() {
	printf("Scale Matrix Test\n");
	initMat(curMatrix);
	myScale(2.5, 3, 4);
	printMat(curMatrix);
	printf("\n");
}

void testMyRotate() {
	printf("Rotate Matrix Test\n");
	initMat(curMatrix);
	myRotate(45,1,1,1);
	printMat(curMatrix);
	printf("\n");
}

int main() {
	testMatrixMultiplication();
	testIdentityMatrixInit();
	testMyTranslate();
	testMyScale();
	testMyRotate();
	return 0;
}