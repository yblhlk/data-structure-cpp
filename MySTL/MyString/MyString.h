#pragma once

#include<cstring>
#include<iostream>
#include<cstring>
#include<cassert>
using namespace std;

class MyString
{
private:
	char* _str;
	size_t _size;
	size_t _capacity;

public:
	static const size_t npos = -1;
//构造函数:
	// 构造函数0 : 默认构造函数(不能同时有两个默认构造函数)
	MyString();
	// 构造函数1 : 使用字符数组、常量字符串。
	MyString(const char* str);
	MyString(const char* s, size_t count);
	/* 构造函数2 : 拷贝构造(深拷贝) */
	// 拷贝构造一般写法
	//MyString(const MyString& s)
	//{
	//	// 所有 结构体/类 本质上都只有两种成员变量：基本类型、指针类型（自定义类型本质上也就是这两种类型的一个集合体）
	//	// 而深拷贝的关键在于实现对 指针类型指向空间 的拷贝，
	//	// 即开辟一个新空间，再把内容拷贝到这个新空间。
	//	// 调用自定义类型成员的拷贝构造也是在把它的 指针类型指向空间 进行拷贝。
	//	
	//	_size = s._size; // 在类中可以访问同类对象的私有成员。因为在是在类的内部实现的，并不是对外的，所以并不违背类的封装的思想。
	//	_capacity = s._capacity;
	//	_str = new char[_capacity + 1]; // +1 : 保存'\0'
	//	strcpy(_str, s._str); //拷贝字符数组用strcpy
	//}
	// 拷贝构造现代写法(借用构造函数)
	void swap(MyString& s);
	MyString(const MyString& s);
	MyString(const MyString& s, size_t start, size_t len = MyString::npos);
	// 构造函数3 : 使用n个字符进行构造
	MyString(int count, const char c); //不支持直接使用单个字符来构造
	/* 构造函数4 : 移动构造 */ 
	// 移动构造函数会“窃取”另一个std::string对象的内部资源（如字符数组和长度），而不是复制它们。这可以显著提高性能，特别是当处理大型字符串时。
	// string (string&& str) noexcept; //STL中移动构造函数的函数声明。
	//MyString(MyString&& s) noexcept
	//{
	//	// “窃取”s的资源
	//	_size = s._size;
	//	_capacity = s._capacity;
	//	_str = s._str;
	//	// 将s置空，确保s不再有原来的资源
	//	s._size = s._capacity  = 0;
	//	s._str = nullptr;
	//}
	// 移动构造的现代写法
	MyString(MyString&& s) noexcept;

// 析构函数
	~MyString();

// 赋值运算符重载
	MyString& operator= (const MyString& s);
	MyString& operator= (const char* s);
	MyString& operator= (char c);
	// 移动赋值：作用是掠夺目标对象的资源。
	MyString& operator= (MyString&& s) noexcept;
};






// 移动构造函数
// 用来窃取”另一个对象的内部资源，而不是复制它们。这可以显著提高性能。
// a.“窃取”右值对象的资源。
// b. 将右值对象置空，确保该对象不再有原来的资源。
// c. 没有const，且不抛出异常。
//    std::string s2 = std::move(s1); //会调用string的移动构造函数。

