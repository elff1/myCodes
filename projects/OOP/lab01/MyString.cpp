#include "MyString.h"
#include <string.h>

// C风格字符串构造函数
MyString ::MyString(const char *s){
	Capacity = 0;		// 字符串初始化
	str = 0;
	n = strlen(s);		// 获得字符串长度
	ensureMinCap(n);	// 保障最小字符串容量
	memcpy(str, s, n);	// 复制字符串数据
}

// 复制构造函数
MyString ::MyString(const MyString& s){
	Capacity = 0;		// 字符串初始化
	str = 0;
	n = s.n;
	ensureMinCap(n);	// 保障最小字符串容量
	memcpy(str, s.str, n);	// 复制字符串数据
}

// 析构函数
MyString ::~MyString(){
	delete []str;	// 释放字符串空间
}

// 获得字符串长度
int MyString ::size(){
	return n;
}

// 最小字符串容量保障
void MyString ::ensureMinCap(const int cap){
	// 当当前容量不足时，进行扩容
	if(Capacity < cap){
		char *nstr = new char[cap];		// 申请足够的新空间
		memset(nstr + Capacity, 0, cap - Capacity);	// 将新空间的高位部分初始化为0
		memcpy(nstr, str, Capacity);	// 负责原字符串数据
		delete []str;		// 释放原字符串空间
		str = nstr;		// 更新字符串信息
		Capacity = cap;
	}
}

// 在字符串末尾增加一个字符
void MyString ::append(const char ch){
	ensureMinCap(n+1);	// 保障最小字符串容量
	str[n++] = ch;		// 在字符串末尾添加新的字符
}

// 从一指定位置开始子串查找
int MyString ::find(const MyString& s, const int k){
	int i, j, p, f, sn;

	sn = s.n;
	// 从指定的k位开始查找子串
	for(p = k; p <= n - sn; p++){
		f = 1;
		// 对子串中的字符与母串逐个比较
		for(i = p, j = 0; (i < n) && (j < sn); i++, j++)
			if(str[i] != s[j]){
				f = 0;
				break;
			}
		if(f) return p;		// 找到后，返回子串在母串中的起始位置
	}
	return n;	// 未找到，返回字符串长度
}

/*
* 字符串比较
* 小返回-1，相同返回0，大返回1
*/
int MyString ::compare(const MyString& s){
	int i, j, sn;

	sn = s.n;
	for(i = 0; i < n && i < sn; i++){
		if(str[i] < s[i])
			return -1;
		if(str[i] > s[i])
			return 1;
	}
	if(i < n)
		return 1;
	if(i < sn)
		return -1;
	return 0;
}

// 获得C风格字符串
char *MyString ::CStyle(){
	char *s;
	int i;

	s = new char[n+1];	// 申请C风格字符串空间
	// 对其逐个赋值
	for(i = 0; i < n; i++)
		s[i] = str[i];
	s[n] = 0;	// 最后一位设为0
	return s;	// 返回其首地址
}

// 左值下标访问
char& MyString ::operator [](const int k){
	return str[k];
}

// 右值下标访问
const char& MyString ::operator [](const int k) const{
	return str[k];
}

// 赋值操作
MyString& MyString ::operator =(const MyString& s){
	ensureMinCap(s.n);	// 保障最小字符串容量
	memcpy(str, s.str, s.n);	// 复制字符串数据
	n = s.n;	// 更新字符串长度
	return *this;
}

// 字符串输入
istream& operator >> (istream& is, MyString& s){
	int ch;
	
	s.n = 0;		// 初始化字符串长度
	// 忽略white space
	do{
		ch = is.get();
		if(ch == EOF)return is;		// 若输入已读完，则返回
	}while(ch == ' ' || ch == '\t' || ch == '\n');
	// 读入字符串，直到遇到white space或输入结束
	do{
		s.append(ch);
		ch = is.get();
	}while(ch != ' ' && ch != '\t' && ch != '\n' && ch != EOF);
	return is;
}

// 字符串输出
ostream& operator << (ostream& os, const MyString& s){
	int i;

	// 依次将字符串中各字符输出
	for(i = 0; i < s.n; i++)
		os << s.str[i];
	return os;
}