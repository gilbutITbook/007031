#include "stdio.h"
#include "stdlib.h"

#define MAX_CAPACITY 100
#define ERROR_VALUE -999


//예제 9-1
typedef struct tNode
{
	int value;
	struct tNode* lChild;
	struct tNode* rChild;
} treeNode;

//해결책 9-1
treeNode* levelOrderBinaryTreeUtil(int arr[], int size, int start)
{
	treeNode* curr = (treeNode*)malloc(sizeof(treeNode));
	curr->value = arr[start];
	curr->lChild = curr->rChild = NULL;
	int left = 2 * start + 1;
	int right = 2 * start + 2;
	if (left < size)
		curr->lChild = levelOrderBinaryTreeUtil(arr, size, left);
	if (right < size)
		curr->rChild = levelOrderBinaryTreeUtil(arr, size, right);
	return curr;
}
treeNode* levelOrderBinaryTree(int arr[], int size)
{
	return levelOrderBinaryTreeUtil(arr, size, 0);
}

int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	treeNode* t = levelOrderBinaryTree(arr, sizeof(arr) / sizeof(int));
	return 0;
}

//해결책 9-2
void printPreOrder(treeNode* root) /* 전위 순회  */
{
	if (root) {
		printf(" %d ", root->value);
		printPreOrder(root->lChild);
		printPreOrder(root->rChild);
	}
}

//해결책 9-3
void printPostOrder(treeNode* root) /*  후위 순회  */
{
	if (root) {
		printPostOrder(root->lChild);
		printPostOrder(root->rChild);
		printf(" %d ", root->value);
	}
}

//해결책 9-4
void printInOrder(treeNode* root) /*  중위 순회  */
{
	if (root) {
		printInOrder(root->lChild);
		printf(" %d ", root->value);
		printInOrder(root->rChild);
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 예제에서 사용하는  큐와 스택 관련 코드들
#define MAX_CAPACITY 100
#define ERROR_VALUE -999

typedef struct Queue_t
{
	int front;
	int back;
	int size;
	int data[MAX_CAPACITY];
} Queue;

void QueueInitialize(Queue* que)
{
	que->back = 0;
	que->front = 0;
	que->size = 0;
}

void QueueAdd(Queue* que, int value)
{
	if (que->size >= MAX_CAPACITY) {
		printf("\n Queue is full.");
		return;
	}
	else {
		que->size++;
		que->data[que->back] = value;
		que->back = (que->back + 1) % (MAX_CAPACITY - 1);
	}
}

int QueueRemove(Queue* que)
{
	int value;
	if (que->size <= 0) {
		printf("\n Queue is empty.");
		return ERROR_VALUE;
	}
	else {
		que->size--;
		value = que->data[que->front];
		que->front = (que->front + 1) % (MAX_CAPACITY - 1);
	}
	return value;
}

int QueueFront(Queue* que)
{
	return que->data[que->front];
}

int QueueBack(Queue* que)
{
	return que->data[que->back - 1];
}

int QueueRemoveBack(Queue* que)
{
	int value;
	if (que->size <= 0) {
		printf("\n Queue is empty.");
		return ERROR_VALUE;
	}
	else {
		que->size--;
		value = que->data[que->back - 1];
		que->back = (que->back - 1) % (MAX_CAPACITY - 1);
	}
	return value;
}

int QueueIsEmpty(Queue* que)
{
	return que->size == 0;
}

int QueueSize(Queue* que)
{
	return que->size;
}

typedef struct stack
{
	int top;
	int data[MAX_CAPACITY];
} Stack;

int min(int a, int b)
{
	return a > b ? b : a;
}

int max(int a, int b)
{
	return a < b ? b : a;
}

void StackInitialize(Stack* stk);
void StackPush(Stack* stk, int value);
int StackPop(Stack* stk);
int StackTop(Stack* stk);
int StackIsEmpty(Stack* stk);
int StackSize(Stack* stk);

void StackInitialize(Stack* stk)
{
	stk->top = -1;
}

void StackPush(Stack* stk, int value)
{
	if (stk->top < MAX_CAPACITY - 1) {
		stk->top++;
		stk->data[stk->top] = value;
	}
	else {
		printf("stack overflow\n");
	}
}

int StackPop(Stack* stk)
{
	if (stk->top >= 0) {
		int value = stk->data[stk->top];
		stk->top--;
		return value;
	}
	printf("stack empty\n");
	return ERROR_VALUE;
}

int StackTop(Stack* stk)
{
	int value = stk->data[stk->top];
	return value;
}

int StackIsEmpty(Stack* stk)
{
	return (stk->top == -1);
}

int StackSize(Stack* stk)
{
	return (stk->top + 1);
}

void StackPrint(Stack* stk)
{
	printf("Stack :: ");
	for (int i = stk->top; i >= 0; i--) {
		printf("%d ", stk->data[i]);
	}
	printf("\n");
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//해결책 9-5
void PrintBredthFirst(treeNode* root)
{
	Queue que;
	QueueInitialize(&que);
	treeNode* temp = NULL;
	if (root != NULL)
		QueueAdd(&que, (int)root);
	while (QueueSize(&que) != 0) {
		temp = (treeNode*)QueueRemove(&que);
		printf("%d ", temp->value);
		if (temp->lChild != NULL)
			QueueAdd(&que, (int)temp->lChild);
		if (temp->rChild != NULL)
			QueueAdd(&que, (int)temp->rChild);
	}
}

//해결책 9-6
void PrintDepthFirst(treeNode* root)
{
	Stack stk;
	StackInitialize(&stk);
	treeNode* temp = NULL;
	if (root != NULL)
		StackPush(&stk, (int)root);
	while (StackSize(&stk) != 0) {
		temp = (treeNode*)StackPop(&stk);
		printf("%d ", temp->value);
		if (temp->rChild != NULL)
			StackPush(&stk, (int)temp->rChild);
		if (temp->lChild != NULL)
			StackPush(&stk, (int)temp->lChild);
	}
}

//해결책 9-7-1
void PrintLevelOrderLineByLine(treeNode* root)
{
	Queue que1;
	QueueInitialize(&que1);
	Queue que2;
	QueueInitialize(&que2);
	treeNode* temp = NULL;
	if (root != NULL)
		QueueAdd(&que1, (int)root);
	while (QueueSize(&que1) != 0 || QueueSize(&que2) != 0) {
		while (QueueSize(&que1) != 0) {
			temp = (treeNode*)QueueRemove(&que1);
			printf("%d ", temp->value);
			if (temp->lChild != NULL)
				QueueAdd(&que2, (int)temp->lChild);
			if (temp->rChild != NULL)
				QueueAdd(&que2, (int)temp->rChild);
		}
		printf("\n");
	
		while (QueueSize(&que2) != 0) {
			temp = (treeNode*)QueueRemove(&que2);
			printf("%d ", temp->value);
			if (temp->lChild != NULL)
				QueueAdd(&que1, (int)temp->lChild);
			if (temp->rChild != NULL)
				QueueAdd(&que1, (int)temp->rChild);
		}
		printf("\n");
	}
}

//해결책 9-7-2
void PrintLevelOrderLineByLine2(treeNode* root)
{
	Queue que;
	QueueInitialize(&que);
	treeNode* temp = NULL;
	int count;

	if (root != NULL)
		QueueAdd(&que, (int)root);
	while (QueueSize(&que) != 0) {
		count = QueueSize(&que);
		while (count > 0) {
			temp = (treeNode*)QueueRemove(&que);
			printf("%d ", temp->value);
			if (temp->lChild != NULL)
				QueueAdd(&que, (int)temp->lChild);
			if (temp->rChild != NULL)
				QueueAdd(&que, (int)temp->rChild);
			count -= 1;
		}
		printf("\n");
	}
}

//해결책 9-8
void PrintSpiralTree(treeNode* root)
{
	Stack stk1;
	StackInitialize(&stk1);

	Stack stk2;
	StackInitialize(&stk2);

	treeNode* temp = NULL;
	if (root != NULL)
		StackPush(&stk1, (int)root);

	while (StackSize(&stk1) != 0 || StackSize(&stk2) != 0) {
		while (StackSize(&stk1) != 0) {
			temp = (treeNode*)StackPop(&stk1);
			printf("%d ", temp->value);
			if (temp->rChild != NULL)
				StackPush(&stk2, (int)temp->rChild);
			if (temp->lChild != NULL)
				StackPush(&stk2, (int)temp->lChild);
		}
		while (StackSize(&stk2) != 0) {
			temp = (treeNode*)StackPop(&stk2);
			printf("%d ", temp->value);
			if (temp->lChild != NULL)
				StackPush(&stk1, (int)temp->lChild);
			if (temp->rChild != NULL)
				StackPush(&stk1, (int)temp->rChild);
		}
	}
}

//해결책 9-9
treeNode* NthPreeOrder(treeNode* root, int index) /* 전위 순회  */
{
	static int count = 0;
	treeNode* temp = NULL;

	if (root){ 
		count++;
		if (count == index) {
			printf(" %d ", root->value);
			return root;
		}

		temp = NthPreeOrder(root->lChild, index);
		if (temp)
			return temp;

		temp = NthPreeOrder(root->rChild, index);
		if (temp)
			return temp;
	}
	return NULL;
}

//해결책 9-10
treeNode* NthPostOrder(treeNode* root, int index) /*  후위 순회  */
{
	static int count = 0;
	treeNode* temp = NULL;

	if (root) {
		temp = NthPostOrder(root->lChild, index);
		if (temp)
			return temp;

		temp = NthPostOrder(root->rChild, index);
		if (temp)
			return temp;

		count++;

		if (count == index) {
			printf(" %d ", root->value);
			return root;
		}
	}
	return NULL;
}

//해결책 9-11
treeNode* NthInOrder(treeNode* root, int index) /*  중위 순회  */
{
	static int count = 0;
	treeNode* temp = NULL;

	if (root) {
		temp = NthInOrder(root->lChild, index);
		if (temp)
			return temp;

		count++;
		if (count == index)	{
			printf(" %d ", root->value);
			return root;
		}

		temp = NthInOrder(root->rChild, index);
		if (temp)
			return temp;
	}
	return NULL;
}

//해결책 9-12
void printAllPathUtil(treeNode* curr, Stack* stk)
{
	if (curr == NULL)
		return;
	StackPush(stk, curr->value);
	if (curr->lChild == NULL && curr->rChild == NULL) {
		StackPrint(stk);
		StackPop(stk);
		return;
	}
	printAllPathUtil(curr->rChild, stk);
	printAllPathUtil(curr->lChild, stk);
	StackPop(stk);
}

void printAllPath(treeNode* root)
{
	Stack stk;
	StackInitialize(&stk);
	printAllPathUtil(root, &stk);
}

//해결책 9-13
int numNodes(treeNode* root)
{
	if (!root)
		return 0;
	else
		return (1 + numNodes(root->rChild) + numNodes(root->lChild));
}

//해결책 9-14
int sumAllBT(treeNode* root)
{
	if (root == NULL)
		return 0;

	return root->value + sumAllBT(root->lChild) + sumAllBT(root->rChild);
}

//해결책 9-15
int numLeafs(treeNode* root)
{
	if (!root)
		return 0;
	if (!root->lChild && !root->rChild)
		return 1;
	else
		return (numLeafs(root->rChild) + numLeafs(root->lChild));
}

//해결책 9-16
int numFullNodesBT(treeNode* root)
{
	int count = 0;
	int left, right;

	if (root == NULL)
		return 0;

	left = numFullNodesBT(root->lChild);
	right = numFullNodesBT(root->rChild);

	count = left + right;

	if (root->lChild && root->rChild) // 이 줄은 다른 문제를 풀기 위해 변경될 수 있습니다.
		count++;

	return count;
}

//해결책 9-17
int searchBT(treeNode* root, int value)
{
	int max;
	int left, right;

	if (root == NULL)
		return 0;

	if (root->value == value)
		return 1;

	left = searchBT(root->lChild, value);
	if (left)
		return 1;

	right = searchBT(root->rChild, value);
	if (right)
		return 1;

	return 0;
}

//해결책 9-18
int findMaxBT(treeNode* root)
{
	int max;
	int left, right;

	if (root == NULL)
		return INT_MIN;

	max = root->value;
	left = findMaxBT(root->lChild);
	right = findMaxBT(root->rChild);

	if (left > max)
		max = left;
	if (right > max)
		max = right;

	return max;
}

//해결책 9-19
int treeDepth(treeNode* root)
{
	if (!root)
		return 0;
	else
	{
		int lDepth = treeDepth(root->lChild);
		int rDepth = treeDepth(root->rChild);

		if (lDepth > rDepth)
			return lDepth + 1;
		else
			return rDepth + 1;
	}
}

int maxDepthBT(treeNode* node)
{
	if(!node)
		return 0;
		
	int ans = maxDepthBT(node->lChild);
	int right = maxDepthBT(node->rChild);
	if(ans < right)
		ans = right;

	return ans + 1;
}

//해결책 9-20
int maxLengthPathBT(treeNode* root) // 지름
{
	int max;
	int leftPath, rightPath;
	int leftMax, rightMax;

	if (root == NULL)
		return 0;

	leftPath = maxDepthBT(root->lChild);
	rightPath = maxDepthBT(root->rChild);

	max = leftPath + rightPath + 1;

	leftMax = maxLengthPathBT(root->lChild);
	rightMax = maxLengthPathBT(root->rChild);

	if (leftMax > max)
		max = leftMax;

	if (rightMax > max)
		max = rightMax;

	return max;
}

//해결책 9-21
treeNode* LcaBT(treeNode* root, treeNode* firstPtr, treeNode* secondPtr)
{
	treeNode* left, * right;

	if (root == NULL)
		return NULL;

	if (root == firstPtr || root == secondPtr)
		return root;

	left = LcaBT(root->lChild, firstPtr, secondPtr);
	right = LcaBT(root->rChild, firstPtr, secondPtr);

	if (left && right)
		return root;
	else if (left)
		return left;
	else
		return right;
}

//해결책 9-22
int isIdentical(treeNode* root1, treeNode* root2)
{
	if (!root1 && !root2)
		return 1;
	else if (!root1 || !root2)
		return 0;
	else
		return (isIdentical(root1->lChild, root2->lChild) && isIdentical(root1->rChild, root2->rChild) && (root1->value == root2->value));
}

//해결책 9-23
treeNode* copyTree(treeNode* root)
{
	treeNode* temp;

	if (root != NULL) {
		temp = (treeNode*)malloc(sizeof(treeNode));
		if (!temp)
			return NULL;
		temp->value = root->value;
		temp->lChild = copyTree(root->lChild);
		temp->rChild = copyTree(root->rChild);
		return temp;
	}
	else
		return NULL;
}

//해결책 9-24
treeNode * copyMirrorTree(treeNode * root)
{
	treeNode* temp;

	if (root != NULL) {
		temp = (treeNode*)malloc(sizeof(treeNode));
		if (!temp)
			return NULL;

		temp->value = root->value;
		temp->lChild = copyMirrorTree(root->rChild);
		temp->rChild = copyMirrorTree(root->lChild);
		return temp;
	}
	else
		return NULL;
}

//해결책 9-25
treeNode* freeTree(treeNode* root)
{
	if (root) {
		root->lChild = freeTree(root->lChild);
		root->rChild = freeTree(root->rChild);

		if (root->lChild == NULL && root->rChild == NULL) {
			free(root);
			return NULL;
		}
	}
	return NULL;
}

void freeTree2(treeNode **rootPtr)
{
	*rootPtr = freeTree(*rootPtr);
}

//해결책 9-26-1
int isCompleteTree(treeNode* root)
{
	Queue que;
	QueueInitialize(&que);
	treeNode* temp = NULL;
	int noChild = 0;
	if (root != NULL)
		QueueAdd(&que, (int)root);
	while (QueueSize(&que) != 0) {
		temp = (treeNode*)QueueRemove(&que);
		if (temp->lChild != NULL) {
			if (noChild == 1)
				return 0;
			QueueAdd(&que, (int)temp->lChild);
		}
		else {
			noChild = 1;
		}
		if (temp->rChild != NULL) {
			if (noChild == 1)
				return 0;
			QueueAdd(&que, (int)temp->rChild);
		}
		else {}
			noChild = 1;
		}
	}
	return 1;
}

//해결책 9-26-2
int isCompleteTreeUtil(treeNode* curr, int index, int count)
{
	if (curr == NULL)
		return 1;
	if (index > count)
		return 0;
	return isCompleteTreeUtil(curr->lChild, index * 2 + 1, count) && isCompleteTreeUtil(curr->rChild, index * 2 + 2, count);
}

int isCompleteTree2(treeNode* root)
{
	int count = findCount(root);
	return isCompleteTreeUtil(root, 0, count);
}


//해결책 9-27-1
int isHeapUtil(treeNode* curr, int parentValue)
{
	if (curr == NULL)
		return 1;
	if (curr->value < parentValue)
		return 0;
	return (isHeapUtil(curr->lChild, curr->value) && isHeapUtil(curr->rChild, curr->value));
}

int isHeap(treeNode* root)
{
	int infi = -9999999;
	return (isCompleteTree(root) && isHeapUtil(root, infi));
}

//해결책 9-27-1
int isHeapUtil2(treeNode* curr, int index, int count, int parentValue)
{
	if (curr == NULL)
		return 1;
	if (index > count)
		return 0;
	if (curr->value < parentValue)
		return 0;
	return isHeapUtil2(curr->lChild, index * 2 + 1, count, curr->value) && isHeapUtil2(curr->rChild, index * 2 + 2, count, curr->value);
}

int isHeap2(treeNode* root)
{
	int count = findCount(root);
	int parentValue = -9999999;
	return isHeapUtil2(root, 0, count, parentValue);
}

//해결책 9-28
void iterativePreOrder(treeNode* root)
{
	Stack stk;
	StackInitialize(&stk);
	treeNode* curr = NULL;
	if (root != NULL)
		StackPush(&stk, (int)root);
	while (StackSize(&stk) != 0) {
		curr = (treeNode*)StackPop(&stk);
		printf("%d ", curr->value);
		if (curr->rChild != NULL)
			StackPush(&stk, (int)curr->rChild);
		if (curr->lChild != NULL)
			StackPush(&stk, (int)curr->lChild);
	}
}

//해결책 9-29
void iterativePostOrder(treeNode* root)
{
	Stack stk;
	StackInitialize(&stk);
	Stack visited;
	StackInitialize(&visited);
	treeNode* curr = NULL;
	int vtd;

	if (root != NULL) {
		StackPush(&stk, (int)root);
		StackPush(&visited, 0);
	}

	while (StackSize(&stk) != 0) {
		curr = (treeNode*)StackPop(&stk);
		vtd = StackPop(&visited);
		if (vtd == 1)
			printf("%d ", curr->value);
		else{ 
			StackPush(&stk, (int)curr);
			StackPush(&visited, 1);
			if (curr->rChild != NULL) {
				StackPush(&stk, (int)curr->rChild);
				StackPush(&visited, 0);
			}
			if (curr->lChild != NULL) {
				StackPush(&stk, (int)curr->lChild);
				StackPush(&visited, 0);
			}
		}
	}
}

//해결책 9-30
void iterativeInOrder(treeNode* root)
{
	Stack stk;
	StackInitialize(&stk);
	Stack visited;
	StackInitialize(&visited);
	treeNode* curr = NULL;
	int vtd;

	if (root != NULL) {
		StackPush(&stk, (int)root);
		StackPush(&visited, 0);
	}

	while (StackSize(&stk) != 0) {
		curr = (treeNode*)StackPop(&stk);
		vtd = StackPop(&visited);
		if (vtd == 1)
			printf("%d ", curr->value);
		else {
			if (curr->rChild != NULL) {
				StackPush(&stk, (int)curr->rChild);
				StackPush(&visited, 0);
			}
			StackPush(&stk, (int)curr);
			StackPush(&visited, 1);
			if (curr->lChild != NULL) {
				StackPush(&stk, (int)curr->lChild);
				StackPush(&visited, 0);
			}
		}
	}
}

//해결책 9-31
treeNode* treeToListRec(treeNode* curr)
{
	treeNode* head, * tail, * tempHead;

	if (!curr)
		return NULL;

	if (curr->lChild == NULL && curr->rChild == NULL) {
		curr->lChild = curr;
		curr->rChild = curr;
		return curr;
	}
	if (curr->lChild) {
		head = treeToListRec(curr->lChild);
		tail = head->lChild;
		curr->lChild = tail;
		tail->rChild = curr;
	}
	else
		head = curr;

	if (curr->rChild) {
		tempHead = treeToListRec(curr->rChild);
		tail = tempHead->lChild;
		curr->rChild = tempHead;
		tempHead->lChild = curr;
	}
	else
		tail = curr;

	head->lChild = tail;
	tail->rChild = head;
	return head;
}

//해결책 9-32
treeNode* CreateBinaryTreeUtil(int arr[], int start, int end)
{
	treeNode* curr;
	if (start > end)
		return NULL;
	int mid = (start + end) / 2;
	curr = (treeNode*)malloc(sizeof(treeNode));
	curr->value = arr[mid];
	curr->lChild = CreateBinaryTreeUtil(arr, start, mid - 1);
	curr->rChild = CreateBinaryTreeUtil(arr, mid + 1, end);
	return curr;
}

treeNode* CreateBinaryTree(int arr[], int size)
{
	return CreateBinaryTreeUtil(arr, 0, size - 1);
}

int main2()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	treeNode* t2 = CreateBinaryTree(arr, 10);
}

//해결책 9-33
treeNode* insertNode(treeNode* root, int value)
{
	if (root == NULL) {
		root = (treeNode*)malloc(sizeof(treeNode));
		if (root == NULL) {
			printf("fallel memory shortage ...");
			return root;
		}
		root->value = value;
		root->lChild = root->rChild = NULL;
	}
	else {
		if (root->value >= value)
			root->lChild = insertNode(root->lChild, value);
		else
			root->rChild = insertNode(root->rChild, value);
	}
	return root;
}

void insertNode2(treeNode** ptrRoot, int value)
{
	*ptrRoot = insertNode(*ptrRoot, value);
}

//해결책 9-34
treeNode* findNode(treeNode* root, int value)
{
	if (!root)
		return NULL;
	if (root->value == value)
		return root;
	else {
		if (root->value > value)
			return findNode(root->lChild, value);
		else
			return findNode(root->rChild, value);
	}
}

//해결책 9-35
treeNode* findMin(treeNode* root)
{
	if (root)
		while (root->lChild) {
			root = root->lChild;
		}
	return root;
}

int minValue(treeNode *root)
{
	if (root) {
		while (root->lChild) {
			root = root->lChild;
		}
		return root->value;
	}
	return 99999;
}

//해결책 9-36
treeNode* findMax(treeNode* root)
{
	if (root) {
		while (root->rChild) {
			root = root->rChild;
		}
	}
	return root;
}

int maxValue(treeNode* root)
{
	if (root) {
		while (root->rChild) {
			root = root->rChild;
		}
		return root->value;
	}
	return -999;
}

//해결책 9-37-1
int isBST(treeNode* root)
{
	if (!root)
		return 1;

	if (root->lChild && maxValue(root->lChild) > root->value)
		return 0;
	if (root->rChild && minValue(root->rChild) <= root->value)
		return 0;

	return (isBST(root->lChild) && isBST(root->rChild));
}

//해결책 9-37-2
int isBSTUtil2(treeNode* root, int min, int max)
{
	if (!root)
		return 1;

	if (root->value < min || root->value > max)
		return 0;

	return isBSTUtil2(root->lChild, min, root->value) && isBSTUtil2(root->rChild, root->value, max);
}

#define INT_MIN -99999
#define INT_MAX 99999
int isBST2(treeNode* root)
{
	return isBSTUtil2(root, INT_MIN, INT_MAX);
}

//해결책 9-37-3
int isBSTUtil3(treeNode* root, int* value) /* 중위 순회 */
{
	int ret;
	if (root) {
		ret = isBSTUtil3(root->lChild, value);
		if (!ret)
			return 0;

		if (*value > root->value)
			return 0;

		*value = root->value;

		ret = isBSTUtil3(root->rChild, value);
		if (!ret)
			return 0;
	}
	return 1;
}

int isBST3(treeNode* root)
{
	int temp = 0;
	return isBSTUtil3(root, &temp);
}

//해결책 9-38
treeNode* deleteNode(treeNode* root, int value)
{
	treeNode* temp = NULL;
	if (root) {
		if (root->value == value) {
			if (root->lChild == NULL && root->rChild == NULL) {
				free(root);
				return NULL;
			}
			else {
				if (root->lChild == NULL) {
					temp = root->rChild;
					free(root);
					return temp;
				}
				if (root->rChild == NULL) {
					temp = root->lChild;
					free(root);
					return temp;
				}

				temp = findMax(root->lChild);
				root->value = temp->value;
				root->lChild = deleteNode(root->lChild, temp->value);
			}
		}
		else {
			if (root->value > value)
				root->lChild = deleteNode(root->lChild, value);
			else
				root->rChild = deleteNode(root->rChild, value);
		}
	}
	return root;
}

void deleteNodeWrapper(treeNode** rootPtr, int value)
{
	*rootPtr = deleteNode(*rootPtr, value);
}

//해결책 9-39
treeNode* LcaBST(treeNode* root, treeNode* firstPtr, treeNode* secondPtr)
{
	if (!firstPtr || !secondPtr || !root)
		return root;

	if (root->value > firstPtr->value && root->value > secondPtr->value) {
		return LcaBST(root->lChild, firstPtr, secondPtr);
	}
	if (root->value < firstPtr->value && root->value < secondPtr->value) {
		return LcaBST(root->rChild, firstPtr, secondPtr);
	}
	return root;
}

//해결책 9-40
treeNode* trimOutsideRange(treeNode* root, int min, int max)
{
	treeNode* tempNode;
	if (root == NULL)
		return NULL;

	root->rChild = trimOutsideRange(root->rChild, min, max);
	root->lChild = trimOutsideRange(root->lChild, min, max);

	if (root->value < min) {
		tempNode = root->rChild;
		freeTree(root->lChild);
		free(root);
		return tempNode;
	}

	if (root->value > max) {
		tempNode = root->lChild;
		freeTree(root->rChild);
		free(root);
		return tempNode;
	}

	return root;
}

//해결책 9-41
void printInRange(treeNode* root, int min, int max)
{
	if (!root)
		return;

	printInRange(root->lChild, min, max);

	if (root->value >= min && root->value <= max)
		printf(" %d ", root->value);

	printInRange(root->rChild, min, max);
}

//해결책 9-42-1
int CeilBST(treeNode* root, int value)
{
	int ceil = 0;
	while (root) {
		if (root->value == value) {
			ceil = root->value;
			break;
		}
		else if (root->value > value) {
			ceil = root->value;
			root = root->lChild;
		}
		else
		{
			root = root->rChild;
		}
	}
	return ceil;
}

//해결책 9-42-2
int FloorBST(treeNode* root, int value)
{
	int floor = 0;
	while (root) {
		if (root->value == value) {
			floor = root->value;
			break;
		}
		else if (root->value > value) {
			root = root->lChild;
		}
		else {
			floor = root->value;
			root = root->rChild;
		}
	}
	return floor;
}

//해결책 9-44
int isBSTArray(int preorder[], int size)
{
	Stack stk;
	int value;
	StackInitialize(&stk);
	int root = -999999;
	for (int i = 0; i < size; i++) {
		value = preorder[i];

		// 오른쪽 자식의 값이 루트보다 작은지 확인합니다.
		if (value < root)
			return 0;
		// 먼저 왼쪽 자식이 제거됩니다.
		// 마지막에 꺼낸 값이 루트가 됩니다.
		while (StackSize(&stk) > 0 && StackTop(&stk) < value)
			root = StackPop(&stk);
		// 스택에 현재 값을 추가합니다.
		StackPush(&stk, value);
	}
	return 1;
}

int main3()
{
	int preorder1[] = { 30, 20, 25, 70, 200 };
	printf("Is BST Array: %d \n", isBSTArray(preorder1, 5));
}