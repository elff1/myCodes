#include "MyString.h"
#include <string.h>

// C����ַ������캯��
MyString ::MyString(const char *s){
	Capacity = 0;		// �ַ�����ʼ��
	str = 0;
	n = strlen(s);		// ����ַ�������
	ensureMinCap(n);	// ������С�ַ�������
	memcpy(str, s, n);	// �����ַ�������
}

// ���ƹ��캯��
MyString ::MyString(const MyString& s){
	Capacity = 0;		// �ַ�����ʼ��
	str = 0;
	n = s.n;
	ensureMinCap(n);	// ������С�ַ�������
	memcpy(str, s.str, n);	// �����ַ�������
}

// ��������
MyString ::~MyString(){
	delete []str;	// �ͷ��ַ����ռ�
}

// ����ַ�������
int MyString ::size(){
	return n;
}

// ��С�ַ�����������
void MyString ::ensureMinCap(const int cap){
	// ����ǰ��������ʱ����������
	if(Capacity < cap){
		char *nstr = new char[cap];		// �����㹻���¿ռ�
		memset(nstr + Capacity, 0, cap - Capacity);	// ���¿ռ�ĸ�λ���ֳ�ʼ��Ϊ0
		memcpy(nstr, str, Capacity);	// ����ԭ�ַ�������
		delete []str;		// �ͷ�ԭ�ַ����ռ�
		str = nstr;		// �����ַ�����Ϣ
		Capacity = cap;
	}
}

// ���ַ���ĩβ����һ���ַ�
void MyString ::append(const char ch){
	ensureMinCap(n+1);	// ������С�ַ�������
	str[n++] = ch;		// ���ַ���ĩβ����µ��ַ�
}

// ��һָ��λ�ÿ�ʼ�Ӵ�����
int MyString ::find(const MyString& s, const int k){
	int i, j, p, f, sn;

	sn = s.n;
	// ��ָ����kλ��ʼ�����Ӵ�
	for(p = k; p <= n - sn; p++){
		f = 1;
		// ���Ӵ��е��ַ���ĸ������Ƚ�
		for(i = p, j = 0; (i < n) && (j < sn); i++, j++)
			if(str[i] != s[j]){
				f = 0;
				break;
			}
		if(f) return p;		// �ҵ��󣬷����Ӵ���ĸ���е���ʼλ��
	}
	return n;	// δ�ҵ��������ַ�������
}

/*
* �ַ����Ƚ�
* С����-1����ͬ����0���󷵻�1
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

// ���C����ַ���
char *MyString ::CStyle(){
	char *s;
	int i;

	s = new char[n+1];	// ����C����ַ����ռ�
	// ���������ֵ
	for(i = 0; i < n; i++)
		s[i] = str[i];
	s[n] = 0;	// ���һλ��Ϊ0
	return s;	// �������׵�ַ
}

// ��ֵ�±����
char& MyString ::operator [](const int k){
	return str[k];
}

// ��ֵ�±����
const char& MyString ::operator [](const int k) const{
	return str[k];
}

// ��ֵ����
MyString& MyString ::operator =(const MyString& s){
	ensureMinCap(s.n);	// ������С�ַ�������
	memcpy(str, s.str, s.n);	// �����ַ�������
	n = s.n;	// �����ַ�������
	return *this;
}

// �ַ�������
istream& operator >> (istream& is, MyString& s){
	int ch;
	
	s.n = 0;		// ��ʼ���ַ�������
	// ����white space
	do{
		ch = is.get();
		if(ch == EOF)return is;		// �������Ѷ��꣬�򷵻�
	}while(ch == ' ' || ch == '\t' || ch == '\n');
	// �����ַ�����ֱ������white space���������
	do{
		s.append(ch);
		ch = is.get();
	}while(ch != ' ' && ch != '\t' && ch != '\n' && ch != EOF);
	return is;
}

// �ַ������
ostream& operator << (ostream& os, const MyString& s){
	int i;

	// ���ν��ַ����и��ַ����
	for(i = 0; i < s.n; i++)
		os << s.str[i];
	return os;
}