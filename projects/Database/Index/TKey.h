#ifndef _TKey_H
#define _TKey_H

#include <iostream>
#include <string>

using namespace std;

class TKey{
	friend ostream &operator<<(ostream &, const TKey &);
public:
	int iKey;
	float fKey;
	string sKey;
	char type;

	TKey(){};
	TKey(int i);
	TKey(float f);
	TKey(string s);
	TKey(char *data, char t);
	~TKey();

	bool operator==(const TKey &);
	bool operator!=(const TKey &);
	bool operator>(const TKey &);
	bool operator>=(const TKey &);
	bool operator<(const TKey &);
	bool operator<=(const TKey &);

	const char *toData();
};

#endif // _TKey_H