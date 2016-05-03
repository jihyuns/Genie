#ifndef __GENIE_FRIENDLY__
#define __GENIE_FRIENDLY__
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

class Genie_Friendly
{

private:
	double friendly;
public:
	Genie_Friendly(){
		friendly=0;
		last_check_time =0;
		curr_time =0;
		refreshTime(last_check_time);
	};
	void refreshTime(time_t& timeI);
	void KoreanStemmingFunc(string input);
	void split(string &input , char delim);
	void checkFriendly(int EmotionNum,int MemoryNum);
	void calculateFriendly(int val);
	time_t getLastTime();
	time_t getCurrTime();
	int usedCheck(int EmotionNum, int MemoryNum);	
	void upFriendly(int val);
	void printFriendly();
public: 

	// if test done then these values  will change private

	vector<string> inputSet;
	time_t last_check_time;
	time_t curr_time;
};

#endif
