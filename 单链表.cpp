#include<iostream>
using namespace std;


// �ڵ���
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
} Node; //typedef�������������޷�ʹ�ã�����������Ч��


// ������
class LinkList
{
private:
	Node* head;
	size_t size;

	// �����ڵ�
	Node* createNode(Datatype data, Node* next = nullptr)
	{
		Node* node = new Node(data, next); //�ڶ��ϴ����ܱ��������������������⡣
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
	
	// ��ָ���±괦����
	void insert(Datatype data, int index) //�±���β����Ϊint������size_t(size_t���ǽ�ֹ����)
	{
		if (index > size || index < 0)
			cout << "��λ�ò�֧�ֲ��룡" << endl;
		else if(index == 0)
		{
			Node* newnode = createNode(data, head);
			head = newnode;
			size++;
		}
		else
		{
			// a. �ҵ�Ŀ��ڵ� �� ǰһ���ڵ�
			Node* goal = head;
			Node* prv_goal = head;
			for (int i = 0; i < index; i++)
			{
				prv_goal = goal;
				goal = goal->getNext();
			}
			// b. ����
			Node* newnode = createNode(data, goal);
			prv_goal->setNext(newnode);
			++size;
		}
	}

	// ɾ��
	void erase(int index)
	{
		if (index > size-1 || index < 0)
			cout << "��λ�ò�֧��ɾ����" << endl;
		else if (index == 0)
		{
			Node* d = head;
			head = head->getNext();
			delete(d);
			size--;
		}
		else
		{
			// a. �ҵ�Ҫɾ���Ľڵ����ǰһ���ڵ�
			Node* de = head;
			Node* prv_de = head;
			for (int i = 0; i < index; ++i)
			{
				prv_de = de;
				de = de->getNext();
			}

			// b.ɾ��
			prv_de->setNext(de->getNext());
			delete(de);
			size--;
		}
	}

	// β��
	void push_back(Datatype data)
	{
		
		if (head == nullptr)
		{
			head = createNode(data);
		}
		else
		{
			// a. �ҵ�β�ڵ�
			Node* tail = head;
			while (tail->getNext() != nullptr)
			{
				tail = tail->getNext();
			}

			// b. �����������½ڵ�
			tail->setNext(createNode(data));
			size++; //�ڵ�����++
		}
	}

	// ͷ��
	void push_front(Datatype data)
	{
		// a. �����½ڵ�
		// b. ���½ڵ�ָ��ͷ���
		Node* newnode = createNode(data, head);

		// c. �ı�ͷָ��ָ��
		head = newnode;
		size++; //�ڵ�����++
	}

	// ͷɾ
	void pop_front()
	{
		if (head)
		{
			// a. ��¼ͷ���
			Node* h = head;
			head = head->getNext();
			delete(h);
			size--; //�ڵ�����--
		}
		else
		{
			cout << "��ǰ����Ϊ�գ���֧��ɾ����" << endl;
		}
	}

	void print()
	{
		Node* cur = head;
		if (cur == nullptr)
		{
			cout << "��ǰ����Ϊ�ա�" << endl;
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

	// βɾ
	void pop_back()
	{
		// ���ʶ����Աʱ�������Ƿ�Ϊ��һ��Ҫ�������ǣ�����Ϊһ�����������ǡ�
		if(head == nullptr)
		{
		cout << "��ǰ����Ϊ�գ���֧��ɾ����" << endl;
		}
		else if (head->getNext()) //Ӧ����else if ��Ȼ headΪ��Ҳ����getNext()�ᱼ����
		{
			// a.�ҵ�β�ڵ� �� ��ǰһ���ڵ�
			Node* ptail = head;
			Node* tail = head->getNext();
			while (tail->getNext())
			{
				ptail = tail;
				tail = tail->getNext();
			}

			// b. ɾ��β�ڵ�
			ptail->setNext(nullptr);
			delete(tail);
			size--; //�ڵ�����--
		}
		else if(head->getNext() == nullptr)
		{
			// ֻ��ͷ���������Ȼͷָ��ָ��nullptr
			delete(head);
			head = nullptr;
			size--; //�ڵ�����--
		}	
	}

	Datatype operator[] (int index)
	{
		// �±����Ҫ���ǣ�
		// Խ�磬������/����
		if (size < index + 1 || index < 0)
		{
			cout << "Խ����ʣ�����-1 ��" << endl;
			return -1;
		}
		else if(size == 0)
		{
			cout << "����Ϊ�գ�����-1 ��" << endl;
			return -1;
		}
		else
		{
			// a. ͨ��ѭ��Ѱ�ҽڵ�
			Node* cur = head;
			for (int i = 0; i < index; i++)
			{
				cur = cur->getNext();
			}
			// b. ���ؽڵ��б��������
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

// �ܽ᣺
// ����Ҫ�������ݣ������ǿ����Ƿ�Ϊ�գ�Ϊ��Ҫ�ı�ͷָ�룩
// ɾ��Ҫ�����Ƿ�Ϊ�գ�size==0?)
// �±����Ҫ���ǣ��Ƿ�Խ��(�Ƿ�Ϊ��)��
// �����size��ɾ��ʱҪ--������ʱҪ++��