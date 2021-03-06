/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class pers_di_thsapi_THSApi */

#ifndef _Included_pers_di_thsapi_THSApi
#define _Included_pers_di_thsapi_THSApi
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     pers_di_thsapi_THSApi
 * Method:    initialize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_initialize
  (JNIEnv *, jclass);

/*
 * Class:     pers_di_thsapi_THSApi
 * Method:    getAvailableMoney
 * Signature: (Lpers/di/thsapi/THSApi/ObjectContainer;)I
 */
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_getAvailableMoney
  (JNIEnv *, jclass, jobject);

/*
 * Class:     pers_di_thsapi_THSApi
 * Method:    getTotalAssets
 * Signature: (Lpers/di/thsapi/THSApi/ObjectContainer;)I
 */
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_getTotalAssets
  (JNIEnv *, jclass, jobject);

/*
 * Class:     pers_di_thsapi_THSApi
 * Method:    getAllStockMarketValue
 * Signature: (Lpers/di/thsapi/THSApi/ObjectContainer;)I
 */
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_getAllStockMarketValue
  (JNIEnv *, jclass, jobject);

/*
 * Class:     pers_di_thsapi_THSApi
 * Method:    getHoldStockList
 * Signature: (Ljava/util/List;)I
 */
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_getHoldStockList
  (JNIEnv *, jclass, jobject);

/*
 * Class:     pers_di_thsapi_THSApi
 * Method:    getCommissionOrderList
 * Signature: (Ljava/util/List;)I
 */
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_getCommissionOrderList
  (JNIEnv *, jclass, jobject);

/*
 * Class:     pers_di_thsapi_THSApi
 * Method:    getDealOrderList
 * Signature: (Ljava/util/List;)I
 */
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_getDealOrderList
  (JNIEnv *, jclass, jobject);

/*
 * Class:     pers_di_thsapi_THSApi
 * Method:    buyStock
 * Signature: (Ljava/lang/String;IF)I
 */
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_buyStock
  (JNIEnv *, jclass, jstring, jint, jfloat);

/*
 * Class:     pers_di_thsapi_THSApi
 * Method:    sellStock
 * Signature: (Ljava/lang/String;IF)I
 */
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_sellStock
  (JNIEnv *, jclass, jstring, jint, jfloat);

#ifdef __cplusplus
}
#endif
#endif
