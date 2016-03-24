#include <iostream>
#include "header\Genie_Speech.h"
int main(void)
{
	/*
		sample code 
		input - simsimi - tts
	*/
	Genie_Speech a;
	a.setUrl("a09e07c8-2351-4433-b812-9c8b03e7ddfc");
	string b = a.getResult("¾È³ç");

	cout << "Result : " << b << endl;
	a.textToSpeech(b);
	return 0;
}