#pragma once
/*
	2.3-1:使用图2-4作为模型，说明归并排序在数组A = {3, 41, 52, 26, 38, 57, 9, 49}上的操作。
								   3 9 26 38 41 49 52 57
							     3 26 41 52 | 9 38 49 57
							   3 41 | 26 52 || 38 57 | 9 49
					3 | 41   ||   52 | 26   ||   38 | 57   ||   9 | 49
*/

/* 
	2.3-2：重写过程MERGE，使之不使用哨兵，而是一旦数组L或R的所有元素均被复制回A就立即停止，
		然后把另一个数组的剩余部分复制回A。
*/
void merge2(int* numList, int startPos, int centerPos, int endPos) {
	auto n1 = centerPos - startPos + 1;
	auto n2 = endPos - centerPos;
	int* leftList = new int[n1];
	int* rightList = new int[n2];

	for (int index = 0; index < n1; index++) {
		leftList[index] = numList[startPos + index];        //[startPos, centerPos]
	}

	for (int index = 0; index < n2; index++) {
		rightList[index] = numList[centerPos + index + 1];       //(centerPos, endPos]
	}

	int leftIndex = 0, rightIndex = 0;
	for (int index = startPos; index <= endPos; index++) {
		if (leftIndex < n1 && rightIndex < n2) {
			if (leftList[leftIndex] < rightList[rightIndex]) {
				numList[index] = leftList[leftIndex];
				leftIndex = leftIndex + 1;
			}
			else {
				numList[index] = rightList[rightIndex];
				rightIndex = rightIndex + 1;
			}
		}
		else if (rightIndex < n2) {
			numList[index] = rightList[rightIndex];
			rightIndex = rightIndex + 1;
		}
		else if (leftIndex < n1) {
			numList[index] = leftList[leftIndex];
			leftIndex = leftIndex + 1;
		}
	}

	delete[] leftList;
	delete[] rightList;
}

/*
	数学归纳法：
	证明当n= 1时命题成立。
	假设n=m时命题成立，那么可以推导出在n=m+1时命题也成立。（m代表任意自然数）。

	2.3-3：使用数学归纳法证明：当n刚好是2的幂时，以下递归式的解是T(n) = nlgn。
			2				若 n = 2
	T(n) = 
			2T(n/2) + n		若 n = 2^k, k > 1
	
	解：
		1、 当 k = 1时， T(n) = 2 * lg 2 = 2， 成立
		2、 假设k = m(m > 1)时，命题成立 即， T(2^m) = 2T(2^m / 2) + 2^m = 2^m * lg2^m，
			则对于k = m + 1时， 
				T(2^(m + 1)) 
					= 2T(2^(m + 1) / 2) + 2^(m + 1)
					= 2T(2^m) + 2^(m + 1)
					= 2(2^m * lg2^m) + 2^(m + 1)
					= 2^(m+1) * (1 + lg2^m)
					= 2^(m + 1) * lg2^(m + 1)
			所以T(n) = nlgn


*/

/*
	2.3-4：我们可以把插入排序表示为如下的一个递归过程。
		为了排序A[1..n]，我们递归地排序A[1..n-1]，然后把A[n]插入已排序的数组A[1..n-1]。
		为插入排序的这个递归版本的最坏情况运行时间写一个递归式。

解：
		T(n)					n
								(n - 1)
								(n - 2)
				0				若n = 1
		T(n) = 
				(n - 1) + T(n - 1)	若n > 1
*/

