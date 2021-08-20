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
		左旋：左旋只影响旋转结点和其右子树的结构，把右子树的结点往左子树挪了。
			当前节点变成右子节点的左子节点，右子节点变成当前节点的父节点
			如果右子节点有左子节点，右子节点的左子节点变成当前节点的右子节点
	*/
	void leftRotate(Node* node) {
		auto currNode = node;
		auto rightChildNode = node->getRightChild();
		currNode->setRightChild(rightChildNode->getLeftChild());
		if (rightChildNode->getLeftChild() != _nilNode) {		// 判断node右子节点的左子节点是否为空
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
		右旋：右旋只影响旋转结点和其左子树的结构，把左子树的结点往右子树挪了。
			当前节点变为左子节点的右子节点，左子节点变为当前节点的父节点
			如果左子节点有右子节点，则左子节点的右子节点变为当前节点的左子节点

	*/
	void rightRotate(Node* node) {
		auto currNode = node;
		auto leftChildNode = node->getLeftChild();
		currNode->setLeftChild(leftChildNode->getRightChild());
		if (leftChildNode->getRightChild() != _nilNode) {	//如果左子节点有右子节点，则左子节点的右子节点变为当前节点的左子节点
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
	一棵红黑树是满足下面红黑性质的二叉搜索树:
		1. 每个结点或是红色的,或是黑色的。
		2. 根结点是黑色的。
		3. 每个叶结点(NIL)是黑色的。
		4. 如果一个结点是红色的，则它的两个子结点都是黑色的。
		5. 对每个结点，从该结点到其所有后代叶结点的简单路径上，均包含相同数目的黑色结点。
	*/
	/*
		在调用rbInsertFixUp操作时，哪些红黑性质可能会被破坏呢?
			性质1和性质3继续成立，因为新插入的红结点的两个子结点都是哨兵_nilNode。
			性质5，即从一个指定结点开始的每条简单路径上的黑结点的个数都是相等的，也会成立，
				因为结点currNode代替了(黑色)哨兵，并且结点z本身是有哨兵孩子的红结点。

			这样来看，仅可能被破坏的就是性质2和性质4。即根结点需要为黑色以及一个红结点不能有红孩子。
			这两个性质可能被破坏是因为currNode被着为红色。
			如果currNode是根结点，则破坏了性质2;
			如果currNode的父结点是红结点，则破坏了性质4。
	*/
	void rbInsertFixUp(Node* node) {
		auto currNode = node;
		/*
			while循环在每次迭代的开头保持下列3个部分的不变式:
				a.结点currNode是红结点。
				b.如果currNode->getParent()是根结点，则currNode->getParent()是黑结点。
				c.如果有任何红黑性质被破坏，则至多只有一条被破坏，或是性质2，或是性质4。
					如果性质2被破坏，其原因为z是根结点且是红结点。如果性质4被破坏，其原因为z和z.p都是红结点。

		*/
		while (currNode->getParent()->getColor() == RED_COLOR) {		// 因为根节点是黑色，所以进入不了循环
			if (currNode->getParent() == currNode->getParent()->getParent()->getLeftChild()) {	// 如果node父节点是左节点
				auto parentRightBro = currNode->getParent()->getParent()->getRightChild();
				if (parentRightBro->getColor() == RED_COLOR) {
					/*
						由于currNode的叔结点parentRightBro是红色的,
						结点被重新着色，并且指针z沿树上升
					*/
					currNode->getParent()->setColor(BLACK_COLOR);
					parentRightBro->setColor(BLACK_COLOR);
					currNode->getParent()->getParent()->setColor(RED_COLOR);	// 不置红将违反性质5
					currNode = currNode->getParent()->getParent();
				}
				else if (currNode == currNode->getParent()->getRightChild()) {
					currNode = currNode->getParent();
					/*
						左旋：
							当前节点变成右子节点的左子节点，右子节点变成当前节点的父节点
							如果右子节点有左子节点，右子节点的左子节点变成当前节点的右子节点
					*/
					leftRotate(currNode);
				}
				currNode->getParent()->setColor(BLACK_COLOR);
				currNode->getParent()->getParent()->setColor(RED_COLOR);
				/*
					右旋：右旋只影响旋转结点和其左子树的结构，把左子树的结点往右子树挪了。
						当前节点变为左子节点的右子节点，左子节点变为当前节点的父节点
						如果左子节点有右子节点，则左子节点的右子节点变为当前节点的左子节点

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
						右旋：右旋只影响旋转结点和其左子树的结构，把左子树的结点往右子树挪了。
							当前节点变为左子节点的右子节点，左子节点变为当前节点的父节点
							如果左子节点有右子节点，则左子节点的右子节点变为当前节点的左子节点
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
