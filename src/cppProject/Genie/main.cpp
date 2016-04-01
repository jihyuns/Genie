#include <iostream>
#include "header\Genie_Speech.h"

int main(void)
{
	/*
	sample code
	input - simsimi - tts
	*/
	//AIzaSyBB9IBGzHMyO4PJaRdAcFNZY5zaeRjEqbM

	Genie_Speech a;
	//a.setUrl_stt("<key>");
	string c = a.getResult_stt(3);

	cout << c << endl;

	//a.setUrl_simsimi("<key>");
	string b = a.getResult_simsimi(c);

	cout << "Result : " << b << endl;
	a.textToSpeech(b);
	return 0;
}