#include<iostream>
#include <new> // Ϊ��ʹ�� std::bad_alloc  
using namespace std;

// ģ�� + �ڲ��� + ���쳣
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
		// catch�鴦�����쳣�󣬳������ִ�к�����try-catch�ṹ֮��Ĵ��룬������ֱ���˳�������(������catch�����Ѿ��˳���
		try
		{
			Node* newnode = new Node(data, next); //new�����Ķ��󲻻����ź������������ڶ��ϣ�Ҫ�����ֶ�����
			return newnode;
		}
		catch (const std::bad_alloc& ex)
		{
			cout << "�½ڵ㿪��ʧ�ܣ�" << ex.what() << endl;
			return nullptr;
		}
	}
public:
	LinkList()
	{
		_head = nullptr;
		_size = 0;
	}
	// ��������
	~LinkList()
	{
		Node* cur = _head;
		Node* del = cur;
		cout << "==============׼���ͷ�����ռ�==============" << endl;
		while (cur)
		{
			del = cur;
			cur = cur->getNext();
			delete del;
			cout << "�ͷ��������С�����" << endl;
		}
		_size = 0;
		cout << "==============���ͷ�����ռ�==============" << endl;
	}
	// ����
	void insert(const T& data, int index)
	{
		if (index > _size || index < 0)
		{
			cout << "��λ���޷����룡" << endl;
		}
		else if (index == 0)
		{
			Node* newnode = createNode(data, _head);
			_head = newnode;
			_size++;
		}
		else
		{
			// a.�ҵ�����λ�ô��Ľڵ����ǰһ���ڵ�
			Node* cur = _head;
			Node* prv_cur = _head;
			for (int i = 0; i < index; i++)
			{
				prv_cur = cur;
				cur = cur->getNext();
			}
			// b. ����
			Node* newnode = new Node(data, cur);
			prv_cur->setNext(newnode);
			_size++;
		}

		return ;
	}

	// ɾ��
	void erase(int index)
	{
		if (index >= _size || index < 0)
		{
			cout << "��λ�ò�����ɾ����" << endl;
		}
		else if(index == 0)
		{
			Node* delete_node = this->_head;
			this->_head = this->_head->getNext();
			this->_size--;
		}
		else
		{
			// a. �ҵ�Ҫɾ���Ľڵ�͵�ǰһ���ڵ�
			Node* delete_node = this->_head;
			Node* prv_node = this->_head;
			for (int i = 0; i < index; ++i)
			{
				prv_node = delete_node;
				delete_node = delete_node->getNext();
			}

			// b. ɾ��
			prv_node->setNext(delete_node->getNext());
			delete(delete_node);
			delete_node = nullptr;
			this->_size--;
		}
	}

	// ����ͷ��㣺
	Node* getHead()
	{
		return _head;
	}

	int getSize()
	{
		return _size;
	}

	// ��ӡ��������д����һ�������û����������ȡ�Ķ����أ�
};

int main()
{
	LinkList<int> ll;
	ll.insert(1, 1);

	// ͷ��
	ll.insert(1, 0);
	ll.insert(0, 0);
	ll.insert(2, 0);
	
	// ͷɾ
	ll.erase(0);

	// β��
	ll.insert(2, ll.getSize());
	ll.insert(3, ll.getSize());
	ll.insert(4, ll.getSize());
	ll.insert(5, ll.getSize());

	// ����
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
	
	// ɾ��
	ll.erase(4);
	ll.erase(4);
	ll.erase(4);

	// βɾ
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

// ģ�� + �ڲ��� + ���쳣
// 3.���쳣 ��
// 3.1 catch�鴦�����쳣�󣬳������ִ�к�����try-catch�ṹ֮��Ĵ��룬
//     ������ֱ���˳�������(������catch�����Ѿ��˳���
//     �����쳣��һ���ص���ǣ������������쳣�ĳ��ֶ���ֹ��
//     ���쳣��throwʱ�����������ǡ����������˳������������쳣����ǰ�˳���



// �����¼��
// 1. ���βα��в�ƥ�䡣
//    ��������������д�� -_-||| �� 
//    ��סC++��˽�еĳ�Ա����ǰ����һ��_ �����ʶ����Ա��ô�һ��this�������������ͻ�����û��������� 

// 2. ����ָ��ͳ�Ա
//    ����ָ����->�����ʳ�Ա��