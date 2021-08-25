#ifndef __REDBLACKTREEHASSIZE_H__
#define __REDBLACKTREEHASSIZE_H__
#include "Node.h"
class RedBlackTreeHasSize
{
public:
	RedBlackTreeHasSize() {
		_nilNode = new Node(UINT32_MAX, INT64_MAX, BLACK_COLOR);
		_root = _nilNode;
	}
	~RedBlackTreeHasSize() {
		deleteNode(_root);
		delete _nilNode;
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

	void rbDelete(Node* node) {
		auto currNode = node;
		auto currNodeColor = currNode->getColor();
		Node* replaceNode;

		/*
			当想要删除结点node，且此时node的子节点少于2个时，
			node从节点中删除，并让replaceNode成为node
		*/
		if (node->getLeftChild() == _nilNode) {
			replaceNode = node->getRightChild();
			rbTransplant(node, node->getRightChild());
		}
		else if (node->getRightChild() == _nilNode) {
			replaceNode = node->getLeftChild();
			rbTransplant(node, node->getLeftChild());
		}

		/*
			当node有两个子节点时，currNode应该是node的后继，并且currNode将移动至树中node的位置。

		*/
		else {
			currNode = treeMinimum(node->getRightChild());		/// 计算出应替换的节点
			currNodeColor = currNode->getColor();
			replaceNode = currNode->getRightChild();
			if (currNode->getParent() == node) {		// 判断应替换的节点的父节点是否是待删除的节点
				replaceNode->setParent(currNode);			// 如果是不用处理
			}
			else {
				rbTransplant(currNode, currNode->getRightChild());
				currNode->setRightChild(node->getRightChild());
				currNode->getRightChild()->setParent(currNode);
			}
			rbTransplant(node, currNode);
			currNode->setLeftChild(node->getLeftChild());
			currNode->getLeftChild()->setParent(currNode);
			currNode->setColor(node->getColor());
		}

		/*
			如果结点currNode是黑色的，则会产生三个问题，可以通过调用rbDeleteFixUp进行补救。
			第一，如果node是原来的根结点，而node的一个红色的孩子成为新的根结点，这就违反了性质2。
			第二，如果replaceNode和移动后的repalceNode->getParent()是红色的，则违反了性质4。
			第三，在树中移动currNode将导致先前包含currNode的任何简单路径上黑结点个数少1。
			因此，currNode的任何祖先都不满足性质5。
			改正这一问题的办法是将现在占有currNode原来位置的结点repalceNode视为还有一重额外的黑色。
			也就是说，如果将任意包含结点repalceNode的简单路径上黑结点个数加1，则在这种假设下，性质5成立。
			当将黑结点currNode删除或移动时，将其黑色“下推”给结点node。
			现在问题变为结点repalceNode可能既不是红色，又不是黑色，从而违反了性质1。
			现在的结点repalceNode是双重黑色或者红黑色，这就分别给包含repalceNode的简单路径上黑结点数贡献了2或1。
			repalceNode的color属性仍然是RED(如果repalceNode是红黑色的)或者BLACK(如果repalceNode是双重黑色的)。换句话说，
			结点额外的黑色是针对repalceNode结点的，而不是反映在它的color属性上的。

		*/
		if (currNodeColor == BLACK_COLOR) {
			rbDeleteFixUp(replaceNode);
		}
		delete node;
		node = nullptr;
	}

	// 最小值
	Node* treeMinimum(Node* node) {
		auto currNode = node;
		while (currNode->getLeftChild() != nullptr) {
			currNode = currNode->getLeftChild();
		}
		return currNode;
	}

	/*
		查找具有给定秩的元素(秩：在中序遍历树时输出的位置)
		返回一个指针，指向以node为根的子树中包含第i小关键字的结点。
	*/
	Node* osSelect(Node* node, uint32_t index) {
		auto leftHasNodeSize = node->getLeftChild()->getSize() + 1;
		if (index == leftHasNodeSize)
			return node;
		else if (index < leftHasNodeSize)
			return osSelect(node->getLeftChild(), index);
		else
			return osSelect(node->getRightChild(), index - leftHasNodeSize);
	}
	Node* osSelect(uint32_t index) {
		return osSelect(_root, index);
	}

	//确定一个元素的秩(秩：在中序遍历树时输出的位置)
	uint32_t osRank(Node* node) {
		auto leftHasNodeSize = node->getLeftChild()->getSize() + 1;
		auto currNode = node;
		while (currNode != _root) {
			if (currNode == currNode->getParent()->getRightChild())
				leftHasNodeSize += currNode->getParent()->getLeftChild()->getSize() + 1;
			currNode = currNode->getParent();
		}

		return leftHasNodeSize;
	}

private:
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
		rightChildNode->setSize(currNode->getSize());
		currNode->setSize(currNode->getLeftChild()->getSize() + currNode->getRightChild()->getSize() + 1);
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
		leftChildNode->setSize(currNode->getSize());
		currNode->setSize(currNode->getLeftChild()->getSize() + currNode->getRightChild()->getSize() + 1);
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

		该函数重新着色节点，并旋转，旋转是为了保证红黑树的相对平衡
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
				else {
					if (currNode == currNode->getParent()->getRightChild()) {
						currNode = currNode->getParent();
						/*
							左旋：
								当前节点变成右子节点的左子节点，右子节点变成当前节点的父节点
								如果右子节点有左子节点，右子节点的左子节点变成当前节点的右子节点
						*/
						leftRotate(currNode);
					}
					/*
						此处逻辑如果下一次迭代开始时currNode->getParent()是根节点，则它是黑色
					*/
					currNode->getParent()->setColor(BLACK_COLOR);
					currNode->getParent()->getParent()->setColor(RED_COLOR);
					/*
						右旋：右旋只影响旋转结点和其左子树的结构，把左子树的结点往右子树挪了。
							当前节点变为左子节点的右子节点，左子节点变为当前节点的父节点
							如果左子节点有右子节点，则左子节点的右子节点变为当前节点的左子节点

					*/
					rightRotate(currNode->getParent()->getParent());
				}
			}
			else {
				auto parentLeftBro = currNode->getParent()->getParent()->getLeftChild();
				if (parentLeftBro->getColor() == RED_COLOR) {
					currNode->getParent()->setColor(BLACK_COLOR);
					parentLeftBro->setColor(BLACK_COLOR);
					currNode->getParent()->getParent()->setColor(RED_COLOR);
					currNode = currNode->getParent()->getParent();
				}
				else {
					if (currNode == currNode->getParent()->getLeftChild()) {
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
		}
		_root->setColor(BLACK_COLOR);
	}

	void rbTransplant(Node* deleteNode, Node* replaceNode) {
		if (deleteNode->getParent() == _nilNode)
			_root = replaceNode;
		else if (deleteNode == deleteNode->getParent()->getLeftChild())
			deleteNode->getParent()->setLeftChild(replaceNode);
		else
			deleteNode->getParent()->setRightChild(replaceNode);

		replaceNode->setParent(deleteNode->getParent());
	}

	/*
		过程RB-DELETE-FIXUP恢复性质1、性质2和性质4。
			性质1：每个结点或是红色的,或是黑色的。
			性质2：根结点是黑色的。
			性质4：如果一个结点是红色的，则它的两个子结点都是黑色的。
	*/
	void rbDeleteFixUp(Node* node) {
		auto currNode = node;

		/*
			while循环的目标是将额外的黑色沿树上移，直到：
				1、currNode指向红黑节点， 将currNode->setColor(BLACK_COLOR);
				2、currNode指向根节点，此时可以简单的移除额外的黑色。

		*/
		while (currNode != _root && currNode->getColor() == BLACK_COLOR) {
			if (currNode == currNode->getParent()->getLeftChild()) {
				auto rightBroNode = currNode->getParent()->getRightChild();
				if (rightBroNode->getColor() == RED_COLOR) {
					/*
						情况1：currNode的兄弟节点rightBroNode是红色
							发生在结点currNode的兄弟结点rightBroNode为红色时。
							因为rightBroNode必须有黑色子结点，所以可以改变rightBroNode和currNode->getParent()的颜色，
							然后对currNode->getParent()做一次左旋而不违反红黑树的任何性质。
							现在，currNode的新兄弟结点是旋转之前rightBroNode的某个子结点，其颜色为黑色。这样，就将情况1转换为情况2、3或4处理。
					*/
					rightBroNode->setColor(BLACK_COLOR);
					currNode->getParent()->setColor(RED_COLOR);
					leftRotate(currNode->getParent());
					rightBroNode = currNode->getParent()->getRightChild();
				}
				if (rightBroNode->getLeftChild()->getColor() == BLACK_COLOR && rightBroNode->getRightChild()->getColor() == BLACK_COLOR) {
					/*
						情况2：currNode的兄弟节点rightBroNode是黑色，而且rightBroNode的两个子节点都是黑色

					*/
					rightBroNode->setColor(RED_COLOR);
					currNode = currNode->getParent();
				}
				else {
					if (rightBroNode->getRightChild()->getColor() == BLACK_COLOR) {
						rightBroNode->getLeftChild()->setColor(BLACK_COLOR);
						rightBroNode->setColor(RED_COLOR);
						rightRotate(rightBroNode);
						rightBroNode = currNode->getParent()->getRightChild();
					}
					rightBroNode->setColor(currNode->getParent()->getColor());
					currNode->getParent()->setColor(BLACK_COLOR);
					rightBroNode->getRightChild()->setColor(BLACK_COLOR);
					leftRotate(currNode->getParent());
					currNode = _root;
				}
			}
			else {
				auto leftBroNode = currNode->getParent()->getLeftChild();
				if (leftBroNode->getColor() == RED_COLOR) {
					leftBroNode->setColor(BLACK_COLOR);
					currNode->getParent()->setColor(RED_COLOR);
					rightRotate(currNode->getParent());
					leftBroNode = currNode->getParent()->getLeftChild();
				}
				if (leftBroNode->getLeftChild()->getColor() == BLACK_COLOR && leftBroNode->getRightChild()->getColor() == BLACK_COLOR) {
					leftBroNode->setColor(RED_COLOR);
					currNode = currNode->getParent();
				}
				else {
					if (leftBroNode->getLeftChild()->getColor() == BLACK_COLOR) {
						leftBroNode->getRightChild()->setColor(BLACK_COLOR);
						leftBroNode->setColor(RED_COLOR);
						leftRotate(leftBroNode);
						leftBroNode = currNode->getParent()->getLeftChild();
					}
					leftBroNode->setColor(currNode->getParent()->getColor());
					currNode->getParent()->setColor(BLACK_COLOR);
					leftBroNode->getLeftChild()->setColor(BLACK_COLOR);
					rightRotate(currNode->getParent());
					currNode = _root;
				}
			}
		}

		currNode->setColor(BLACK_COLOR);
	}

	void deleteNode(Node* node) {
		if (node != nullptr) {
			deleteNode(node->getLeftChild());
			deleteNode(node->getRightChild());
			if (node != _nilNode)
				delete node;
		}
	}
private:
	Node* _root;
	Node* _nilNode;

};

#endif // !__REDBLACKTREEHASSIZE_H__
