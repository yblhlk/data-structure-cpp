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
//���캯��:
	// ���캯��0 : Ĭ�Ϲ��캯��(����ͬʱ������Ĭ�Ϲ��캯��)
	MyString();
	// ���캯��1 : ʹ���ַ����顢�����ַ�����
	MyString(const char* str);
	MyString(const char* s, size_t count);
	// ���캯��2 : ��������(���)
	// ���������ִ�д��(���ù��캯��)
	void swap(MyString& s);
	MyString(const MyString& s);
	MyString(const MyString& s, size_t start, size_t len = MyString::npos);
	// ���캯��3 : ʹ��n���ַ����й���
	MyString(int count, const char c); //��֧��ֱ��ʹ�õ����ַ�������
	// ���캯��4 : �ƶ�����
	MyString(MyString&& s) noexcept;

// ��������
	~MyString();

// ��ֵ���������
	MyString& operator= (const MyString& s);
	//MyString& operator= (MyString s);
	MyString& operator= (const char* s);
	MyString& operator= (char c);
	// �ƶ���ֵ���������Ӷ�Ŀ��������Դ��
	MyString& operator= (MyString&& s) noexcept;

// ������(Iterator)
	iterator begin();
	iterator end();

// ��������(capacity operation)
	size_t size() const; //��const��Ϊ����const����Ҳ��ʹ��
	size_t capacity() const;
	bool empty() const;
	void reserve(size_t n);
	void resize(size_t n, char c = '\0');
	void clear();

// Ԫ�ط��� (Element access)
	char& operator[] (size_t i); //[]
	const char& operator[] (size_t i) const; //[]
	char& at(size_t i); //at()
	const char& at(size_t i) const; //at()

// �޸Ĳ���(Modifiers):
	void expansion();
	void push_back(char c);
	MyString& append(const MyString& str);
	MyString& append(const MyString& str, size_t subpos, size_t sublen = npos);
	MyString& append(const char* s);
	MyString& append(const char* s, size_t n);
	MyString& append(size_t n, char c);
};

//����STL�е�string����дһ��MyString��
//day1.���캯������������
//day2.��ֵ���������
//day3.������ & ��������
