#include "miniSQL.h"
#include"TKey.h"

TKey::TKey(int i){
	iKey = i;
	type = TYPE_INT;
}

TKey::TKey(float f){
	fKey = f;
	type = TYPE_FLOAT;
}

TKey::TKey(string s){
	sKey = s;
	type = TYPE_CHARS;
}

TKey::TKey(char *data, char t){
	type = t;
	switch (type){
	case TYPE_CHARS:
		sKey = string(data);
		break;
	case TYPE_FLOAT:
		fKey = *(float *)data;
		break;
	case TYPE_INT:
		iKey = *(int *)data;
		break;
	}
}

TKey::~TKey(){}

bool TKey::operator==(const TKey &b){
	if(type != b.type)
		return false;
	switch (type){
	case TYPE_CHARS:
		return sKey == b.sKey;
	case TYPE_FLOAT:
		return fKey == b.fKey;
	case TYPE_INT:
		return iKey == b.iKey;
	}
	return false;
}

bool TKey::operator!=(const TKey &b){
	if(type != b.type)
		return false;
	switch (type){
	case TYPE_CHARS:
		return sKey != b.sKey;
	case TYPE_FLOAT:
		return fKey != b.fKey;
	case TYPE_INT:
		return iKey != b.iKey;
	}
	return false;
}

bool TKey::operator<(const TKey &b){
	if(type != b.type)
		return false;
	switch (type){
	case TYPE_CHARS:
		return sKey < b.sKey;
	case TYPE_FLOAT:
		return fKey < b.fKey;
	case TYPE_INT:
		return iKey < b.iKey;
	}
	return false;
}

bool TKey::operator<=(const TKey &b){
	if(type != b.type)
		return false;
	switch (type){
	case TYPE_CHARS:
		return sKey <= b.sKey;
	case TYPE_FLOAT:
		return fKey <= b.fKey;
	case TYPE_INT:
		return iKey <= b.iKey;
	}
	return false;
}

bool TKey::operator>(const TKey &b){
	if(type != b.type)
		return false;
	switch (type){
	case TYPE_CHARS:
		return sKey > b.sKey;
	case TYPE_FLOAT:
		return fKey > b.fKey;
	case TYPE_INT:
		return iKey > b.iKey;
	}
	return false;
}

bool TKey::operator>=(const TKey &b){
	if(type != b.type)
		return false;
	switch (type){
	case TYPE_CHARS:
		return sKey >= b.sKey;
	case TYPE_FLOAT:
		return fKey >= b.fKey;
	case TYPE_INT:
		return iKey >= b.iKey;
	}
	return false;
}

const char *TKey::toData(){
	switch (type){
	case TYPE_CHARS:
		return sKey.c_str();
	case TYPE_FLOAT:
		return (char *)&fKey;
	case TYPE_INT:
		return (char *)&iKey;
	}
}

ostream &operator<<(ostream &out, const TKey &key){
	switch (key.type){
	case TYPE_CHARS:
		out << key.sKey;
		break;
	case TYPE_FLOAT:
		out << key.fKey;
		break;
	case TYPE_INT:
		out << key.iKey;
		break;
	}
	return out;
}