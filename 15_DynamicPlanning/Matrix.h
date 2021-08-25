#ifndef __MATRIX_H__
#define __MATRIX_H__
#include <stdint.h>
#include <vector>
#include <iostream>
class Matrix
{
public:
	Matrix(uint32_t columns, uint32_t rows) {
		_columns = columns;
		_rows = rows;

		for (int currColumns = 0; currColumns < _columns; currColumns++) {
			for (int currRows = 0; currRows < _rows; currRows++) {
				_data.push_back(0);
			}
		}
	}
	~Matrix() {
		
	}

	uint32_t getColumns() {
		return _columns;
	}

	uint32_t getRows() {
		return _rows;
	}

	void set(uint32_t rows, uint32_t columns, int32_t data) {
		_data[(rows - 1) * _rows + (columns - 1)] = data;
	}

	int32_t get(uint32_t rows, uint32_t columns) {
		return _data[(rows - 1) * _rows + (columns - 1)];
	}

	void print() {
		for (auto currRows = 1; currRows <= _columns; currRows++) {
			for (auto currColumns = 1; currColumns <= _rows; currColumns++) {
				std::cout << get(currRows, currColumns) << "\t";
			}
			std::cout << std::endl;
		}
	}

private:
	uint32_t _columns;			// ÁÐ
	uint32_t _rows;				// ÐÐ
	std::vector<int32_t> _data;
};

#endif