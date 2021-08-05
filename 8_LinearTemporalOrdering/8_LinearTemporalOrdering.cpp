#include <iostream>
#include <vector>
#include <limits>
/*
比较排序:
	在排序的最终结果中，各元素的次序依赖于它们之间的比较。
	第八章之前，我们介绍的所有排序算法都是比较排序。
	对包含n个元素的输人序列来说，任何比较排序在最坏情况下都要经过Q(nlgn)次比较。
	因此，归并排序和堆排序是渐近最优的，并且任何已知的比较排序最多就是在常数因子上优于它们。

线性时间排序：
	三种线性时间复杂度的排序算法:计数排序、基数排序和桶排序。
	这些算法是用运算而不是比较来确定排序顺序的。因此，下界(nlgn)对它们是不适用的。
*/

/*
计数排序：
	计数排序的基本思想是:对每一个输人元素x，确定小于x的元素个数。
	利用这一信息，就可以直接把x放到它在输出数组中的位置上了。
	例如，如果有17个元素小于x，则x就应该在第18个输出位置上。
	当有几个元素相同时，这一方案要略做修改。因为不能把它们放在同一个输出位置上。

	在计数排序算法的代码中，假设输人是一个数组A[1 .. n]，A.length = n。
	我们还需要两个数组: B[1 .. n]存放排序的输出，C[0 .. k]提供临时存储空间。

	在实际工作中，当k=O(n)时，我们一般会采用计数排序,这时的运行时间为渐近紧确(n)。
*/
void countingSort(std::vector<int>& numVec, std::vector<int>& outVector, int maxNum) {
	std::vector<int> tempVec;
	for (int i = 0; i <= maxNum; i++) {
		tempVec.push_back(0);
		outVector.push_back(INT_MAX);
	}
	for (auto iter = numVec.cbegin(); iter != numVec.cend(); iter++) {
		tempVec[numVec[*iter]] = tempVec[numVec[*iter]] + 1;
	}
	for (int i = 1; i < maxNum; i++) {
		tempVec[i] = tempVec[i] + tempVec[i - 1];
	}
	for (int i = numVec.size() - 1; i > 0; i--) {
		outVector[tempVec[numVec[i]]] = numVec[i];
		tempVec[numVec[i]] = tempVec[numVec[i]] - 1;
	}
}

/*
基数排序
*/



/*
桶排序
	桶排序(bucket sort)假设输入数据服从均匀分布，平均情况下它的时间代价为O(n)。
	桶排序假设输入是由一个随机过程产生，该过程将元素均匀、独立地分布在[0，1)区间上。

算法：
	桶排序将[0，1)区间划分为n个相同大小的子区间，或称为桶。
	然后，将n个输入数分别放到各个桶中。
	因为输入数据是均匀、独立地分布在[0, 1)区间上，所以一般不会出现很多数落在同一个桶中的情况。
	为了得到输出结果，我们先对每个桶中的数进行排序，然后遍历每个桶，按照次序把各个桶中的元素列出来即可。
*/
int getMax(std::vector<int>& numVec) {
	int max = 0;
	for (auto iter = numVec.cbegin(); iter != numVec.cend(); iter++)
	{
		if (*iter > max) {
			max = *iter;
		}
	}
	return max;
}
void bucketSort(std::vector<int>& numVec, int bulletNum) {
	int maxNum = getMax(numVec);
	std::vector<std::vector<int>> bulletList;
	for (int i = 0; i < bulletNum; i++) {
		bulletList.push_back(std::vector<int>());
	}
	for (auto iter = numVec.cbegin(); iter != numVec.cend(); iter++) {
		auto key = ((*iter) / maxNum) * bulletNum;
		bulletList[key].push_back(*iter);
	}
	for (int i = 0; i < bulletNum; i++) {
		auto bulletVec = bulletList[i];
		for (auto iter = bulletVec.cbegin(); iter != bulletVec.cend(); iter++) {
			//TODO sort bulletVec
		}
	}
	//TODO concatenate the bulletList;
}


void printInitVector(int size, int maxNum) {
	for (int i = 0; i < size; i++) {
		int num = rand() % (maxNum + 1);
		std::cout << "numVec.push_back(" << num << ");" << std::endl;
	}
}

void initVec(std::vector<int>& numVec) {
	numVec.push_back(41);
	numVec.push_back(85);
	numVec.push_back(72);
	numVec.push_back(38);
	numVec.push_back(80);
	numVec.push_back(69);
	numVec.push_back(65);
	numVec.push_back(68);
	numVec.push_back(96);
	numVec.push_back(22);
	numVec.push_back(49);
	numVec.push_back(67);
	numVec.push_back(51);
	numVec.push_back(61);
	numVec.push_back(63);
	numVec.push_back(87);
	numVec.push_back(66);
	numVec.push_back(24);
	numVec.push_back(80);
	numVec.push_back(83);
	numVec.push_back(71);
	numVec.push_back(60);
	numVec.push_back(64);
	numVec.push_back(52);
	numVec.push_back(90);
	numVec.push_back(60);
	numVec.push_back(49);
	numVec.push_back(31);
	numVec.push_back(23);
	numVec.push_back(99);
	numVec.push_back(94);
	numVec.push_back(11);
	numVec.push_back(25);
	numVec.push_back(24);
	numVec.push_back(51);
	numVec.push_back(15);
	numVec.push_back(13);
	numVec.push_back(39);
	numVec.push_back(67);
	numVec.push_back(97);
	numVec.push_back(19);
	numVec.push_back(76);
	numVec.push_back(12);
	numVec.push_back(33);
	numVec.push_back(99);
	numVec.push_back(18);
	numVec.push_back(92);
	numVec.push_back(35);
	numVec.push_back(74);
	numVec.push_back(0);
	numVec.push_back(95);
	numVec.push_back(71);
	numVec.push_back(39);
	numVec.push_back(33);
	numVec.push_back(39);
	numVec.push_back(32);
	numVec.push_back(37);
	numVec.push_back(45);
	numVec.push_back(57);
	numVec.push_back(71);
	numVec.push_back(95);
	numVec.push_back(5);
	numVec.push_back(71);
	numVec.push_back(24);
	numVec.push_back(86);
	numVec.push_back(8);
	numVec.push_back(51);
	numVec.push_back(54);
	numVec.push_back(74);
	numVec.push_back(24);
	numVec.push_back(75);
	numVec.push_back(70);
	numVec.push_back(33);
	numVec.push_back(63);
	numVec.push_back(29);
	numVec.push_back(99);
	numVec.push_back(58);
	numVec.push_back(94);
	numVec.push_back(52);
	numVec.push_back(13);
	numVec.push_back(35);
	numVec.push_back(99);
	numVec.push_back(46);
	numVec.push_back(57);
	numVec.push_back(71);
	numVec.push_back(23);
	numVec.push_back(17);
	numVec.push_back(3);
	numVec.push_back(94);
	numVec.push_back(48);
	numVec.push_back(77);
	numVec.push_back(18);
	numVec.push_back(83);
	numVec.push_back(11);
	numVec.push_back(83);
	numVec.push_back(25);
	numVec.push_back(59);
	numVec.push_back(62);
	numVec.push_back(2);
	numVec.push_back(78);
}

void printVec(std::vector<int>& numVec) {
	for (auto iter = numVec.cbegin(); iter != numVec.cend(); iter++) {
		if (*iter != INT_MAX)
			std::cout << *iter << ", ";
	}

	std::cout << std::endl;
}

int main()
{
	std::vector<int> numVec, outVec;
	initVec(numVec);

	countingSort(numVec, outVec, 100);
	printVec(outVec);

}
