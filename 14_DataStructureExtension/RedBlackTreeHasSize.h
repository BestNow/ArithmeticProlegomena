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
			����Ҫɾ�����node���Ҵ�ʱnode���ӽڵ�����2��ʱ��
			node�ӽڵ���ɾ��������replaceNode��Ϊnode
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
			��node�������ӽڵ�ʱ��currNodeӦ����node�ĺ�̣�����currNode���ƶ�������node��λ�á�

		*/
		else {
			currNode = treeMinimum(node->getRightChild());		/// �����Ӧ�滻�Ľڵ�
			currNodeColor = currNode->getColor();
			replaceNode = currNode->getRightChild();
			if (currNode->getParent() == node) {		// �ж�Ӧ�滻�Ľڵ�ĸ��ڵ��Ƿ��Ǵ�ɾ���Ľڵ�
				replaceNode->setParent(currNode);			// ����ǲ��ô���
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
			������currNode�Ǻ�ɫ�ģ��������������⣬����ͨ������rbDeleteFixUp���в��ȡ�
			��һ�����node��ԭ���ĸ���㣬��node��һ����ɫ�ĺ��ӳ�Ϊ�µĸ���㣬���Υ��������2��
			�ڶ������replaceNode���ƶ����repalceNode->getParent()�Ǻ�ɫ�ģ���Υ��������4��
			�������������ƶ�currNode��������ǰ����currNode���κμ�·���Ϻڽ�������1��
			��ˣ�currNode���κ����ȶ�����������5��
			������һ����İ취�ǽ�����ռ��currNodeԭ��λ�õĽ��repalceNode��Ϊ����һ�ض���ĺ�ɫ��
			Ҳ����˵�����������������repalceNode�ļ�·���Ϻڽ�������1���������ּ����£�����5������
			�����ڽ��currNodeɾ�����ƶ�ʱ�������ɫ�����ơ������node��
			���������Ϊ���repalceNode���ܼȲ��Ǻ�ɫ���ֲ��Ǻ�ɫ���Ӷ�Υ��������1��
			���ڵĽ��repalceNode��˫�غ�ɫ���ߺ��ɫ����ͷֱ������repalceNode�ļ�·���Ϻڽ����������2��1��
			repalceNode��color������Ȼ��RED(���repalceNode�Ǻ��ɫ��)����BLACK(���repalceNode��˫�غ�ɫ��)�����仰˵��
			������ĺ�ɫ�����repalceNode���ģ������Ƿ�ӳ������color�����ϵġ�

		*/
		if (currNodeColor == BLACK_COLOR) {
			rbDeleteFixUp(replaceNode);
		}
		delete node;
		node = nullptr;
	}

	// ��Сֵ
	Node* treeMinimum(Node* node) {
		auto currNode = node;
		while (currNode->getLeftChild() != nullptr) {
			currNode = currNode->getLeftChild();
		}
		return currNode;
	}

	/*
		���Ҿ��и����ȵ�Ԫ��(�ȣ������������ʱ�����λ��)
		����һ��ָ�룬ָ����nodeΪ���������а�����iС�ؼ��ֵĽ�㡣
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

	//ȷ��һ��Ԫ�ص���(�ȣ������������ʱ�����λ��)
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
		rightChildNode->setSize(currNode->getSize());
		currNode->setSize(currNode->getLeftChild()->getSize() + currNode->getRightChild()->getSize() + 1);
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
		leftChildNode->setSize(currNode->getSize());
		currNode->setSize(currNode->getLeftChild()->getSize() + currNode->getRightChild()->getSize() + 1);
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

		�ú���������ɫ�ڵ㣬����ת����ת��Ϊ�˱�֤����������ƽ��
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
				else {
					if (currNode == currNode->getParent()->getRightChild()) {
						currNode = currNode->getParent();
						/*
							������
								��ǰ�ڵ������ӽڵ�����ӽڵ㣬���ӽڵ��ɵ�ǰ�ڵ�ĸ��ڵ�
								������ӽڵ������ӽڵ㣬���ӽڵ�����ӽڵ��ɵ�ǰ�ڵ�����ӽڵ�
						*/
						leftRotate(currNode);
					}
					/*
						�˴��߼������һ�ε�����ʼʱcurrNode->getParent()�Ǹ��ڵ㣬�����Ǻ�ɫ
					*/
					currNode->getParent()->setColor(BLACK_COLOR);
					currNode->getParent()->getParent()->setColor(RED_COLOR);
					/*
						����������ֻӰ����ת�������������Ľṹ�����������Ľ����������Ų�ˡ�
							��ǰ�ڵ��Ϊ���ӽڵ�����ӽڵ㣬���ӽڵ��Ϊ��ǰ�ڵ�ĸ��ڵ�
							������ӽڵ������ӽڵ㣬�����ӽڵ�����ӽڵ��Ϊ��ǰ�ڵ�����ӽڵ�

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
		����RB-DELETE-FIXUP�ָ�����1������2������4��
			����1��ÿ�������Ǻ�ɫ��,���Ǻ�ɫ�ġ�
			����2��������Ǻ�ɫ�ġ�
			����4�����һ������Ǻ�ɫ�ģ������������ӽ�㶼�Ǻ�ɫ�ġ�
	*/
	void rbDeleteFixUp(Node* node) {
		auto currNode = node;

		/*
			whileѭ����Ŀ���ǽ�����ĺ�ɫ�������ƣ�ֱ����
				1��currNodeָ���ڽڵ㣬 ��currNode->setColor(BLACK_COLOR);
				2��currNodeָ����ڵ㣬��ʱ���Լ򵥵��Ƴ�����ĺ�ɫ��

		*/
		while (currNode != _root && currNode->getColor() == BLACK_COLOR) {
			if (currNode == currNode->getParent()->getLeftChild()) {
				auto rightBroNode = currNode->getParent()->getRightChild();
				if (rightBroNode->getColor() == RED_COLOR) {
					/*
						���1��currNode���ֵܽڵ�rightBroNode�Ǻ�ɫ
							�����ڽ��currNode���ֵܽ��rightBroNodeΪ��ɫʱ��
							��ΪrightBroNode�����к�ɫ�ӽ�㣬���Կ��Ըı�rightBroNode��currNode->getParent()����ɫ��
							Ȼ���currNode->getParent()��һ����������Υ����������κ����ʡ�
							���ڣ�currNode�����ֵܽ������ת֮ǰrightBroNode��ĳ���ӽ�㣬����ɫΪ��ɫ���������ͽ����1ת��Ϊ���2��3��4����
					*/
					rightBroNode->setColor(BLACK_COLOR);
					currNode->getParent()->setColor(RED_COLOR);
					leftRotate(currNode->getParent());
					rightBroNode = currNode->getParent()->getRightChild();
				}
				if (rightBroNode->getLeftChild()->getColor() == BLACK_COLOR && rightBroNode->getRightChild()->getColor() == BLACK_COLOR) {
					/*
						���2��currNode���ֵܽڵ�rightBroNode�Ǻ�ɫ������rightBroNode�������ӽڵ㶼�Ǻ�ɫ

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
