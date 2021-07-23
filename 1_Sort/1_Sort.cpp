#include <iostream>
#include <limits.h>
#include <chrono>

void outputNumList(int* preSortList, int num);
int* getNumList();
void timeBegin();
void timeEnd();

// 插入排序
void insertSort(int* preSortList, int num) {
	for (int i = 1; i < num; i++) {
		auto key = *(preSortList + i);
		int index = i - 1;

		while (index >= 0 && preSortList[index] > key) {
			*(preSortList + index + 1) = *(preSortList + index);
			index = index - 1;
		}
		*(preSortList + index + 1) = key;
	}
}

//归并排序
void merge(int* numList, int startPos, int centerPos, int endPos) {
	auto n1 = centerPos - startPos + 1;
	auto n2 = endPos - centerPos;
	int* leftList = new int[n1 + 1];
	int* rightList = new int[n2 + 1];
	leftList[n1] = INT_MAX;
	rightList[n2] = INT_MAX;

	for (int index = 0; index < n1; index++) {
		leftList[index] = numList[startPos + index];        //[startPos, centerPos]
	}

	for (int index = 0; index < n2; index++) {
		rightList[index] = numList[centerPos + index + 1];       //(centerPos, endPos]
	}

	int leftIndex = 0, rightIndex = 0;
	for (int index = startPos; index <= endPos; index++) {
		if (leftList[leftIndex] < rightList[rightIndex]) {
			numList[index] = leftList[leftIndex];
			leftIndex = leftIndex + 1;
		}
		else {
			numList[index] = rightList[rightIndex];
			rightIndex = rightIndex + 1;
		}
	}

	delete[] leftList;
	delete[] rightList;
}
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
void mergeSort(int* numList, int startPos, int endPos) {
	if (startPos < endPos) {
		auto centerPos = static_cast<int>((startPos + endPos) / 2);
		mergeSort(numList, startPos, centerPos);
		mergeSort(numList, centerPos + 1, endPos);
		merge(numList, startPos, centerPos, endPos);
		//merge2(numList, startPos, centerPos, endPos);
	}
}



int main()
{
	timeBegin();
	int* a = getNumList();
	insertSort(a, 100);
	outputNumList(a, 100);
	delete a;
	timeEnd();

	timeBegin();
	a = getNumList();
	mergeSort(a, 0, 99);
	outputNumList(a, 100);
	delete a;
	timeEnd();

}

void outputNumList(int* preSortList, int num) {
	for (int i = 0; i < num; i++) {
		std::cout << *(preSortList + i);
		if (i != num - 1) {
			std::cout << ",";
		}
	}

	std::cout << std::endl;
}

int* getNumList() {
	int* numList = new int[100];
	numList[0] = 126;
	numList[1] = 56359;
	numList[2] = 19331;
	numList[3] = 80875;
	numList[4] = 58501;
	numList[5] = 47988;
	numList[6] = 35030;
	numList[7] = 89597;
	numList[8] = 82285;
	numList[9] = 74661;
	numList[10] = 17411;
	numList[11] = 85895;
	numList[12] = 71051;
	numList[13] = 51354;
	numList[14] = 30400;
	numList[15] = 1499;
	numList[16] = 9141;
	numList[17] = 36446;
	numList[18] = 14732;
	numList[19] = 16590;
	numList[20] = 98853;
	numList[21] = 44570;
	numList[22] = 11909;
	numList[23] = 467;
	numList[24] = 892;
	numList[25] = 37789;
	numList[26] = 53167;
	numList[27] = 57119;
	numList[28] = 60177;
	numList[29] = 60717;
	numList[30] = 16624;
	numList[31] = 66305;
	numList[32] = 45079;
	numList[33] = 35213;
	numList[34] = 5704;
	numList[35] = 60769;
	numList[36] = 78332;
	numList[37] = 80261;
	numList[38] = 51989;
	numList[39] = 30196;
	numList[40] = 87598;
	numList[41] = 72668;
	numList[42] = 95591;
	numList[43] = 92572;
	numList[44] = 53936;
	numList[45] = 14234;
	numList[46] = 46209;
	numList[47] = 23533;
	numList[48] = 86224;
	numList[49] = 20961;
	numList[50] = 77966;
	numList[51] = 84366;
	numList[52] = 99680;
	numList[53] = 99970;
	numList[54] = 61150;
	numList[55] = 39244;
	numList[56] = 26622;
	numList[57] = 29729;
	numList[58] = 84015;
	numList[59] = 2375;
	numList[60] = 37587;
	numList[61] = 9263;
	numList[62] = 67721;
	numList[63] = 5622;
	numList[64] = 879;
	numList[65] = 91880;
	numList[66] = 27589;
	numList[67] = 27290;
	numList[68] = 58791;
	numList[69] = 69119;
	numList[70] = 83762;
	numList[71] = 72650;
	numList[72] = 48494;
	numList[73] = 20536;
	numList[74] = 74374;
	numList[75] = 46846;
	numList[76] = 45797;
	numList[77] = 94916;
	numList[78] = 74444;
	numList[79] = 10828;
	numList[80] = 59905;
	numList[81] = 38524;
	numList[82] = 73501;
	numList[83] = 60897;
	numList[84] = 57241;
	numList[85] = 36134;
	numList[86] = 15156;
	numList[87] = 22511;
	numList[88] = 42516;
	numList[89] = 80289;
	numList[90] = 51711;
	numList[91] = 98999;
	numList[92] = 75155;
	numList[93] = 34557;
	numList[94] = 16899;
	numList[95] = 65731;
	numList[96] = 49190;
	numList[97] = 6354;
	numList[98] = 69976;
	numList[99] = 50481;
	return numList;
}

std::chrono::system_clock::time_point myt;

void timeBegin() {
	myt = std::chrono::system_clock::now();
}

void timeEnd() {
	auto curTime = std::chrono::system_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(curTime - myt);
	std::cout << "Cost Time:" << (duration.count()) << std::endl;
}
