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

typedef  struct Queue{
	Node* frontNode;
	Node* rearNode;
	int nodeCounts;
} Queue;

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
		tempNode->featureArray[i] = 1/(float)rand()*1000;
		printf("%f\t", tempNode->featureArray[i]);
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
	queue->frontNode = tempNode;
	queue->rearNode = tempNode;
	queue->nodeCounts++;
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
Queue** makeSampleArray()
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
/*
이 프로젝트에서 queuePop은 노드를 추출 하는 것이므로
추출한 Node의 next를 NULL로 해줘야 한다.
*/
Node* queuePop(Queue* dataQueue)
{
	if (dataQueue->nodeCounts == 0)
	{
		printf("WARNINGS : QUEUE UNDERFLOW");
		exit(-1);
	}
	Node* tempNode = dataQueue->frontNode;
	dataQueue->frontNode = tempNode->next;
	tempNode->next = NULL;
	dataQueue->nodeCounts--;
	return tempNode;
}
float nodeDistance(Node* firstNode, Node* secondNode)
{
	if (firstNode == NULL || secondNode == NULL)
	{
		return 0;
	}
	float sum = 0, deviation = 0;
	for (int i = 0; i < featureCount; i++)
	{
		deviation = (firstNode->featureArray[i]) - (secondNode->featureArray[i]);
		//printf("%f\t%f\t\n", firstNode->featureArray[i], secondNode->featureArray[i]);
		//printf("DEV : %f\n", deviation);
		deviation *= deviation;
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
		float tempDistance = nodeDistance(tempNode, queueArray[i]->frontNode);
		if (shortestDistance > tempDistance)
		{
			//printf("%f\t", tempFloat);
			shortestDistance = tempDistance;
			shortestIndex = i;
		}
	}
	//printf("%d\n", shortestIndex);
	queueArray[shortestIndex]->rearNode->next = tempNode;
	queueArray[shortestIndex]->rearNode = tempNode;
	queueArray[shortestIndex]->nodeCounts++;
}

void shortestQueueRenew(Queue** sampleArray)
{
	int shortestIndex;
	float shortestDistance = 3.4028234664e+38;
	shortestIndex = 0;
	for (int i = 0; i < numberK; i++)
	{
		Node* tempNode = sampleArray[i]->frontNode;
		Node* currentNode = sampleArray[i]->frontNode->next; // 새로운 기능의 Node Pop 필요 1. frontNode->next를 
		while (1)
		{
			for (int j = 0; j < numberK; j++)
			{
				float tempDistance = nodeDistance(currentNode, sampleArray[i]->frontNode);
				if (shortestDistance > tempDistance)
				{
					shortestDistance = tempDistance;
					shortestIndex = j;
				}
			}
			if (shortestIndex != i)
			{
				tempNode->next = currentNode->next;
				sampleArray[i]->nodeCounts--;
				currentNode->next = NULL;
				sampleArray[shortestIndex]->rearNode->next = currentNode;
				sampleArray[shortestIndex]->nodeCounts++;
			}
			if (currentNode == sampleArray[i]->rearNode)
			{
				break;
			}
			currentNode = currentNode->next;
		}
	}

	/*
	rearNode를 마지막 Node로 지정한다.
	*/
	for (int i = 0; i < numberK; i++)
	{
		Node* tempRearNode = sampleArray[i]->rearNode;
		while (tempRearNode != NULL)
		{
			sampleArray[i]->rearNode = tempRearNode;
			tempRearNode = tempRearNode->next;
		}
	}
}

void showQueue(Queue* queue)
{
	printf("NODE CNTS: %d\n", queue->nodeCounts);
	if (queue->nodeCounts == 0)
	{
		printf("EMPTY QUEUE");
	}
	else
	{
		int index = 0;
		Node* currentNode = queue->frontNode;
		while (currentNode != NULL)
		{
			printf("%3d\t", index++);
			for (int i = 0; i < featureCount; i++)
			{
				printf("%f\t", currentNode->featureArray[i]);
			}
			printf("\n");
			currentNode = currentNode->next;
		}
	}
}
void meanQueue(Queue* queue)
{
	int totalCount = queue->nodeCounts;
	float* sumArray = calloc(featureCount,  sizeof(float));

	Node* currentNode = queue->frontNode->next;
	while (currentNode != NULL)
	{
		for (int i = 0; i < featureCount; i++)
		{
			sumArray[i] += currentNode->featureArray[i];
		}
		currentNode = currentNode->next;
	}
	for (int i = 0; i < featureCount; i++)
	{
		sumArray[i] /= totalCount;
		queue->frontNode->featureArray[i] = sumArray[i];
	}
}
void showQueueArray(Queue** queueArray)
{
	for (int i = 0; i < numberK; i++)
	{
		printf("[ INDEX: %d ]\n", i);
		showQueue(queueArray[i]);
	}
}
void showNodeCounts(Queue** queueArray)
{
	for (int i = 0; i < numberK; i++)
	{
		printf("INDEX %d:", i);
		printf("%3d\n", queueArray[i]->nodeCounts);
	}
	printf("\n");
}

void main(void) {
	srand(1000);

	/*
	inputQueue
	*/
	Queue* inputQueue = makeFileQueue();
	//showQueue(inputQueue);

	/*
	sampleArray를 생성한다.
	*/
	Queue** sampleArray;
	sampleArray = makeSampleArray();
	//showQueueArray(sampleArray);
	//showQueueArray(sampleArray);

	/*
	
	*/
	while (inputQueue->nodeCounts != 0) 
	{
		Node* testNode = queuePop(inputQueue);
		//shortestQueuePush(sampleArray, testNode);
	}
	//showQueue(inputQueue);
	//showQueueArray(sampleArray);


	//shortestQueueRenew(sampleArray);
	return;
}
