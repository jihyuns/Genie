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
	string busId;
	Libcurl_Wrapper* gCurl;
	Genie_Convenience(){
		key = ;
		busId = ;
		gCurl = new Libcurl_Wrapper();
		/*
		*
		*	key is secret
		*	Edit by DongDongJu
		*/
	};
	/*	...
		if you want add on
	*/
	public:
	string getBusData(string url);
	/*	...
		if you want add on
	*/	
};

#endif