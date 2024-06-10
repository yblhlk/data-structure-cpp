#include<iostream>
using namespace std;


// 节点类
typedef int Datatype;

typedef class LindListNode
{
private:
	Datatype _data;
	LindListNode* _next;
public:
	LindListNode(Datatype data, LindListNode* next) {
		_data = data;
		_next = next;
	}
	LindListNode* getNext()
	{
		return _next;
	}
	void setNext(LindListNode* next)
	{
		_next = next;
	}

	Datatype getData()
	{
		return _data;
	}
} Node; //typedef重命名在类内无法使用，创建完后才生效。


// 链表类
class LinkList
{
private:
	Node* head;
	size_t size;

	// 创建节点
	Node* createNode(Datatype data, Node* next = nullptr)
	{
		Node* node = new Node(data, next); //在堆上创建能避免出了作用域就析构问题。
		return node;
	}
public:
	LinkList()
	{
		head = nullptr;
		size = 0;
	}
	size_t getSize()
	{
		return size;
	}
	
	// 在指定下标处插入
	void insert(Datatype data, int index) //下标的形参最好为int而不是size_t(size_t不是禁止负数)
	{
		if (index > size || index < 0)
			cout << "该位置不支持插入！" << endl;
		else if(index == 0)
		{
			Node* newnode = createNode(data, head);
			head = newnode;
			size++;
		}
		else
		{
			// a. 找到目标节点 和 前一个节点
			Node* goal = head;
			Node* prv_goal = head;
			for (int i = 0; i < index; i++)
			{
				prv_goal = goal;
				goal = goal->getNext();
			}
			// b. 插入
			Node* newnode = createNode(data, goal);
			prv_goal->setNext(newnode);
			++size;
		}
	}

	// 删除
	void erase(int index)
	{
		if (index > size-1 || index < 0)
			cout << "该位置不支持删除！" << endl;
		else if (index == 0)
		{
			Node* d = head;
			head = head->getNext();
			delete(d);
			size--;
		}
		else
		{
			// a. 找到要删除的节点和它前一个节点
			Node* de = head;
			Node* prv_de = head;
			for (int i = 0; i < index; ++i)
			{
				prv_de = de;
				de = de->getNext();
			}

			// b.删除
			prv_de->setNext(de->getNext());
			delete(de);
			size--;
		}
	}

	// 尾插
	void push_back(Datatype data)
	{
		
		if (head == nullptr)
		{
			head = createNode(data);
		}
		else
		{
			// a. 找到尾节点
			Node* tail = head;
			while (tail->getNext() != nullptr)
			{
				tail = tail->getNext();
			}

			// b. 创建并插入新节点
			tail->setNext(createNode(data));
			size++; //节点数量++
		}
	}

	// 头插
	void push_front(Datatype data)
	{
		// a. 创建新节点
		// b. 让新节点指向头结点
		Node* newnode = createNode(data, head);

		// c. 改变头指针指向
		head = newnode;
		size++; //节点数量++
	}

	// 头删
	void pop_front()
	{
		if (head)
		{
			// a. 记录头结点
			Node* h = head;
			head = head->getNext();
			delete(h);
			size--; //节点数量--
		}
		else
		{
			cout << "当前链表为空，不支持删除。" << endl;
		}
	}

	void print()
	{
		Node* cur = head;
		if (cur == nullptr)
		{
			cout << "当前链表为空。" << endl;
		}
		else
		{
			while (cur)
			{
				cout << cur->getData() << " -> ";
				cur = cur->getNext();
			}
			cout << "null" << endl;
		}
	}

	// 尾删
	void pop_back()
	{
		// 访问对象成员时，对象是否为空一定要单独考虑，且作为一个大类来考虑。
		if(head == nullptr)
		{
		cout << "当前链表为空，不支持删除。" << endl;
		}
		else if (head->getNext()) //应该是else if 不然 head为空也访问getNext()会奔溃。
		{
			// a.找到尾节点 和 其前一个节点
			Node* ptail = head;
			Node* tail = head->getNext();
			while (tail->getNext())
			{
				ptail = tail;
				tail = tail->getNext();
			}

			// b. 删除尾节点
			ptail->setNext(nullptr);
			delete(tail);
			size--; //节点数量--
		}
		else if(head->getNext() == nullptr)
		{
			// 只有头结点的情况，然头指针指向nullptr
			delete(head);
			head = nullptr;
			size--; //节点数量--
		}	
	}

	Datatype operator[] (int index)
	{
		// 下标访问要考虑：
		// 越界，空数组/链表
		if (size < index + 1 || index < 0)
		{
			cout << "越界访问！返回-1 。" << endl;
			return -1;
		}
		else if(size == 0)
		{
			cout << "链表为空！返回-1 。" << endl;
			return -1;
		}
		else
		{
			// a. 通过循环寻找节点
			Node* cur = head;
			for (int i = 0; i < index; i++)
			{
				cur = cur->getNext();
			}
			// b. 返回节点中保存的数据
			return cur->getData();
		}
	}
};



int main()
{
	LinkList ll;
	ll.print();
	ll.push_front(0);
	ll.push_front(-1);
	ll.push_front(-2);
	ll.push_front(1);
	ll.print();
	ll.pop_front();
	ll.print();
	ll.pop_front();
	ll.print();
	ll.pop_back();
	ll.print();
	ll.pop_back();
	ll.print();
	ll.pop_back();
	ll.print();

	ll.push_front(1);
	ll.push_front(2);
	ll.push_front(3);
	ll.push_front(4);
	ll.print();

	
	ll.push_back(0);
	ll.push_back(-1);
	ll.push_back(-2);
	ll.print();

	ll.insert(-3, ll.getSize());
	ll.insert(-4, ll.getSize());
	ll.insert(-5, ll.getSize());
	ll.print();
	cout << ll.getSize() << endl;

	ll.insert(5, 0);
	ll.insert(6, 0);
	ll.insert(7, 0);
	ll.print();
	cout << ll.getSize() << endl;

	ll.erase(ll.getSize());
	ll.erase(ll.getSize() - 1);
	cout << ll.getSize() << endl;
	ll.erase(0);
	cout << ll.getSize() << endl;
	ll.print();
	ll.insert(7, 5);
	ll.print();
	ll.erase(5);
	ll.print();

	cout << ll[-1] << endl;
	cout << ll[ll.getSize()] << endl;
	return 0;
}

// 总结：
// 插入要考虑扩容（链表是考虑是否为空，为空要改变头指针）
// 删除要考虑是否为空（size==0?)
// 下标访问要考虑，是否越界(是否为空)。
// 如果有size，删除时要--，增加时要++。