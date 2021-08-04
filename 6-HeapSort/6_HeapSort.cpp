#include <iostream>

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
int getLeftIndex(int i) {
    return (i << 1);
}
int getRightIndex(int i) {
    return (i << 1) + 1;
}
void maxHeapify(int* numList, int i, int numListSize) {
    int leftIndex = getLeftIndex(i);
    int rightIndex = getRightIndex(i);

    int largestIndex;
    if (leftIndex <= numListSize && numList[leftIndex] > numList[i])
        largestIndex = leftIndex;
    else
        largestIndex = i;
    if (rightIndex <= numListSize && numList[rightIndex] > numList[largestIndex])
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
    for (int i = numListSize << 1; i > 0; i--) {
        maxHeapify(numList, i, numListSize);
    }
}

int main()
{
    std::cout << "Hello World!\n";
}