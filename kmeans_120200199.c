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
함수 [ sturctFromDRandom]는
	featureCount개 데이터를 Node의 data 멤버에 할당한다.
	featureCount는 데이터에 따라 달라지지만 값은 고정이므로 동적할당을 이용한다.
	Node를 선언하고 data멤버에 값을 할당하기 전에 data의 주소에 동적할당을 한다.
함수의 동작 순서는 다음과 같다.
	1. Node를 선언한다.
	2. Node의 멤버 중 float*로 선언된 featureArray를 동적할당하여 선언한다.
	3. for문을 featureCount번 실행하여 featureArray[i]에 (float)rand(1000)값을 저장한다.
*/
Node* structFromRandom()
{
	Node* tempNode = malloc(sizeof(Node));
	tempNode->featureArray = malloc(featureCount * sizeof(float));
	for (int i = 0; i < featureCount; i++)
	{
		(tempNode->featureArray)[i] = 1/(float)rand(1000)*10000;
	}
	tempNode->next = NULL;
	return tempNode;
}
/*
 * 함수명 : structFromArray
 * 입력형식 : float** , 1D Array Pointer
 * 출력형식 : Node* , Node Pointer
 * 함수[ structFromArray] 설명

 * 함수의 동작 순서
	1.
*/
Node* structFromArray(float* dataArray)
{
	Node* tempNode = malloc(sizeof(Node));
	tempNode->featureArray = malloc(featureCount * sizeof(float));
	for (int i = 0; i < featureCount; i++)
	{
		(tempNode->featureArray)[i] = dataArray[i];
	}
	tempNode->next = NULL;
	return tempNode;
}
/*
 * 함수명 : structFromFile
 * 입력형식 : 
 * 출력형식 : Node* , Node Pointer
 * 함수[ structFromFile ] 설명

 * 함수의 동작 순서
	1.
*/
Node* structFromFile(FILE** inputFile)
{
	Node* tempNode = malloc(sizeof(Node));
	tempNode->featureArray = malloc(featureCount * sizeof(float));
	for (int i = 0; i < featureCount; i++)
	{
		fscanf(*inputFile, "%f", &((tempNode->featureArray)[i]));
		//printf("%f\t", (tempNode->featureArray)[i]);
	}
	tempNode->next = NULL;
	return tempNode;
}
/*
 * 함수명 : pushArrayStruct
 * 입력형식 : Queue*	float*
 * 출력형식 : void
 * 함수 [ pushArrayStruct] 설명

 * 함수의 동작 순서
	1.
*/
void pushArrayStruct(Queue* queue, float* dataArray)
{
	Node* tempNode = structFromArray(dataArray);
	queue->rearNode = tempNode;
	queue->frontNode = tempNode;
}
void pushQueue(Queue* queue, Node* tempNode)
{
	if (queue->nodeCounts == 0)
	{
		queue->frontNode = tempNode;
	}
	else
	{
		queue->rearNode->next = tempNode;
	}
	queue->rearNode = tempNode;
	queue->nodeCounts++;
}
/*
함수 [ pushFirst ]는
	새로운 Node를 선언하고 dataArray에 담긴 값을 담아		// 함수 [ structFromData ]를 사용한다.
	주어진 Queue*의 frontNode에  Node를 추가한다.
함수의 동작순서는 다음과 같다.
	1. 함수 [ structFromData ]를 호출하여 Node를 선언하고
		dataArray에 담긴 값을 Node의 멤버 float* featureArray에 할당한다.
*/
void pushFirst(Queue* queue)
{
	Node* tempNode = structFromRandom();
	queue->rearNode = tempNode;
	queue->frontNode = tempNode;
}
/*
함수 [ makeQueue ] 는
	
함수의 동작순서는 다음과 같다.
	1. 
*/
Queue* makeQueue()
{
	Queue* tempQueue = malloc(sizeof(Queue));
	tempQueue->frontNode = NULL;
	tempQueue->rearNode = NULL;
	tempQueue->nodeCounts = 0;
	return tempQueue;
}
// 랜덤 샘플을 Queue에 담는 함수
/*
 * 함수명 : makeQueueArray
 * 입력형식 : void
 * 출력형식 : Queue**
 * 함수[ queueArray] 설명
	
 * 함수의 동작 순서
	1.
*/
Queue** makeQueueArray()
{
	Queue** queueArray = malloc(numberK * sizeof(Queue*));
	for (int i = 0; i < numberK; i++)
	{
		queueArray[i] = makeQueue();
		pushFirst(queueArray[i]);
	}
	return queueArray;
}
/*
 * 함수명 : makeInputQueue
 * 입력형식 : float**
 * 출력형식 : Queue**
 * 함수[ queueArray] 설명

 * 함수의 makeInputQueue 순서
	1.
*/
Queue** makeInputQueue(float** dataArray)
{
	Queue** queueArray = malloc(dataCount * sizeof(Queue*));
	for (int i = 0; i < dataCount; i++)
	{
		queueArray[i] = makeQueue();
		pushArrayStruct(queueArray[i], dataArray[i]);
	}
	return queueArray;
}

// 입력데이터를 Queue에 담는 함수
/*
 * 함수명 : makeFileQueue
 * 입력형식 : void
 * 출력형식 : Queue*
 * 함수[ structFromFile ] 설명
		입력 파일에 저장된 입력 데이터를 구조체에 담아 저장하고
 * 함수의 동작 순서
		1. 입력데이터 ' input.txt ' 파일을 읽어서 파일 포인터 ' inputFile '에 저장한다.
		2. 파일 첫줄에 주어지는 값 을 각 변수에 저장한다.
			dataCount : 입력 데이터 수, featureCount : feature 수 , numberK : 샘플데이터 수
		3. [ Queue ] 구조체의 포인터 변수 ' tempQueue ' 를 선언한다. 
			앞서 정의한  함수 [ makequeue ]를 호출한다.
		4. ' dataCount ' 만큼 반복문을 수행한다.
			4-1. 입력데이터를 [ Node ] 구조체의 변수 ' tempNode ' 에 저장한다.
			4-2.  linked list로 큐를 구현하여 저장한다.
		5. 파일을 닫는다.
		6. ' tempQueue ' 를 반환한다. 
	함수 종료.
*/
Queue* makeFileQueue()
{
	FILE* inputFile = fopen("input.txt", "r");
	fscanf(inputFile, "%d %d %d", &dataCount, &featureCount, &numberK);
	//printf("%d %d %d", dataCount, featureCount, numberK);

	Queue* tempQueue = makeQueue();
	for (int i = 0; i < dataCount; i++)
	{
		Node* tempNode = structFromFile(&inputFile);
		pushQueue(tempQueue, tempNode);
	}
	fclose(inputFile);
	return tempQueue;
}

Node* queuePop(Queue* dataQueue)
{
	if (dataQueue->nodeCounts == 0)
	{
		printf("WARNINGS : QUEUE UNDERFLOW");
		exit(-1);
	}
	Node* tempNode = dataQueue->frontNode;
	dataQueue->frontNode = tempNode->next;
	dataQueue->nodeCounts--;
	return tempNode;
}

float nodeDistance(Node* firstNode, Node* secondNode)
{
	float sum = 0, deviation = 0;
	for (int i = 0; i < featureCount; i++)
	{
		deviation = firstNode->featureArray[i] - secondNode->featureArray[i];
		//printf("%f\t%f\t\n", firstNode->featureArray[i], secondNode->featureArray[i]);
		//printf("DEV : %f\n", deviation);
		deviation = deviation * deviation;
		//printf("DEV^2 : %f\n", deviation);
		sum += deviation;
	}
	return sum;
}


/*
 * 함수명 : shortestQueuePush
 * 입력형식 : 
 * 출력형식 : void
 * 함수[ shortestQueuePush ] 설명
		
 * 함수의 동작 순서
		1. 
	함수 종료.
*/
void shortestQueuePush(Queue** queueArray, Node* tempNode)
{
	int shortestIndex;
	float shortestDistance = 3.4028234664e+38;
	shortestIndex = 0;
	for (int i = 0; i < numberK; i++)
	{
		float tempFloat = nodeDistance(tempNode, queueArray[i]->frontNode);
		if (shortestDistance > tempFloat)
		{
			//printf("%f\t", tempFloat);
			shortestDistance = tempFloat;
			shortestIndex = i;
		}
	}
	printf("%d\n", shortestIndex);
	queueArray[shortestIndex]->rearNode->next = tempNode;
	queueArray[shortestIndex]->rearNode = tempNode;
	queueArray[shortestIndex]->nodeCounts++;
}


void main(void) {
	FILE* inputFile;
	float** dataArray;				// inputFile의 값을 저장하고 있는 [ featureCount ] 차원 배열
	float** sampleArray;			// numberK개 Queue*를 저장하고 있는 1차원 배열, samplePoint를 featureArray로 갖는다.
	Queue** queueArray;

	dataToArray(&inputFile, &dataArray);
	//printf("%d %d %d\n", dataCount, featureCount, numberK);
	//printFloat2DArray(dataArray, dataCount, featureCount);
	randomSampleArray(&sampleArray);
	//printFloat2DArray(sampleArray, numberK, featureCount);

				/*
				함수 [ structFormDRandom] 테스트										[ TEST PRINT #1 ]
				*/
				Node* testRandomNode = structFromRandom();
				for (int i = 0; i < featureCount; i++)
				{
					//printf("TEST PRINT #1:\t%f\n", testRandomNode->featureArray[i]);
				}

				/*
				함수 [ pushFirst ] 테스트															[ TEST PRINT #2 ]
				*/
				Queue* firstQueue = makeQueue();
				pushFirst(firstQueue);
				for (int i = 0; i < featureCount; i++)
				{
					//printf("TEST PRINT #2:\t%f\n", firstQueue->frontNode->featureArray[i]);
				}
				
				/*
				함수 [ makeQueueArray ] 테스트											[ TEST PRINT #3 ]
				*/
				queueArray = makeQueueArray();
				for (int i = 0; i < numberK; i++)
				{
					printf("TEST PRINT #3:\t");
					for (int j = 0; j < featureCount; j++)
					{
						printf("%f\t", queueArray[i]->frontNode->featureArray[j]);
					}
					printf("\n");
				}

				/*
				함수 [ structFromArray ] 테스트												[ TEST PRINT #4 ]
				*/
				float sampleArrayElement[] = { -0.7303783878, 1.2121255077 };
				Node* testArrayNode = structFromArray(sampleArrayElement);
				for (int i = 0; i < featureCount; i++)
				{
					//printf("TEST PRINT #4:\t%f\n", testArrayNode->featureArray[i]);
				}

				/*
				함수 [ pushArrayStruct ] 테스트												[ TEST PRINT #5 ]
				*/
				Queue* secondQueue = makeQueue();
				pushArrayStruct(secondQueue, sampleArrayElement);
				for (int i = 0; i < featureCount; i++)
				{
					//printf("TEST PRINT #5:\t%f\n", secondQueue->frontNode->featureArray[i]);
				}

				/*
				함수 [ makeInputQueue ] 테스트											[ TEST PRINT #6 ]
				*/
				Queue** secondQueueArray = makeInputQueue(dataArray);
				for (int i = 0; i < dataCount; i++)
				{
					for (int j = 0; j < featureCount; j++)
					{
						//printf("TEST PRINT #6:\t%f\t", secondQueueArray[i]->frontNode->featureArray[j]);
					}
					//printf("\n");
				}

				/*
				함수 [ makeFileQueue ] 테스트												[ TEST PRINT #7 ]
				*/
				Queue* thirdQueue = makeFileQueue();
				Node* currentNode = thirdQueue->frontNode;

				for (int i = 0; i < dataCount; i++)
				{
					//printf("TEST PRINT #7:\t%3d\t", i);
					for (int j = 0; j < featureCount; j++)
					{
						//printf("%f\t", currentNode->featureArray[j]);
					}
					currentNode = currentNode->next;
					//printf("\n");
				}

				///*
				//함수 [ queuePop ] 테스트															[ TEST PRINT #8 ]
				//*/
				//Node* thirdTempNode = queuePop(thirdQueue);
				////printf("TEST PRINT #8:\t");
				//for (int i = 0; i < featureCount; i++)
				//{
				//	//printf("%f\t", thirdTempNode->featureArray[i]);
				//}
				////printf("\n");
				//
				///*
				//함수 [ nodeDistance ] 테스트														[ TEST PRINT #9 ]
				//*/
				//float maxDistance = 0;
				//int maxIndex = 0;
				//for (int i = 0; i < numberK; i++)
				//{
				//	float tempFloat = nodeDistance(thirdTempNode, queueArray[i]->frontNode);
				//	//printf("TEST PRINT #9:\t%f\n", tempFloat);
				//	if (maxDistance > tempFloat)
				//	{
				//		maxDistance = tempFloat;
				//		maxIndex = i;
				//	}
				//}
				////printf("%d\n", maxIndex);


				///*
				//함수 [ shortestQueuePush ] 테스트											[ TEST PRINT #10 ]
				//*/
				//shortestQueuePush(queueArray, thirdTempNode);
				////printf("TEST PRINT #10:\t%f\n", queueArray[0]->frontNode->next->featureArray[0]);

				while (thirdQueue->nodeCounts != 0)
				{
					Node* testNode = queuePop(thirdQueue);
					shortestQueuePush(queueArray, testNode);
				}
				for (int i = 0; i < numberK; i++)
				{
					printf("queueArray[%d]: %d\n", i, queueArray[i]->nodeCounts);
				}

				for (int i = 0; i < numberK; i++)
				{
					Node* currentNode = queueArray[i]->frontNode;
					printf("INDEX: %d\n", i);
					while (currentNode->next != NULL)
					{
						for (int j = 0; j < featureCount; j++)
						{
							printf("%f ", currentNode->featureArray[j]);
						}
						currentNode = currentNode->next;
						printf("\n");
					}
					

				}

	return;
}
/*
함수[ functionNameRegulation] 는
	
함수의 동작순서는 다음과 같다.
	1.
*/

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
	fclose(*inputFile);
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