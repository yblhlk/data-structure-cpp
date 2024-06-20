#include "MyString.h"

// 1.���캯��
// ���캯��0 : Ĭ�Ϲ��캯��(����ͬʱ������Ĭ�Ϲ��캯��)
MyString::MyString()
{
	_str = nullptr;
	_size = _capacity = 0;
}
// ���캯��1 : ʹ���ַ����顢�����ַ�����
MyString::MyString(const char* str)
{
	_size = strlen(str);
	_capacity = _size;
	_str = new char[_capacity + 1](); // +1 : ����'\0'
	strcpy(_str, str); //�����ַ�������strcpy
}
MyString::MyString(const char* s, size_t count)
{
	assert(count <= strlen(s));

	_size = count;
	_capacity = _size;
	_str = new char[_capacity + 1](); // +1 : ����'\0'���ַ������п��ܲ���\0
	size_t slen = strlen(s);
	for (int i = 0; i < count; ++i)
		_str[i] = s[i];
}
// ���캯��2 : ��������(���)
/* a.���������ȥд��(�����¿ռ�) */
//MyString(const MyString& s)
//{
//	// ���� �ṹ��/�� �����϶�ֻ�����ֳ�Ա�������������͡�ָ�����ͣ��Զ������ͱ�����Ҳ�������������͵�һ�������壩
//	// ������Ĺؼ�����ʵ�ֶ� ָ������ָ��ռ� �Ŀ�����
//	// ������һ���¿ռ䣬�ٰ����ݿ���������¿ռ䡣
//	// �����Զ������ͳ�Ա�Ŀ�������Ҳ���ڰ����� ָ������ָ��ռ� ���п�����
//	
//	_size = s._size; // �����п��Է���ͬ������˽�г�Ա����Ϊ����������ڲ�ʵ�ֵģ������Ƕ���ģ����Բ���Υ����ķ�װ��˼�롣
//	_capacity = s._capacity;
//	_str = new char[_capacity + 1](); // +1 : ����'\0'
//	strcpy(_str, s._str); //�����ַ�������strcpy
//}
/* b.���������ִ�д��(���ù��캯��) */
void MyString::swap(MyString& s)
{
	std::swap(this->_str, s._str);
	std::swap(this->_size, s._size);
	std::swap(this->_capacity, s._capacity);
}
MyString::MyString(const MyString& s) 
	:_str(nullptr)
	, _size(0)
	, _capacity(0)
{
	MyString tmp(s._str); //���ù��캯������һ����ʱ����
	swap(tmp);   //�����Լ�д�Ľ���������ʹ��std::swap��������
}
MyString::MyString(const MyString& s, size_t start, size_t len)
{
	// ����û�û����len
	if (len == npos)
		len = strlen(s._str) - start;
	else
		assert(((long long)len + start) < strlen(s._str));

	_size = len;
	_capacity = _size;
	_str = new char[_capacity + 1](); // +1 : ����'\0'���ַ������п��ܲ���\0
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
// ���캯��3 : ʹ��n���ַ����й���
MyString::MyString(int count, const char c) //��֧��ֱ��ʹ�õ����ַ�������
{
	_size = count;
	_capacity = count;
	_str = new char[count + 1](); // +1 : ����'\0'
	for (int i = 0; i < count; i++)
		_str[i] = c;
}
/* ���캯��4 : �ƶ����� */
/* a.�ƶ������ȥд�� */
// �ƶ����캯���ᡰ��ȡ����һ��std::string������ڲ���Դ�����ַ�����ͳ��ȣ��������Ǹ������ǡ����������������ܣ��ر��ǵ���������ַ���ʱ��
// string (string&& str) noexcept; //STL���ƶ����캯���ĺ���������
//MyString(MyString&& s) noexcept
//{
//	// a.����ȡ��s����Դ
//	_size = s._size;
//	_capacity = s._capacity;
//	_str = s._str;
//	// b.��s�ÿգ�ȷ��s������ԭ������Դ
//	s._size = s._capacity  = 0;
//	s._str = nullptr;
//}
/* b.�ƶ�������ִ�д�� */
MyString::MyString(MyString&& s) noexcept
	: _str(nullptr)
	, _size(0)
	, _capacity(0)
{
	swap(s); // ֱ�ӵ����Լ�д��swap����ȡ��s����Դ
}

// 2.��������
MyString::~MyString()
{
	if (_str)
		delete[] _str;
	_str = nullptr;
	_size = _capacity = 0;
}

// 3.��ֵ���������
/*��ֵ���������1: MyString����ֵ*/
/*a.��ȥ��д��*/
//MyString& MyString::operator= (const MyString& s)
//{
//	//a. �ж��Ƿ���Լ���ֵ
//	if (&s != this)
//	{
//		//b. �������������Ҫ������ʱ���󣨷�ֹ���ʱ�����ٿռ�ʧ�ܣ�
//		char* tmp = nullptr;
//		try
//		{
//			tmp = new char[s._capacity]();
//		}
//		catch (std::bad_alloc& e)
//		{
//			cout << "new�ռ�ʧ�ܣ�" << e.what() << endl;
//		}
//		// c. ����ԭ�ռ�
//		delete[] this->_str;
//		this->_str = tmp;
//		strcpy(this->_str, tmp);
//		this->_size = s._size;
//		this->_capacity = s._capacity;
//	}
//	
//	return *this; // Ϊ��֧��������ֵ
//}
/*b.�ִ�д��1*/
MyString& MyString::operator= (const MyString& s)
{
	// a. �ж��Ƿ���Լ���ֵ
	if (&s != this)
	{
		//b. ���ù��캯������һ����ʱ����(��̬���٣���ȻҪ�Լ��ͷţ�
		MyString tmp(s._str);
		//c. �����Լ�д��swap�����������������������
		swap(tmp); //ֱ�ӽ�������ָ���ָ��(�����տ�ʼд���ˣ���̬���٣���ȻҪ�Լ��ͷţ�
		//d. �ͷ���ʱ���󣬻��Զ��������������ͷš�
	}
	return *this;
}
/*c.�ִ�д��2*/
//���ǵ���ָ��������β���ʵ�εĿ���������ֱ���Ӷ����Դ��
//ȱ���������޷��ж��Ƿ������Ҹ�ֵ�������Լ����Լ���ֵʱЧ�ʸ��͡�
//MyString& MyString::operator= (MyString s)
//{
//	swap(s);
//	return *this;
//}
/*��ֵ���������2: char����������ַ�����ֵ*/
MyString& MyString::operator= (const char* s)
{
	MyString tmp(s);
	swap(tmp);
	return *this;
}
/*��ֵ���������3: char�ַ���ֵ*/
MyString& MyString::operator= (char c)
{
	MyString tmp(&c); // ��Խ����--����
	swap(tmp);
	return *this;
}
/*��ֵ���������4: �ƶ���ֵ*/
MyString& MyString::operator= (MyString&& s) noexcept
{
	swap(s);
	return *this;
}