/************************************************************************/
/* Author: DJ
** Class Name: TrackInfo
** Used for: record track info
*/
/************************************************************************/

#include "TrackInfo.h"
#include <string>
#include <iostream>
#define FILE_NAME  "track_info.dat"
using namespace std;
TrackInfo::TrackInfo(void)
{

	max_id = -1;
	isInitialized =false;
}



void TrackInfo::initialize(void)
{
	int temp_id;
	char temp_name[256];
	FILE* fp = fopen(FILE_NAME, "r");
	if (fp==NULL)
	{
		max_id = -1;
		return;
	}
	fscanf(fp, "%d", &max_id);
 
	for (int i= 0;i<=max_id;i++)
	{
		fscanf(fp, "%d ", &temp_id); 
		fgets(temp_name,256,fp);
	 
		info_map.insert(pair<int, string>(temp_id, temp_name));
	}
		 
	fclose(fp);
	isInitialized =true;
}

int TrackInfo::generateNewTrackId(string trackName)
{
	max_id ++;
	info_map.insert(pair<int, string>(max_id, trackName));
	return max_id;
}

string TrackInfo::getTrackInfo( int tack_id )
{
	map<int,string>::iterator it;
	it = info_map.find(tack_id);
	if (it==info_map.end())
	{
		return "No info";
	}
	else
	{
		return it->second;
	}
}

bool TrackInfo::dumpTrackInfo()
{
	FILE *file = fopen(FILE_NAME, "w");
	char name[256];
	if (file==NULL)
	{
		return false;
	}
	fprintf(file,"%d\n",max_id );
	map<int, string>::iterator iter = info_map.begin();
	for (;iter!=info_map.end(); ++iter)
	{
		//name = iter->second;
		fprintf(file, "%d %s",iter->first, iter->second.c_str());
		fprintf(file,"\n");		fprintf(file,"\n");
	}
	fclose(file);
	return true;
}

TrackInfo::~TrackInfo(void)
{
}