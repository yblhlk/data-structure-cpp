#include<iostream>
#include <new> // 为了使用 std::bad_alloc  
#include <stdexcept>   // 为了使用 std::out_of_range
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

	// 扩容
	void expansion()
	{
		if (_size == _capacity)
		{
			// a. 创建新数组 (扩容一定要记得改变capacity)
			_capacity = _capacity == 0 ? 4 : _capacity * 2;
			try
			{
				T* newarr = new T[_capacity];
				// b. 拷贝内容到新数组
				for (int i = 0; i < _size; ++i)
				{
					*(newarr + i) = *(_arr + i);
				}
				// c. 删除原数组
				if (_arr)
					delete[](_arr);
				// d. 改变数组指针指向
				_arr = newarr;
			}
			catch (std::bad_alloc ex)
			{
				cout << "扩容失败！" << ex.what() << endl;
				return;
			}		
		}
	}

	// 插入
	void insert(const T& data, int index)
	{
		if (index > _capacity || index < 0)
		{
			cout << "该位置不支持插入" << endl;
		}
		else
		{
			// a. 顺序表插入的第一件事就是检查和扩容
			expansion();
			// b. 挪动数据
			for (int i = _size; i > index; --i)
			{
				_arr[i] = _arr[i - 1];
			}
			// c. 插入数据
			_arr[index] = data;
			// d. size++
			_size++;
		}
	}

	// 删除
	void erase(int index)
	{
		if (index >= _size || index < 0)
		{
			cout << "该位置不支持删除！" << endl;
		}
		else 
		{
			for (int i = index+1; i < _size; ++i)
				_arr[i-1] = _arr[i];
			_size--;
		}
	}

	// 重载[]
	T& operator[](int index) throw (std::out_of_range) //异常规格说明。
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
		cout << "非法访问: " << ex.what() << endl;
	}
}
int main()
{
	ArrayList<int> al;
	// 异常处理：
	al.insert(10, 10);
	try
	{
		al[10];
	}
	catch (std::out_of_range ex)
	{
		cout << "非法访问: " << ex.what() << endl;
	}

	// 头插：
	al.insert(0, 0);
	al.insert(-1, 0);
	al.insert(-2, 0);
	print("al", al);

	// 尾插：
	al.insert(1, al.getSize());
	al.insert(2, al.getSize());
	al.insert(3, al.getSize());
	al.insert(4, al.getSize());
	al.insert(5, al.getSize());
	print("al", al);

	// 插入：
	al.insert(34, 6);
	al.insert(33, 6);
	al.insert(44, 8);
	print("al", al);

	// 头删
	al.erase(0);
	al.erase(0);
	print("al", al);

	// 尾删
	al.erase(al.getSize() - 1);
	print("al", al);

	// 删除
	al.erase(4);
	al.erase(4);
	al.erase(4);
	print("al", al);

	return 0;
}

//总结：
// 一、异常：
// 1. 异常抛出会直接终止函数。
// 2. std::out_of_range ： 专门处理越界访问的异常，在<stdexcept>下。
// 3. 异常规格说明：在函数声明后加一个throw(),()里放可能抛出的异常的类型。
// 4. C++中抛出的异常不处理，编译器不会报错，但会强制终止程序。


// 二、扩容问题
// 1. 扩容一定要记得改变capacity的大小，就像插入和删除一定要改变size的大小。
// 2. new无法原地扩容。