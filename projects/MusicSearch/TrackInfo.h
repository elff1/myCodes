/************************************************************************/
/* Author: DJ
** Class Name: TrackInfo
** Used for: record track info
*/
/************************************************************************/

#pragma once
#include <map>
#include <string>
class TrackInfo
{
	int max_id;
	bool isInitialized;
	std::map<int, std::string> info_map;
	
public:
	TrackInfo(void);
	/*在调用下面功能前请先调用此函数初始化内存！*/
	void initialize(void);
	/*此功能提供给歌曲入库是提供一个唯一的歌曲id存入数据库*/
	int generateNewTrackId(std::string track_name);
	/*此功能提供给查询是获得歌曲id对应的歌曲信息
	返回NULL 如果没有找到*/
	std::string getTrackInfo(int tack_id);
	/*每次使用完之后请调用以下函数将内容同步回文件！*/
	bool dumpTrackInfo();

	~TrackInfo(void);
};

