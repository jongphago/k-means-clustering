#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int dataCount = 0;		
int featureCount = 0;	
int numberK = 0;			
int scanfCount = 0;	

typedef struct Node {
	float* featureArray;
	struct Node* next;
} Node;
typedef  struct Stack {
	Node* top;
} Stack;

void push(Stack* waitingStack, Node* node);
void pushAfterFirst(Stack* stack, Node* node);
Stack* makeStack();

Stack** makeSampleArray();
Stack** makeWaitingArray();

float nodeDistance(Node* firstNode, Node* testNode);
void meanStack(Stack* stack);
void meanStackArray(Stack** stack);
void updateSample(Stack** sampleArray, Stack** waitingArray);
void linkStack(Stack** sampleArray, Stack** waitingArray);

int isStackNULL(Stack* stack)
{

	if (stack->top == NULL)
	{
		return 1;
	}
	return 0;
}
int isStackArrayNULL(Stack** stackArray)
{
	int mul = 1;
	for (int i = 0; i < numberK; i++)
	{
		mul *= isStackNULL(stackArray[i]);
	}
	if (mul == 1)
	{
		return 1;
	}
	return 0;
}

void showStack(Stack* stack);
void showStackCount(Stack* stack);
void showStackCountArray(Stack** stackArray);
void showStackArray(Stack** stackArray);
void showFirst(Stack* stack);
void showFirstArray(Stack** stackArray);
void showStackFinal(Stack* stack);
void showStackFinalArray(Stack** stackArray);

void writeFile(Stack* stack, FILE* fileOutput);
void writeFileArray(Stack** stackArray);


void main(void)
{
	srand(1000);
	int iteration = 10;

	Stack** sampleArray = makeSampleArray();
	/*showStackCountArray(sampleArray);
	showFirstArray(sampleArray);
	showStackArray(sampleArray);*/
	Stack** waitingArray = makeWaitingArray();

	for (int i = 0; i < iteration; i++)
	{
		meanStackArray(sampleArray);
		updateSample(sampleArray, waitingArray);
		/*printf("1. Update sampleArray NodeCounts\n");
		showStackArray(sampleArray);
		printf("2. Temporary waitingArray NodeCounts\n");
		showStackArray(waitingArray);*/
		if (isStackArrayNULL(waitingArray)) break;
		linkStack(sampleArray, waitingArray);
		/*printf(">> Final sampleArray NodeCounts\n");
		showStackArray(sampleArray);
		printf("\n\n");
		showStackCountArray(sampleArray);*/
	}
	//showStackFinalArray(sampleArray);
	writeFileArray(sampleArray);
}

/*
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
*/

Stack* makeStack()
{
	Stack* stack = malloc(sizeof(stack));
	stack->top = NULL;
}
Stack** makeSampleArray()
{
	FILE* fileInput = fopen("input.txt", "r");
	fscanf(fileInput, "%d %d %d", &dataCount, &featureCount, &numberK);

	Stack** sampleArray = malloc(numberK * sizeof(Stack*));

	for (int i = 0; i < numberK; i++)
	{
		sampleArray[i] = makeStack();
		Node* firstNode = malloc(sizeof(Node));
		firstNode->featureArray = malloc(featureCount * sizeof(float));
		for (int j = 0; j < featureCount; j++)
		{
			firstNode->featureArray[j] = 1 / (float)rand();
			//firstNode->featureArray[j] = (float)rand();
		}
		firstNode->next = sampleArray[i]->top;
		sampleArray[i]->top = firstNode;
	}

	for (int i = 0; i < dataCount; i++)
	{
		int shortestIndex;
		float shortestDistance = 3.4028234664e+38;

		Node* dataNode = malloc(sizeof(Node));
		dataNode->featureArray = malloc(featureCount * sizeof(float));
		for (int j = 0; j < featureCount; j++)
		{
			fscanf(fileInput, "%f", &(dataNode->featureArray[j]));
		}

		shortestIndex = 0;
		for (int i = 0; i < numberK; i++)
		{
			float tempDistance = nodeDistance(sampleArray[i]->top, dataNode);
			if (shortestDistance > tempDistance)
			{
				shortestDistance = tempDistance;
				shortestIndex = i;
			}
		}
		pushAfterFirst(sampleArray[shortestIndex], dataNode);
	}
	fclose(fileInput);

	return sampleArray;
}
Stack** makeWaitingArray()
{
	Stack** waitingArray = malloc(numberK * sizeof(Stack*));
	for (int i = 0; i < numberK; i++)
	{
		waitingArray[i] = makeStack();
	}
	return waitingArray;
}
void push(Stack* waitingStack, Node* node)
{
	node->next = waitingStack->top;
	waitingStack->top = node;
}
void pushAfterFirst(Stack* stack, Node* node)
{
	Node* firstNode = stack->top;
	node->next = firstNode->next;
	firstNode->next = node;
}
float nodeDistance(Node* firstNode, Node* testNode)
{
	float sum = 0, deviation = 0;
	for (int i = 0; i < featureCount; i++)
	{
		deviation = (firstNode->featureArray[i]) - (testNode->featureArray[i]);
		deviation *= deviation;
		sum += deviation;
	}
	return sum;
}
void meanStack(Stack* stack)
{
	if (stack->top->next == NULL)
	{
		printf("빈 스택에 대해 초기화를 다시 진행합니다.\n");
		for (int i = 0; i < featureCount; i++)
		{
			stack->top->featureArray[i] = 1 / (float)rand();
			//stack->top->featureArray[i] = (float)rand();
		}
		return;
	}

	int nodeCount = 0;
	int sum = 0;
	Node* firstNode = stack->top;
	Node* currentNode = firstNode->next;
	float* sumArray = calloc(featureCount, sizeof(float));
	while (currentNode != NULL)
	{
		nodeCount++;
		for (int i = 0; i < featureCount; i++)
		{
			sumArray[i] += currentNode->featureArray[i];
		}
		currentNode = currentNode->next;
	}
	for (int i = 0; i < featureCount; i++)
	{
		sumArray[i] /= nodeCount;
		firstNode->featureArray[i] = sumArray[i];
	}
}
void meanStackArray(Stack** stack)
{
	for (int i = 0; i < numberK; i++)
	{
		meanStack(stack[i]);
	}
}

/*
sampleArray에 저장된 노드를 순회하며 sampleArray의 첫 번째 노드에 저장된 sample point와 거리를
계산한다.
거리가 가장 가까운 index를 받아온다.
기존 index와 같으면 다음 노드로 넘어가고,
다르면 노드를 sampleArray에서 pop하여 waitingArray의 stack에 push한다.
sampleArray와 waitingArray를 연결한다.
*/
void updateSample(Stack** sampleArray, Stack** waitingArray)
{
	for (int i = 0; i < numberK; i++)
	{
		Node* previousNode = sampleArray[i]->top;
		Node* currentNode = previousNode->next;
		Node* firstNode;
		int shortestIndex;
		float shortestDistance;
		while (currentNode != NULL)
		{
			shortestIndex = 0;
			shortestDistance = 3.4028234664e+38;
			for (int j = 0; j < numberK; j++)
			{
				firstNode = sampleArray[j]->top;
				float tempDistance = nodeDistance(firstNode, currentNode);
				//printf("[ TEST PRINT #1 ] TempDistance: %f\n", tempDistance);						// [ TEST PRINT #1 ]
				if (shortestDistance > tempDistance)
				{
					shortestDistance = tempDistance;
					shortestIndex = j;
					//printf("%d", shortestIndex);
				}
			}
			if (shortestIndex != i)
			{
				Node* tempNode = currentNode;
				previousNode->next = currentNode->next;
				currentNode = previousNode->next;
				push(waitingArray[shortestIndex], tempNode);
			}
			else
			{
				previousNode = previousNode->next;
				currentNode = currentNode->next;
			}
		}
	}
}
void linkStack(Stack** sampleArray, Stack** waitingArray)
{
	for (int i = 0; i < numberK; i++)
	{
		while (waitingArray[i]->top != NULL)
		{
			Node* tempNode = waitingArray[i]->top;
			waitingArray[i]->top = tempNode->next;
			tempNode->next = NULL;

			pushAfterFirst(sampleArray[i], tempNode);
		}
	}
}

void showStack(Stack* stack)
{

	if (stack->top == NULL)
	{
		printf("EMPTY STACK\n");
		return;
	}
	Node* currentNode = stack->top;
	int index = 0;
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
void showStackFinal(Stack* stack)
{

	if (stack->top == NULL)
	{
		printf("EMPTY STACK\n");
		return;
	}
	Node* currentNode = stack->top;
	int index = 0;
	while (currentNode != NULL)
	{
		for (int i = 0; i < featureCount; i++)
		{
			printf("%f ", currentNode->featureArray[i]);
		}
		printf("\n");
		currentNode = currentNode->next;
	}
}
void showStackFinalArray(Stack** stackArray)
{
	for (int i = 0; i < numberK; i++)
	{
		printf("%d\n", i);
		showStackFinal(stackArray[i]);
	}
}
void showStackCount(Stack* stack)
{

	if (stack->top == NULL)
	{
		printf("EMPTY STACK");
		return;
	}
	Node* currentNode = stack->top;
	int index = 0;
	while (currentNode != NULL)
	{
		index++;
		currentNode = currentNode->next;
	}
	printf("%4d", index);
}
void showStackCountArray(Stack** stackArray)
{
	printf("#################################\n");
	for (int i = 0; i < numberK; i++)
	{
		printf("INDEX %d:\t", i);
		showStackCount(stackArray[i]);
		printf("%\n");
	}
	printf("#################################\n\n");
}
void showStackArray(Stack** stackArray)
{
	printf("#################################\n");
	for (int i = 0; i < numberK; i++)
	{
		printf("<<<<<<<<<< %d 번째 원소 >>>>>>>>>>\n", i);
		showStack(stackArray[i]);
	}
	printf("#################################\n\n");

}
void showFirst(Stack* stack)
{

	if (stack->top == NULL)
	{
		printf("EMPTY STACK");
		return;
	}
	Node* currentNode = stack->top;

	for (int i = 0; i < featureCount; i++)
	{
		printf("%f\t", currentNode->featureArray[i]);
	}
}
void showFirstArray(Stack** stackArray)
{
	printf("###############FIRST NODE###############\n");
	for (int i = 0; i < numberK; i++)
	{
		printf("INDEX #%2d\t", i);
		showFirst(stackArray[i]);
		printf("\n");
	}
	printf("########################################\n\n");

}
void writeFile(Stack* stack, FILE* fileOutput)
{

	if (stack->top == NULL)
	{
		fprintf(fileOutput, "EMPTY STACK\n");
		return;
	}
	Node* currentNode = stack->top;
	int index = 0;
	while (currentNode != NULL)
	{
		for (int i = 0; i < featureCount; i++)
		{
			fprintf(fileOutput, "%f ", currentNode->featureArray[i]);
		}
		fprintf(fileOutput, "\n");
		currentNode = currentNode->next;
	}
}
void writeFileArray(Stack** stackArray)
{
	FILE* fileOutput = fopen("output.txt", "w");
	for (int i = 0; i < numberK; i++)
	{
		fprintf(fileOutput, "%d\n", i);
		writeFile(stackArray[i], fileOutput);
	}
	fclose(fileOutput);
}