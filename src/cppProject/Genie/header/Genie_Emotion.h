#ifndef __GENIE_EMOTION__
#define __GENIE_EMOTION__
#include <sstream>

#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#include "pxcsensemanager.h"
#include "PXCFaceConfiguration.h"

#include <opencv2\opencv.hpp>

class Genie_Emotion
{
public:
	~Genie_Emotion();
	void initilize();
	void initilizeFace();
	int* getEmotionData();
private:

	void updateFrame();
	void updateFaceFrame();
	void updateColorImage(PXCImage* colorFrame);
	void resetNums();
	int* getResult();
private:
	PXCSenseManager* senseManager = 0;
	PXCFaceData* faceData = 0;
	PXCEmotion* emotionDet = 0;

	const int COLOR_WIDTH = 640;
	const int COLOR_HEIGHT = 480;
	const int COLOR_FPS = 60;

	static const int NUM_TOTAL_EMOTIONS = 10;
	static const int NUM_PRIMARY_EMOTIONS = 7;
	static const int NUM_SENTIMENT_EMOTIONS = 3;
	static const int FRAME_FOR_CHECK_EMOTIONS = 40;

	int numOfPrimary[7];
	int numOfSentimental[3];
	int numOfExpressions[3];

	int resultData[13];

};


#endif