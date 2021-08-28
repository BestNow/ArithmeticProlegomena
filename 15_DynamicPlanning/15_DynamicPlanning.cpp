#include <iostream>
#include <vector>
#include <stdint.h>
#include "Matrix.h"
uint32_t memoizedCutRodAux(uint32_t length, std::vector<uint32_t>& valueList);

/*
	动态规划
*/

//----------------------------------------------------------------------------------------------------------------
/*
	Serling公司购买长钢条，将其切割为短钢条出售。切割工序本身没有成本支出。公司管理层希望知道最佳的切割方案。
	假定我们知道Serling公司出售一段长度为i英寸的钢条的价格为pi(i=1，2，…，单位为美元)。钢条的长度均为整英寸。

	长度i     1   2   3   4   5   6   7   8   9   10
	价格pi    1   5   8   9   10  17  17  20  24  30
*/
// 递归求解
std::vector<uint32_t> priceList;
uint32_t cutRod(uint32_t length) {
	if (length == 0)
		return 0;
	uint32_t value = 0;
	for (auto index = 1; index <= length; index++) {
		auto currValue = 0;
		if (priceList.size() <= index - 1) {
			currValue = priceList.at(priceList.size() - 1) + cutRod(length - priceList.size());
		}
		else
			currValue = priceList.at(index - 1) + cutRod(length - index);
		if (value < currValue)
			value = currValue;
	}
	return value;
}

// 动态规划求解
//  带备忘的自顶向下法( top-down with memoization)
uint32_t memoizedCutRod(uint32_t length) {
	std::vector<uint32_t> valueList;
	valueList.push_back(0);     // 占位，无实际用处
	for (int index = 1; index <= length; index++) {
		valueList.push_back(0);
	}
	return memoizedCutRodAux(length, valueList);
}
uint32_t memoizedCutRodAux(uint32_t length, std::vector<uint32_t>& valueList) {
	if (valueList.at(length) != 0)
		return valueList.at(length);

	uint32_t value = 0;
	if (length != 0) {
		for (auto index = 1; index <= length; index++) {
			auto currValue = 0;
			if (priceList.size() <= index - 1) {
				currValue = priceList.at(priceList.size() - 1) + memoizedCutRodAux(length - priceList.size(), valueList);
			}
			else
				currValue = priceList.at(index - 1) + memoizedCutRodAux(length - index, valueList);
			if (value < currValue)
				value = currValue;
		}
	}
	valueList[length] = value;
	return value;
}

//  自底向上法(bottom-up method)
uint32_t bottomUpCutRod(uint32_t length) {
	std::vector<uint32_t> valueList;
	valueList.push_back(0);
	for (auto subLength = 1; subLength <= length; subLength++) {
		uint32_t value = 0;
		for (auto subSubLength = 1; subSubLength <= subLength; subSubLength++) {
			auto currValue = 0;
			if (priceList.size() < subSubLength) {
				currValue = priceList.at(priceList.size() - 1) + valueList[subLength - subSubLength];
			}
			else {
				currValue = priceList.at(subSubLength - 1) + valueList[subLength - subSubLength];
			}
			if (value < currValue)
				value = currValue;
		}
		valueList.push_back(value);
	}
	return valueList[length];
}
//----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------
/*
	矩阵链乘法
*/
// 普通乘法
Matrix matrixMultiply(Matrix& aMatrix, Matrix& bMatrix) {
	if (aMatrix.getColumns() != bMatrix.getRows()) {
		return Matrix(0, 0);
	}
	else {
		Matrix cMatrix(aMatrix.getRows(), bMatrix.getColumns());
		for (auto rowIndex = 1; rowIndex <= aMatrix.getRows(); rowIndex++) {
			for (auto columnsIndex = 1; columnsIndex <= bMatrix.getColumns(); columnsIndex++) {
				int32_t currCValue = 0;
				for (auto cIndex = 1; cIndex < aMatrix.getColumns(); cIndex++) {
					currCValue += aMatrix.get(rowIndex, cIndex) * bMatrix.get(cIndex, columnsIndex);
				}
				cMatrix.set(rowIndex, columnsIndex, currCValue);
			}
		}
		return cMatrix;
	}
}


// 计算最优代价
/*
	matrixColAndRowVec:
		假定矩阵Ai的规模为 matrixColAndRowVec[i - 1] * matrixColAndRowVec[i],
		matrixColAndrowVec.size() = n + 1。n为矩阵数量
*/
void matrixChainOrder(std::vector<uint32_t> matrixColAndRowVec,
	std::vector<uint32_t>& productPriceVec,
	std::vector<uint32_t>& optimalSolutionVec)
{
	uint32_t n = matrixColAndRowVec.size() - 1;
	for (uint32_t x = 0; x < n; x++)
		for (uint32_t y = 0; y < n; y++) {
			productPriceVec.push_back(0);
			optimalSolutionVec.push_back(0);
		}

	// 第一个for表示从链长为2的矩阵乘法开始计算，直到链长为n
	for (uint32_t chainLength = 2; chainLength <= n; chainLength++) {
		// 第二个for表示从第一个矩阵遍历到最后链长的第一位
		for (uint32_t minIndex = 1; minIndex <= n - chainLength + 1; minIndex++) {
			uint32_t maxIndex = minIndex + chainLength - 1;
			productPriceVec[(minIndex - 1) * n + (maxIndex - 1)] = UINT_MAX;
			//第三个for表示在指定链长中，计算不同组合的长度，获取最小的链长及应该在哪个地方算乘积
			for (auto index = minIndex; index < maxIndex; index++) {
				// 代价 = 上次左侧乘积次数 + 上次右侧乘积次数 + 这次左侧乘右侧乘积次数
				auto productPrice = productPriceVec[(minIndex - 1) * n + index]
					+ productPriceVec[(index - 1) * n + (maxIndex - 1)]
					+ matrixColAndRowVec[minIndex - 1] * matrixColAndRowVec[index] * matrixColAndRowVec[maxIndex];
				if (productPrice < matrixColAndRowVec[(minIndex - 1) * n + (maxIndex - 1)]) {
					productPriceVec[(minIndex - 1) * n + (maxIndex - 1)] = productPrice;
					optimalSolutionVec[(minIndex - 1) * n + (maxIndex - 1)] = index;
				}
			}
		}
	}

}

//----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------
/*
	最长公共子序列
*/
enum LCSDirection
{
	UNKNOWN = -1,
	LEFT = 0,
	LEFT_UP = 1,
	UP = 2,
};

void lcsLength(std::vector<uint32_t> aList, std::vector<uint32_t> bList,
	std::vector<LCSDirection>& directionVec, std::vector<uint32_t>& lcsValueList)
{
	auto aListSize = aList.size();
	auto bListSize = bList.size();

	for (auto aIndex = 0; aIndex < aListSize; aIndex++)
		for (auto bIndex = 0; bIndex < bListSize; bIndex++)
			directionVec.push_back(LCSDirection::UNKNOWN);

	for (auto aIndex = 0; aIndex <= aListSize; aIndex++)
		for (auto bIndex = 0; bIndex <= bListSize; bIndex++)
			lcsValueList.push_back(0);

	for (auto aIndex = 0; aIndex < aListSize; aIndex++) {
		for (auto bIndex = 0; bIndex < bListSize; bIndex++) {
			if (aList[aIndex] == bList[bIndex]) {
				lcsValueList[(bIndex + 1) * (aListSize + 1) + (aIndex + 1)] = lcsValueList[bIndex * (aListSize + 1) + aIndex] + 1;
				directionVec[bIndex * aListSize + aIndex] = LCSDirection::LEFT_UP;
			}
			else if (lcsValueList[bIndex * (aListSize + 1) + (aIndex + 1)] >= lcsValueList[(bIndex + 1) * (aListSize + 1) + aIndex]) {
				lcsValueList[(bIndex + 1) * (aListSize + 1) + (aIndex + 1)] = lcsValueList[bIndex * (aListSize + 1) + (aIndex + 1)];
				directionVec[bIndex * aListSize + aIndex] = LCSDirection::UP;
			}
			else {
				lcsValueList[(bIndex + 1) * (aListSize + 1) + (aIndex + 1)] = lcsValueList[(bIndex + 1) * (aListSize + 1) + aIndex];
				directionVec[bIndex * aListSize + aIndex] = LCSDirection::LEFT;
			}
		}
	}
}

void printLCS(const std::vector<LCSDirection>& directionVec, std::vector<uint32_t> aList, uint32_t aSize, uint32_t bSize) {
	if (aSize == 0 || bSize == 0)
		return;
	if (directionVec[(bSize - 1) * aList.size() + (aSize - 1)] == LCSDirection::LEFT_UP) {
		printLCS(directionVec, aList, aSize - 1, bSize - 1);
		std::cout << aList[aSize - 1] << " ";
	}
	else if (directionVec[(bSize - 1) * aList.size() + (aSize - 1)] == LCSDirection::UP) {
		printLCS(directionVec, aList, aSize - 1, bSize);
	}
	else {
		printLCS(directionVec, aList, aSize, bSize - 1);
	}
}

//----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------
/*
	最优二叉搜索树
*/
std::vector<int32_t> optimalBST(std::vector<float>& existsProList, std::vector<float>& unexistsProList) {
	std::vector<float> totalExpList, totalProList;
	std::vector<int32_t> rootList;
	uint32_t existsListSize = existsProList.size();
	uint32_t unexistsListSize = unexistsProList.size();


	for (uint32_t index = 0; index < unexistsListSize; index++) {
		for (uint32_t length = 0; length < unexistsListSize; length++) {
			totalExpList.push_back(0);
			totalProList.push_back(0);
		}
	}

	for (uint32_t index = 0; index < existsListSize; index++) {
		for (uint32_t length = 0; length < existsListSize; length++) {
			rootList.push_back(-1);
		}
	}

	for (auto index = 0; index < unexistsListSize; index++) {
		totalExpList[index * unexistsListSize + index] = unexistsProList[index];
		totalProList[index * unexistsListSize + index] = unexistsProList[index];
	}


	for (auto length = 1; length <= existsListSize; length++) {
		for (auto beginPos = 0; beginPos <= existsListSize - length; beginPos++) {

			auto endPos = beginPos + length - 1;
			totalExpList[beginPos * unexistsListSize + (endPos + 1)] = 1e31;

			totalProList[beginPos * unexistsListSize + (endPos + 1)] =
				totalProList[beginPos * unexistsListSize + endPos]
				+ existsProList[endPos] + unexistsProList[endPos + 1];

			for (auto index = beginPos; index <= endPos; index++) {

				auto exp = totalExpList[beginPos * unexistsListSize + index]
					+ totalExpList[(index + 1) * unexistsListSize + (endPos + 1)]
					+ totalProList[beginPos * unexistsListSize + (endPos + 1)];

				if (exp < totalExpList[beginPos * unexistsListSize + (endPos + 1)]) {
					totalExpList[beginPos * unexistsListSize + (endPos + 1)] = exp;
					rootList[beginPos * existsListSize + endPos] = index;
				}
			}
		}
	}

	return rootList;
}

//----------------------------------------------------------------------------------------------------------------

int main()
{
	priceList.push_back(1);
	priceList.push_back(5);
	priceList.push_back(8);
	priceList.push_back(9);
	priceList.push_back(10);
	priceList.push_back(17);
	priceList.push_back(17);
	priceList.push_back(20);
	priceList.push_back(24);
	priceList.push_back(30);

	uint32_t length = 1319;
	std::cout << "length：" << length << " max value is " << bottomUpCutRod(length) << std::endl;
	std::cout << "length：" << length << " max value is " << memoizedCutRod(length) << std::endl;


	Matrix aMatrix(3, 3);
	Matrix bMatrix(3, 3);
	aMatrix.set(1, 1, -90);
	bMatrix.set(1, 1, -644);
	aMatrix.set(1, 2, -170);
	bMatrix.set(1, 2, -76);
	aMatrix.set(1, 3, 241);
	bMatrix.set(1, 3, -931);
	aMatrix.set(2, 1, -464);
	bMatrix.set(2, 1, -599);
	aMatrix.set(2, 2, 639);
	bMatrix.set(2, 2, -460);
	aMatrix.set(2, 3, 651);
	bMatrix.set(2, 3, -80);
	aMatrix.set(3, 1, -831);
	bMatrix.set(3, 1, 664);
	aMatrix.set(3, 2, 215);
	bMatrix.set(3, 2, -822);
	aMatrix.set(3, 3, -720);
	bMatrix.set(3, 3, -547);
	//aMatrix.print();
	//bMatrix.print();

	Matrix cMatrix = matrixMultiply(aMatrix, bMatrix);
	cMatrix.print();


	std::vector<uint32_t> aList;
	std::vector<uint32_t> bList;
	aList.push_back(2);
	aList.push_back(4);
	aList.push_back(3);
	aList.push_back(1);
	aList.push_back(2);
	aList.push_back(1);

	bList.push_back(1);
	bList.push_back(2);
	bList.push_back(3);
	bList.push_back(2);
	bList.push_back(4);
	bList.push_back(1);
	bList.push_back(2);
	std::vector<LCSDirection> directionVec;
	std::vector<uint32_t> lcsValueList;
	lcsLength(aList, bList, directionVec, lcsValueList);
	// 2 4 1 2
	printLCS(directionVec, aList, aList.size(), bList.size());


	std::vector<float> existList;
	std::vector<float> unexistList;

	existList.push_back(0.15);
	existList.push_back(0.10);
	existList.push_back(0.05);
	existList.push_back(0.10);
	existList.push_back(0.20);

	unexistList.push_back(0.05);
	unexistList.push_back(0.10);
	unexistList.push_back(0.05);
	unexistList.push_back(0.05);
	unexistList.push_back(0.05);
	unexistList.push_back(0.10);

	optimalBST(existList, unexistList);
}

