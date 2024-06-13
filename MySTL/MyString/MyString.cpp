#include "MyString.h"

// 1.构造函数
	// 构造函数0 : 默认构造函数(不能同时有两个默认构造函数)
MyString::MyString()
{
	_str = nullptr;
	_size = _capacity = 0;
}
// 构造函数1 : 使用字符数组、常量字符串。
MyString::MyString(const char* str)
{
	_size = strlen(str);
	_capacity = _size;
	_str = new char[_capacity + 1](); // +1 : 保存'\0'
	strcpy(_str, str); //拷贝字符数组用strcpy
}
MyString::MyString(const char* s, size_t count)
{
	assert(count <= strlen(s));

	_size = count;
	_capacity = _size;
	_str = new char[_capacity + 1](); // +1 : 保存'\0'，字符数组中可能不带\0
	size_t slen = strlen(s);
	for (int i = 0; i < count; ++i)
		_str[i] = s[i];
}
// 构造函数2 : 拷贝构造(深拷贝)
//MyString(const MyString& s)
//{
//	// 所有 结构体/类 本质上都只有两种成员变量：基本类型、指针类型（自定义类型本质上也就是这两种类型的一个集合体）
//	// 而深拷贝的关键在于实现对 指针类型指向空间 的拷贝，
//	// 即开辟一个新空间，再把内容拷贝到这个新空间。
//	// 调用自定义类型成员的拷贝构造也是在把它的 指针类型指向空间 进行拷贝。
//	
//	_size = s._size; // 在类中可以访问同类对象的私有成员。因为在是在类的内部实现的，并不是对外的，所以并不违背类的封装的思想。
//	_capacity = s._capacity;
//	_str = new char[_capacity + 1](); // +1 : 保存'\0'
//	strcpy(_str, s._str); //拷贝字符数组用strcpy
//}
void MyString::swap(MyString& s)
{
	std::swap(this->_str, s._str);
	std::swap(this->_size, s._size);
	std::swap(this->_capacity, s._capacity);
}
MyString::MyString(const MyString& s) // 拷贝构造现代写法(借用构造函数)
	:_str(nullptr)
	, _size(0)
	, _capacity(0)
{
	MyString tmp(s._str); //利用构造函数构造一个临时对象
	swap(tmp);   //调用自己写的交换（里面使用std::swap来交换）
}
MyString::MyString(const MyString& s, size_t start, size_t len)
{
	// 如果用户没传入len
	if (len == npos)
		len = strlen(s._str) - start;
	else
		assert(((long long)len + start) < strlen(s._str));

	_size = len;
	_capacity = _size;
	_str = new char[_capacity + 1](); // +1 : 保存'\0'，字符数组中可能不带\0
	size_t slen = strlen(s._str);
	for (int i = 0; i < len; ++i)
	{
		size_t pos = start + i;
		if (pos < slen)
			_str[i] = s._str[pos];
		else
			_str[i] = '\0';
	}
}
// 构造函数3 : 使用n个字符进行构造
MyString::MyString(int count, const char c) //不支持直接使用单个字符来构造
{
	_size = count;
	_capacity = count;
	_str = new char[count + 1](); // +1 : 保存'\0'
	for (int i = 0; i < count; i++)
		_str[i] = c;
}
/* 构造函数4 : 移动构造 */
// 移动构造函数会“窃取”另一个std::string对象的内部资源（如字符数组和长度），而不是复制它们。这可以显著提高性能，特别是当处理大型字符串时。
// string (string&& str) noexcept; //STL中移动构造函数的函数声明。
//MyString(MyString&& s) noexcept
//{
//	// a.“窃取”s的资源
//	_size = s._size;
//	_capacity = s._capacity;
//	_str = s._str;
//	// b.将s置空，确保s不再有原来的资源
//	s._size = s._capacity  = 0;
//	s._str = nullptr;
//}
MyString::MyString(MyString&& s) noexcept// 移动构造的现代写法
	: _str(nullptr)
	, _size(0)
	, _capacity(0)
{
	swap(s); // 直接调用自己写的swap“窃取”s的资源
}

// 析构函数
MyString::~MyString()
{
	if (_str)
		delete[] _str;
	_str = nullptr;
	_size = _capacity = 0;
}

// 赋值运算符重载
MyString& MyString::operator= (const MyString& s)
{}
MyString& MyString::operator= (const char* s)
{}
MyString& MyString::operator= (char c)
{}
MyString& MyString::operator= (MyString&& s) noexcept
{}