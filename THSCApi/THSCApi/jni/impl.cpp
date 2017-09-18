#include "stdafx.h"

#include "pers_di_thsapi_THSApi.h"

#include "../TongHuaShun.h"
#include <string>
using namespace std;

/*
* Class:     pers_di_thsapi_THSApi
* Method:    initialize
* Signature: ()I
*/
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_initialize
(JNIEnv *, jclass)
{
	return 1;
}

/*
* Class:     pers_di_thsapi_THSApi
* Method:    getAvailableMoney
* Signature: (Lpers/di/thsapi/THSApi/ObjectContainer;)I
*/
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_getAvailableMoney
(JNIEnv *, jclass, jobject)
{
	return 1;
}

/*
* Class:     pers_di_thsapi_THSApi
* Method:    getTotalAssets
* Signature: (Lpers/di/thsapi/THSApi/ObjectContainer;)I
*/
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_getTotalAssets
(JNIEnv *, jclass, jobject)
{
	return 1;
}

/*
* Class:     pers_di_thsapi_THSApi
* Method:    getAllStockMarketValue
* Signature: (Lpers/di/thsapi/THSApi/ObjectContainer;)I
*/
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_getAllStockMarketValue
(JNIEnv *, jclass, jobject)
{
	return 1;
}

/*
* Class:     pers_di_thsapi_THSApi
* Method:    getHoldStockList
* Signature: (Ljava/util/List;)I
*/
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_getHoldStockList
(JNIEnv *, jclass, jobject)
{
	return 1;
}

/*
* Class:     pers_di_thsapi_THSApi
* Method:    buyStock
* Signature: (Ljava/lang/String;IF)I
*/
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_buyStock
(JNIEnv *, jclass, jstring, jint, jfloat)
{
	return 1;
}

/*
* Class:     pers_di_thsapi_THSApi
* Method:    sellStock
* Signature: (Ljava/lang/String;IF)I
*/
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_sellStock
(JNIEnv *, jclass, jstring, jint, jfloat)
{
	return 1;
}