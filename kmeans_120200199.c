#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int dataCount = 0;			//
int featureCount = 0;		//
int numberK = 0;				//
int scanfCount = 0;			//

typedef struct Node{
	float* featureArray;
	struct Node* next;
} Node;

/*
Node에 데이터를 저장하려고 하니 feature의 수가 유동적이다.
예상 해결방법은 다음과 같다.
1. float* 형 멤버를 선언하고, 동적할당한다.
2. linked list로 구현한다.
*/

typedef  struct Queue{
	Node* frontNode;
	Node* rearNode;
	int nodeCounts;
} Queue;


void scanfException(int scanfReturn, int scanfTarget);
void dataToArray(FILE** inputFile, float*** dataArray);
void printFloat2DArray(float** dataArray, int firstIndexCount, int secondIndexCount);
void randomSampleArray(float*** sampleArray);
void pushQueue(Queue* queue);


/*
함수 [ queueFromArray ]는
	sampleArray의 원소 수 만큼 Queue를 생성하고 
	생성된 Queue의 첫번째 노드에 sampleArray의 데이터를 각각 queuePush한다.
	생성한 Queue는 1차원 배열에 담아 관리한다.
함수의 동작 순서는 다음과 같다.
	1. 동적할당을 이용하여 numberK개 Queue* 를 담는 배열을 선언한다.
			Queue** queueArray = malloc(numberK * sizeof(Queue*));
	2. for문을 numberK번 돌며 array[i]에 Queue를 선언하고 초기화 한다.
			for (int i = 0; i < numberK; i++) {
				queueArray[i] = malloc(sizeof(Queue));
				...
				}
	3. Node를 생성하고 for문을 featureCount번 돌며 Queue->data에 queuePush한다.
*/
void queueFromArray(Queue** queueArray)
{
	
}

/*
함수 [ pushQueue ]는
	새로운 Node를 선언하고 dataArray에 담긴 값을 담아		// 함수 [ structFromData ]를 사용한다.
	주어진 Queue*의 frontNode에  Node를 추가한다.
함수의 동작순서는 다음과 같다.
	1. 함수 [ structFromData ]를 호출하여 Node를 선언하고
		dataArray에 담긴 값을 Node의 멤버 float* featureArray에 할당한다.
*/
void pushQueue(Queue* queue)
{
	
}
/*
함수 [ sturctFromData ]는
	featureCount개 데이터를 Node의 data 멤버에 할당한다.
	featureCount는 데이터에 따라 달라지지만 값은 고정이므로 동적할당을 이용한다.
	Node를 선언하고 data멤버에 값을 할당하기 전에 data의 주소에 동적할당을 한다.
함수의 동작 순서는 다음과 같다.
	1. Node를 선언한다.
	2. Node의 멤버 중 float*로 선언된 featureArray를 동적할당하여 선언한다.
	3. for문을 featureCount번 실행하여 featureArray[i]에 (float)rand(1000)값을 저장한다.
*/
Node* structFormData()
{
	Node* tempNode = malloc(sizeof(Node));
	tempNode->featureArray = malloc(featureCount * sizeof(float));
	for (int i = 0; i < featureCount; i++)
	{
		(tempNode->featureArray)[i] = (float)rand(1000);
	}
	tempNode->next = NULL;
	return tempNode;
}


void main(void) {
	FILE* inputFile;
	float** dataArray;				// inputFile의 값을 저장하고 있는 [ featureCount ] 차원 배열
	float** sampleArray;			// numberK개 Queue*를 저장하고 있는 1차원 배열, samplePoint를 featureArray로 갖는다.
	Queue* queueArray;

	dataToArray(&inputFile, &dataArray);
	//printf("%d %d %d\n", dataCount, featureCount, numberK);
	//printFloat2DArray(dataArray, dataCount, featureCount);
	randomSampleArray(&sampleArray);
	//printFloat2DArray(sampleArray, numberK, featureCount);

	/*
	함수 [ structFormData() ] 테스트
	*/
	Node* testNode = structFormData();
		for (int i = 0; i < featureCount; i++)
	{
		printf("%f\n", testNode->featureArray[i]);
	}
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