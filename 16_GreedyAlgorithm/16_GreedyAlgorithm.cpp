#include <iostream>
#include <vector>

/*
    贪心算法
*/

//------------------------------------------------------------------------------------------------------------------
/*
    活动选择问题
*/
/*
    递归方式
    Input:
        beginList:      活动开始时间集合
        endList:        活动结束时间集合
        beginPos:       从第几个活动开始
        maxNum:         活动总数

*/
std::vector<uint32_t> recursiveActivitySelector(std::vector<int32_t> beginList, std::vector<int32_t> endList, 
    uint32_t beginPos, uint32_t maxNum) 
{
    std::vector<uint32_t> result;
    auto nextPos = beginPos + 1;
    while (nextPos <= maxNum && beginList[nextPos] < endList[beginPos])
        nextPos = nextPos + 1;
    if (nextPos <= maxNum) {
        result.push_back(nextPos);
        auto currResult = recursiveActivitySelector(beginList, endList, nextPos, maxNum);
        for (auto iter = currResult.cbegin(); iter != currResult.cend(); iter++) {
            result.push_back(*iter);
        }
        return result;
    }
    return result;
}
/*
    迭代方式
*/
std::vector<uint32_t> greedyActivitySelector(std::vector<int32_t> beginList, std::vector<int32_t> endList) {
    auto size = beginList.size();
    std::vector<uint32_t> result;
    result.push_back(1);
    uint32_t currPos = 1;
    for (auto nextPos = 2; nextPos < size; nextPos++) {
        if (beginList[nextPos] >= endList[currPos]) {
            result.push_back(nextPos);
            currPos = nextPos;
        }
    }

    return result;
}
//------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------

//赫夫曼编码


//------------------------------------------------------------------------------------------------------------------


int main()
{
    std::vector<int32_t> beginList;
    std::vector<int32_t> endList;
    beginList.push_back(0);
    beginList.push_back(1);
    beginList.push_back(3);
    beginList.push_back(0);
    beginList.push_back(5);
    beginList.push_back(3);
    beginList.push_back(5);
    beginList.push_back(6);
    beginList.push_back(8);
    beginList.push_back(8);
    beginList.push_back(2);
    beginList.push_back(12);

    endList.push_back(0);
    endList.push_back(4);
    endList.push_back(5);
    endList.push_back(6);
    endList.push_back(7);
    endList.push_back(9);
    endList.push_back(9);
    endList.push_back(10);
    endList.push_back(11);
    endList.push_back(12);
    endList.push_back(14);
    endList.push_back(16);

    auto result = recursiveActivitySelector(beginList, endList, 0, 11);
    

    result = greedyActivitySelector(beginList, endList);
    std::cout << "Hello World!" << std::endl;
}