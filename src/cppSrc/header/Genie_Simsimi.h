#ifndef __GENIE_SIMSIMI__
#define __GENIE_SIMSIMI__

#include "../header/Libcurl_Wrapper.h"
#include <iostream>
#include <string>
#include <WTypes.h >
#include <oleauto.h>

namespace Genie_Simsimi
{
	/*	...
	if you want add on
	*/
}

class Genie_Simsimi
{
private:
	string key;
	string url;
	Libcurl_Wrapper* gCurl;
	Genie_Simsimi(string _key) {
		key = _key;
		url = "";
		gCurl = new Libcurl_Wrapper();
		/*
		*
		*	key is secret
		*	Edit by DongDongJu
		*/
	};

	char* UTF8ToANSI(const char *pszCode);
	char* ANSIToUTF8(const char * pszCode);
	string tokenizer(string source, string type);
public:
	string getResultData(string data);
	void addKeyToURL();
	/*	...
	if you want add on
	*/
};

#endif