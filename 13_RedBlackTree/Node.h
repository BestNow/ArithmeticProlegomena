#ifndef __NODE_H__
#define __NODE_H__
#include<stdint.h>

enum NodeC
{
	RED_COLOR = 0xFF,
	BLACK_COLOR = 0x00,
};


class Node
{
public:
	Node(uint32_t key, int64_t value, uint8_t color = NodeC::BLACK_COLOR) {
		_color = color;
		_key = key;
		_value = value;
		_parent = NULL;
		_leftChild = NULL;
		_rightChild = NULL;
	}

	uint8_t getColor() {
		return _color;
	}

	void setColor(uint8_t color) {
		_color = color;
	}

	uint32_t getKey() {
		return _key;
	}

	int64_t getValue() {
		return _value;
	}

	void setParent(Node* parent) {
		_parent = parent;
	}

	Node* getParent() {
		return _parent;
	}

	void setLeftChild(Node* leftChild) {
		_leftChild = leftChild;
	}

	Node* getLeftChild() {
		return _leftChild;
	}

	void setRightChild(Node* rightChild) {
		_rightChild = rightChild;
	}

	Node* getRightChild() {
		return _rightChild;
	}

private:
	uint8_t _color;
	uint32_t _key;
	int64_t _value;
	Node* _parent;
	Node* _leftChild;
	Node* _rightChild;
};


#endif // !__NODE_H__
