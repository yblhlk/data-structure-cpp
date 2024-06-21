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

// 4. ������
MyString::iterator MyString::begin()
{
	return _str;
}
MyString::iterator MyString::end()
{
	return _str + _size; //end�����һ��Ԫ�ص���һ��λ�á�
}

// 5.��������(capacity operation)
size_t MyString::size() const  //��const��Ϊ����const����Ҳ��ʹ��
{
	return _size;
}
size_t MyString::capacity() const 
{
	return _capacity;
}
bool MyString::empty() const
{
	return (_size == 0);
}
void MyString::reserve(size_t n)
{
	if (n > _size)
	{
		char* tmp = new char[n + 1](); // +1 ���� \0
		strcpy(tmp, _str);
		delete[] _str;
		_str = tmp;
		_capacity = n; //��������
	}
}
void MyString::resize(size_t n, char c = '\0')
{
	if (n > _size)
	{
		reserve(n);//����
		for (int i = _size; i < n; i++)
		{
			_str[i] = c;
		}
		_size = n;
		_str[n] = '\0';
	}
	else
	{
		_str[n] = '\0';
		_size = n;
	}
}
void MyString::clear()
{
	_str[0] = '\0';
	_size = 0;
}

// Ԫ�ط��� (Element access)
char& MyString::operator[] (size_t i) //[]
{
	assert(i < _size);
	return _str[i];
}
const char& MyString::operator[] (size_t i) const //[]
{
	assert(i < _size);
	return _str[i];
}
char& MyString::at(size_t i) //at()
{
	assert(i < _size);
	return _str[i];
}
const char& MyString::at(size_t i) const //at()
{
	assert(i < _size);
	return _str[i];
}


// �޸Ĳ���(Modifiers):
void MyString::expansion()
{
	if (_size == _capacity)
	{
		int newcapacity = (0 == _capacity ? 4 : _capacity * 2);
		char* tmp = new char[newcapacity +1](); //+1 ����\0
		strcmp(tmp, _str);
		delete[] _str;
		_str = tmp;
		_capacity = newcapacity;
	}
}
void MyString::push_back(char c)
{
	//�ж�����(��ʵ���Ը���reserve()�ģ�
	if(_size == _capacity)
	{
		int newcapacity = (0 == _capacity ? 4 : _capacity * 2);
		reserve(newcapacity);
	}
	_str[_size++] = c;
	_str[_size] = '\0';
}
MyString& MyString::append(const MyString& str)
{
	int len = _size + str.size();
	//�ж�����(��ʵ���Ը���reserve()�ģ�
	if (len > _capacity)
	{
		int newcapacity = (0 == len ? 4 : len);
		reserve(len);
	}
	for (int i = _size, j = 0; j < str.size(); i++, j++)
	{
		_str[i] = str[j];
	}
	_str[len] = '\0';
}
MyString& MyString::append(const MyString& str, size_t subpos, size_t sublen)
{
	assert(subpos < str.size());

	if (sublen == MyString::npos)
		sublen = str.size() - subpos;

	int len = _size + sublen;
	//�ж�����(��ʵ���Ը���reserve()�ģ�
	if (len > _capacity)
	{
		int newcapacity = (0 == len ? 4 : len);
		reserve(len);
	}
	for (int i = _size, j = subpos; j < subpos + sublen; i++, j++)
	{
		_str[i] = str[j];
	}
	_str[len] = '\0';
}
MyString& MyString::append(const char* s)
{
	int len = _size + strlen(s);
	//�ж�����(��ʵ���Ը���reserve()�ģ�
	if (len > _capacity)
	{
		int newcapacity = (0 == len ? 4 : len);
		reserve(len);
	}
	for (int i = _size, j = 0; j < strlen(s); i++, j++)
	{
		_str[i] = s[j];
	}
	_str[len] = '\0';
}
MyString& MyString::append(const char* s, size_t n)
{

}
MyString& MyString::append(size_t n, char c)
{}