#ifndef __GENIE_SPEECH__
#define __GENIE_SPEECH__
#include "Libcurl_Wrapper.h"

#include <iostream>
#include <cstring>
// 03.24 by cho
// tts
#include <sapi.h>
#include <atlconv.h>
//simsimi
#include <string>
#include <WTypes.h >
#include <oleauto.h>
//record
#include <al.h>
#include <alc.h>
#include <time.h>
#include "../lib/record/Framework.h"
//json
//https://github.com/miloyip/rapidjson
#include "../lib/rapidjson/document.h"

using namespace rapidjson;
using namespace std;

class Genie_Speech
{
private:
	/*	...
	if you want add on
	*/
	// 03.24 by chos
	//tts
	//string to wstring
	std::wstring stws(const std::string& _src);

	//change encoding
	static char* UTF8ToANSI(const char *pszCode);
	static char* ANSIToUTF8(const char *pszCode);

	//03.31 by cho
	class Simsimi {
	private:
		//simsimi
		std::string key;
		std::string url;
		Libcurl_Wrapper *gCurl;

		std::string tokenzierInResult(std::string source, std::string type);
		std::string eraseSpecialCharter(std::string data);

		void setUrl(const std::string key);
	public:
		//simsimi

		string getResult(const std::string data);
		Simsimi();
	}simsimi;

	class STT {
	private:
		std::string key;
		std::string url;
		Libcurl_Wrapper *gCurl;

		//setting for record
		const int SRATE = 16000;
		const int SSIZE = 1024;

#define	OUTPUT_WAVE_FILE		"record.wav"
#define BUFFERSIZE				4410
#pragma pack (push,1)

		typedef struct
		{
			char			szRIFF[4];
			long			lRIFFSize;
			char			szWave[4];
			char			szFmt[4];
			long			lFmtSize;
			WAVEFORMATEX	wfex;
			char			szData[4];
			long			lDataSize;
		} WAVEHEADER;
#pragma pack (pop)

		int record_time;
		int make_wave_file(const int time);
		std::string jsonToData(char*);//const std::string _json);
		void setUrl(const std::string _key);

	public:
		string getResult(const int time);
		STT();
	}stt;
public:
	/*	...
	if you want add on
	*/
	// 03.24 by cho
	int textToSpeech(const std::string text);

	//03.31 by cho
	//void setUrl_simsimi(const std::string _key);
	std::string getResult_simsimi(const std::string _text);

	//void setUrl_stt(const std::string _key);
	std::string getResult_stt(const int time);

	Genie_Speech();
};

#endif