#include "../header/Genie_Convenience.h"
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
string Genie_Convenience::getBusData(string url){
	return this.gCurl->get(url);
}

string Genie_Convenience::addKeyBusStopIdToURL(){
	this.url->append("?key=");
	this.url->append(this.key);
	this.url->append("?BusRouteId="); // need change 
	this.url->append(this.busStopId);
	return this.url;
};