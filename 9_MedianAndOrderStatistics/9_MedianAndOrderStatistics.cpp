#include <iostream>
#include <vector>
void initVec(std::vector<int>&);
/*
    如果不考虑n的奇偶性，中位数总是出现在i = (n+1)/2(向下取整)处(下中位数)和i = (n+2)/2处(向上取整)(上中位数)。
    本书中所用的“中位数”都是指下中位数。
*/

/*
选择问题：
    从一个由n个互异的元素构成的集合中选择第i个顺序统计量的问题。
    假设集合中的元素都是互异的，但实际上我们所做的都可以推广到集合中包含重复元素的情形。
        输入:一个包含n个(互异的)数的集合A和一个整数i，1 <= i <= n.
        输出:元素x∈A，且A中恰好有i一1个其他元素小于它。
*/

/*
最小值，最大值

同时找到最大值最小值
    具体的方法是记录已知的最小值和最大值。
    不将每一个输人元素与当前的最小值和最大值进行比较
    而是对输入元素成对地进行处理。
    首先，我们将一对输人元素相互进行比较，然后把较小的与当前最小值比较，把较大的与当前最大值进行比较。
    这样，对每两个元素共需3次比较。
*/
int minimum(std::vector<int>& numVec) {
    int min = numVec[0];
    for (auto iter = numVec.cbegin(); iter != numVec.cend(); iter++) {
        if (min > *iter)
            min = *iter;
    }
    return min;
}

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

int randomizedPartition(std::vector<int>& numVec, int leftIndex, int rightIndex) {
    int index = rand() % (rightIndex - leftIndex + 1) + leftIndex;
    int exchangeNum = numVec[index];
    numVec[index] = numVec[rightIndex];
    numVec[rightIndex] = exchangeNum;
    return partition(numVec, leftIndex, rightIndex);
}


/*
    返回数组numVec[leftIndex  .. rightIndex]中第smallIndex小的元素
    41,153,288,292,491,778,1842,1869,2082,2995,
    3035,3548,3902,4664,4827,4966,5436,5447,5537,5705,
    6334,6729,6868,7376,7711,8723,8942,9040,9741,9894,
    9961,11323,11478,11538,11840,11942,12316,12382,12623,12859,
    13931,14604,14771,15006,15141,15350,15724,15890,16118,16541,
    16827,16944,17035,17421,17673,18467,18716,18756,19169,19264,
    19629,19718,19895,19912,19954,20037,21538,21726,22190,22648,
    22929,23281,23805,23811,24084,24370,24393,24464,24626,25547,
    25667,26299,26308,26500,26962,27446,27529,27644,28145,28253,
    28703,29358,30106,30333,31101,31322,32391,32439,32662,32757,
*/
int randomizedSelect(std::vector<int>& numVec, int leftIndex, int rightIndex, int smallIndex) {
    if (leftIndex == rightIndex) {
        return numVec[leftIndex];
    }

    auto keyIndex = randomizedPartition(numVec, leftIndex, rightIndex);
    auto leftNum = keyIndex - leftIndex;
    if (smallIndex == leftNum)
        return numVec[keyIndex];
    else if (smallIndex < keyIndex)
        return randomizedSelect(numVec, leftIndex, keyIndex - 1, smallIndex);
    else
        return randomizedSelect(numVec, keyIndex + 1, rightIndex, smallIndex - keyIndex + 1);
}

int main()
{
    std::vector<int> numVec;
    initVec(numVec);

    auto selectNum = randomizedSelect(numVec, 0, numVec.size() - 1, 2);

    std::cout << selectNum << std::endl;
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

