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
	/* ���캯��2 : ��������(���) */
	// ��������һ��д��
	//MyString(const MyString& s)
	//{
	//	// ���� �ṹ��/�� �����϶�ֻ�����ֳ�Ա�������������͡�ָ�����ͣ��Զ������ͱ�����Ҳ�������������͵�һ�������壩
	//	// ������Ĺؼ�����ʵ�ֶ� ָ������ָ��ռ� �Ŀ�����
	//	// ������һ���¿ռ䣬�ٰ����ݿ���������¿ռ䡣
	//	// �����Զ������ͳ�Ա�Ŀ�������Ҳ���ڰ����� ָ������ָ��ռ� ���п�����
	//	
	//	_size = s._size; // �����п��Է���ͬ������˽�г�Ա����Ϊ����������ڲ�ʵ�ֵģ������Ƕ���ģ����Բ���Υ����ķ�װ��˼�롣
	//	_capacity = s._capacity;
	//	_str = new char[_capacity + 1]; // +1 : ����'\0'
	//	strcpy(_str, s._str); //�����ַ�������strcpy
	//}
	// ���������ִ�д��(���ù��캯��)
	void swap(MyString& s);
	MyString(const MyString& s);
	MyString(const MyString& s, size_t start, size_t len = MyString::npos);
	// ���캯��3 : ʹ��n���ַ����й���
	MyString(int count, const char c); //��֧��ֱ��ʹ�õ����ַ�������
	/* ���캯��4 : �ƶ����� */ 
	// �ƶ����캯���ᡰ��ȡ����һ��std::string������ڲ���Դ�����ַ�����ͳ��ȣ��������Ǹ������ǡ����������������ܣ��ر��ǵ���������ַ���ʱ��
	// string (string&& str) noexcept; //STL���ƶ����캯���ĺ���������
	//MyString(MyString&& s) noexcept
	//{
	//	// ����ȡ��s����Դ
	//	_size = s._size;
	//	_capacity = s._capacity;
	//	_str = s._str;
	//	// ��s�ÿգ�ȷ��s������ԭ������Դ
	//	s._size = s._capacity  = 0;
	//	s._str = nullptr;
	//}
	// �ƶ�������ִ�д��
	MyString(MyString&& s) noexcept;

// ��������
	~MyString();

// ��ֵ���������
	MyString& operator= (const MyString& s);
	MyString& operator= (const char* s);
	MyString& operator= (char c);
	// �ƶ���ֵ���������Ӷ�Ŀ��������Դ��
	MyString& operator= (MyString&& s) noexcept;
};






// �ƶ����캯��
// ������ȡ����һ��������ڲ���Դ�������Ǹ������ǡ����������������ܡ�
// a.����ȡ����ֵ�������Դ��
// b. ����ֵ�����ÿգ�ȷ���ö�������ԭ������Դ��
// c. û��const���Ҳ��׳��쳣��
//    std::string s2 = std::move(s1); //�����string���ƶ����캯����

