#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
20.11.02 21:30 경로변경
*/

int dataCount = 0;			//
int featureCount = 0;		//
int numberK = 0;				//
int scanfCount = 0;			//

void scanfException(int scanfReturn, int scanfTarget);
void dataToArray(FILE** inputFile, float*** dataArray);
void printFloat2DArray(float** dataArray, int firstIndexCount, int secondIndexCount);
void randomSampleArray(float*** sampleArray);

void main(void) {
	FILE* inputFile;
	float** dataArray;
	float** sampleArray;

	dataToArray(&inputFile, &dataArray);
	//printf("%d %d %d\n", dataCount, featureCount, numberK);
	printFloat2DArray(dataArray, dataCount, featureCount);
	randomSampleArray(&sampleArray);
	printFloat2DArray(sampleArray, numberK, featureCount);

	return;
}

/*
함수 [scanfException]은 scanf함수 또는 fscanf 함수가
알맞은 값의 개수를 반환하였는지 확인합니다.
*/
void scanfException(int scanfReturn, int scanfTarget)
{
	if (scanfReturn != scanfTarget)
	{
		printf("SCANF ERROR iS OCCURED.");
		exit(-1);
	}
	return;
}

/*
함수 [dataToArray]는 "input.txt" 파일을 읽어서 점 데이터를
float형 2차원 배열(변수명:dataArray)에 저장합니다.
*/
void dataToArray(FILE** inputFile, float*** dataArray) 
{
	*inputFile = fopen("input.txt", "r");
	if ((*inputFile) == NULL)
	{
		printf("File Open Error");
		exit(-1);
	}
	scanfCount = fscanf(*inputFile, "%d %d %d", &dataCount, &featureCount, &numberK);
	if (scanfCount != 3)
	{
		printf("fscanf Error");
		exit(-1);
	}

	*dataArray = malloc(dataCount * sizeof(float*));
	for (int i = 0; i < dataCount; i++)
	{
		(*dataArray)[i] = malloc(featureCount * sizeof(float));
		if ((*dataArray)[i] == NULL)
		{
			printf("MEMORY ALLOCATION ERROR.");
			exit(-1);
		}
		for (int j = 0; j < featureCount; j++)
		{
			scanfCount = fscanf(*inputFile, "%f", &((*dataArray)[i][j]));
			if (scanfCount != 1) {
				exit(-1);
			}
			scanfException(scanfCount, 1);
		}
	}
}

/*
함수 [printFloat2DArray]는 float type의 2차원 배열을 받아서 
index:		data1		data2		...		dataK 형태로 출력합니다.
행의 수는 firstIndexCount, 열의 수는 secondIndexCount와 같습니다.
*/
void printFloat2DArray(float** dataArray, int firstIndexCount, int secondIndexCount) 
{
	for (int i = 0; i < firstIndexCount; i++)
	{
		printf("%3d:\t", i);
		for (int j = 0; j < secondIndexCount; j++)
		{
			printf("%.3f\t", dataArray[i][j]);
		}
		printf("\n");
	}
}

/*
함수 [randomSampleArray]는 numberK * featureCount 크기의
임의의 점을 생성합니다.
random함수의 seed는 1000으로 고정되어 있습니다.
*/
void randomSampleArray(float*** sampleArray)
{
	srand(1000);
	*sampleArray = malloc(numberK * sizeof(float*));
	for (int i = 0; i < numberK; i++)
	{
		(*sampleArray)[i] = malloc(featureCount * sizeof(float));
		for (int j = 0; j < featureCount; j++)
		{
			(*sampleArray)[i][j] = (float)rand();
		}
	}
}