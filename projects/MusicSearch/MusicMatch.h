#include<iostream>
#include<map>
#include<algorithm>
#include<vector>
#include"DBClient.h"
#include"FastFourier.h"
#include<algorithm>
#include "TrackInfo.h"
#include <list>
#define MAX_VALUE_COLUMN 500
#define SHOW_NUM 30
#define HASH_CAPACITY (2<<21)
#define TARGET_ZONE 100

using namespace std;
class MusicMatch{
	private:
		sound_sequence* fingerprint; 
		string filename;
		int * value_size;
		DBClient *dbclient;
		TrackInfo info;
		FastFourier *ffw;
		int size;
		bool addToResult(string* res, int* number, std::string name);
public:
		MusicMatch();
		~MusicMatch();
		//first init it!
		void initialize();
		//init() get the value_size and initialize the value_list
		bool match(string filename, string *result, int* res_num);
		bool insert(string filename, string track_name);	
};