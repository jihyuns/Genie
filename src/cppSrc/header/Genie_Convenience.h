#ifndef __GENIE_CONVENIENCE__
#define __GENIE_CONVENIENCE__

#include "../header/Libcurl_Wrapper.h"
#include <iostream>
#include <string>

namespace Genie_Convenience
{
	/*	...
		if you want add on
	*/
}

class Genie_Convenience
{
private:
	string key;
	string busStopId;
	string url;
	Libcurl_Wrapper* gCurl;
	Genie_Convenience(){
		key = ;
		busStopId = ;
		url = ;
		gCurl = new Libcurl_Wrapper();
		/*
		*
		*	key is secret
		*	Edit by DongDongJu
		*/
	};
	public:
	string getBusData(string url);
	string addKeyBusStopIdToURL();
	/*	...
		if you want add on
	*/	
};

#endif