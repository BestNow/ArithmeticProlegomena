#ifndef __BINARYSEARCHTREE_H__
#define __BINARYSEARCHTREE_H__
#include "Node.h"
class BinarySearchTree
{
public:
	BinarySearchTree() {
		_root = nullptr;
	}
	~BinarySearchTree() {
		deleteNode(_root);
	}
	// ����
	void treeInsert(Node* node) {
		Node* nodeParent = nullptr;
		Node* currParent = _root;
		while (currParent) {
			nodeParent = currParent;
			if (node->getKey() < currParent->getKey())
				currParent = currParent->getLeftChild();
			else
				currParent = currParent->getRightChild();
		}
		node->setParent(nodeParent);
		if (nodeParent == nullptr)
			_root = node;
		else if (node->getKey() < nodeParent->getKey())
			nodeParent->setLeftChild(node);
		else
			nodeParent->setRightChild(node);
	}

	// �������
	// �������
	// �������
	void inorderTreeWalk() {
		if (_root != nullptr) {
			inorderTreeWalk(_root->getLeftChild());
			std::cout << "key = " << _root->getKey() << "value = " << _root->getValue() << std::endl;
			inorderTreeWalk(_root->getRightChild());
		}
	}

	// ��ѯ������
	Node* treeSearch(Node* node, uint32_t key) {
		if (node == nullptr || key == node->getKey())
			return node;
		if (key < node->getKey())
			return treeSearch(node->getLeftChild(), key);
		else
			return treeSearch(node->getRightChild(), key);
	}

	Node* iterativeTreeSearch(Node* node, uint32_t key) {
		Node* currNode = node;
		while (currNode != nullptr && key != currNode->getKey()) {
			if (key < currNode->getKey())
				currNode = currNode->getLeftChild();
			else
				currNode = currNode->getRightChild();
		}
		return currNode;
	}

	// ��Сֵ
	Node* treeMinimum(Node* node) {
		auto currNode = node;
		while (currNode->getLeftChild() != nullptr) {
			currNode = currNode->getLeftChild();
		}
		return currNode;
	}

	// ���ֵ
	Node* treeMaximum(Node* node) {
		auto currNode = node;
		while (currNode->getRightChild() != nullptr) {
			currNode = currNode->getRightChild();
		}
		return currNode;
	}

	// ��� �Ǵ���node.key����С�ؼ��ֵĽ��
	Node* treeSuccessor(Node* node) {
		auto currNode = node;
		if (currNode->getRightChild() != nullptr) 
			return treeMinimum(currNode->getRightChild());
		
		auto currNodeParent = currNode->getParent();
		while (currNodeParent != nullptr && currNode == currNodeParent->getRightChild()) {
			currNode = currNodeParent;
			currNodeParent = currNodeParent->getParent();
		}
		return currNodeParent;
	}

	// ǰ��
	Node* treePrecursor(Node* node) {
		auto currNode = node;
		if (currNode->getLeftChild() != nullptr)
			return treeMaximum(currNode->getLeftChild());
		auto currNodeParent = currNode->getParent();
		while (currNodeParent != nullptr && currNode == currNodeParent->getLeftChild()) {
			currNode = currNodeParent;
			currNodeParent = currNodeParent->getParent();
		}
		return currNodeParent;
	}

	// ɾ��
	void treeDelete(Node* node) {
		/*
			���zû�����ӣ���ô�����Һ������滻������Һ��ӿ����� NIL��Ҳ���Բ��ǡ�
			��z���Һ�����nullptrʱ����ʱ���������Ϊzû�к��ӽ������Ρ�
			��z���Һ��ӷ�nullptrʱ�������������z����һ�����ӽ������Σ��ú��������Һ��ӡ�
		*/
		if (node->getLeftChild() == nullptr) {
			transplant(node, node->getRightChild());
		}
		/*
			�������һ��������Ϊ�����ӣ���ô�����������滻��
		*/
		else if (node->getRightChild() == nullptr) {
			transplant(node, node->getLeftChild());
		}
		else {
			auto miniNode = treeMinimum(node->getRightChild());		// ��ȡ�ҽڵ���С�Ľڵ㣬�ýڵ�ز��������ӽڵ�
			if (miniNode->getParent() != node) {
				transplant(miniNode, miniNode->getRightChild());		//����С�Ľڵ���ҽڵ㣬��Ϊ��С�ڵ�ĸ��ڵ����ڵ�
				miniNode->setRightChild(node->getRightChild());
				miniNode->getRightChild()->setParent(miniNode);
			}
			transplant(node, miniNode);				//
			miniNode->setLeftChild(node->getLeftChild());
			miniNode->getLeftChild()->setParent(miniNode);
		}

	}

private:
	void deleteNode(Node* node) {
		if (node != nullptr) {
			deleteNode(node->getLeftChild());
			deleteNode(node->getRightChild());
			delete node;
		}
	}

	void inorderTreeWalk(Node* node) {
		if (node != nullptr) {
			inorderTreeWalk(node->getLeftChild());
			std::cout << "key = " << node->getKey() << "value = " << node->getValue() << std::endl;
			inorderTreeWalk(node->getRightChild());
		}
	}

	/*
		Ϊ���ڶ������������ƶ�����������һ���ӹ��� TRANSPLANT����������һ�������滻һ����������Ϊ��˫�׵ĺ��ӽ�㡣
		��TRANSPLANT��һ����vΪ�����������滻һ����uΪ��������ʱ�����u��˫�׾ͱ�Ϊ���v��˫�ף��������v��Ϊu��˫�׵���Ӧ���ӡ�
		��Ҫ�ǽ�deleteNode�ĸ��ڵ��ΪreplaceNode�ĸ��ڵ�
	*/
	void transplant(Node* deleteNode, Node* replaceNode) 
	{
		if (deleteNode->getParent() == nullptr) {
			_root = replaceNode;
		}
		else if (deleteNode == deleteNode->getParent()->getLeftChild()) {
			deleteNode->getParent()->setLeftChild(replaceNode);
		}
		else {
			deleteNode->getParent()->setRightChild(replaceNode);
		}
		if (replaceNode != nullptr) {
			replaceNode->setParent(deleteNode->getParent());
		}
	}

private:
	Node* _root;
};


#endif // !__BINARYSEARCHTREE_H__
