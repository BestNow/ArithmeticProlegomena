#include <iostream>
#include <time.h>

/*
雇佣问题
    假如你要雇用一名新的办公助理。你先前的雇用尝试都失败了，于是你决定找一个雇用代理。
    雇用代理每天给你推荐一个应聘者。你面试这个人，然后决定是否雇用他。
    你必须付给雇用代理一小笔费用，以便面试应聘者。
    然而要真的雇用一个应聘者需要花更多的钱，因为你必须辞掉目前的办公助理，还要付一大笔中介费给雇用代理。
    你承诺在任何时候，都要找最适合的人来担任这项职务。
    因此，你决定在面试完每个应聘者后，如果该应聘者比目前的办公助理更合适，就会辞掉当前的办公助理，然后聘用新的。
    你愿意为该策略付费，但希望能够估算该费用会是多少。
*/
void hireAssistant(int n) {
    int best = 0;
    for (int i = 0; i < n; i++) {
        //面试候选人 i
        //if(候选人i比候选人best更好){
            //best = i;
            //雇佣候选人 i
        //}
    }
}
/*
    对于诸如雇用问题之类的问题，其中假设输入的所有排列等可能出现往往有益，通过概率分析可以指导设计一个随机算法。
    我们不是假设输入的一个分布，而是设定一个分布。
    特别地，在算法运行前，先随机地排列应聘者，以加强所有排列都是等可能出现的性质。
    尽管已经修改了这个算法，我们仍希望雇用一个新的办公助理大约需要lnn次期望值。
    但是现在我们期望对于所有的输入它都是这种情况，而不是对于一个具有特别分布的输入。
*/
void randomizedHireAssistant(int n) {
    //随机排列候选名单
    int best = 0;
    for (int i = 0; i < n; i++) {
        //面试候选人 i
        //if(候选人i比候选人best更好){
            //best = i;
            //雇佣候选人 i
        //}
    }
}
/*
    产生随机排列的一个通常的方法是为数组的每个元素A[i]赋一个随机的优先级P[i]，然后依据优先级对数组A中的元素进行排序。
    例如，如果初始数组A=(1, 2, 3, 4)，随机选择的优先级P=(36, 3, 62, 19)，
    则将产生一个数组B=(2, 4, 1, 3)，因为第2个优先级最小，接下来是第4个，然后第1个，最后第3个。
*/
void permuteBySorting(int* numList, int length) {
    int* p = new int[length];
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        *(p + i) = rand();
    }
    int* returnList = new int[length];

    //以p为标准对numList进行排序
}
/*
    产生随机排列的一个更好方法是原址排列给定数组。
*/
void randomizeInPlace(int* numList, int length) {
    for (int i = 0; i < length; i++) {
        //交换 numList[i] 和 numList[j] //i < j < length  
    }
}

// 概率分析和指示器随机变量的进一步使用
/**
  * 第一个例子是生日悖论。
  * 一个屋子里人数必须要达到多少人，才能使其中两人生日相同的机会达到50%?
  */

int main()
{
    std::cout << "Hello World!\n";
}
