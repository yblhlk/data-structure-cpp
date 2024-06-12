#include<iostream>
#include <new> // 为了使用 std::bad_alloc  
using namespace std;

// 模板 + 内部类 + 抛异常
template<typename T>
class LinkList
{
public:
	static class Node
	{
	private:
		T _data;
		Node* _next;
	public:
		Node(T data = 0, Node* next = nullptr)
		{
			_data = data;
			_next = next;
		}

		T& getData()
		{
			return _data;
		}

		Node* getNext()
		{
			return _next;
		}

		void setNext(Node* next)
		{
			_next = next;
		}
	};
private:
	Node* _head;
	size_t _size;

	Node* createNode(const T& data, Node* next = nullptr)
	{
		// catch块处理完异常后，程序继续执行函数中try-catch结构之后的代码，而不是直接退出函数。(除非在catch块中已经退出）
		try
		{
			Node* newnode = new Node(data, next); //new出来的对象不会随着函数消亡，它在堆上，要我们手动管理。
			return newnode;
		}
		catch (const std::bad_alloc& ex)
		{
			cout << "新节点开辟失败：" << ex.what() << endl;
			return nullptr;
		}
	}
public:
	LinkList()
	{
		_head = nullptr;
		_size = 0;
	}
	// 析构函数
	~LinkList()
	{
		Node* cur = _head;
		Node* del = cur;
		cout << "==============准备释放链表空间==============" << endl;
		while (cur)
		{
			del = cur;
			cur = cur->getNext();
			delete del;
			cout << "释放链表结点中。。。" << endl;
		}
		_size = 0;
		cout << "==============已释放链表空间==============" << endl;
	}
	// 插入
	void insert(const T& data, int index)
	{
		if (index > _size || index < 0)
		{
			cout << "该位置无法插入！" << endl;
		}
		else if (index == 0)
		{
			Node* newnode = createNode(data, _head);
			_head = newnode;
			_size++;
		}
		else
		{
			// a.找到插入位置处的节点和它前一个节点
			Node* cur = _head;
			Node* prv_cur = _head;
			for (int i = 0; i < index; i++)
			{
				prv_cur = cur;
				cur = cur->getNext();
			}
			// b. 插入
			Node* newnode = new Node(data, cur);
			prv_cur->setNext(newnode);
			_size++;
		}

		return ;
	}

	// 删除
	void erase(int index)
	{
		if (index >= _size || index < 0)
		{
			cout << "该位置不允许被删除！" << endl;
		}
		else if(index == 0)
		{
			Node* delete_node = this->_head;
			this->_head = this->_head->getNext();
			this->_size--;
		}
		else
		{
			// a. 找到要删除的节点和的前一个节点
			Node* delete_node = this->_head;
			Node* prv_node = this->_head;
			for (int i = 0; i < index; ++i)
			{
				prv_node = delete_node;
				delete_node = delete_node->getNext();
			}

			// b. 删除
			prv_node->setNext(delete_node->getNext());
			delete(delete_node);
			delete_node = nullptr;
			this->_size--;
		}
	}

	// 返回头结点：
	Node* getHead()
	{
		return _head;
	}

	int getSize()
	{
		return _size;
	}

	// 打印函数不用写，万一保存的是没有重载流提取的对象呢？
};

int main()
{
	LinkList<int> ll;
	ll.insert(1, 1);

	// 头插
	ll.insert(1, 0);
	ll.insert(0, 0);
	ll.insert(2, 0);
	
	// 头删
	ll.erase(0);

	// 尾插
	ll.insert(2, ll.getSize());
	ll.insert(3, ll.getSize());
	ll.insert(4, ll.getSize());
	ll.insert(5, ll.getSize());

	// 插入
	ll.insert(34, 4);
	ll.insert(33, 4);
	ll.insert(44, 6);

	LinkList<int>::Node* cur = ll.getHead();
	for (int i = 0; i < ll.getSize(); i++)
	{
		cout << cur->getData() << " -> ";
		cur = cur->getNext();
	}
	cout << "nullptr" << endl;
	
	// 删除
	ll.erase(4);
	ll.erase(4);
	ll.erase(4);

	// 尾删
	ll.erase(ll.getSize() - 1);
	ll.erase(ll.getSize());

	cur = ll.getHead();
	for (int i = 0; i < ll.getSize(); i++)
	{
		cout << cur->getData() << " -> ";
		cur = cur->getNext();
	}
	cout << "nullptr" << endl;
	return 0;
}

// 模板 + 内部类 + 抛异常
// 3.抛异常 ：
// 3.1 catch块处理完异常后，程序继续执行函数中try-catch结构之后的代码，
//     而不是直接退出函数。(除非在catch块中已经退出）
//     捕获异常的一大特点就是：程序不再随着异常的出现而终止。
//     当异常被throw时，函数并不是“正常”地退出，而是由于异常而提前退出。



// 问题记录：
// 1. 在形参表中不匹配。
//    变量名，函数名写错 -_-||| 。 
//    记住C++中私有的成员变量前带了一个_ 。访问对象成员最好带一个this，这样编译器就会检查有没有这个对象。 

// 2. 对象指针和成员
//    对象指针用->来访问成员。