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
	/*�ڵ������湦��ǰ���ȵ��ô˺�����ʼ���ڴ棡*/
	void initialize(void);
	/*�˹����ṩ������������ṩһ��Ψһ�ĸ���id�������ݿ�*/
	int generateNewTrackId(std::string track_name);
	/*�˹����ṩ����ѯ�ǻ�ø���id��Ӧ�ĸ�����Ϣ
	����NULL ���û���ҵ�*/
	std::string getTrackInfo(int tack_id);
	/*ÿ��ʹ����֮����������º���������ͬ�����ļ���*/
	bool dumpTrackInfo();

	~TrackInfo(void);
};

