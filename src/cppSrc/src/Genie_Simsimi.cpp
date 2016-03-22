#include "../header/Genie_Simsimi.h"
#include "../header/Libcurl_Wrapper.h"
#include <iostream>
#include <cstring>
using namespace std;


/*
add on

ex)

void Genie_Genie_Convenience::Init()
{

}
*/


/*
*
*	func get xml response for bus
*
*	Edit by DongDongJu
*/
string Genie_Convenience::getBusData(string url) {
	return this.gCurl->get(url);
}

string Genie_Convenience::addKeyBusStopIdToURL() {
	this.url->append("?key=");
	this.url->append(this.key);
	this.url->append("?BusRouteId="); // need change 
	this.url->append(this.busStopId);
	return this.url;
};

char* Genie_Simsimi::UTF8ToANSI(const char *pszCode) {
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
char* Genie_Simsimi::ANSIToUTF8(const char * pszCode){
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
string Genie_Simsimi::tokenizer(string source, string type) {
	if (type == "id")		return NULL;

	int first_tokenizer_index = source.find(type);

	int add_num;
	string charater;

	if (type == "result") 
		add_num = 9;		charater = ",";
	}
	else if (type == "response") {
		add_num = 12;		charater = "\"";
	}
	string temp = source.substr(first_tokenizer_index + add_num);
	int second_tokenizer_index = temp.find(charater);// find "
	return temp.substr(0, second_tokenizer_index);
}
string Genie_Simsimi::getResultData(string data) {
	string _url = url;
	char *escape_str = curl_easy_escape(curl, ANSIToUTF8(data.c_str()), strlen(data.c_str()) + 2);
	url += escape_str;

	string result_data = gCurl->get(url);
	char *result_data_ansi = UTF8ToANSI(result_data.c_str());

	string result_code = tokenizer(string(ansi), "result");
	cout << "print result" << endl;
	cout << result_code << endl;
	if (result_code == "100") {// ok
		return response = tokenizer(string(ansi), "response");
	}
	//else {// no
	//	return NULL;
	//}
	return NULL;
}
void Genie_Simsimi::addKeyToURL() {
	url += "http://sandbox.api.simsimi.com/request.p?key=";
	url += key;
	url += "&lc=ko&ft=1.0&text=";
}