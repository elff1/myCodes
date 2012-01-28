#include "MusicMatch.h"

//比较函数
bool value_comparer(map<int,int>::value_type &i1, map<int,int>::value_type &i2)
{
	return i1.second<i2.second;
}

//一个没什么用的构造函数
MusicMatch::MusicMatch(){ 
};

//一个没什么用的构造函数
MusicMatch::~MusicMatch(){ 
	delete []fingerprint; 
	delete []value_size;
	delete []dbclient;
	delete ffw;
};

void MusicMatch::initialize(){
	dbclient=new DBClient(HASH_CAPACITY,"MusicFingerPrint.db");
	dbclient->dbBuild();
	//构造FFT类完成转换工作
	ffw=new FastFourier();
	info.initialize();
}
bool MusicMatch::match(string filename, string* res, int *res_num){

	int size;
	int total_size;
	*res_num = 0;
	this->fingerprint=ffw->transform(filename,&total_size,&size);
	if (fingerprint==NULL)
	{
		return false ;
	} 

	//决定关联点选择区间
	int target_zone=TARGET_ZONE;
	int key_size=target_zone*size ;
	Key * keys=new Key[key_size];
	//values数组用于存放Value节点
	Value ** values = new Value *[key_size];
	//value_size用于放每个hash值对应value的个数
	value_size = new int[key_size];
	double now_fre1=0;
	double now_fre2=0;
	int num_count =0;
	int* distance_time = new int[key_size];
	int count=0;
	for(int i=0;i<size-1;i++){
		num_count=0;
		double freq1=fingerprint[i].frequance;
		for(int j=i+1;j<size&&j<=i+target_zone;j++){
			double freq2= fingerprint[j].frequance;
			double delta_time=fingerprint[j].time-fingerprint[i].time;
			if (num_count>6||abs(freq1-freq2)<10|| abs(freq1-freq2)>20|| 
				delta_time>1||delta_time<0.2||(freq1==now_fre1&&freq2==now_fre2))
			{
				continue;
			}
			num_count++;
			distance_time[count] = fingerprint[i].time;
			keys[count++]= freq1*20000+freq2*100 +delta_time*250; 
			now_fre2 = freq2; 
		}
		now_fre1 = freq1; 
	} 
	bool result=dbclient->dbQuery(keys,count,value_size,values); 

	delete[]keys;

	//查询结果计数
	map<int,int> counter; 
	if(result){
		for(int i=0;i<count;i++){ 
			for(int j=0;j<value_size[i];j++){
				//生成查询结果的map
				++counter[values[i][j].trackID*10000+abs(distance_time[i]-values[i][j].leftTime)]; 
			}
		} 
		map<int,int>::iterator iter; 
		map<int,int> result_map;  

		int cmp_num=0;
		int track_1=-1,track_2=-1,track_3=-1;
		int track1_num=0, track2_num=0,track3_num=0;
		for(int i=0;i<SHOW_NUM&&i<counter.size();++i){

			iter=max_element(counter.begin(), counter.end(),value_comparer);
			result_map[iter->first]= iter->second ;
			cout<<info.getTrackInfo(iter->first/10000)<<endl;
			cout<< iter->second <<endl;
			addToResult(res,res_num,info.getTrackInfo(iter->first/10000));
			 
				if (cmp_num==0)
				{
					track_1=iter->first/10000;
					track1_num = iter->second;
					++cmp_num;
				} else if (cmp_num==1)
				{
					track_2 = iter->first/10000;
					track2_num = iter->second;
					++cmp_num;
				} else if (cmp_num==2)
				{
					track_3 = iter->first/10000;
					track3_num = iter->second;

					++cmp_num;
				} 
			counter.erase(iter);
		} 
		if(track1_num>20){
			if (track1_num>track2_num*1.7)
			{
				(*res_num)=1;
			}else if((track_1==track_2)&&(track_1!=track_3)&&(track1_num>track3_num*1.3))
			{
				(*res_num)=1;
			}else if((track_1==track_2)&&(track_2==track_3)){
				(*res_num)=1;
			}
		}
		cout<<"num:::"<<endl;
		cout<<track1_num<<endl;
		cout<<track2_num<<endl;
		cout<<track3_num<<endl;
		cout<<track_1<<endl;
		cout<<track_2<<endl;
		cout<<track_3<<endl;
		cout<<"track1_num:"<<track1_num<<endl;
		cout<<"res_num:"<<*res_num<<endl;

		delete []values;
		return true;

	}
	delete []values;
	return false;
};

bool MusicMatch::insert(string filename, string track_name){
	//构造FFT类完成转换工作

	int size;
	int total_size; 
	int track_id = info.generateNewTrackId(track_name);
	info.dumpTrackInfo();
	printf("finish generate id...\n");
	this->fingerprint=ffw->transform(filename,&total_size,&size);
	cout<<"tag1"<<endl;
	if (fingerprint==NULL)
	{
		return false;
	}
	map<int,int> counter;   
	bool result=false;
	//决定关联点选择区间
	int target_zone=TARGET_ZONE;
	int key_size=(2*size-target_zone-1)*target_zone/2;
	SimReco *reco = new SimReco[key_size]; 
	double now_fre1=0;
	double now_fre2=0;
	int count=0;
	int num_count =0;
	for(int i=0;i<size-1;i++){
		double freq1=fingerprint[i].frequance;
		num_count = 0;
		for(int j=i+1;j<size&&j<=i+target_zone;j++){
			double freq2= fingerprint[j].frequance;
			double delta_time=fingerprint[j].time-fingerprint[i].time;
			if (num_count>6||abs(freq1-freq2)<10|| abs(freq1-freq2)>20|| delta_time>1||delta_time<0.2||(freq1==now_fre1&&freq2==now_fre2))
			{
				continue;
			}
			reco[count].key= freq1*20000+freq2*100 +delta_time*250;  
			reco[count].val.leftTime = fingerprint[i].time;
			reco[count++].val.trackID = track_id;
			now_fre2 = freq2;
			num_count++;
		}
		now_fre1 = freq1;
	} 
	cout<<"cout:"<<count<<endl;  
	dbclient->dbInsert(reco, count);  
	dbclient->dbSync(); 
	delete[]reco;
	return true;

};


bool MusicMatch::addToResult(string* res,int *number, std::string name) {
	if ((*number)>10)
	{
		return false;
	}
	for (int i=0;i<*number;i++)
	{
		if (std::strcmp(res[i].c_str(),name.c_str())==0)
		{
			return false;
		}
	}
	res[*number] = name;
	(*number)++;
	return true;
}