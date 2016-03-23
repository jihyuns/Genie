#ifndef __GENIE_SINGLETON__
#define __GENIE_SINGLETON__
#include <cassert>

/*
*	using example
*
*	#include "Genie_Singleton.h"
*	class A : public Genie_Singleton<A> {
*	
*	public void ...
*	};
*
*
*	when u use member -> A::Instance()->... 
*	
*	Edit by DongDongJu
*/


template <class T>
class Genie_Singleton
{

private:
	static T* Ginstance;
	Genie_Singleton(Genie_Singleton const);
	Genie_Singleton& operator=(Genie_Singleton const&);

public:
	/*
	*	gflag guaranted unique instance
	*/
	static bool gflag;

	/*
	*	singleton instance constructor
	*	edit by DongDongJu
	*/	
	static T* Instance(){
		if(!Ginstance){
			gflag = true;
			Ginstance = new Genie_Singleton;
		}
		assert(Ginstance !=NULL);
		return Ginstance;
	}

	/*
	*	singleton instance constructor
	*	edit by DongDongJu
	*/	
	static void destroyInstance(){
		if(Ginstance){
			delete Ginstance;
			Ginstance = NULL;
		}
	}

protected:
	Genie_Singleton(){
		assert(!Ginstance);
		assert(gflag);
	};
};

template <class T> T* Genie_Singleton<t>::Ginstance = NULL;
template <class T> bool Genie_Singleton<t>::gflag = false;

#endif


