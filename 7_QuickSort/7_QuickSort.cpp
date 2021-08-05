#include <iostream>
#include <vector>
void printVector(int vecSize);
void initVec(std::vector<int>& numVec);
void printVec(std::vector<int>& numList);

/*
快速排序
    对于包含n个数的输入数组来说，快速排序是一种最坏情况时间复杂度为O(n^2)的排序算法。
    虽然最坏情况时间复杂度很差，但是快速排序通常是实际排序应用中最好的选择，因为它的平均性能非常好:
    它的期望时间复杂度是O(nlgn)，而且O(nlgn)中隐含的常数因子非常小。
    是原址排序。

快速排序思想：
    分解:
        数组A[p..r]被划分为两个(可能为空)子数组A[p .. q-1]和A[q+1 .. r]，
        使得A[p .. q-1]中的每一个元素都小于等于A[q]，
        而A[q]也小于等于 A[q+1 .. r]中的每个元素。
        其中，计算下标q也是划分过程的一部分。
    解决:
        通过递归调用快速排序，对子数组A[p .. q-1]和A[q+1 .. r]进行排序。
    合并:
        因为子数组都是原址排序的，所以不需要合并操作:数组A[p .. r]已经有序。

性能：
    快速排序的运行时间依赖于划分是否平衡，而平衡与否又依赖于用于划分的元素。
    如果划分是平衡的，那么快速排序算法性能与归并排序一样。 O(nlogn)
    如果划分是不平衡的，那么快速排序的性能就接近于插入排序了。O(n^(1-2)) n 到 n^2 之间

*/
/*
实现对子数组的原址重排
    对于数组numVec来说，leftIndex leftRightIndex, rightLeftIndex, rightIndex将其分为两个部分
    leftIndex .. leftRightIndex | x | rightLeftIndex .. rightIndex
*/
int partition(std::vector<int>& numVec, int leftIndex, int rightIndex) {
    int x = numVec[rightIndex];
    int leftRightIndex = leftIndex - 1;
    for (int rightLeftIndex = leftIndex; rightLeftIndex < rightIndex; rightLeftIndex++) {
        if (numVec[rightLeftIndex] <= x) {
            leftRightIndex = leftRightIndex + 1;
            int exchangeNum = numVec[leftRightIndex];
            numVec[leftRightIndex] = numVec[rightLeftIndex];
            numVec[rightLeftIndex] = exchangeNum;
        }
    }
    // 循环执行完
    //leftIndex ..leftRightIndex | rightLeftIndex .. rightIndex - 1| x

    leftRightIndex = leftRightIndex + 1;
    numVec[rightIndex] = numVec[leftRightIndex];
    numVec[leftRightIndex] = x;

    return leftRightIndex;
}
void quickSort(std::vector<int>& numVec, int leftIndex, int rightIndex) {
    if (leftIndex < rightIndex) {
        int centerIndex = partition(numVec, leftIndex, rightIndex);
        quickSort(numVec, leftIndex, centerIndex - 1);
        quickSort(numVec, centerIndex + 1, rightIndex);
    }
}

/*
快速排序的随机化版本
    随机抽样是从子数组A[p..r]中随机选择一个元素作为主元。
    为达到这一目的，首先将A[r]与从A[p .. r]中随机选出的一个元素交换。
    通过对序列p，…，r的随机抽样，我们可以保证主元元素r = A[r]是等概率地从子数组的r-p+1个元素中选取的。
    因为主元元素是随机选取的，我们期望在平均情况下，对输入数组的划分是比较均衡的。
*/
int randomizedPartition(std::vector<int>& numVec, int leftIndex, int rightIndex) {
    int index = rand() % (rightIndex - leftIndex + 1) + leftIndex;
    int exchangeNum = numVec[index];
    numVec[index] = numVec[rightIndex];
    numVec[rightIndex] = exchangeNum;
    return partition(numVec, leftIndex, rightIndex);
}
void randomizedQuickSort(std::vector<int>& numVec, int leftIndex, int rightIndex) {
    if (leftIndex < rightIndex) {
        int centerIndex = randomizedPartition(numVec, leftIndex, rightIndex);
        randomizedQuickSort(numVec, leftIndex, centerIndex - 1);
        randomizedQuickSort(numVec, centerIndex + 1, rightIndex);
    }
}


int main()
{
    std::vector<int> numVec;
    initVec(numVec);

    quickSort(numVec, 0, numVec.size() - 1);
    printVec(numVec);

    numVec.clear();
    initVec(numVec);
    randomizedQuickSort(numVec, 0, numVec.size() - 1);
    printVec(numVec);
}

void initVec(std::vector<int>& numVec) {
    numVec.push_back(41);
    numVec.push_back(18467);
    numVec.push_back(6334);
    numVec.push_back(26500);
    numVec.push_back(19169);
    numVec.push_back(15724);
    numVec.push_back(11478);
    numVec.push_back(29358);
    numVec.push_back(26962);
    numVec.push_back(24464);
    numVec.push_back(5705);
    numVec.push_back(28145);
    numVec.push_back(23281);
    numVec.push_back(16827);
    numVec.push_back(9961);
    numVec.push_back(491);
    numVec.push_back(2995);
    numVec.push_back(11942);
    numVec.push_back(4827);
    numVec.push_back(5436);
    numVec.push_back(32391);
    numVec.push_back(14604);
    numVec.push_back(3902);
    numVec.push_back(153);
    numVec.push_back(292);
    numVec.push_back(12382);
    numVec.push_back(17421);
    numVec.push_back(18716);
    numVec.push_back(19718);
    numVec.push_back(19895);
    numVec.push_back(5447);
    numVec.push_back(21726);
    numVec.push_back(14771);
    numVec.push_back(11538);
    numVec.push_back(1869);
    numVec.push_back(19912);
    numVec.push_back(25667);
    numVec.push_back(26299);
    numVec.push_back(17035);
    numVec.push_back(9894);
    numVec.push_back(28703);
    numVec.push_back(23811);
    numVec.push_back(31322);
    numVec.push_back(30333);
    numVec.push_back(17673);
    numVec.push_back(4664);
    numVec.push_back(15141);
    numVec.push_back(7711);
    numVec.push_back(28253);
    numVec.push_back(6868);
    numVec.push_back(25547);
    numVec.push_back(27644);
    numVec.push_back(32662);
    numVec.push_back(32757);
    numVec.push_back(20037);
    numVec.push_back(12859);
    numVec.push_back(8723);
    numVec.push_back(9741);
    numVec.push_back(27529);
    numVec.push_back(778);
    numVec.push_back(12316);
    numVec.push_back(3035);
    numVec.push_back(22190);
    numVec.push_back(1842);
    numVec.push_back(288);
    numVec.push_back(30106);
    numVec.push_back(9040);
    numVec.push_back(8942);
    numVec.push_back(19264);
    numVec.push_back(22648);
    numVec.push_back(27446);
    numVec.push_back(23805);
    numVec.push_back(15890);
    numVec.push_back(6729);
    numVec.push_back(24370);
    numVec.push_back(15350);
    numVec.push_back(15006);
    numVec.push_back(31101);
    numVec.push_back(24393);
    numVec.push_back(3548);
    numVec.push_back(19629);
    numVec.push_back(12623);
    numVec.push_back(24084);
    numVec.push_back(19954);
    numVec.push_back(18756);
    numVec.push_back(11840);
    numVec.push_back(4966);
    numVec.push_back(7376);
    numVec.push_back(13931);
    numVec.push_back(26308);
    numVec.push_back(16944);
    numVec.push_back(32439);
    numVec.push_back(24626);
    numVec.push_back(11323);
    numVec.push_back(5537);
    numVec.push_back(21538);
    numVec.push_back(16118);
    numVec.push_back(2082);
    numVec.push_back(22929);
    numVec.push_back(16541);
}
void printVector(int vecSize) {
    for (int i = 0; i < vecSize; i++) {
        std::cout << "numVec.push_back(" << rand() << ");" << std::endl;
    }
}

void printVec(std::vector<int>& numList) {
    for (auto begin = numList.cbegin(); begin != numList.cend(); begin++) {
        std::cout << *begin << ",";
    }
    std::cout << std::endl;
}