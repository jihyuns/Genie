#define _CRT_SECURE_NO_WARNINGS
#include "../header/Genie_Speech.h"
#define _key_stt_ "<key>"
#define _key_simsimi_ "<key>"


// 03.24 by cho
Genie_Speech::Genie_Speech() {
	//gCurl = new Libcurl_Wrapper();
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
	if (SUCCEEDED(hr)) {
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

//void Genie_Speech::setUrl_simsimi(const std::string _key) {
//	simsimi.setUrl(_key);
//}

std::string Genie_Speech::getResult_simsimi(const std::string _text) {
	return simsimi.getResult(_text.c_str());
}

//void Genie_Speech::setUrl_stt(const std::string _key) {
//	stt.setUrl(_key);
//}

std::string Genie_Speech::getResult_stt(const int time) {
	return stt.getResult(time);
}

std::string Genie_Speech::Simsimi::tokenzierInResult(std::string source, std::string type) {
	if (type == "id")		return NULL;

	int first_tokenizer_index = source.find(type);

	int add_num;
	string charater;

	if (type == "result") {
		add_num = 9;		charater = ",";
	}
	else if (type == "response") {
		add_num = 12;		charater = "\"";
	}
	string temp = source.substr(first_tokenizer_index + add_num);
	int second_tokenizer_index = temp.find(charater);// find "
	return temp.substr(0, second_tokenizer_index);
}

//http://www.devpia.com/MAEUL/Contents/Detail.aspx?BoardID=50&MAEULNo=20&no=697699&ref=697692
std::string Genie_Speech::Simsimi::eraseSpecialCharter(std::string data) {
	std::string result;
	for (int i = 0; i < data.size(); i++) {
		if (((data[i] & 0x80) == 0x80))
			result += data[i];
		else if (data[i] == ' ')
			result += data[i];
		else if (((data[i] >= 0x41) && (data[i] <= 0x5A)) || ((data[i] >= 0x61) && (data[i] <= 0x7A)))
			result += data[i];
		else if ((data[i] >= 0xA1) && (data[i + 1] >= 0xA1))
			continue;
		else
			continue;
	}
	return result;
}

void Genie_Speech::Simsimi::setUrl(const std::string _key) {
	url += "http://sandbox.api.simsimi.com/request.p?key=";
	url += _key;
	url += "&lc=ko&ft=1.0&text=";
}

std::string Genie_Speech::Simsimi::getResult(const std::string data) {
	char *utf8 = Genie_Speech::ANSIToUTF8(data.c_str());
	char *escape_str = gCurl->getescape(utf8, strlen(utf8));//curl_easy_escape(curl, ANSIToUTF8(data.c_str()), strlen(data.c_str()) + 2);
	url += escape_str;

	string result_data = gCurl->get(url);
	char *result_data_ansi = Genie_Speech::UTF8ToANSI(result_data.c_str());

	//debug
	cout << result_data_ansi << endl;

	string result_code = tokenzierInResult(string(result_data_ansi), "result");
	cout << "print result" << endl;
	cout << result_code << endl;
	if (result_code == "100") {// ok
		return eraseSpecialCharter(tokenzierInResult(string(result_data_ansi), "response"));
	}

	return NULL;
}

Genie_Speech::Simsimi::Simsimi() {
	gCurl = new Libcurl_Wrapper();
	setUrl(_key_simsimi_);
}


int Genie_Speech::STT::make_wave_file(const int time = 3) {
	ALint			iSamplesAvailable;
	FILE			*pFile;
	ALchar			Buffer[BUFFERSIZE];
	WAVEHEADER		sWaveHeader;
	ALint			iDataSize = 0;
	ALint			iSize;
	ALint sample;

	clock_t begin, end;
	begin = clock();

	//ALFWInit();

	alGetError();
	ALCdevice *device = alcCaptureOpenDevice(NULL, SRATE, AL_FORMAT_MONO16, BUFFERSIZE);
	if (alGetError() != AL_NO_ERROR) {
		return 0;
	}

	// Create / open a file for the captured data
	pFile = fopen(OUTPUT_WAVE_FILE, "wb");

	// Prepare a WAVE file header for the captured data
	sprintf(sWaveHeader.szRIFF, "RIFF");
	sWaveHeader.lRIFFSize = 0;
	sprintf(sWaveHeader.szWave, "WAVE");
	sprintf(sWaveHeader.szFmt, "fmt ");
	sWaveHeader.lFmtSize = sizeof(WAVEFORMATEX);
	sWaveHeader.wfex.nChannels = 1;
	sWaveHeader.wfex.wBitsPerSample = 16;
	sWaveHeader.wfex.wFormatTag = WAVE_FORMAT_PCM;
	sWaveHeader.wfex.nSamplesPerSec = SRATE;
	sWaveHeader.wfex.nBlockAlign = sWaveHeader.wfex.nChannels * sWaveHeader.wfex.wBitsPerSample / 8;
	sWaveHeader.wfex.nAvgBytesPerSec = sWaveHeader.wfex.nSamplesPerSec * sWaveHeader.wfex.nBlockAlign;
	sWaveHeader.wfex.cbSize = 0;
	sprintf(sWaveHeader.szData, "data");
	sWaveHeader.lDataSize = 0;

	fwrite(&sWaveHeader, sizeof(WAVEHEADER), 1, pFile);

	alcCaptureStart(device);

	while (true) {
		alcGetIntegerv(device, ALC_CAPTURE_SAMPLES, 1, &iSamplesAvailable);

		if (iSamplesAvailable > (BUFFERSIZE / sWaveHeader.wfex.nBlockAlign))
		{
			// Consume Samples
			alcCaptureSamples(device, Buffer, BUFFERSIZE / sWaveHeader.wfex.nBlockAlign);

			// Write the audio data to a file
			fwrite(Buffer, BUFFERSIZE, 1, pFile);

			// Record total amount of data recorded
			iDataSize += BUFFERSIZE;
		}

		if ((clock() - begin) / 1000 > time)
			break;
		// ... do something with the buffer 

	}

	alcCaptureStop(device);

	alcGetIntegerv(device, ALC_CAPTURE_SAMPLES, 1, &iSamplesAvailable);
	while (iSamplesAvailable)
	{
		if (iSamplesAvailable > (BUFFERSIZE / sWaveHeader.wfex.nBlockAlign))
		{
			alcCaptureSamples(device, Buffer, BUFFERSIZE / sWaveHeader.wfex.nBlockAlign);
			fwrite(Buffer, BUFFERSIZE, 1, pFile);
			iSamplesAvailable -= (BUFFERSIZE / sWaveHeader.wfex.nBlockAlign);
			iDataSize += BUFFERSIZE;
		}
		else
		{
			alcCaptureSamples(device, Buffer, iSamplesAvailable);
			fwrite(Buffer, iSamplesAvailable * sWaveHeader.wfex.nBlockAlign, 1, pFile);
			iDataSize += iSamplesAvailable * sWaveHeader.wfex.nBlockAlign;
			iSamplesAvailable = 0;
		}
	}

	// Fill in Size information in Wave Header
	fseek(pFile, 4, SEEK_SET);
	iSize = iDataSize + sizeof(WAVEHEADER) - 8;
	fwrite(&iSize, 4, 1, pFile);
	fseek(pFile, 42, SEEK_SET);
	fwrite(&iDataSize, 4, 1, pFile);

	fclose(pFile);

	alcCaptureCloseDevice(device);

	return 0;
}

std::string Genie_Speech::STT::jsonToData(char* _json) {//const std::string _json) {
	if (strcmp(_json, "{\"result\":[]}\n")) {
		Document document;
		document.Parse(&_json[14]);

		const Value& a = document["result"];
		const Value& b = a[0]["alternative"];
		const Value& c = b[0]["transcript"];
		return c.GetString();
	}
	return "";
}
//https://www.google.com/speech-api/v2/recognize?output=json&lang=ko-KR&key=AIzaSyBB9IBGzHMyO4PJaRdAcFNZY5zaeRjEqbM&client=chromium
void Genie_Speech::STT::setUrl(const std::string _key) {
	url += "www.google.com/speech-api/v2/recognize?output=json&lang=ko-KR&key=";
	url += _key;
	url += "&client=chromium";
}

std::string Genie_Speech::STT::getResult(const int time) {
	make_wave_file(time);

	std::string _data = gCurl->get_stt(url, OUTPUT_WAVE_FILE);

	char *ansi = UTF8ToANSI(_data.c_str());

	string result = jsonToData(ansi);

	return result;
}

Genie_Speech::STT::STT() {
	gCurl = new Libcurl_Wrapper();
	setUrl(_key_stt_);
}