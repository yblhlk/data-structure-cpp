#include "MyString.h"
#include<cstring>
#include<iostream>
#include<cstring>
#include<cassert>
using namespace std;

int main()
{
	MyString s;
	MyString s1(1, 'a');
	MyString s2("abc");
	MyString s3("abcdefg", 4);
	MyString s4(s2);
	MyString s5(std::move(s2));

	return 0;
}