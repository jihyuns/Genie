#include "Genie_Friendly.h"


void Genie_Friendly::split(string &input , char delim)
{
	stringstream ss(input);
	string item;
	while(getline(ss,item,delim)){
		(this->inputSet).push_back(item);
	}
}
void Genie_Friendly::KoreanStemmingFunc(string input)
{
	split(input,' ');
}
void Genie_Friendly::refreshTime(time_t& timeI)
{
	timeI = time(NULL);
}
time_t Genie_Friendly::getLastTime()
{
	return this->last_check_time;
}
time_t Genie_Friendly::getCurrTime()
{
	return this->curr_time;
}
int Genie_Friendly::usedCheck(int EmotionNum, int MemoryNum)
{
	refreshTime(this->curr_time);	
	if((this->curr_time - this->last_check_time > 60*60*24)&& EmotionNum ==0 && MemoryNum == 0)
	{
		return 1;
	}
	else if((this->curr_time - this->last_check_time > 7*60*60*24))
		return 2;
	return 0;
}
void Genie_Friendly::calculateFriendly(int val)
{
	if(this->friendly >= 0 && this->friendly < 20 )
	{
		this->friendly += 1.2*val;
	}
	else if(this->friendly >= 21 && this->friendly < 40)
	{
		this->friendly += 1.1*val;
	}
	else if(this->friendly >= 41 && this->friendly < 60)
	{
		this->friendly += 0.8*val;
	}
	else if(this->friendly >= 61 && this->friendly < 80)
	{
		this->friendly += 0.4*val;
	}
	else if(this->friendly >= 81 && this->friendly < 100)
	{
		this->friendly += 0.2*val;
	}
	else if(this->friendly < 0)
	{
		this->friendly = 0;
	}
	else if(this->friendly > 100)
	{
		this->friendly = 100;
	}
}
void Genie_Friendly::printFriendly()
{
	cout<<this->friendly<<endl;
}
void Genie_Friendly::upFriendly(int val)
{
	calculateFriendly(val);
}
void Genie_Friendly::checkFriendly(int EmotionNum, int MemoryNum)
{
	if(usedCheck(EmotionNum, MemoryNum) == 1) // 하루동안 사용한적이 없을떄
		calculateFriendly(-3);
	else if(usedCheck(EmotionNum, MemoryNum) == 2) // 일주일 넘었을때
		calculateFriendly(-10);
}