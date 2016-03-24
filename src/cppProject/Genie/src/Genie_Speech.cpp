#include <iostream>
#include <cstring>
#include "../header/Genie_Speech.h"
// 03.24 by cho
// tts
#include <sapi.h>
#include <atlconv.h>
using namespace std;


/*
	add on

	ex)
	
	void Genie_Genie_Speech::Init()
	{
	
	}
*/

// 03.24 by cho
std::wstring Genie_Speech::stws(const std::string& _src) {
	USES_CONVERSION;
	return std::wstring(A2W(_src.c_str()));
}

//usage  text_to_speech("¾È³ç");
//or std::string a = "¾È³ç";  text_to_speech(a);
int Genie_Speech::text_to_speech(const std::string text) {
	std::wstring Ltext = stws(text.c_str());

	ISpVoice * pVoice = NULL;
	if (FAILED(::CoInitialize(NULL)))		return FALSE;
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	if (SUCCEEDED(hr))	{
		LPCWSTR str = Ltext.c_str();
		hr = pVoice->Speak(Ltext.c_str(), 0, NULL);//SPF_IS_XML
		pVoice->Release();
		pVoice = NULL;
	}
	else {
		return -1;
	}
	::CoUninitialize();
	return 1;
}