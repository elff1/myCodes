#ifndef _MyString_H
#define _MyString_H

#include <iostream>
using namespace std;

// 定义字符串类
class MyString{
private:
	int n,Capacity;		// n为字符串长度，Capacity为字符串空间容量
	char *str;			// str为字符串首地址
	void ensureMinCap(const int);	// 最小字符串容量保障

public:
	MyString(){n=Capacity=0;str=0;}	// 无参构造函数
	MyString(const char *);		// C风格字符串构造函数
	MyString(const MyString&);	// 复制构造函数
	~MyString();	// 析构函数
	int size();		// 获得字符串长度
	void append(const char);	// 在字符串末尾增加一个字符
	int find(const MyString&,const int);	// 从一指定位置开始子串查找
	int compare(const MyString&);		// 字符串比较
	char *CStyle();		// 获得C风格字符串
	char& operator [](const int);	// 左值下标访问
	const char& operator [](const int) const;	// 右值下标访问
	MyString& operator = (const MyString&);		// 赋值操作
	
friend istream& operator >> (istream&, MyString&);	// 字符串输入
friend ostream& operator << (ostream&, const MyString&);	// 字符串输出
};

#endif //_MyString_H