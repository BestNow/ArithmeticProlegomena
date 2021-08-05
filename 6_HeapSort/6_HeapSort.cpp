#include <iostream>

void printNumList(int numListSize);
int* getNumList(int* numListSize);
void outputNumList(int* preSortList, int num);

/*
	堆排序
		与归并排序一样，但不同于插入排序的是，堆排序的时间复杂度是O(nlgn)。
		而与插入排序相同，但不同于归并排序的是，堆排序同样具有空间原址性:任何时候都只需要常数个额外的元素空间存储临时数据。
		因此，堆排序是集合了我们目前已经讨论的两种排序算法优点的一种排序算法。

		(二叉)堆是一个数组，它可以被看成一个近似的完全二叉树(见B.5.3节)。
		树上的每一个结点对应数组中的一个元素。除了最底层外，该树是完全充满的，而且是从左向右填充。
		表示堆的数组A包括两个属性:A.length(通常)给出数组元素的个数，A.heap-size表示有多少个堆元素存储在该数组中。
		也就是说，虽然A[1 .. A.length]可能都存有数据，但只有A[1 .. A.heap-size]中存放的是堆的有效元素，这里，0≤A.heap-size≤A.length。
		树的根结点是A[1]，这样给定一个结点的下标i，我们很容易计算得到它的父结点、左孩子和右孩子的下标:
		Parent(i)
			return A[i >> 1];

		Left(i)
			return A[i << 1];

		Right(i)
			return A[i << 1 + 1];

	分类：
		二叉堆可以分为两种形式:最大堆和最小堆。
		在这两种堆中，结点的值都要满足堆的性质，但一些细节定义则有所差异。
		在最大堆中，最大堆性质是指除了根以外的所有结点i都要满足:
			A[PARENT(i)]≥A[i] 也就是说，某个结点的值至多与其父结点一样大。
		最小堆的组织方式正好相反:最小堆性质是指除了根以外的所有结点主都有:
			A[PARENT(i)]≤A[i] 最小堆中的最小元素存放在根结点中。

	在堆排序算法中，使用的是最大堆，最小堆通常用于构造优先队列。
*/

/*
	MAX-HEAPIFY是用于维护最大堆性质的重要过程。
		它的输人为一个数组A和一个下标i。
		在调用MAX-HEAPIFY的时候，我们假定根结点为LEFT(i)和RIGHT(i)的二叉树都是最大堆,
		但这时A[i]有可能小于其孩子，这样就违背了最大堆的性质。
		MAX-HEAPIFY通过让A[i]的值在最大堆中“逐级下降”，从而使得以下标i为根结点的子树重新遵循最大堆的性质。
*/
int getParentIndex(int i) {
	return (i + 1) >> 1;
}
int getLeftIndex(int i) {
	return ((i + 1) << 1) - 1;
}
int getRightIndex(int i) {
	return ((i+1) << 1);
}
void maxHeapify(int* numList, int i, int numListSize) {
	int leftIndex = getLeftIndex(i);
	int rightIndex = getRightIndex(i);

	int largestIndex;
	if (leftIndex < numListSize && numList[leftIndex] > numList[i])
		largestIndex = leftIndex;
	else
		largestIndex = i;
	if (rightIndex < numListSize && numList[rightIndex] > numList[largestIndex])
		largestIndex = rightIndex;

	if (largestIndex != i) {
		int exchangeNum = numList[i];
		numList[i] = numList[largestIndex];
		numList[largestIndex] = exchangeNum;
		maxHeapify(numList, largestIndex, numListSize);
	}
}
/*
	我们可以用自底向上的方法利用过程MAX-HEAPIFY把一个大小为n=A.length的数组A[1 .. n]转换为最大堆。
	子数组A[n >> 1] + 1..n)中的元素都是树的叶结点。
	每个叶结点都可以看成只包含一个元素的堆。
	过程BUILD-MAX-HEAP对树中的其他结点都调用一次MAX-HEAPIFY。
*/
void buildMaxHeap(int* numList, int numListSize) {
	for (int i = (numListSize >> 1) - 1; i >= 0; i--) {
		maxHeapify(numList, i, numListSize);
	}
}
/*
堆排序
	初始时候，堆排序算法利用BUILD-MAX-HEAP将输入数组A[1 .. n]建成最大堆，其中n=A.length。
	因为数组中的最大元素总在根结点A[1]中，通过把它与A[n]进行互换，我们可以让该元素放到正确的位置。
	这时候，如果我们从堆中去掉结点n(这一操作可以通过减少A.heapsize的值来实现)，
	剩余的结点中，原来根的孩子结点仍然是最大堆，而新的根结点可能会违背最大堆的性质。
	为了维护最大堆的性质，我们要做的是调用MAX-HEAPIFY(A，1)，从而在A[1..n-1]上构造一个新的最大堆。
	堆排序算法会不断重复这一过程，直到堆的大小从n—1降到2。
*/
void heapSort(int* numList, int numListSize) {
	buildMaxHeap(numList, numListSize);     //数组中的最大元素总在根结点A[1]中
	for (int i = numListSize - 1; i >= 1; i--) {
		//通过把它与A[n]进行互换，我们可以让该元素放到正确的位置
		int exchangeNum = numList[0];
		numList[0] = numList[i];
		numList[i] = exchangeNum;

		numListSize = numListSize - 1;
		maxHeapify(numList, 0, numListSize);
	}
}


/*
关于堆排序的实际应用
	优先队列(priority queue)是一种用来维护由一组元素构成的集合S的数据结构，其中的每一个元素都有一个相关的值，称为关键字(key)。
	一个最大优先队列支持以下操作:
		INSERT(S，x):把元素工插入集合S中。这一操作等价于S = S并{x}。
		MAXIMUM(S):返回S中具有最大键字的元素。
		EXTRACT-MAX(S):去掉并返回S中的具有最大键字的元素。
		INCREASE-KEY(S，x，k):将元素x的关键字值增加到k，这里假设k的值不小于x的原关键字值。
	可以基于最大堆实现最大优先队列
	最小优先队列支持的操作包括
		INSERT
		MINIMUM
		EXTRACT-MIN
		DECREASE-KEY
	最小优先队列可以被用于基于事件驱动的模拟器。
*/
/*
	TODO:最大优先队列的实现，需保证数组按从大到小排序
*/
int heapMaxImum(int* numList) {
	return *numList;
}

// 去掉并返回S中的具有最大键字的元素。
int heapExtractMax(int* numList, int numListSize) {
	if (numListSize < 1)
		std::cout << "Error" << std::endl;

	int max = *numList;
	*numList = *(numList + numListSize - 1);
	numListSize = numListSize - 1;
	maxHeapify(numList, 1, numListSize);
	return max;
}

// 将元素x的关键字值增加到k，这里假设k的值不小于x的原关键字值。
int heapIncreaseKey(int* numList, int i, int key, int numListSize) {
	if (numList[i] > key)
		std::cout << "new key is smaller than current key" << std::endl;
	numList[i] = key;
	while (i > 0 && numList[getParentIndex(i)] < numList[i]) {
		int num = numList[i];
		numList[i] = numList[getParentIndex(i)];
		numList[getParentIndex(i)] = num;
		i = getParentIndex(i);
	}
	return 0;
}

int main()
{
	int numListSize = 0;
	int* numList = getNumList(&numListSize);

	heapSort(numList, numListSize);
	outputNumList(numList, numListSize);

	std::cout << "Hello World!\n";
}

int* getNumList(int* numListSize) {
	*numListSize = 10;
	int* numList = new int[10];
	numList[0] = 41;
	numList[1] = 18467;
	numList[2] = 6334;
	numList[3] = 26500;
	numList[4] = 19169;
	numList[5] = 15724;
	numList[6] = 11478;
	numList[7] = 29358;
	numList[8] = 26962;
	numList[9] = 24464;
	//numList[10] = 5705;

	return numList;
}

void printNumList(int numListSize) {
	for (int i = 0; i < numListSize; i++) {
		std::cout << "numList[" << i << "] = " << rand() << ";" << std::endl;
	}
}

void outputNumList(int* preSortList, int num) {
	for (int i = 0; i < num; i++) {
		std::cout << *(preSortList + i);
		if (i != num - 1) {
			std::cout << ",";
		}
	}

	std::cout << std::endl;
}