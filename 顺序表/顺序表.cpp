#include<iostream>
#include <memory> 
using namespace std;

// 使用 std::shared_ptr 管理new数组，要自定义删除器
struct ArrayDeleter {
	void operator()(int* p) const {
		delete[] p;
	}
};

typedef int datatype;

class ArrayList
{
private:
	shared_ptr<datatype> _array; //智能指针，因为new扩容要重新new一个数组所以使用shared_ptr。
	size_t _size;
	size_t _capacity;
public:
	ArrayList(int capacity = 0)
		: _size(0)
		, _array(new datatype[capacity], ArrayDeleter()) // 区分[] 和 (), 智能指针shared_ptr管理数组要自定义删除器
	{
		_capacity = capacity;
	}

	size_t size()
	{
		return _size;
	}

	// 检查扩容
	void expansion()
	{
		if (_size == _capacity)
		{
			// new无法原地扩容，只能新开、拷贝、重定向
			// a. 创建一个新数组
			_capacity = (_capacity == 0 ? 4 : _capacity * 2);
			shared_ptr<datatype> newarray(new datatype[_capacity], [](datatype* p) { delete[] p; });
			// b. 将原数组的内容拷贝到新数组中
			for (int i = 0; i < _size; i++)
			{
				*(newarray.get()+i) = *(_array.get() + i);
			}
			// c. 释放原数组，交换指针指向。
			_array.reset();
			_array.swap(newarray);
		}
	}

	// 插入
	void insert(datatype data, int index)
	{
		// 尾插是按size来尾插，不是按capacity来尾插。
		if (index > _capacity || index < -1)
		{
			cout << "该位置不支持插入，请检查是否超出容量，或为负数" << endl;
		}
		else
		{
			// a.检查扩容
			expansion();
			// b.挪动数据
			for (int i = _size; i > index; i--)
			{
				_array.get()[i] = _array.get()[i - 1];
			}
			// c.插入数据
			_array.get()[index] = data;
			_size++;
		}
	}

	// 删除
	void erase(int index)
	{
		if (index >= _size || index < 0)
		{
			cout << " 该位置不支持删除！ " << endl;
		}
		else
		{
			// 向前覆盖
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
			cout << "该位置不支持访问, 返回随机值 : ";
		}
		else
			return _array.get()[index];
	}
};

int main()
{
	ArrayList al;

	// 尾插
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

	// 头插
	al.insert(0, 0);
	al.insert(-1, 0);
	al.insert(-2, 0);
	cout << "al.size() : " << al.size() << ", al { ";
	for (int i = 0; i < al.size(); i++)
		cout << al[i] << ", ";
	cout << "};" << endl;

	// 插入
	al.insert(34, 6);
	al.insert(33, 6);
	al.insert(44, 8);
	cout << "al.size() : " << al.size() << ", al { ";
	for (int i = 0; i < al.size(); i++)
		cout << al[i] << ", ";
	cout << "};" << endl;

	// 头删
	al.erase(0);
	al.erase(0);
	cout << "al.size() : " << al.size() << ", al { ";
	for (int i = 0; i < al.size(); i++)
		cout << al[i] << ", ";
	cout << "};" << endl;

	// 尾删
	al.erase(al.size() - 1);
	al.erase(al.size() - 1);
	cout << "al.size() : " << al.size() << ", al { ";
	for (int i = 0; i < al.size(); i++)
		cout << al[i] << ", ";
	cout << "};" << endl;

	// 删除
	al.erase(4);
	al.erase(4);
	al.erase(4);
	cout << "al.size() : " << al.size() << ", al { ";
	for (int i = 0; i < al.size(); i++)
		cout << al[i] << ", ";
	cout << "};" << endl;
	return 0;
}

// 错误一：
// 智能指针能进行下标访问和修改：ptr.get()[index];
// 要注意：new 中()和[] 的区别：()是初始化，[]是表示数组。

// 结论：
// 智能指针在C++中的主要作用是自动管理动态分配的内存，防止内存泄漏和悬空指针等问题。智能指针通常用于管理单个对象的指针，而不是数组的指针。
// 对于std::unique_ptr，你可以使用模板特化std::unique_ptr<T[]>来管理指向数组的指针。这样，当std::unique_ptr被销毁时，它会调用delete[]来释放数组内存。
// 对于std::shared_ptr，你需要提供一个自定义删除器（custom deleter），该删除器会在最后一个std::shared_ptr被销毁时调用delete[]来释放数组内存。
// 智能指针shared_ptr管理数组要自定义删除器：
// 仿函数：struct ArrayDeleter {
//				void operator()(int* p) const {
//					delete[] p;
//				}
//			};
// 传入一个lambda表达式：[](int* p) { delete[] p; }


// 插入是看capacity,尾插是看size,删除是看size.
// 插入：要检查扩容(新数组,拷贝数据，改变指向)、挪动数据（从最后一个开始挪动）、插入数据（size++)
// 删除：从删除位置的下一个位置向前覆盖到最后一个位置。size--;