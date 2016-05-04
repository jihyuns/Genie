#include "../header/Genie_Emotion.h"
using namespace std;
/*
	edit by DongDongJu
	emotion detector for realsense r200
*/
Genie_Emotion::~Genie_Emotion()
{
	if (senseManager != 0){
		senseManager->Release();
	}
}

void Genie_Emotion::initilize()
{
	senseManager = PXCSenseManager::CreateInstance();
	if (senseManager == 0) {
		throw std::runtime_error("1\n");
	}
	resetNums();
	initilizeFace();
}

void Genie_Emotion::initilizeFace(){
	auto sts = senseManager->EnableFace();
	if (sts<PXC_STATUS_NO_ERROR) {
		throw std::runtime_error("2\n");
	}
	sts = senseManager->EnableEmotion();
	PXCFaceModule* faceModule = senseManager->QueryFace();
	if (faceModule == 0) {
		throw std::runtime_error("3\n");
	}
	PXCFaceConfiguration* config = faceModule->CreateActiveConfiguration();
	if (config == 0) {
		throw std::runtime_error("4\n");
	}

	config->SetTrackingMode(PXCFaceConfiguration::TrackingModeType::FACE_MODE_COLOR);
	sts = senseManager->Init();
	if (sts<PXC_STATUS_NO_ERROR) {
		throw std::runtime_error("5\n");
	}
	auto device = senseManager->QueryCaptureManager()->QueryDevice();
	if (device == 0) {
		throw std::runtime_error("6\n");
	}
	device->SetMirrorMode(PXCCapture::Device::MirrorMode::MIRROR_MODE_HORIZONTAL);
	PXCCapture::DeviceInfo deviceInfo;
	device->QueryDeviceInfo(&deviceInfo);
	if (deviceInfo.model == PXCCapture::DEVICE_MODEL_IVCAM) {
		device->SetDepthConfidenceThreshold(1);
		device->SetIVCAMFilterOption(6);
		device->SetIVCAMMotionRangeTradeOff(21);
	}

	config->detection.isEnabled = true;
	config->QueryExpressions()->Enable();
	config->QueryExpressions()->EnableAllExpressions();
	config->QueryExpressions()->properties.maxTrackedFaces = 2;
	config->ApplyChanges();

	faceData = faceModule->CreateOutput();

}
int* Genie_Emotion::getEmotionData()
{
	int i = 0;
	int* result = NULL;

	for (i = 0; i<FRAME_FOR_CHECK_EMOTIONS; i++)
		updateFrame(&Genie_Emotion::updateFaceFrame);

	result = getResult();

	if (result != NULL)
		return result;
	else
		throw std::runtime_error("getResult error!");
}

void Genie_Emotion::updateFrame(func fp)
{
	int i = 0;
	pxcStatus sts = senseManager->AcquireFrame(true);
	if (sts < PXC_STATUS_NO_ERROR) {
		return;
	}
	(this->*fp)();
	senseManager->ReleaseFrame();
}
void Genie_Emotion::updateFaceFrameFN()
{
	const PXCCapture::Sample *sample = senseManager->QuerySample();
	if (sample) {
		updateColorImage(sample->color);
	}
	PXCEmotion::EmotionData arrData[NUM_TOTAL_EMOTIONS];
	emotionDet = senseManager->QueryEmotion();
	if (emotionDet == 0) {
		throw std::runtime_error("7");
		return;
	}
	faceData->Update();
	const int numFaces = faceData->QueryNumberOfDetectedFaces();
	faceNum = numFaces;
}
void Genie_Emotion::updateFaceFrame(){
	const PXCCapture::Sample *sample = senseManager->QuerySample();
	if (sample) {
		updateColorImage(sample->color);
	}
	PXCEmotion::EmotionData arrData[NUM_TOTAL_EMOTIONS];
	emotionDet = senseManager->QueryEmotion();
	if (emotionDet == 0) {
		throw std::runtime_error("7");
		return;
	}
	const char *EmotionLabels[NUM_PRIMARY_EMOTIONS] = {
		"ANGER",
		"CONTEMPT",
		"DISGUST",
		"FEAR",
		"JOY",
		"SADNESS",
		"SURPRISE"
	};
	const char *SentimentLabels[NUM_SENTIMENT_EMOTIONS] = {
		"NEGATIVE",
		"POSITIVE",
		"NEUTRAL"
	};

	faceData->Update();
	const int numFaces = faceData->QueryNumberOfDetectedFaces();
	// 사람이 몇명인지 확인

	//사람 숫자만큼 , face가 없을 경우 확인하지 않음
	for (int i = 0; i < numFaces; ++i) {
		auto face = faceData->QueryFaceByIndex(i);
		if (face == 0){
			continue;
		}

		PXCRectI32 faceRect = { 0 };
		PXCFaceData::PoseEulerAngles poseAngle = { 0 };
		PXCFaceData::ExpressionsData *expressionData;
		PXCFaceData::ExpressionsData::FaceExpressionResult expressionResult;

		auto detection = face->QueryDetection();
		if (detection != 0){
			detection->QueryBoundingRect(&faceRect);
		}

		// 표정 데이터 요청
		expressionData = face->QueryExpressions();
		if (expressionData != NULL)
		{
			if (expressionData->QueryExpression(PXCFaceData::ExpressionsData::EXPRESSION_MOUTH_OPEN, &expressionResult)){
				{
					if (expressionResult.intensity >= 70)
						numOfExpressions[0]++;
				}
			}
			if (expressionData->QueryExpression(PXCFaceData::ExpressionsData::EXPRESSION_TONGUE_OUT, &expressionResult)){
				{
					if (expressionResult.intensity >= 70)
						numOfExpressions[1]++;
				}
			}
			if (expressionData->QueryExpression(PXCFaceData::ExpressionsData::EXPRESSION_SMILE, &expressionResult)){
				{
					if (expressionResult.intensity >= 70)
						numOfExpressions[2]++;
				}
			}

		}
		emotionDet->QueryAllEmotionData(i, &arrData[0]);
		int idx_outstanding_emotion = -1;
		bool IsSentimentPresent = false;
		pxcI32 maxscoreE = -3; pxcF32 maxscoreI = 0;
		for (int i = 0; i<NUM_PRIMARY_EMOTIONS; i++) {
			if (arrData[i].evidence < maxscoreE)  continue;
			if (arrData[i].intensity < maxscoreI) continue;
			maxscoreE = arrData[i].evidence;
			maxscoreI = arrData[i].intensity;
			idx_outstanding_emotion = i;
		}
		if (idx_outstanding_emotion != -1) {
			{
				numOfPrimary[idx_outstanding_emotion]++;
			}
		}
		if (maxscoreI > 0.4){
			IsSentimentPresent = true;
		}
		if (IsSentimentPresent){
			int idx_sentiment_emotion = -1;
			maxscoreE = -3; maxscoreI = 0;
			for (int i = 0; i<(10 - NUM_PRIMARY_EMOTIONS); i++) {
				if (arrData[NUM_PRIMARY_EMOTIONS + i].evidence  < maxscoreE) continue;
				if (arrData[NUM_PRIMARY_EMOTIONS + i].intensity < maxscoreI) continue;
				maxscoreE = arrData[NUM_PRIMARY_EMOTIONS + i].evidence;
				maxscoreI = arrData[NUM_PRIMARY_EMOTIONS + i].intensity;
				idx_sentiment_emotion = i;
			}
			if (idx_sentiment_emotion != -1){
				{
					numOfSentimental[idx_outstanding_emotion]++;
				}
			}
		}


	}
}
void Genie_Emotion::updateColorImage(PXCImage* colorFrame)
{
	if (colorFrame == 0){
		return;
	}

	PXCImage::ImageInfo info = colorFrame->QueryInfo();
	PXCImage::ImageData data;
	pxcStatus sts = colorFrame->AcquireAccess(PXCImage::Access::ACCESS_READ, PXCImage::PixelFormat::PIXEL_FORMAT_RGB24, &data);
	if (sts < PXC_STATUS_NO_ERROR) {
		throw std::runtime_error("8\n");
	}
	colorFrame->ReleaseAccess(&data);
}
void Genie_Emotion::resetNums()
{
	int i = 0;
	for (i = 0; i < NUM_PRIMARY_EMOTIONS; i++)
		numOfPrimary[i] = 0;
	for (i = 0; i < NUM_SENTIMENT_EMOTIONS; i++)
		numOfSentimental[i] = 0;
	for (i = 0; i < 3; i++)
		numOfExpressions[i] = 0;
}
void Genie_Emotion::printNums() // for test
{
	const char *EmotionLabels[NUM_PRIMARY_EMOTIONS] = {
		"ANGER",
		"CONTEMPT",
		"DISGUST",
		"FEAR",
		"JOY",
		"SADNESS",
		"SURPRISE"
	};
	const char *SentimentLabels[NUM_SENTIMENT_EMOTIONS] = {
		"NEGATIVE",
		"POSITIVE",
		"NEUTRAL"
	};
	const char *ExpressionLabels[3] = {
		"MOUTHOPEN",
		"TONGUEOUT",
		"SMILE"
	};
	int i = 0;
	for (i = 0; i < NUM_PRIMARY_EMOTIONS; i++)
		printf("%s %d\n",EmotionLabels[i], numOfPrimary[i]);
	for (i = 0; i < NUM_SENTIMENT_EMOTIONS; i++)
		printf("%s %d\n",SentimentLabels[i], numOfSentimental[i]);
	for (i = 0; i < 3; i++)
		printf("%s %d\n",ExpressionLabels[i], numOfExpressions[i]);
}

int  Genie_Emotion::getFaceNum()
{
	int i = 0;
	faceNum = 0;

	for (i = 0; i <FRAME_FOR_CHECK_FACE_EXIST; i++){
		if (faceNum != 0)
			return 1;
		updateFrame(&Genie_Emotion::updateFaceFrameFN);
	}
	return 0;
}

int* Genie_Emotion::getResult()
{
	int i = 0;
	for (i = 0; i < 7; i++)
		resultData[i] = numOfPrimary[i];
	for (i = 0; i < 3; i++)
		resultData[7 + i] = numOfSentimental[i];
	for (i = 0; i < 3; i++)
		resultData[10 + i] = numOfExpressions[i];
	return resultData;
}