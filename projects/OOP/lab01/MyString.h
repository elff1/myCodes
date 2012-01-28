#ifndef _MyString_H
#define _MyString_H

#include <iostream>
using namespace std;

// �����ַ�����
class MyString{
private:
	int n,Capacity;		// nΪ�ַ������ȣ�CapacityΪ�ַ����ռ�����
	char *str;			// strΪ�ַ����׵�ַ
	void ensureMinCap(const int);	// ��С�ַ�����������

public:
	MyString(){n=Capacity=0;str=0;}	// �޲ι��캯��
	MyString(const char *);		// C����ַ������캯��
	MyString(const MyString&);	// ���ƹ��캯��
	~MyString();	// ��������
	int size();		// ����ַ�������
	void append(const char);	// ���ַ���ĩβ����һ���ַ�
	int find(const MyString&,const int);	// ��һָ��λ�ÿ�ʼ�Ӵ�����
	int compare(const MyString&);		// �ַ����Ƚ�
	char *CStyle();		// ���C����ַ���
	char& operator [](const int);	// ��ֵ�±����
	const char& operator [](const int) const;	// ��ֵ�±����
	MyString& operator = (const MyString&);		// ��ֵ����
	
friend istream& operator >> (istream&, MyString&);	// �ַ�������
friend ostream& operator << (ostream&, const MyString&);	// �ַ������
};

#endif //_MyString_H