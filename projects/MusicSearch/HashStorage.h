#ifndef _HASHSTORAGE_H_
#define _HASHSTORAGE_H_

#include <vector>

typedef int Key;
typedef struct value_node{
	int trackID;
	float leftTime;
}Value;

typedef struct reco_node{
	Key key;
	Value val;
}SimReco;

class HashStorage{
private:
	std::vector<Value>* values;
	std::vector<SimReco> inserted;
	int capacity;
	char* filename;
public:
	HashStorage();
	HashStorage(int cap, char* fname);
	~HashStorage();
	int dump();
	int load();
	int count(Key key);
	bool insert(SimReco record, bool isBuild);
	void clear();
	std::vector<Value>& operator[](Key key);
};

#endif
