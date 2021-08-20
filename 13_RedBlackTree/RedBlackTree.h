#ifndef __REDBLACKTREE_H__
#define __REDBLACKTREE_H__
#include "Node.h"
#include<limits>


class RedBlackTree
{
public:
	RedBlackTree() {
		_root = nullptr;
		_nilNode = new Node(UINT32_MAX, INT64_MAX, BLACK_COLOR);
	}
	~RedBlackTree() {

	}

	/*
		����������ֻӰ����ת�������������Ľṹ�����������Ľ����������Ų�ˡ�
			��ǰ�ڵ������ӽڵ�����ӽڵ㣬���ӽڵ��ɵ�ǰ�ڵ�ĸ��ڵ�
			������ӽڵ������ӽڵ㣬���ӽڵ�����ӽڵ��ɵ�ǰ�ڵ�����ӽڵ�
	*/
	void leftRotate(Node* node) {
		auto currNode = node;
		auto rightChildNode = node->getRightChild();
		currNode->setRightChild(rightChildNode->getLeftChild());
		if (rightChildNode->getLeftChild() != _nilNode) {		// �ж�node���ӽڵ�����ӽڵ��Ƿ�Ϊ��
			rightChildNode->getLeftChild()->setParent(currNode);
		}
		rightChildNode->setParent(currNode->getParent());
		if (currNode->getParent() == _nilNode) {
			_root = rightChildNode;
		}
		else if (currNode == currNode->getParent()->getLeftChild()) {
			currNode->getParent()->setLeftChild(rightChildNode);
		}
		else {
			currNode->getParent()->setRightChild(rightChildNode);
		}
		rightChildNode->setLeftChild(currNode);
		currNode->setParent(rightChildNode);
	}

	/*
		����������ֻӰ����ת�������������Ľṹ�����������Ľ����������Ų�ˡ�
			��ǰ�ڵ��Ϊ���ӽڵ�����ӽڵ㣬���ӽڵ��Ϊ��ǰ�ڵ�ĸ��ڵ�
			������ӽڵ������ӽڵ㣬�����ӽڵ�����ӽڵ��Ϊ��ǰ�ڵ�����ӽڵ�

	*/
	void rightRotate(Node* node) {
		auto currNode = node;
		auto leftChildNode = node->getLeftChild();
		currNode->setLeftChild(leftChildNode->getRightChild());
		if (leftChildNode->getRightChild() != _nilNode) {	//������ӽڵ������ӽڵ㣬�����ӽڵ�����ӽڵ��Ϊ��ǰ�ڵ�����ӽڵ�
			leftChildNode->getRightChild()->setParent(currNode);
		}
		leftChildNode->setParent(currNode->getParent());
		if (currNode->getParent() == _nilNode) {
			_root = leftChildNode;
		}
		else if (currNode == currNode->getParent()->getLeftChild()) {
			currNode->getParent()->setLeftChild(leftChildNode);
		}
		else {
			currNode->getParent()->setRightChild(leftChildNode);
		}
		leftChildNode->setRightChild(currNode);
		currNode->setParent(leftChildNode);
	}

	void rbInsert(Node* node) {
		auto parentNode = _nilNode;
		auto childNode = _root;
		while (childNode != _nilNode) {
			parentNode = childNode;
			if (node->getKey() < childNode->getKey())
				childNode = childNode->getLeftChild();
			else
				childNode = childNode->getRightChild();
		}
		node->setParent(parentNode);
		if (parentNode == _nilNode)
			_root = node;
		else if (node->getKey() < parentNode->getKey())
			parentNode->setLeftChild(node);
		else
			parentNode->setRightChild(node);

		node->setLeftChild(_nilNode);
		node->setRightChild(_nilNode);
		node->setColor(RED_COLOR);
		rbInsertFixUp(node);
	}

	/*
	һ�ú�������������������ʵĶ���������:
		1. ÿ�������Ǻ�ɫ��,���Ǻ�ɫ�ġ�
		2. ������Ǻ�ɫ�ġ�
		3. ÿ��Ҷ���(NIL)�Ǻ�ɫ�ġ�
		4. ���һ������Ǻ�ɫ�ģ������������ӽ�㶼�Ǻ�ɫ�ġ�
		5. ��ÿ����㣬�Ӹý�㵽�����к��Ҷ���ļ�·���ϣ���������ͬ��Ŀ�ĺ�ɫ��㡣
	*/
	/*
		�ڵ���rbInsertFixUp����ʱ����Щ������ʿ��ܻᱻ�ƻ���?
			����1������3������������Ϊ�²���ĺ���������ӽ�㶼���ڱ�_nilNode��
			����5������һ��ָ����㿪ʼ��ÿ����·���ϵĺڽ��ĸ���������ȵģ�Ҳ�������
				��Ϊ���currNode������(��ɫ)�ڱ������ҽ��z���������ڱ����ӵĺ��㡣

			���������������ܱ��ƻ��ľ�������2������4�����������ҪΪ��ɫ�Լ�һ�����㲻���к캢�ӡ�
			���������ʿ��ܱ��ƻ�����ΪcurrNode����Ϊ��ɫ��
			���currNode�Ǹ���㣬���ƻ�������2;
			���currNode�ĸ�����Ǻ��㣬���ƻ�������4��
	*/
	void rbInsertFixUp(Node* node) {
		auto currNode = node;
		/*
			whileѭ����ÿ�ε����Ŀ�ͷ��������3�����ֵĲ���ʽ:
				a.���currNode�Ǻ��㡣
				b.���currNode->getParent()�Ǹ���㣬��currNode->getParent()�Ǻڽ�㡣
				c.������κκ�����ʱ��ƻ���������ֻ��һ�����ƻ�����������2����������4��
					�������2���ƻ�����ԭ��Ϊz�Ǹ�������Ǻ��㡣�������4���ƻ�����ԭ��Ϊz��z.p���Ǻ��㡣

		*/
		while (currNode->getParent()->getColor() == RED_COLOR) {		// ��Ϊ���ڵ��Ǻ�ɫ�����Խ��벻��ѭ��
			if (currNode->getParent() == currNode->getParent()->getParent()->getLeftChild()) {	// ���node���ڵ�����ڵ�
				auto parentRightBro = currNode->getParent()->getParent()->getRightChild();
				if (parentRightBro->getColor() == RED_COLOR) {
					/*
						����currNode������parentRightBro�Ǻ�ɫ��,
						��㱻������ɫ������ָ��z��������
					*/
					currNode->getParent()->setColor(BLACK_COLOR);
					parentRightBro->setColor(BLACK_COLOR);
					currNode->getParent()->getParent()->setColor(RED_COLOR);	// ���ú콫Υ������5
					currNode = currNode->getParent()->getParent();
				}
				else if (currNode == currNode->getParent()->getRightChild()) {
					currNode = currNode->getParent();
					/*
						������
							��ǰ�ڵ������ӽڵ�����ӽڵ㣬���ӽڵ��ɵ�ǰ�ڵ�ĸ��ڵ�
							������ӽڵ������ӽڵ㣬���ӽڵ�����ӽڵ��ɵ�ǰ�ڵ�����ӽڵ�
					*/
					leftRotate(currNode);
				}
				currNode->getParent()->setColor(BLACK_COLOR);
				currNode->getParent()->getParent()->setColor(RED_COLOR);
				/*
					����������ֻӰ����ת�������������Ľṹ�����������Ľ����������Ų�ˡ�
						��ǰ�ڵ��Ϊ���ӽڵ�����ӽڵ㣬���ӽڵ��Ϊ��ǰ�ڵ�ĸ��ڵ�
						������ӽڵ������ӽڵ㣬�����ӽڵ�����ӽڵ��Ϊ��ǰ�ڵ�����ӽڵ�

				*/
				rightRotate(currNode->getParent()->getParent());
			}
			else {
				auto parentLeftBro = currNode->getParent()->getParent()->getLeftChild();
				if (parentLeftBro->getColor() == RED_COLOR) {
					currNode->getParent()->setColor(BLACK_COLOR);
					parentLeftBro->setColor(BLACK_COLOR);
					currNode->getParent()->getParent()->setColor(RED_COLOR);
					currNode = currNode->getParent()->getParent();                                                                                                         
				}
				else if (currNode == currNode->getParent()->getLeftChild()) {
					currNode = currNode->getParent();
					/*
						����������ֻӰ����ת�������������Ľṹ�����������Ľ����������Ų�ˡ�
							��ǰ�ڵ��Ϊ���ӽڵ�����ӽڵ㣬���ӽڵ��Ϊ��ǰ�ڵ�ĸ��ڵ�
							������ӽڵ������ӽڵ㣬�����ӽڵ�����ӽڵ��Ϊ��ǰ�ڵ�����ӽڵ�
					*/
					rightRotate(currNode);
				}
				currNode->getParent()->setColor(BLACK_COLOR);
				currNode->getParent()->getParent()->setColor(RED_COLOR);
				leftRotate(currNode->getParent()->getParent());                        
			}
		}
		_root->setColor(BLACK_COLOR);
	}

private:
	Node* _root;
	Node* _nilNode;
};

#endif // !__REDBLACKTREE_H__
