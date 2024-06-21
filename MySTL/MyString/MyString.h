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
	typedef char* iterator;
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

// 迭代器(Iterator)
	iterator begin();
	iterator end();

// 容量操作(capacity operation)
	size_t size() const; //加const是为了让const对象也能使用
	size_t capacity() const;
	bool empty() const;
	void reserve(size_t n);
	void resize(size_t n, char c = '\0');
	void clear();

// 元素访问 (Element access)
	char& operator[] (size_t i); //[]
	const char& operator[] (size_t i) const; //[]
	char& at(size_t i); //at()
	const char& at(size_t i) const; //at()

// 修改操作(Modifiers):
	void expansion();
	void push_back(char c);
	MyString& append(const MyString& str);
	MyString& append(const MyString& str, size_t subpos, size_t sublen = npos);
	MyString& append(const char* s);
	MyString& append(const char* s, size_t n);
	MyString& append(size_t n, char c);
};

//参照STL中的string类来写一个MyString：
//day1.构造函数和析构函数
//day2.赋值运算符重载
//day3.迭代器 & 容量操作
