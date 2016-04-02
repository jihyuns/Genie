#include <iostream>
#include <cstring>
#include "../header/Genie_Datamanagement.h"
using namespace std;


/*
	add on

	ex)
	
	void Genie_Genie_Datamanagement::Init()
	{
	
	}
*/

//by cho 04.02
int Genie_Datamanagement::getFriendly() {
	return friendly;
}

void Genie_Datamanagement::setFriendly(const int num) {
	friendly = num;
}

void Genie_Datamanagement::upFriendly(const int num = 1) {
	firendly += num;
}

void Genie_Datamanagement::downFriendly(const int num = 1) {
	friendly -= num;
}