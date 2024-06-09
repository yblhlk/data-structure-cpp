#include<iostream>
#include <memory> 
using namespace std;

// ʹ�� std::shared_ptr ����new���飬Ҫ�Զ���ɾ����
struct ArrayDeleter {
	void operator()(int* p) const {
		delete[] p;
	}
};

typedef int datatype;

class ArrayList
{
private:
	shared_ptr<datatype> _array; //����ָ�룬��Ϊnew����Ҫ����newһ����������ʹ��shared_ptr��
	size_t _size;
	size_t _capacity;
public:
	ArrayList(int capacity = 0)
		: _size(0)
		, _array(new datatype[capacity], ArrayDeleter()) // ����[] �� (), ����ָ��shared_ptr��������Ҫ�Զ���ɾ����
	{
		_capacity = capacity;
	}

	size_t size()
	{
		return _size;
	}

	// �������
	void expansion()
	{
		if (_size == _capacity)
		{
			// new�޷�ԭ�����ݣ�ֻ���¿����������ض���
			// a. ����һ��������
			_capacity = (_capacity == 0 ? 4 : _capacity * 2);
			shared_ptr<datatype> newarray(new datatype[_capacity], [](datatype* p) { delete[] p; });
			// b. ��ԭ��������ݿ�������������
			for (int i = 0; i < _size; i++)
			{
				*(newarray.get()+i) = *(_array.get() + i);
			}
			// c. �ͷ�ԭ���飬����ָ��ָ��
			_array.reset();
			_array.swap(newarray);
		}
	}

	// ����
	void insert(datatype data, int index)
	{
		// β���ǰ�size��β�壬���ǰ�capacity��β�塣
		if (index > _capacity || index < -1)
		{
			cout << "��λ�ò�֧�ֲ��룬�����Ƿ񳬳���������Ϊ����" << endl;
		}
		else
		{
			// a.�������
			expansion();
			// b.Ų������
			for (int i = _size; i > index; i--)
			{
				_array.get()[i] = _array.get()[i - 1];
			}
			// c.��������
			_array.get()[index] = data;
			_size++;
		}
	}

	// ɾ��
	void erase(int index)
	{
		if (index >= _size || index < 0)
		{
			cout << " ��λ�ò�֧��ɾ���� " << endl;
		}
		else
		{
			// ��ǰ����
			for (int i = index; i < _size-1; ++i)
			{
				_array.get()[i] = _array.get()[i + 1];
			}
			_size--;
		}
	}

	datatype operator[] (int index)
	{
		if (index >= _size || index < 0)
		{
			cout << "��λ�ò�֧�ַ���, �������ֵ : ";
		}
		else
			return _array.get()[index];
	}
};

int main()
{
	ArrayList al;

	// β��
	al.insert(1, al.size());
	al.insert(2, al.size());
	al.insert(3, al.size());
	al.insert(4, al.size());
	al.insert(5, al.size());
	al.insert(6, al.size());
	cout << al.size() << endl;
	cout << "al.size() : " << al.size() << ", al { ";
	for (int i = 0; i < al.size(); i++)
		cout << al[i] << ", ";
	cout << "};" << endl;

	// ͷ��
	al.insert(0, 0);
	al.insert(-1, 0);
	al.insert(-2, 0);
	cout << "al.size() : " << al.size() << ", al { ";
	for (int i = 0; i < al.size(); i++)
		cout << al[i] << ", ";
	cout << "};" << endl;

	// ����
	al.insert(34, 6);
	al.insert(33, 6);
	al.insert(44, 8);
	cout << "al.size() : " << al.size() << ", al { ";
	for (int i = 0; i < al.size(); i++)
		cout << al[i] << ", ";
	cout << "};" << endl;

	// ͷɾ
	al.erase(0);
	al.erase(0);
	cout << "al.size() : " << al.size() << ", al { ";
	for (int i = 0; i < al.size(); i++)
		cout << al[i] << ", ";
	cout << "};" << endl;

	// βɾ
	al.erase(al.size() - 1);
	al.erase(al.size() - 1);
	cout << "al.size() : " << al.size() << ", al { ";
	for (int i = 0; i < al.size(); i++)
		cout << al[i] << ", ";
	cout << "};" << endl;

	// ɾ��
	al.erase(4);
	al.erase(4);
	al.erase(4);
	cout << "al.size() : " << al.size() << ", al { ";
	for (int i = 0; i < al.size(); i++)
		cout << al[i] << ", ";
	cout << "};" << endl;
	return 0;
}

// ����һ��
// ����ָ���ܽ����±���ʺ��޸ģ�ptr.get()[index];
// Ҫע�⣺new ��()��[] ������()�ǳ�ʼ����[]�Ǳ�ʾ���顣

// ���ۣ�
// ����ָ����C++�е���Ҫ�������Զ�����̬������ڴ棬��ֹ�ڴ�й©������ָ������⡣����ָ��ͨ�����ڹ����������ָ�룬�����������ָ�롣
// ����std::unique_ptr�������ʹ��ģ���ػ�std::unique_ptr<T[]>������ָ�������ָ�롣��������std::unique_ptr������ʱ���������delete[]���ͷ������ڴ档
// ����std::shared_ptr������Ҫ�ṩһ���Զ���ɾ������custom deleter������ɾ�����������һ��std::shared_ptr������ʱ����delete[]���ͷ������ڴ档
// ����ָ��shared_ptr��������Ҫ�Զ���ɾ������
// �º�����struct ArrayDeleter {
//				void operator()(int* p) const {
//					delete[] p;
//				}
//			};
// ����һ��lambda���ʽ��[](int* p) { delete[] p; }


// �����ǿ�capacity,β���ǿ�size,ɾ���ǿ�size.
// ���룺Ҫ�������(������,�������ݣ��ı�ָ��)��Ų�����ݣ������һ����ʼŲ�������������ݣ�size++)
// ɾ������ɾ��λ�õ���һ��λ����ǰ���ǵ����һ��λ�á�size--;