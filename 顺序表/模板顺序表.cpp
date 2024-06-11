#include<iostream>
#include <new> // Ϊ��ʹ�� std::bad_alloc  
#include <stdexcept>   // Ϊ��ʹ�� std::out_of_range
using namespace std;

template<class T>
class ArrayList
{
private:
	T* _arr;
	int _size;
	int _capacity;
public:
	ArrayList(int capacity = 0)
	{
		_arr = nullptr;
		_size = 0;
		_capacity = capacity;
	}

	// ����
	void expansion()
	{
		if (_size == _capacity)
		{
			// a. ���������� (����һ��Ҫ�ǵøı�capacity)
			_capacity = _capacity == 0 ? 4 : _capacity * 2;
			try
			{
				T* newarr = new T[_capacity];
				// b. �������ݵ�������
				for (int i = 0; i < _size; ++i)
				{
					*(newarr + i) = *(_arr + i);
				}
				// c. ɾ��ԭ����
				if (_arr)
					delete[](_arr);
				// d. �ı�����ָ��ָ��
				_arr = newarr;
			}
			catch (std::bad_alloc ex)
			{
				cout << "����ʧ�ܣ�" << ex.what() << endl;
				return;
			}		
		}
	}

	// ����
	void insert(const T& data, int index)
	{
		if (index > _capacity || index < 0)
		{
			cout << "��λ�ò�֧�ֲ���" << endl;
		}
		else
		{
			// a. ˳������ĵ�һ���¾��Ǽ�������
			expansion();
			// b. Ų������
			for (int i = _size; i > index; --i)
			{
				_arr[i] = _arr[i - 1];
			}
			// c. ��������
			_arr[index] = data;
			// d. size++
			_size++;
		}
	}

	// ɾ��
	void erase(int index)
	{
		if (index >= _size || index < 0)
		{
			cout << "��λ�ò�֧��ɾ����" << endl;
		}
		else 
		{
			for (int i = index+1; i < _size; ++i)
				_arr[i-1] = _arr[i];
			_size--;
		}
	}

	// ����[]
	T& operator[](int index) throw (std::out_of_range) //�쳣���˵����
	{
		if (index >= _size || index < 0)
			throw std::out_of_range("Vector index out of range");
		else
			return _arr[index];
	}

	size_t getSize()
	{
		return _size;
	}
};

void print(const string& name, ArrayList<int>& al)
{
	try
	{
		cout << name << ": { ";
		for (int i = 0; i < al.getSize() - 1; ++i)
			cout << al[i] << ", ";
		cout << al[al.getSize()-1] << " }; size = " << al.getSize() << endl;
	}
	catch (std::out_of_range ex)
	{
		cout << "�Ƿ�����: " << ex.what() << endl;
	}
}
int main()
{
	ArrayList<int> al;
	// �쳣����
	al.insert(10, 10);
	try
	{
		al[10];
	}
	catch (std::out_of_range ex)
	{
		cout << "�Ƿ�����: " << ex.what() << endl;
	}

	// ͷ�壺
	al.insert(0, 0);
	al.insert(-1, 0);
	al.insert(-2, 0);
	print("al", al);

	// β�壺
	al.insert(1, al.getSize());
	al.insert(2, al.getSize());
	al.insert(3, al.getSize());
	al.insert(4, al.getSize());
	al.insert(5, al.getSize());
	print("al", al);

	// ���룺
	al.insert(34, 6);
	al.insert(33, 6);
	al.insert(44, 8);
	print("al", al);

	// ͷɾ
	al.erase(0);
	al.erase(0);
	print("al", al);

	// βɾ
	al.erase(al.getSize() - 1);
	print("al", al);

	// ɾ��
	al.erase(4);
	al.erase(4);
	al.erase(4);
	print("al", al);

	return 0;
}

//�ܽ᣺
// һ���쳣��
// 1. �쳣�׳���ֱ����ֹ������
// 2. std::out_of_range �� ר�Ŵ���Խ����ʵ��쳣����<stdexcept>�¡�
// 3. �쳣���˵�����ں����������һ��throw(),()��ſ����׳����쳣�����͡�
// 4. C++���׳����쳣���������������ᱨ������ǿ����ֹ����


// ������������
// 1. ����һ��Ҫ�ǵøı�capacity�Ĵ�С����������ɾ��һ��Ҫ�ı�size�Ĵ�С��
// 2. new�޷�ԭ�����ݡ�