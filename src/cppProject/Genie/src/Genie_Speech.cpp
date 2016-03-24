#include <iostream>
#include <cstring>
#include "../header/Genie_Speech.h"
// 03.24 by cho
// tts
#include <sapi.h>
#include <atlconv.h>
//simsimi
#include <string>
#include <WTypes.h >
#include <oleauto.h>
using namespace std;


/*
	add on

	ex)
	
	void Genie_Genie_Speech::Init()
	{
	
	}
*/

// 03.24 by cho
Genie_Speech::Genie_Speech() {
	gCurl = new Libcurl_Wrapper();
}

std::wstring Genie_Speech::stws(const std::string& _src) {
	USES_CONVERSION;
	return std::wstring(A2W(_src.c_str()));
}

//usage  text_to_speech("¾È³ç");
//or std::string a = "¾È³ç";  text_to_speech(a);
int Genie_Speech::textToSpeech(const std::string text) {
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

char* Genie_Speech::UTF8ToANSI(const char *pszCode) {
	BSTR    bstrWide;
	char*   pszAnsi;
	int     nLength;
	// Get nLength of the Wide Char buffer
	nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, lstrlen(pszCode) + 1,
		NULL, NULL);
	bstrWide = SysAllocStringLen(NULL, nLength);
	// Change UTF-8 to Unicode (UTF-16)
	MultiByteToWideChar(CP_UTF8, 0, pszCode, lstrlen(pszCode) + 1, bstrWide,
		nLength);
	// Get nLength of the multi byte buffer 
	nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
	pszAnsi = new char[nLength];
	// Change from unicode to mult byte
	WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
	SysFreeString(bstrWide);
	return pszAnsi;
}

char* Genie_Speech::ANSIToUTF8(const char *pszCode) {
	int		nLength, nLength2;
	BSTR	bstrCode;
	char*	pszUTFCode = NULL;

	nLength = MultiByteToWideChar(CP_ACP, 0, pszCode, lstrlen(pszCode), NULL, NULL);
	bstrCode = SysAllocStringLen(NULL, nLength);
	MultiByteToWideChar(CP_ACP, 0, pszCode, lstrlen(pszCode), bstrCode, nLength);

	nLength2 = WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, pszUTFCode, 0, NULL, NULL);
	pszUTFCode = (char*)malloc(nLength2 + 1);
	WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, pszUTFCode, nLength2, NULL, NULL);

	return pszUTFCode;
}

std::string Genie_Speech::tokenzierInResult(std::string source, std::string type) {
	if (type == "id")		return NULL;

	int first_tokenizer_index = source.find(type);

	int add_num;
	string charater;

	if (type == "result"){
		add_num = 9;		charater = ",";
	}
	else if (type == "response") {
		add_num = 12;		charater = "\"";
	}
	string temp = source.substr(first_tokenizer_index + add_num);
	int second_tokenizer_index = temp.find(charater);// find "
	return temp.substr(0, second_tokenizer_index);
}

void Genie_Speech::setUrl(const std::string _key) {
	url += "http://sandbox.api.simsimi.com/request.p?key=";
	url += _key;
	url += "&lc=ko&ft=1.0&text=";
}

std::string Genie_Speech::getResult(const std::string data) {
	char *utf8 = ANSIToUTF8(data.c_str());
	char *escape_str = gCurl->getescape(utf8, strlen(utf8));//curl_easy_escape(curl, ANSIToUTF8(data.c_str()), strlen(data.c_str()) + 2);
	url += escape_str;

	string result_data = gCurl->get(url);
	char *result_data_ansi = UTF8ToANSI(result_data.c_str());

	//debug
	cout << result_data_ansi << endl;

	string result_code = tokenzierInResult(string(result_data_ansi), "result");
	cout << "print result" << endl;
	cout << result_code << endl;
	if (result_code == "100") {// ok
		return tokenzierInResult(string(result_data_ansi), "response");
	}

	return NULL;
}