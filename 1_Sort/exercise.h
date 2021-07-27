#pragma once
/*
	2.3-1:ʹ��ͼ2-4��Ϊģ�ͣ�˵���鲢����������A = {3, 41, 52, 26, 38, 57, 9, 49}�ϵĲ�����
								   3 9 26 38 41 49 52 57
							     3 26 41 52 | 9 38 49 57
							   3 41 | 26 52 || 38 57 | 9 49
					3 | 41   ||   52 | 26   ||   38 | 57   ||   9 | 49
*/

/* 
	2.3-2����д����MERGE��ʹ֮��ʹ���ڱ�������һ������L��R������Ԫ�ؾ������ƻ�A������ֹͣ��
		Ȼ�����һ�������ʣ�ಿ�ָ��ƻ�A��
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
	��ѧ���ɷ���
	֤����n= 1ʱ���������
	����n=mʱ�����������ô�����Ƶ�����n=m+1ʱ����Ҳ��������m����������Ȼ������

	2.3-3��ʹ����ѧ���ɷ�֤������n�պ���2����ʱ�����µݹ�ʽ�Ľ���T(n) = nlgn��
			2				�� n = 2
	T(n) = 
			2T(n/2) + n		�� n = 2^k, k > 1
	
	�⣺
		1�� �� k = 1ʱ�� T(n) = 2 * lg 2 = 2�� ����
		2�� ����k = m(m > 1)ʱ��������� ���� T(2^m) = 2T(2^m / 2) + 2^m = 2^m * lg2^m��
			�����k = m + 1ʱ�� 
				T(2^(m + 1)) 
					= 2T(2^(m + 1) / 2) + 2^(m + 1)
					= 2T(2^m) + 2^(m + 1)
					= 2(2^m * lg2^m) + 2^(m + 1)
					= 2^(m+1) * (1 + lg2^m)
					= 2^(m + 1) * lg2^(m + 1)
			����T(n) = nlgn


*/

/*
	2.3-4�����ǿ��԰Ѳ��������ʾΪ���µ�һ���ݹ���̡�
		Ϊ������A[1..n]�����ǵݹ������A[1..n-1]��Ȼ���A[n]���������������A[1..n-1]��
		Ϊ�������������ݹ�汾����������ʱ��дһ���ݹ�ʽ��

�⣺
		T(n)					n
								(n - 1)
								(n - 2)
				0				��n = 1
		T(n) = 
				(n - 1) + T(n - 1)	��n > 1
*/

