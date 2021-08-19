#include <iostream>
#include <vector>
#include <limits>

/*
一种动态集合结构，至少需要支持Insert、Search、Delete字典操作。
散列表
    散列表是实现字典操作的一种有效数据结构。
    当实际存储的关键字数目比全部的可能关键字总数要小时，采用散列表就成为直接数组寻址的一种有效替代，
    因为散列表使用一个长度与实际存储的关键字数目成比例的数组来存储。
*/

/*
直接寻址表
    一个关键字对应一个空位
*/
int directorAddressSearch(std::vector<int> numList, int index) {
    return numList[index];
}
void directAddressInsert(std::vector<int> numList, int index, int value) {
    numList[index] = value;
}
void directAddressDelete(std::vector<int> numList, int index) {
    numList[index] = INT_MAX;
}

/*
散列表
    当存储在字典中的关键字集合K比所有可能的关键字的全域U要小许多时，散列表需要的存储空间要比直接寻址表少得多。
    特别地，我们能将散列表的存储需求降至O(|K|)，同时散列表中查找一个元素的优势仍得到保持，只需要O(1)的时间。
    问题是这个界是针对平均情况时间的，而对直接寻址来说，它是适用于最坏情况时间的。

    在直接寻址方式下，具有关键字k的元素被存放在槽k中。
    在散列方式下，该元素存放在槽h(k)中;即利用散列函数(hash function)h，由关键字k计算出槽的位置。

    这里存在一个问题:两个关键字可能映射到同一个槽中。我们称这种情形为冲突(collision)。幸运的是，我们能找到有效的方法来解决冲突。
    当然，理想的解决方法是避免所有的冲突。我们可以试图选择一个合适的散列函数h来做到这一点。
    一个想法就是使h尽可能的“随机”，从而避免冲突或者使冲突的次数最小化。
    但是，由于|U|>m，故至少有两个关键字其散列值相同，所以要想完全避免冲突是不可能的。
    因此，我们一方面可以通过精心设计的散列函数来尽量减少冲突的次数，另一方面仍需要有解决可能出现冲突的办法。
  
*/

/*
解决可能出现冲突的办法1：
    链接法
*/
int geth(int index) {
    return index % 100;
}
void chaninedHashInsert(std::vector<std::vector<std::pair<int,int>>> numVecVec, int index, int key) {
    auto insertIndex = geth(index);
    auto numVec = numVecVec[insertIndex];
    numVec.push_back(std::make_pair(index, key));
}
int chaninedHashSearch(std::vector<std::vector<std::pair<int, int>>> numVecVec, int index) {
    auto insertIndex = geth(index);
    auto numVec = numVecVec[insertIndex];
    for (auto iter = numVec.cbegin(); iter != numVec.cend(); iter++) {
        if (iter->first == index) {
            return iter->second;
        }
    }
}
void chainedHashDelete(std::vector<std::vector<std::pair<int, int>>> numVecVec, int index) {
    auto insertIndex = geth(index);
    auto numVec = numVecVec[insertIndex];
    for (auto iter = numVec.cbegin(); iter != numVec.cend(); iter++) {
        if (iter->first == index) {
            numVec.erase(iter);
            break;
        }
    }
}

/*
散列函数
    好的散列函数的特点
        应(近似地)满足简单均匀散列假设:每个关键字都被等可能地散列到m个槽位中的任何一个，
        并与其他关键字已散列到哪个槽位无关。

*/


int main()
{
    std::cout << "Hello World!\n";
}
