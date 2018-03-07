#include "stdafx.h"

#include "pers_di_thsapi_THSApi.h"

#include "../TongHuaShun.h"
#include <string>
using namespace std;

static string jstringTostring(JNIEnv* env, jstring jstr)
{
	string rtnString;
	char* rtn = NULL;
	jclass clsstring = env->FindClass("java/lang/String");
	jstring strencode = env->NewStringUTF("utf-8");
	jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
	jsize alen = env->GetArrayLength(barr);
	jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
	if (alen > 0)
	{
		rtn = new char[alen + 1];
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
		rtnString = string(rtn);
		delete [] rtn;
		rtn = NULL;
	}
	env->ReleaseByteArrayElements(barr, ba, 0);

	return rtnString;
}

static jobject floatTojobject(JNIEnv* env, float value)
{
	// create float obj
	jclass jcls_Float = env->FindClass("Ljava/lang/Float;");
	if (NULL == jcls_Float)
	{
		TESTLOG("   floatTojobject jcls_Float ERROR\n");
		return NULL;
	}
	jmethodID mid_Float_init = env->GetMethodID(jcls_Float, "<init>", "(F)V");
	if (NULL == mid_Float_init)
	{
		TESTLOG("   floatTojobject mid_Float_init ERROR\n");
		return NULL;
	}
	jobject jobj_Float = env->NewObject(jcls_Float, mid_Float_init, value);
	if (NULL == jobj_Float)
	{
		TESTLOG("   floatTojobject jobj_Float ERROR\n");
		return NULL;
	}
	return jobj_Float;
}

/*
* Class:     pers_di_thsapi_THSApi
* Method:    initialize
* Signature: ()I
*/
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_initialize
(JNIEnv *, jclass)
{
	//DFileLog::GetInstance()->Clear();
	//DFileLog::GetInstance()->EnableSaveLog(true);

	int err = 0;
	err = THSAPI_TongHuaShunInit();
	return err;
}


/*
* Class:     pers_di_thsapi_THSApi
* Method:    getAvailableMoney
* Signature: (Lpers/di/thsapi/THSApi/ObjectContainer;)I
*/
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_getAvailableMoney
(JNIEnv * env, jclass cls, jobject obj)
{
	TESTLOG("Java_pers_di_thsapi_THSApi_getAvailableMoney\n");

	if (NULL == obj)
	{
		return -1;
	}

	int err = 0;
	float availableMoney = 0.0f;
	// frequency limit
	{
		static int s_lastErr = 0;
		static float s_lastData = 0.0f;
		static DWORD s_dwLastCall = 0;
		DWORD dwCurTC = ::GetTickCount();
		DWORD dwPeriod = dwCurTC - s_dwLastCall;
		if (dwPeriod > 1000*10)
		{
			s_lastErr = THSAPI_GetAvailableMoney(s_lastData);
			s_dwLastCall = dwCurTC;
		}
		err = s_lastErr;
		availableMoney = s_lastData;
	}
	TESTLOG("   THSAPI_GetAvailableMoney err(%d) AvailableMoney(%f)\n",err,availableMoney);

	jclass cls_obj = env->GetObjectClass(obj);
	jmethodID mid_set = env->GetMethodID(cls_obj,"set","(Ljava/lang/Object;)V");

	jobject jobj_Float = floatTojobject(env, availableMoney);
	if (NULL == jobj_Float)
	{
		return -2;
	}

	// set obj
	env->CallVoidMethod(obj, mid_set, jobj_Float);

	return 0;
}

/*
* Class:     pers_di_thsapi_THSApi
* Method:    getTotalAssets
* Signature: (Lpers/di/thsapi/THSApi/ObjectContainer;)I
*/
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_getTotalAssets
(JNIEnv * env, jclass cls, jobject obj)
{
	TESTLOG("Java_pers_di_thsapi_THSApi_getTotalAssets\n");

	if (NULL == obj)
	{
		return -1;
	}

	int err = 0;
	float totalAssets = 0.0f;
	// frequency limit
	{
		static int s_lastErr = 0;
		static float s_lastData = 0.0f;
		static DWORD s_dwLastCall = 0;
		DWORD dwCurTC = ::GetTickCount();
		DWORD dwPeriod = dwCurTC - s_dwLastCall;
		if (dwPeriod > 1000*10)
		{
			s_lastErr = THSAPI_GetTotalAssets(s_lastData);
			s_dwLastCall = dwCurTC;
		}
		err = s_lastErr;
		totalAssets = s_lastData;
	}
	TESTLOG("   THSAPI_GetTotalAssets err(%d) TotalAssets(%f)\n",err,totalAssets);

	jclass cls_obj = env->GetObjectClass(obj);
	jmethodID mid_set = env->GetMethodID(cls_obj,"set","(Ljava/lang/Object;)V");

	jobject jobj_Float = floatTojobject(env, totalAssets);
	if (NULL == jobj_Float)
	{
		return -2;
	}

	// set obj
	env->CallVoidMethod(obj, mid_set, jobj_Float);

	return 0;
}

/*
* Class:     pers_di_thsapi_THSApi
* Method:    getAllStockMarketValue
* Signature: (Lpers/di/thsapi/THSApi/ObjectContainer;)I
*/
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_getAllStockMarketValue
(JNIEnv * env, jclass cls, jobject obj)
{
	TESTLOG("Java_pers_di_thsapi_THSApi_getAllStockMarketValue\n");

	if (NULL == obj)
	{
		return -1;
	}

	int err = 0;
	float allStockMarketValue = 0.0f;
	// frequency limit
	{
		static int s_lastErr = 0;
		static float s_lastData = 0.0f;
		static DWORD s_dwLastCall = 0;
		DWORD dwCurTC = ::GetTickCount();
		DWORD dwPeriod = dwCurTC - s_dwLastCall;
		if (dwPeriod > 1000*10)
		{
			s_lastErr = THSAPI_GetAllStockMarketValue(s_lastData);
			s_dwLastCall = dwCurTC;
		}
		err = s_lastErr;
		allStockMarketValue = s_lastData;
	}
	TESTLOG("   THSAPI_GetAllStockMarketValue err(%d) AllStockMarketValue(%f)\n",err,allStockMarketValue);

	jclass cls_obj = env->GetObjectClass(obj);
	jmethodID mid_set = env->GetMethodID(cls_obj,"set","(Ljava/lang/Object;)V");

	jobject jobj_Float = floatTojobject(env, allStockMarketValue);
	if (NULL == jobj_Float)
	{
		return -2;
	}

	// set obj
	env->CallVoidMethod(obj, mid_set, jobj_Float);

	return 0;
}

/*
* Class:     pers_di_thsapi_THSApi
* Method:    getHoldStockList
* Signature: (Ljava/util/List;)I
*/
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_getHoldStockList
(JNIEnv * env, jclass cls, jobject obj)
{
	TESTLOG("Java_pers_di_thsapi_THSApi_getHoldStockList\n");

	if (NULL == obj)
	{
		return -1;
	}

	int err = 0;
	std::list<HoldStock> cResultList;
	// frequency limit
	{
		static int s_lastErr = 0;
		static std::list<HoldStock> s_lastData;
		static DWORD s_dwLastCall = 0;
		DWORD dwCurTC = ::GetTickCount();
		DWORD dwPeriod = dwCurTC - s_dwLastCall;
		if (dwPeriod > 1000*10)
		{
			s_lastErr = THSAPI_GetHoldStockList(s_lastData);
			s_dwLastCall = dwCurTC;
		}
		err = s_lastErr;
		cResultList = s_lastData;
	}
	TESTLOG("   THSAPI_GetHoldStockList err(%d) cResultList size(%d)\n",err,cResultList.size());

	jclass jcls_ArrayList = env->GetObjectClass(obj);
	if (NULL == jcls_ArrayList)
	{
		TESTLOG("   jcls_ArrayList ERROR\n");
	}
	jmethodID mid_ArrayList_add = env->GetMethodID(jcls_ArrayList, "add", "(Ljava/lang/Object;)Z");
	if (NULL == mid_ArrayList_add)
	{
		TESTLOG("   mid_ArrayList_add ERROR\n");
	}

	jclass jcls_HoldStock = env->FindClass("pers/di/thsapi/THSApi$HoldStock");
	if (NULL == jcls_HoldStock)
	{
		TESTLOG("   jcls_HoldStock ERROR\n");
	}
	jmethodID mid_HoldStock_init = env->GetMethodID(jcls_HoldStock, "<init>", "()V");
	if (NULL == mid_HoldStock_init)
	{
		TESTLOG("   mid_HoldStock_init ERROR\n");
	}

	std::list<HoldStock>::iterator it;
	for (it = cResultList.begin(); it != cResultList.end(); it++)
	{
		HoldStock cHoldStock = *it;
		jobject jobj_HoldStock = env->NewObject(jcls_HoldStock, mid_HoldStock_init);
		if (NULL == jobj_HoldStock)
		{
			TESTLOG("   jobj_HoldStock ERROR\n");
		}

		jfieldID fid_stockID = env->GetFieldID(jcls_HoldStock, "stockID", "Ljava/lang/String;");
		if (NULL == fid_stockID)
		{
			TESTLOG("   fid_stockID ERROR\n");
		}
		jstring jstr_stockID = env->NewStringUTF(cHoldStock.stockID.c_str());
		env->SetObjectField(jobj_HoldStock, fid_stockID, jstr_stockID);

		jfieldID fid_totalAmount = env->GetFieldID(jcls_HoldStock, "totalAmount", "I");
		if (NULL == fid_totalAmount)
		{
			TESTLOG("   fid_totalAmount ERROR\n");
		}
		jint jint_totalAmount = cHoldStock.totalAmount;
		env->SetIntField(jobj_HoldStock, fid_totalAmount, jint_totalAmount);

		jfieldID fid_availableAmount = env->GetFieldID(jcls_HoldStock, "availableAmount", "I");
		if (NULL == fid_availableAmount)
		{
			TESTLOG("   fid_availableAmount ERROR\n");
		}
		jint jint_availableAmount = cHoldStock.availableAmount;
		env->SetIntField(jobj_HoldStock, fid_availableAmount, jint_availableAmount);

		jfieldID fid_refProfitLoss = env->GetFieldID(jcls_HoldStock, "refProfitLoss", "F");
		if (NULL == fid_refProfitLoss)
		{
			TESTLOG("   fid_refProfitLoss ERROR\n");
		}
		jfloat jfloat_refProfitLoss = cHoldStock.refProfitLoss;
		env->SetFloatField(jobj_HoldStock, fid_refProfitLoss, jfloat_refProfitLoss);

		jfieldID fid_refPrimeCostPrice = env->GetFieldID(jcls_HoldStock, "refPrimeCostPrice", "F");
		if (NULL == fid_refPrimeCostPrice)
		{
			TESTLOG("   fid_refPrimeCostPrice ERROR\n");
		}
		jfloat jfloat_refPrimeCostPrice = cHoldStock.refPrimeCostPrice;
		env->SetFloatField(jobj_HoldStock, fid_refPrimeCostPrice, jfloat_refPrimeCostPrice);

		jfieldID fid_curPrice = env->GetFieldID(jcls_HoldStock, "curPrice", "F");
		if (NULL == fid_curPrice)
		{
			TESTLOG("   fid_curPrice ERROR\n");
		}
		jfloat jfloat_curPrice = cHoldStock.curPrice;
		env->SetFloatField(jobj_HoldStock, fid_curPrice, jfloat_curPrice);

		env->CallBooleanMethod(obj, mid_ArrayList_add, jobj_HoldStock);
	}

	return 0;
}

/*
* Class:     pers_di_thsapi_THSApi
* Method:    getCommissionOrderList
* Signature: (Ljava/util/List;)I
*/
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_getCommissionOrderList
(JNIEnv * env, jclass cls, jobject obj)
{
	TESTLOG("Java_pers_di_thsapi_THSApi_getCommissionOrderList\n");

	if (NULL == obj)
	{
		return -1;
	}

	int err = 0;
	std::list<CommissionOrder> cResultList;
	// frequency limit
	{
		static int s_lastErr = 0;
		static std::list<CommissionOrder> s_lastData;
		static DWORD s_dwLastCall = 0;
		DWORD dwCurTC = ::GetTickCount();
		DWORD dwPeriod = dwCurTC - s_dwLastCall;
		if (dwPeriod > 1000*10)
		{
			s_lastErr = THSAPI_GetCommissionOrderList(s_lastData);
			s_dwLastCall = dwCurTC;
		}
		err = s_lastErr;
		cResultList = s_lastData;
	}
	TESTLOG("   THSAPI_GetCommissionOrderList err(%d) cResultList size(%d)\n",err,cResultList.size());

	jclass jcls_ArrayList = env->GetObjectClass(obj);
	if (NULL == jcls_ArrayList)
	{
		TESTLOG("   jcls_ArrayList ERROR\n");
	}
	jmethodID mid_ArrayList_add = env->GetMethodID(jcls_ArrayList, "add", "(Ljava/lang/Object;)Z");
	if (NULL == mid_ArrayList_add)
	{
		TESTLOG("   mid_ArrayList_add ERROR\n");
	}

	jclass jcls_CommissionOrder = env->FindClass("pers/di/thsapi/THSApi$CommissionOrder");
	if (NULL == jcls_CommissionOrder)
	{
		TESTLOG("   jcls_CommissionOrder ERROR\n");
	}
	jmethodID mid_CommissionOrder_init = env->GetMethodID(jcls_CommissionOrder, "<init>", "()V");
	if (NULL == mid_CommissionOrder_init)
	{
		TESTLOG("   mid_HoldStock_init ERROR\n");
	}

	std::list<CommissionOrder>::iterator it;
	for (it = cResultList.begin(); it != cResultList.end(); it++)
	{
		CommissionOrder cCommissionOrder = *it;
		jobject jobj_CommissionOrder = env->NewObject(jcls_CommissionOrder, mid_CommissionOrder_init);
		if (NULL == jobj_CommissionOrder)
		{
			TESTLOG("   jobj_CommissionOrder ERROR\n");
		}

		jfieldID fid_time = env->GetFieldID(jcls_CommissionOrder, "time", "Ljava/lang/String;");
		if (NULL == fid_time)
		{
			TESTLOG("   fid_time ERROR\n");
		}
		jstring jstr_time = env->NewStringUTF(cCommissionOrder.time.c_str());
		env->SetObjectField(jobj_CommissionOrder, fid_time, jstr_time);

		jfieldID fid_stockID = env->GetFieldID(jcls_CommissionOrder, "stockID", "Ljava/lang/String;");
		if (NULL == fid_stockID)
		{
			TESTLOG("   fid_stockID ERROR\n");
		}
		jstring jstr_stockID = env->NewStringUTF(cCommissionOrder.stockID.c_str());
		env->SetObjectField(jobj_CommissionOrder, fid_stockID, jstr_stockID);

		jfieldID fid_tranAct = env->GetFieldID(jcls_CommissionOrder, "tranAct", "Lpers/di/thsapi/THSApi$TRANACT;");
		if (NULL == fid_tranAct)
		{
			TESTLOG("   fid_tranAct ERROR\n");
		}
		jclass jcls_TRANACT = env->FindClass("pers/di/thsapi/THSApi$TRANACT");
		jfieldID fid_BUY    = env->GetStaticFieldID(jcls_TRANACT, "BUY", "Lpers/di/thsapi/THSApi$TRANACT;");
		jfieldID fid_SELL   = env->GetStaticFieldID(jcls_TRANACT, "SELL", "Lpers/di/thsapi/THSApi$TRANACT;");
		jobject jobj_TranAct = env->GetStaticObjectField(jcls_TRANACT, fid_BUY);
		if (TRANACT_SELL == cCommissionOrder.tranAct)
		{
			jobj_TranAct = env->GetStaticObjectField(jcls_TRANACT, fid_SELL);
		} 
		env->SetObjectField(jobj_CommissionOrder, fid_tranAct, jobj_TranAct);

		jfieldID fid_commissionAmount = env->GetFieldID(jcls_CommissionOrder, "commissionAmount", "I");
		if (NULL == fid_commissionAmount)
		{
			TESTLOG("   fid_commissionAmount ERROR\n");
		}
		jint jint_fid_commissionAmount = cCommissionOrder.commissionAmount;
		env->SetIntField(jobj_CommissionOrder, fid_commissionAmount, jint_fid_commissionAmount);

		jfieldID fid_commissionPrice = env->GetFieldID(jcls_CommissionOrder, "commissionPrice", "F");
		if (NULL == fid_commissionPrice)
		{
			TESTLOG("   fid_commissionPrice ERROR\n");
		}
		jfloat jfloat_commissionPrice = cCommissionOrder.commissionPrice;
		env->SetFloatField(jobj_CommissionOrder, fid_commissionPrice, jfloat_commissionPrice);

		jfieldID fid_dealAmount = env->GetFieldID(jcls_CommissionOrder, "dealAmount", "I");
		if (NULL == fid_dealAmount)
		{
			TESTLOG("   fid_dealAmount ERROR\n");
		}
		jint jint_fid_dealAmount = cCommissionOrder.dealAmount;
		env->SetIntField(jobj_CommissionOrder, fid_dealAmount, jint_fid_dealAmount);

		jfieldID fid_dealPrice = env->GetFieldID(jcls_CommissionOrder, "dealPrice", "F");
		if (NULL == fid_dealPrice)
		{
			TESTLOG("   fid_dealPrice ERROR\n");
		}
		jfloat jfloat_dealPrice = cCommissionOrder.dealPrice;
		env->SetFloatField(jobj_CommissionOrder, fid_dealPrice, jfloat_dealPrice);

		env->CallBooleanMethod(obj, mid_ArrayList_add, jobj_CommissionOrder);
	}

	return 0;
}

/*
* Class:     pers_di_thsapi_THSApi
* Method:    getDealOrderList
* Signature: (Ljava/util/List;)I
*/
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_getDealOrderList
(JNIEnv * env, jclass cls, jobject obj)
{
	TESTLOG("Java_pers_di_thsapi_THSApi_getDealOrderList\n");

	if (NULL == obj)
	{
		return -1;
	}

	int err = 0;
	std::list<DealOrder> cResultList;
	// frequency limit
	{
		static int s_lastErr = 0;
		static std::list<DealOrder> s_lastData;
		static DWORD s_dwLastCall = 0;
		DWORD dwCurTC = ::GetTickCount();
		DWORD dwPeriod = dwCurTC - s_dwLastCall;
		if (dwPeriod > 1000*10)
		{
			s_lastErr = THSAPI_GetDealOrderList(s_lastData);
			s_dwLastCall = dwCurTC;
		}
		err = s_lastErr;
		cResultList = s_lastData;
	}
	TESTLOG("   THSAPI_GetDealOrderList err(%d) cResultList size(%d)\n",err,cResultList.size());

	jclass jcls_ArrayList = env->GetObjectClass(obj);
	if (NULL == jcls_ArrayList)
	{
		TESTLOG("   jcls_ArrayList ERROR\n");
	}
	jmethodID mid_ArrayList_add = env->GetMethodID(jcls_ArrayList, "add", "(Ljava/lang/Object;)Z");
	if (NULL == mid_ArrayList_add)
	{
		TESTLOG("   mid_ArrayList_add ERROR\n");
	}

	jclass jcls_DealOrder = env->FindClass("pers/di/thsapi/THSApi$DealOrder");
	if (NULL == jcls_DealOrder)
	{
		TESTLOG("   jcls_DealOrder ERROR\n");
	}
	jmethodID mid_DealOrder_init = env->GetMethodID(jcls_DealOrder, "<init>", "()V");
	if (NULL == mid_DealOrder_init)
	{
		TESTLOG("   mid_DealOrder_init ERROR\n");
	}

	std::list<DealOrder>::iterator it;
	for (it = cResultList.begin(); it != cResultList.end(); it++)
	{
		DealOrder cDealOrder = *it;
		jobject jobj_DealOrder = env->NewObject(jcls_DealOrder, mid_DealOrder_init);
		if (NULL == jobj_DealOrder)
		{
			TESTLOG("   jobj_DealOrder ERROR\n");
		}

		jfieldID fid_time = env->GetFieldID(jcls_DealOrder, "time", "Ljava/lang/String;");
		if (NULL == fid_time)
		{
			TESTLOG("   fid_time ERROR\n");
		}
		jstring jstr_time = env->NewStringUTF(cDealOrder.time.c_str());
		env->SetObjectField(jobj_DealOrder, fid_time, jstr_time);

		jfieldID fid_stockID = env->GetFieldID(jcls_DealOrder, "stockID", "Ljava/lang/String;");
		if (NULL == fid_stockID)
		{
			TESTLOG("   fid_stockID ERROR\n");
		}
		jstring jstr_stockID = env->NewStringUTF(cDealOrder.stockID.c_str());
		env->SetObjectField(jobj_DealOrder, fid_stockID, jstr_stockID);

		jfieldID fid_tranAct = env->GetFieldID(jcls_DealOrder, "tranAct", "Lpers/di/thsapi/THSApi$TRANACT;");
		if (NULL == fid_tranAct)
		{
			TESTLOG("   fid_tranAct ERROR\n");
		}
		jclass jcls_TRANACT = env->FindClass("pers/di/thsapi/THSApi$TRANACT");
		jfieldID fid_BUY    = env->GetStaticFieldID(jcls_TRANACT, "BUY", "Lpers/di/thsapi/THSApi$TRANACT;");
		jfieldID fid_SELL   = env->GetStaticFieldID(jcls_TRANACT, "SELL", "Lpers/di/thsapi/THSApi$TRANACT;");
		jobject jobj_TranAct = env->GetStaticObjectField(jcls_TRANACT, fid_BUY);
		if (TRANACT_SELL == cDealOrder.tranAct)
		{
			jobj_TranAct = env->GetStaticObjectField(jcls_TRANACT, fid_SELL);
		} 
		env->SetObjectField(jobj_DealOrder, fid_tranAct, jobj_TranAct);

		jfieldID fid_dealAmount = env->GetFieldID(jcls_DealOrder, "dealAmount", "I");
		if (NULL == fid_dealAmount)
		{
			TESTLOG("   fid_dealAmount ERROR\n");
		}
		jint jint_fid_dealAmount = cDealOrder.dealAmount;
		env->SetIntField(jobj_DealOrder, fid_dealAmount, jint_fid_dealAmount);

		jfieldID fid_dealPrice = env->GetFieldID(jcls_DealOrder, "dealPrice", "F");
		if (NULL == fid_dealPrice)
		{
			TESTLOG("   fid_dealPrice ERROR\n");
		}
		jfloat jfloat_dealPrice = cDealOrder.dealPrice;
		env->SetFloatField(jobj_DealOrder, fid_dealPrice, jfloat_dealPrice);

		env->CallBooleanMethod(obj, mid_ArrayList_add, jobj_DealOrder);
	}
	return 0;
}

/*
* Class:     pers_di_thsapi_THSApi
* Method:    buyStock
* Signature: (Ljava/lang/String;IF)I
*/
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_buyStock
(JNIEnv * env, jclass, jstring stockId, jint amount, jfloat price)
{
	int rtn = 0;
	string sStockId = jstringTostring(env, stockId);
	int iBuyAmount = amount;
	float fPrice = price;
	rtn = THSAPI_BuyStock(sStockId.c_str(), iBuyAmount, fPrice);
	return rtn;
}

/*
* Class:     pers_di_thsapi_THSApi
* Method:    sellStock
* Signature: (Ljava/lang/String;IF)I
*/
JNIEXPORT jint JNICALL Java_pers_di_thsapi_THSApi_sellStock
(JNIEnv * env, jclass, jstring stockId, jint amount, jfloat price)
{
	int rtn = 0;
	string sStockId = jstringTostring(env, stockId);
	int iSellAmount = amount;
	float fPrice = price;
	rtn = THSAPI_SellStock(sStockId.c_str(), iSellAmount, fPrice);
	return rtn;
}