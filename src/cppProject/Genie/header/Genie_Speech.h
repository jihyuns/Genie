#ifndef __GENIE_SPEECH__
#define __GENIE_SPEECH__
#include "Libcurl_Wrapper.h"



class Genie_Speech
{
	private:
	/*	...
		if you want add on
	*/
		// 03.24 by cho
		//tts
		std::wstring stws(const std::string& _src);
		//simsimi
		std::string key;
		std::string url;
		Libcurl_Wrapper *gCurl;

		char* UTF8ToANSI(const char *pszCode);
		char* ANSIToUTF8(const char *pszCode);
		std::string tokenzierInResult(std::string source, std::string type);
	public:
	/*	...
		if you want add on
	*/	
		// 03.24 by cho
		int textToSpeech(const std::string text);
		//simsimi
		void setUrl(const std::string key);
		string getResult(const std::string data);

		Genie_Speech();
};

#endif