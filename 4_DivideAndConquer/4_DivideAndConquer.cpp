#include <iostream>
#include <limits>
#include "Matrix.h"

int* getNumList();
Matrix* getLeftMatrix();
Matrix* getRightMatrix();

/*低价买入，高价卖出问题*/
/*
    分治策略的求解方法
        假如要寻找子数组A[low, high]的最大子数组。必定位于以下之一
        ·完全位于子数组A[low, high]中，因此 low ≤ i ≤ j ≤ mid
        ·完全位于子数组A[mid + 1 .. high]中，因此mid < i ≤ j ≤ high
        ·跨越了中点，因此low ≤ i ≤ mid < j ≤ high
*/
void findMaxCrossingSubarray(int* array, int low, int mid, int high, int* maxLeft, int* maxRight, int* totalSum) {
    // 跨越了中点，因此low ≤ i ≤ mid < j ≤ high
    int leftSum = INT_MIN,
        sum = 0;

    for (int index = mid; index >= low; --index) {
        sum = sum + array[index];
        if (sum > leftSum) {
            leftSum = sum;
            *maxLeft = index;
        }
    }

    int rightSum = INT_MIN;
    sum = 0;
    for (int index = mid + 1; index <= high; index++) {
        sum = sum + array[index];
        if (sum > rightSum) {
            rightSum = sum;
            *maxRight = index;
        }
    }

    *totalSum = leftSum + rightSum;
}
void findMaxImumSubarray(int* array, int low, int high, int* lowIndex = 0, int* highIndex = 0, int* totalSum = 0) {
    if (high == low) {
        *lowIndex = low;
        *highIndex = high;
        *totalSum = array[low];
    }
    else {
        int mid = (low + high) / 2;
        int leftLow = 0, leftHigh = 0, leftSum = 0;
        findMaxImumSubarray(array, low, mid, &leftLow, &leftHigh, &leftSum);
        int rightLow = 0, rightHigh = 0, rightSum = 0;
        findMaxImumSubarray(array, mid + 1, high, &rightLow, &rightHigh, &rightSum);
        int crossingLow = 0, crossingHigh = 0, crossingSum = 0;
        findMaxCrossingSubarray(array, low, mid, high, &crossingLow, &crossingHigh, &crossingSum);
        if (leftSum >= rightSum && leftSum >= crossingSum) {
            *lowIndex = leftLow; *highIndex = leftHigh; *totalSum = leftSum;
        }
        else if (rightSum >= leftSum && rightSum >= crossingSum) {
            *lowIndex = rightLow; *highIndex = rightHigh; *totalSum = rightSum;
        }
        else {
            *lowIndex = crossingLow; *highIndex = crossingHigh; *totalSum = crossingSum;
        }
    }
}

/*矩阵相乘的算法*/
Matrix* squareMatrixxMultiply(Matrix* A, Matrix* B) {
    // 传统方式
    int n = A->getLine();
    Matrix* C = new Matrix(n);
    for (int line = 1; line <= n; line++) {
        for (int row = 1; row <= n; row++) {
            int c = 0;
            for (int index = 1; index <= n; index++) {
                c = c + A->get(line, index) * B->get(index, row);
                C->set(row, line, c);
            }
        }
    }
    return C;
}

Matrix* squareMatrixMultiplyRecursive(Matrix* A, Matrix* B) {
    auto n = A->getLine();
    Matrix* C = new Matrix(n);
    if (n == 1)
        C->set(1, 1, A->get(1, 1) * B->get(1, 1));
    else {
        int midLine = n / 2;
        
        Matrix* A11 = new Matrix(midLine);
        Matrix* A12 = new Matrix(n - midLine);
        Matrix* A21 = new Matrix(midLine);
        Matrix* A22 = new Matrix(n - midLine);
    }
}

int main()
{
    int* array = getNumList();
    int lowIndex, highIndex, totalSum;
    findMaxImumSubarray(array, 0, 99, &lowIndex, &highIndex, &totalSum);
    std::cout << "最低Index:" << lowIndex << "，最大Index:" << highIndex << "，总值:" << totalSum << std::endl;
    delete[] array;

    Matrix* leftMatrix = getLeftMatrix();
    Matrix* rightMatrix = getRightMatrix();
    std::cout << "Left Matrix:" << std::endl;
    leftMatrix->print();
    std::cout << "Right Matrix:" << std::endl;
    rightMatrix->print();
    Matrix* resultMatrix = squareMatrixxMultiply(leftMatrix, rightMatrix);
    std::cout << "Result Matrix:" << std::endl;
    resultMatrix->print();
}

int* getNumList() {
	int* numList = new int[100];
    numList[0] = -998;
    numList[1] = 127;
    numList[2] = -614;
    numList[3] = 618;
    numList[4] = 170;
    numList[5] = -40;
    numList[6] = -300;
    numList[7] = 792;
    numList[8] = 646;
    numList[9] = 493;
    numList[10] = -652;
    numList[11] = 718;
    numList[12] = 421;
    numList[13] = 27;
    numList[14] = -392;
    numList[15] = -971;
    numList[16] = -818;
    numList[17] = -271;
    numList[18] = -706;
    numList[19] = -669;
    numList[20] = 978;
    numList[21] = -109;
    numList[22] = -762;
    numList[23] = -991;
    numList[24] = -983;
    numList[25] = -244;
    numList[26] = 63;
    numList[27] = 142;
    numList[28] = 204;
    numList[29] = 214;
    numList[30] = -668;
    numList[31] = 326;
    numList[32] = -98;
    numList[33] = -296;
    numList[34] = -886;
    numList[35] = 215;
    numList[36] = 567;
    numList[37] = 606;
    numList[38] = 40;
    numList[39] = -396;
    numList[40] = 752;
    numList[41] = 454;
    numList[42] = 912;
    numList[43] = 852;
    numList[44] = 79;
    numList[45] = -716;
    numList[46] = -76;
    numList[47] = -530;
    numList[48] = 725;
    numList[49] = -581;
    numList[50] = 560;
    numList[51] = 688;
    numList[52] = 994;
    numList[53] = 1000;
    numList[54] = 223;
    numList[55] = -215;
    numList[56] = -468;
    numList[57] = -406;
    numList[58] = 681;
    numList[59] = -953;
    numList[60] = -248;
    numList[61] = -815;
    numList[62] = 355;
    numList[63] = -888;
    numList[64] = -983;
    numList[65] = 838;
    numList[66] = -448;
    numList[67] = -454;
    numList[68] = 176;
    numList[69] = 383;
    numList[70] = 676;
    numList[71] = 453;
    numList[72] = -30;
    numList[73] = -590;
    numList[74] = 488;
    numList[75] = -63;
    numList[76] = -84;
    numList[77] = 899;
    numList[78] = 489;
    numList[79] = -784;
    numList[80] = 198;
    numList[81] = -230;
    numList[82] = 470;
    numList[83] = 218;
    numList[84] = 145;
    numList[85] = -277;
    numList[86] = -697;
    numList[87] = -550;
    numList[88] = -150;
    numList[89] = 606;
    numList[90] = 34;
    numList[91] = 980;
    numList[92] = 503;
    numList[93] = -309;
    numList[94] = -662;
    numList[95] = 315;
    numList[96] = -16;
    numList[97] = -873;
    numList[98] = 400;
    numList[99] = 10;
	return numList;
}

Matrix* getLeftMatrix() {
    Matrix* matrix = new Matrix(5);
    matrix->set(1, 1, 1);
    matrix->set(1, 2, 10);
    matrix->set(1, 3, -1);
    matrix->set(1, 4, 6);
    matrix->set(1, 5, 0);
    matrix->set(2, 1, 2);
    matrix->set(2, 2, -5);
    matrix->set(2, 3, -1);
    matrix->set(2, 4, 0);
    matrix->set(2, 5, -2);
    matrix->set(3, 1, 3);
    matrix->set(3, 2, 0);
    matrix->set(3, 3, 9);
    matrix->set(3, 4, -4);
    matrix->set(3, 5, 10);
    matrix->set(4, 1, 10);
    matrix->set(4, 2, -10);
    matrix->set(4, 3, 6);
    matrix->set(4, 4, 4);
    matrix->set(4, 5, -7);
    matrix->set(5, 1, 6);
    matrix->set(5, 2, -7);
    matrix->set(5, 3, -5);
    matrix->set(5, 4, -2);
    matrix->set(5, 5, 10);
    return matrix;
}

Matrix* getRightMatrix() {
    Matrix* matrix = new Matrix(5);

    matrix->set(1, 1, 1);
    matrix->set(1, 2, 0);
    matrix->set(1, 3, -10);
    matrix->set(1, 4, 4);
    matrix->set(1, 5, 5);
    matrix->set(2, 1, -3);
    matrix->set(2, 2, -1);
    matrix->set(2, 3, -3);
    matrix->set(2, 4, -9);
    matrix->set(2, 5, -8);
    matrix->set(3, 1, 1);
    matrix->set(3, 2, 1);
    matrix->set(3, 3, -1);
    matrix->set(3, 4, 8);
    matrix->set(3, 5, 1);
    matrix->set(4, 1, -8);
    matrix->set(4, 2, 7);
    matrix->set(4, 3, 4);
    matrix->set(4, 4, 10);
    matrix->set(4, 5, 4);
    matrix->set(5, 1, 6);
    matrix->set(5, 2, -10);
    matrix->set(5, 3, 6);
    matrix->set(5, 4, -4);
    matrix->set(5, 5, -6);
    return matrix;
}

