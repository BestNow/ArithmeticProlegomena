#pragma once
#include <limits>
#include <iostream>
class Matrix {
public:
	//lineNum 行数 rowNum 列数
	Matrix(int lineNum, int rowNum) {
		_lineNum = lineNum;
		_rowNum = rowNum;
		matrix = new int[_lineNum * _rowNum];
	}

	Matrix(int lineRowNum) {
		_lineNum = _rowNum = lineRowNum;
		matrix = new int[_lineNum * _rowNum];
	}

	int get(int line, int row) {
		if (line > _lineNum || row > _rowNum)
			return INT_MAX;
		return matrix[(line - 1) * _rowNum + (row - 1)];
	}

	void set(int line, int row, int num) {
		if (line <= _lineNum && row <= _rowNum)
			matrix[(line - 1) * _rowNum + (row - 1)] = num;
	}
	
	~Matrix() {
		delete[] matrix;
	}

	int getLine() {
		return _lineNum;
	}

	int getRow() {
		return _rowNum;
	}

	void print() {
		for (int line = 1; line <= _lineNum; line++) {
			for (int row = 1; row <= _rowNum; row++) {
				auto num = get(line, row);
				std::cout << get(line, row) << "\t";
			}
			std::cout << std::endl;
		}
	}
private:
	int* matrix = nullptr;
	int _lineNum, _rowNum;
};