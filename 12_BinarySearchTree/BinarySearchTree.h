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
	// 插入
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

	// 中序遍历
	// 先序遍历
	// 后序遍历
	void inorderTreeWalk() {
		if (_root != nullptr) {
			inorderTreeWalk(_root->getLeftChild());
			std::cout << "key = " << _root->getKey() << "value = " << _root->getValue() << std::endl;
			inorderTreeWalk(_root->getRightChild());
		}
	}

	// 查询二叉树
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

	// 最小值
	Node* treeMinimum(Node* node) {
		auto currNode = node;
		while (currNode->getLeftChild() != nullptr) {
			currNode = currNode->getLeftChild();
		}
		return currNode;
	}

	// 最大值
	Node* treeMaximum(Node* node) {
		auto currNode = node;
		while (currNode->getRightChild() != nullptr) {
			currNode = currNode->getRightChild();
		}
		return currNode;
	}

	// 后继 是大于node.key的最小关键字的结点
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

	// 前驱
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

	// 删除
	void treeDelete(Node* node) {
		/*
			如果z没有左孩子，那么用其右孩子来替换，这个右孩子可以是 NIL，也可以不是。
			当z的右孩子是nullptr时，此时这种情况归为z没有孩子结点的情形。
			当z的右孩子非nullptr时，这种情况就是z仅有一个孩子结点的情形，该孩子是其右孩子。
		*/
		if (node->getLeftChild() == nullptr) {
			transplant(node, node->getRightChild());
		}
		/*
			如果仅有一个孩子且为其左孩子，那么用其左孩子来替换。
		*/
		else if (node->getRightChild() == nullptr) {
			transplant(node, node->getLeftChild());
		}
		else {
			auto miniNode = treeMinimum(node->getRightChild());		// 获取右节点最小的节点，该节点必不包含左子节点
			if (miniNode->getParent() != node) {
				transplant(miniNode, miniNode->getRightChild());		//将最小的节点的右节点，变为最小节点的父节点的左节点
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
		为了在二叉搜索树内移动子树，定义一个子过程 TRANSPLANT，它是用另一棵子树替换一棵子树并成为其双亲的孩子结点。
		当TRANSPLANT用一棵以v为根的子树来替换一棵以u为根的子树时，结点u的双亲就变为结点v的双亲，并且最后v成为u的双亲的相应孩子。
		主要是将deleteNode的父节点变为replaceNode的父节点
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
