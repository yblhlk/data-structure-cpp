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
	// 构造函数2 : 拷贝构造(深拷贝)
	// 拷贝构造现代写法(借用构造函数)
	void swap(MyString& s);
	MyString(const MyString& s);
	MyString(const MyString& s, size_t start, size_t len = MyString::npos);
	// 构造函数3 : 使用n个字符进行构造
	MyString(int count, const char c); //不支持直接使用单个字符来构造
	// 构造函数4 : 移动构造
	MyString(MyString&& s) noexcept;

// 析构函数
	~MyString();

// 赋值运算符重载
	MyString& operator= (const MyString& s);
	//MyString& operator= (MyString s);
	MyString& operator= (const char* s);
	MyString& operator= (char c);
	// 移动赋值：作用是掠夺目标对象的资源。
	MyString& operator= (MyString&& s) noexcept;
};

//参照STL中的string类来写一个MyString：
//day1.构造函数和析构函数




// 移动构造函数
// 用来窃取”另一个对象的内部资源，而不是复制它们。这可以显著提高性能。
// a.“窃取”右值对象的资源。
// b. 将右值对象置空，确保该对象不再有原来的资源。
// c. 没有const，且不抛出异常。
//    std::string s2 = std::move(s1); //会调用string的移动构造函数。

// 现代写法的本质：
// 复用构造函数来创建一个临时变量，再用自己写的swap进行交换，最后利用析构函数的性质自动释放原资源。

