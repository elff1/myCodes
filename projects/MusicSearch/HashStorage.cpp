#include "HashStorage.h"
#include <iostream>
#include <stdio.h>
using namespace std;
HashStorage::HashStorage(int cap, char*fname){
	
	capacity = cap;
	filename = fname;
	cout<<sizeof(std::vector<Value>)<<endl;
	cout<<capacity<<endl;
	values = new std::vector<Value>[capacity];
}

HashStorage::HashStorage(){
	capacity = 1<<21;
	filename = "data";
	values = new std::vector<Value>[capacity];

}

HashStorage::~HashStorage(){
	clear();
	delete[] values;
}

bool HashStorage::insert(SimReco record, bool isBuild){

	if(record.key<0 || record.key>=capacity){
		return false;
	}

	values[record.key].push_back(record.val);
	if(!isBuild){
		inserted.push_back(record);		
	}
	return true;
}

int HashStorage::load(){
	FILE* fp = NULL;
	fp = fopen(filename, "rb+");
	
	if(fp == NULL){
		return -1;
	} 
	int block_size = sizeof(SimReco);
	SimReco data_block;
	int cnt = 0;

	while(!feof(fp)){
		int flag = fread(&data_block, block_size, 1, fp);

		if(flag < 1) break;
		//printf("sto:::%d %f %d\n",data_block.key, data_block.val.leftTime,data_block.val.trackID);
		if(insert(data_block, true)){
			
			cnt++;
		}
		else{
			continue;
		}
		
	} 
	fclose(fp);
	return cnt;
}

int HashStorage::dump(){
	FILE* fp = NULL;
	fp = fopen(filename, "ab+");
	
	if(fp == NULL){
		return -1;
	}
	
	if(inserted.empty()){
		return 0;
	}
	
	int cnt = 0;
	int block_size = sizeof(SimReco);
 
	std::vector<SimReco>::iterator iter;
	for(iter = inserted.begin(); iter!=inserted.end(); iter++){
		SimReco data_block = *iter;
		if(fwrite(&data_block, block_size, 1, fp)){
		 
			cnt++;
		}
		else{
			continue;
		}
	}
 
	inserted.clear();
 
	return cnt;
}

std::vector<Value>& HashStorage::operator[](Key key){
	return values[key];
}

int HashStorage::count(Key key){
	return values[key].size();
}

void HashStorage::clear(){
	for(int i=0; i<capacity; i++){
		values[i].clear();
	}
}
