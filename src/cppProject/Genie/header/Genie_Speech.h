#ifndef __GENIE_SPEECH__
#define __GENIE_SPEECH__




class Genie_Speech
{
	private:
	/*	...
		if you want add on
	*/
		// 03.24 by cho
		std::wstring stws(const std::string& _src);
		
	public:
	/*	...
		if you want add on
	*/	
		// 03.24 by cho
		int text_to_speech(const std::string text);
};

#endif