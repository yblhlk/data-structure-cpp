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
};

//����STL�е�string����дһ��MyString��
//day1.���캯������������




// �ƶ����캯��
// ������ȡ����һ��������ڲ���Դ�������Ǹ������ǡ����������������ܡ�
// a.����ȡ����ֵ�������Դ��
// b. ����ֵ�����ÿգ�ȷ���ö�������ԭ������Դ��
// c. û��const���Ҳ��׳��쳣��
//    std::string s2 = std::move(s1); //�����string���ƶ����캯����

// �ִ�д���ı��ʣ�
// ���ù��캯��������һ����ʱ�����������Լ�д��swap���н���������������������������Զ��ͷ�ԭ��Դ��

